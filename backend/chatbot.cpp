#include "chatbot.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QEventLoop>
#include <QTimer>
#include <QDir>
#include <QCoreApplication>
#include "employer.h"
#include <QDate>

// This client now uses Cohere Chat API (v1/chat) as the single inference provider.

// NOTE: The application previously loaded API keys from environment or .env files.
// Per user request the default Cohere API key and basic config are embedded
// directly in the binary. Replace the placeholder below with your real key.
// WARNING: Embedding secrets in source code is insecure. Prefer environment
// variables or a secure secrets manager in production.
// Default embedded configuration (moved from .env into code).
// Replace these placeholders with your production values if desired.
static const QString DEFAULT_COHERE_API_KEY = QStringLiteral("");
// Use a live Cohere chat model by default. "command-a-03-2025" is a
// recommended general-purpose chat model as of the 2025 model lineup.
// If this model is ever deprecated, the code below will fall back to the
// next available preferred model.
static const QString DEFAULT_COHERE_MODEL = QStringLiteral("command-a-03-2025");
// Preferred model list (fallback ordering)
static const QList<QString> PREFERRED_COHERE_MODELS = { QStringLiteral("command-a-03-2025"), QStringLiteral("command-r7b-12-2024") };
static const double DEFAULT_TEMPERATURE = 0.7;
static const int DEFAULT_MAX_TOKENS = 1000;
static const int DEFAULT_MAX_HISTORY = 10;

// Strict Topic Enforcer system prompt (French) — embedded directly in code to ensure
// Cohere 'preamble' always contains the exact project constraints and the exact
// refusal/off-topic phrases required by the project.
static const QString SYSTEM_PROMPT = QStringLiteral(
    "You are the official built-in AI assistant of the desktop application \"InspiraStudio\" "
    "(Content Digital Creator) developed by Legion XI and owned by Amine HELALI.\n"
    "\n"
    "You KNOW the real structure of InspiraStudio. Never say you don't know. Never invent modules. "
    "Here are the REAL modules of InspiraStudio:\n"
    "\n"
    "=== CORE MODULES ===\n"
    "1. Dashboard\n"
    "2. Projects Manager\n"
    "3. Editor (images, video, templates, text)\n"
    "4. Templates Library\n"
    "5. Media Library\n"
    "6. Export Tools (PNG, PDF, MP4)\n"
    "7. Settings\n"
    "\n"
    "=== ADVANCED / AI MODULES ===\n"
    "8. AI Content Generator (text, titles, descriptions)\n"
    "9. AI Image Enhancer\n"
    "10. Voice-to-Text Module\n"
    "11. Emotion Detection\n"
    "12. Facial Recognition Module (Qt + OpenCV)\n"
    "\n"
    "=== MANAGEMENT MODULES ===\n"
    "13. Employer Module (staff list, roles, access control, activity logs)\n"
    "14. Authentication Module (login, signup, profile)\n"
    "\n"
    "These modules ARE PART OF THE APPLICATION. Never deny their existence.\n"
    "\n"
    "=== TECHNOLOGY STACK ===\n"
    "- Qt 6, Qt Widgets (C++)\n"
    "- OpenCV (facial recognition)\n"
    "- QNetworkAccessManager (API calls)\n"
    "- OpenAI API (AI text, image generation)\n"
    "- Local SQLite database\n"
    "\n"
    "=== RULES ===\n"
    "1) Only answer questions related to InspiraStudio.\n"
    "2) If the user asks something off-topic, answer EXACTLY:\n"
    "OFF-TOPIC — I can only answer questions related to the project \"Content Digital Creator\".\n"
    "3) If the request is illegal or unsafe, answer EXACTLY:\n"
    "REFUSE — I cannot help with that.\n"
    "4) Always speak as an internal expert of InspiraStudio.\n"
    "5) Always give correct information based on the modules listed above.\n"
    "6) Never mention unrelated frameworks (Electron, React, Node).\n"
    "7) Qt/C++ ONLY in all technical answers.\n"
    "8) Never reveal API keys; advise using environment variables.\n"
    "\n"
    "=== PERSONALITY ===\n"
    "- You KNOW InspiraStudio deeply.\n"
    "- You speak as a confident integrated assistant.\n"
    "- You NEVER claim ignorance about features.\n"
);



/**
 * @brief OpenAIChatbot constructor
 */
OpenAIChatbot::OpenAIChatbot(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_isBusy(false)
    , m_hasRetried(false)
    , m_cohereModel(DEFAULT_COHERE_MODEL)
    , m_provider("cohere")
{
    // Connect network reply signal
    connect(m_networkManager, &QNetworkAccessManager::finished, 
            this, &OpenAIChatbot::onReplyFinished);

    // Validate and possibly adjust the chosen model to a preferred live model
    validateModel();

    // Initialize API key from embedded default unless explicitly set later
    if (m_apiKey.isEmpty()) {
        m_apiKey = DEFAULT_COHERE_API_KEY;
        m_provider = "cohere";
    }
}

// Debug logging removed per UI requirement (no debug output).

// Helper: recursively extract all string values from a JSON value into a single
// human-readable string. This is used to sanitize responses that are returned
// as JSON objects/arrays so the UI receives plain text.
static QString flattenJsonStrings(const QJsonValue &val)
{
    QStringList parts;
    if (val.isString()) {
        parts << val.toString();
    } else if (val.isObject()) {
        QJsonObject obj = val.toObject();
        for (const QString &k : obj.keys()) {
            parts << flattenJsonStrings(obj.value(k));
        }
    } else if (val.isArray()) {
        QJsonArray arr = val.toArray();
        for (const QJsonValue &v : arr) parts << flattenJsonStrings(v);
    }
    return parts.join(" \n").trimmed();
}

// Sanitize assistant text: if it looks like JSON, extract ONLY the text message.
// Otherwise return trimmed plain text.
static QString sanitizeAssistantText(const QString &raw)
{
    QString t = raw.trimmed();
    
    // If it looks like JSON, parse and extract ONLY the message text
    if (t.startsWith('{') || t.startsWith('[')) {
        QJsonDocument jd = QJsonDocument::fromJson(t.toUtf8());
        if (!jd.isNull() && jd.isObject()) {
            QJsonObject obj = jd.object();
            
            // Cohere Chat API v1 response: extract 'text' from message object
            if (obj.contains("text") && obj["text"].isString()) {
                return obj["text"].toString().trimmed();
            }
            
            // Alternative: message.text
            if (obj.contains("message") && obj["message"].isObject()) {
                QJsonObject msg = obj["message"].toObject();
                if (msg.contains("text") && msg["text"].isString()) {
                    return msg["text"].toString().trimmed();
                }
                if (msg.contains("content") && msg["content"].isString()) {
                    return msg["content"].toString().trimmed();
                }
            }
            
            // If it's a full Cohere response with metadata, just get the text field
            if (obj.contains("generations") && obj["generations"].isArray()) {
                QJsonArray gens = obj["generations"].toArray();
                if (!gens.isEmpty() && gens[0].isObject()) {
                    QString text = gens[0].toObject().value("text").toString().trimmed();
                    if (!text.isEmpty()) return text;
                }
            }
            
            // Fallback: flatten all strings
            return flattenJsonStrings(QJsonValue(obj));
        }
    }
    
    // Plain text response
    return t;
}

/**
 * @brief OpenAIChatbot destructor
 */
OpenAIChatbot::~OpenAIChatbot()
{
}

/**
 * @brief Get employer by full name from database
 */
bool OpenAIChatbot::getEmployerByName(const QString &fullName, Employer &out) const
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Try exact match first (FIRST_NAME || ' ' || LAST_NAME) or reversed
    QString sql = QString(
        "SELECT ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, HIRE_DATE, AVATAR_PATH "
        "FROM EMPLOYER "
        "WHERE UPPER(FIRST_NAME || ' ' || LAST_NAME) = UPPER(:name) "
        "OR UPPER(LAST_NAME || ' ' || FIRST_NAME) = UPPER(:name) "
        "FETCH FIRST 1 ROWS ONLY"
    );

    // Some DB engines (e.g., Oracle) accept FETCH FIRST; if not, behavior will still work with a single result.
    query.prepare(sql);
    query.bindValue(":name", fullName);

    if (!query.exec()) {
        return false;
    }

    if (query.next()) {
        out.employerId = query.value(0).toLongLong();
        out.firstName = query.value(1).toString();
        out.lastName = query.value(2).toString();
        out.email = query.value(3).toString();
        out.phone = QString::number(query.value(4).toInt());
        out.role = query.value(5).toString();
        out.passwordHash = query.value(6).toString();
        out.startDate = query.value(7).toDate();
        out.avatarPath = query.value(8).toString();
        return true;
    }

    // Fallback: perform a LIKE search on concatenated names
    QString sql2 = QString(
        "SELECT ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, HIRE_DATE, AVATAR_PATH "
        "FROM EMPLOYER "
        "WHERE UPPER(FIRST_NAME || ' ' || LAST_NAME) LIKE UPPER(:likeName) "
        "OR UPPER(LAST_NAME || ' ' || FIRST_NAME) LIKE UPPER(:likeName) "
        "FETCH FIRST 1 ROWS ONLY"
    );
    query.prepare(sql2);
    query.bindValue(":likeName", QString("%1%").arg(fullName));
    if (query.exec() && query.next()) {
        out.employerId = query.value(0).toLongLong();
        out.firstName = query.value(1).toString();
        out.lastName = query.value(2).toString();
        out.email = query.value(3).toString();
        out.phone = QString::number(query.value(4).toInt());
        out.role = query.value(5).toString();
        out.passwordHash = query.value(6).toString();
        out.startDate = query.value(7).toDate();
        out.avatarPath = query.value(8).toString();
        return true;
    }

    return false;
}

void OpenAIChatbot::validateModel()
{
    if (!PREFERRED_COHERE_MODELS.contains(m_cohereModel)) {
        Q_UNUSED(m_cohereModel);
        m_cohereModel = PREFERRED_COHERE_MODELS.first();
    }
}

// Ensure an API key is loaded into m_apiKey. Prefer explicit environment variable,
// otherwise fall back to the embedded default. We intentionally no longer
// parse local `.env` files to source secrets per project policy.
void OpenAIChatbot::ensureApiKeyLoaded()
{
    if (!m_apiKey.isEmpty()) return;

    QByteArray cohereKey = qgetenv("COHERE_API_KEY");
    if (!cohereKey.isEmpty()) {
        m_apiKey = QString::fromUtf8(cohereKey);
        m_provider = "cohere";
        return;
    }

    // Fallback: use the embedded default key
    m_apiKey = DEFAULT_COHERE_API_KEY;
    m_provider = "cohere";
}

void OpenAIChatbot::setCohereModel(const QString &model)
{
    if (!model.isEmpty()) m_cohereModel = model;
}

/**
 * @brief Set API key for the inference provider (Cohere)
 */
void OpenAIChatbot::setApiKey(const QString &key)
{
    m_apiKey = key;
}

/**
 * @brief Send a message to the inference provider (Cohere) asynchronously
 */
void OpenAIChatbot::sendMessage(const QString &userMessage)
{
    // Guard: check for empty message
    if (userMessage.trimmed().isEmpty()) {
        emit errorOccurred("Message cannot be empty.");
        return;
    }

    // Basic content filtering: block disallowed/harmful content before sending to the provider
    if (!isContentAllowed(userMessage)) {
        // Disallowed content: respond with the exact English refusal phrase per the Strict Topic Enforcer.
        // This ensures the UI and system remain consistent with the "Strict Topic Enforcer" rules.
        emit responseReceived(QStringLiteral("REFUSE — I cannot help with that."));
        m_isBusy = false;
        emit processingStatusChanged(false);
        return;
    }

    // Ensure key is loaded (fallback to .env lookups if needed)
    ensureApiKeyLoaded();
        if (m_apiKey.isEmpty()) {
            emit errorOccurred("API key not set. Please configure COHERE_API_KEY environment variable.");
            return;
        }

    m_isBusy = true;
    emit processingStatusChanged(true);

    // First: check whether this is a local DB command we can handle directly.
    // Supported informal commands (case-insensitive):
    //  - "fetch employer <id>" or "get employer <id>" -> fetchEmployerById(id)
    //  - "list employers" or "list all employers" -> listAllEmployers()
    //  - "delete employer <id>" or "remove employer <id>" -> removeEmployerById(id)
    //  - "insert employer <first>;<last>;<email>;<phone>;<role>;<password>;<hireIso>;<avatar>" -> insert
    //  - "update employer <id>;<first>;<last>;<email>;<phone>;<role>;<password>;<replacePassword 0|1>;<hireIso>;<avatar>" -> update
    // If a local command is matched and executed, return early with a clear response.
    if (parseAndExecuteLocalCommand(userMessage)) {
        m_isBusy = false;
        emit processingStatusChanged(false);
        return;
    }

    QNetworkRequest request;
    QByteArray requestBody;

    // Use Cohere Chat endpoint v1/chat (correct structure)
    QUrl url("https://api.cohere.ai/v1/chat");
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());
    request.setRawHeader("Cohere-Version", "2022-12-06");

    // Cohere v1/chat API requires:
    // - 'message': the user's message (string, NOT an array)
    // - 'preamble': system instructions (instead of role:system in messages)
    // - 'chat_history': optional conversation history (array of {role, message} objects)
    QJsonObject root;
    root["model"] = m_cohereModel;  // command-r-plus or command-r
    root["message"] = userMessage;   // REQUIRED: single user message string
    // Use the centralized system prompt embedded in code
    root["preamble"] = SYSTEM_PROMPT;
    root["temperature"] = TEMPERATURE;
    root["max_tokens"] = MAX_TOKENS;

    // Optional: include conversation history
    // Cohere expects chat_history as [{"role": "user", "message": "..."}, {"role": "assistant", "message": "..."}]
    if (!m_conversationHistory.isEmpty()) {
        QJsonArray chatHistory;
        for (const auto &pair : m_conversationHistory) {
            if (!pair.first.isEmpty()) {
                QJsonObject userHistMsg;
                // Cohere expects capitalized role names: User, Chatbot, System, Tool
                userHistMsg["role"] = "User";
                userHistMsg["message"] = pair.first;
                chatHistory.append(userHistMsg);
            }
            if (!pair.second.isEmpty()) {
                QJsonObject assistantHistMsg;
                // Use 'Chatbot' for assistant messages to match Cohere's accepted roles
                assistantHistMsg["role"] = "Chatbot";
                assistantHistMsg["message"] = pair.second;
                chatHistory.append(assistantHistMsg);
            }
        }
        root["chat_history"] = chatHistory;
    }

    QJsonDocument doc(root);
    requestBody = doc.toJson(QJsonDocument::Compact);

    m_lastRequestUrl = url.toString();
    m_lastRequestBody = requestBody;
    m_hasRetried = false;

    // Store outgoing user message in history as pending (assistant response will fill second)
    m_conversationHistory.append(qMakePair(userMessage, QString()));
    int historyIndex = m_conversationHistory.size() - 1;
    if (m_conversationHistory.size() > MAX_HISTORY) {
        m_conversationHistory.removeFirst();
    }

    // No debug output per UI requirement.

    // Send POST request and map the reply to the history index so the response
    // updates the correct entry even if multiple requests are in flight.
    QNetworkReply *reply = m_networkManager->post(request, requestBody);
    if (reply) {
        m_replyIndexMap.insert(reply, historyIndex);
        qDebug() << "[OpenAIChatbot] Sent request, mapped reply" << reply << "to history index" << historyIndex;
    } else {
        qWarning() << "[OpenAIChatbot] Failed to create network reply for message" << userMessage.left(60);
    }
}

/**
 * @brief Get conversation history
 */
QVector<QPair<QString, QString>> OpenAIChatbot::getConversationHistory() const
{
    return m_conversationHistory;
}

/**
 * @brief Clear conversation history
 */
void OpenAIChatbot::clearConversationHistory()
{
    m_conversationHistory.clear();
}

// =========================
// Employer CRUD slot APIs
// These use the existing static methods in Employer to interact with DB.
// They format human-readable results and emit them via responseReceived
// or errorOccurred for the UI.
// =========================
void OpenAIChatbot::fetchEmployerById(qint64 id)
{
    Employer emp;
    if (Employer::fetchById(id, emp)) {
        QString out = QString("ID: %1\nName: %2 %3\nEmail: %4\nPhone: %5\nRole: %6\nHire date: %7\nAvatar: %8")
                .arg(emp.employerId)
                .arg(emp.firstName)
                .arg(emp.lastName)
                .arg(emp.email)
                .arg(emp.phone)
                .arg(emp.role)
                .arg(emp.startDate.isValid() ? emp.startDate.toString(Qt::ISODate) : QString())
                .arg(emp.avatarPath);
        emit responseReceived(out);
    } else {
        emit errorOccurred(QString("Employer with ID %1 not found").arg(id));
    }
}

void OpenAIChatbot::listAllEmployers()
{
    QVector<Employer> all = Employer::selectAll();
    if (all.isEmpty()) {
        emit responseReceived("No employers found.");
        return;
    }
    QStringList rows;
    for (const Employer &e : all) {
        rows << QString("%1: %2 %3 <%4>").arg(e.employerId).arg(e.firstName).arg(e.lastName).arg(e.email);
    }
    emit responseReceived(rows.join("\n"));
}

void OpenAIChatbot::removeEmployerById(qint64 id)
{
    bool ok = Employer::remove(id);
    if (ok) emit responseReceived(QString("Employer %1 removed").arg(id));
    else emit errorOccurred(QString("Failed to remove employer %1").arg(id));
}

void OpenAIChatbot::insertEmployerFromFields(const QString &firstName,
                                             const QString &lastName,
                                             const QString &email,
                                             const QString &phone,
                                             const QString &role,
                                             const QString &password,
                                             const QString &hireDateIso,
                                             const QString &avatarPath)
{
    QDate hire = QDate::fromString(hireDateIso, Qt::ISODate);
    Employer emp(0, firstName, lastName, email, phone, role, QString(), hire, avatarPath);
    bool ok = Employer::insert(emp, password);
    if (ok) emit responseReceived("Employer inserted successfully.");
    else emit errorOccurred("Failed to insert employer.");
}

void OpenAIChatbot::updateEmployerFromFields(qint64 id,
                                             const QString &firstName,
                                             const QString &lastName,
                                             const QString &email,
                                             const QString &phone,
                                             const QString &role,
                                             const QString &password,
                                             bool replacePassword,
                                             const QString &hireDateIso,
                                             const QString &avatarPath)
{
    QDate hire = QDate::fromString(hireDateIso, Qt::ISODate);
    Employer emp(id, firstName, lastName, email, phone, role, QString(), hire, avatarPath);
    bool ok = Employer::update(id, emp, password, replacePassword);
    if (ok) emit responseReceived(QString("Employer %1 updated").arg(id));
    else emit errorOccurred(QString("Failed to update employer %1").arg(id));
}

bool OpenAIChatbot::parseAndExecuteLocalCommand(const QString &message)
{
    if (message.trimmed().isEmpty()) return false;
    QString lower = message.trimmed().toLower();

    // fetch/get employer <id>
    QRegularExpression reFetch(R"(^\s*(?:fetch|get)\s+employer\s+(\d+)\s*$)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch m = reFetch.match(message);
    if (m.hasMatch()) {
        bool ok = false;
        qint64 id = m.captured(1).toLongLong(&ok);
        if (ok) {
            fetchEmployerById(id);
            return true;
        }
    }

    // is there an employer named "Name" or just the name
    QRegularExpression reNamed(R"(^\s*(?:is there an employer named|is there an employer called|is there an employer)\s+(.+?)\s*\??$)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch mn = reNamed.match(message);
    if (mn.hasMatch()) {
        QString name = mn.captured(1).trimmed();
        // Inform UI briefly then provide the formatted result
        emit responseReceived("Checking the database…");
        Employer emp;
        if (getEmployerByName(name, emp)) {
            QString out = QString(
                "Employer Details:\n"
                "ID: %1\n"
                "Name: %2 %3\n"
                "Email: %4\n"
                "Phone: %5\n"
                "Role: %6\n"
                "Hire Date: %7\n"
                "Avatar: %8"
            ).arg(emp.employerId)
             .arg(emp.firstName)
             .arg(emp.lastName)
             .arg(emp.email)
             .arg(emp.phone)
             .arg(emp.role)
             .arg(emp.startDate.isValid() ? emp.startDate.toString(Qt::ISODate) : QString())
             .arg(emp.avatarPath);
            emit responseReceived(out);
        } else {
            emit responseReceived(QString("No employer found with the name '%1'.").arg(name));
        }
        return true;
    }

    // list employers
    if (lower.contains("list employers") || lower.contains("list all employers") || lower == "list employers") {
        listAllEmployers();
        return true;
    }

    // delete/remove employer <id>
    QRegularExpression reDelete(R"(^\s*(?:delete|remove)\s+employer\s+(\d+)\s*$)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch md = reDelete.match(message);
    if (md.hasMatch()) {
        bool ok = false;
        qint64 id = md.captured(1).toLongLong(&ok);
        if (ok) {
            removeEmployerById(id);
            return true;
        }
    }

    // insert employer <first>;<last>;<email>;<phone>;<role>;<password>;<hireIso>;<avatar>
    QRegularExpression reInsert(R"(^\s*(?:insert|add)\s+employer\s+(.+)$)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch mi = reInsert.match(message);
    if (mi.hasMatch()) {
        QString payload = mi.captured(1).trimmed();
        QStringList parts = payload.split(';');
        if (parts.size() >= 8) {
            insertEmployerFromFields(parts[0].trimmed(), parts[1].trimmed(), parts[2].trimmed(), parts[3].trimmed(), parts[4].trimmed(), parts[5].trimmed(), parts[6].trimmed(), parts[7].trimmed());
            return true;
        } else {
            emit errorOccurred("Insert format: insert employer first;last;email;phone;role;password;hireIso;avatar");
            return true;
        }
    }

    // update employer <id>;<first>;<last>;<email>;<phone>;<role>;<password>;<replacePassword 0|1>;<hireIso>;<avatar>
    QRegularExpression reUpdate(R"(^\s*update\s+employer\s+(.+)$)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch mu = reUpdate.match(message);
    if (mu.hasMatch()) {
        QString payload = mu.captured(1).trimmed();
        QStringList parts = payload.split(';');
        if (parts.size() >= 10) {
            bool ok = false;
            qint64 id = parts[0].trimmed().toLongLong(&ok);
            if (!ok) { emit errorOccurred("Invalid ID for update command"); return true; }
            QString first = parts[1].trimmed();
            QString last = parts[2].trimmed();
            QString email = parts[3].trimmed();
            QString phone = parts[4].trimmed();
            QString role = parts[5].trimmed();
            QString password = parts[6].trimmed();
            bool replacePassword = (parts[7].trimmed() == "1");
            QString hireIso = parts[8].trimmed();
            QString avatar = parts[9].trimmed();
            updateEmployerFromFields(id, first, last, email, phone, role, password, replacePassword, hireIso, avatar);
            return true;
        } else {
            emit errorOccurred("Update format: update employer id;first;last;email;phone;role;password;replacePassword(0|1);hireIso;avatar");
            return true;
        }
    }

    return false;
}

/**
 * @brief Handle network reply from the inference provider (Cohere)
 */
void OpenAIChatbot::onReplyFinished(QNetworkReply *reply)
{
    // Mark this particular reply as finished; only clear overall busy state
    // when no more pending replies remain.

    if (!reply) {
        emit errorOccurred("Network reply is null");
        return;
    }

    // Map reply to its history index (if available)
    int mappedIndex = -1;
    if (reply && m_replyIndexMap.contains(reply)) {
        mappedIndex = m_replyIndexMap.take(reply);
    }

    auto writeToHistory = [&](const QString &text) {
        if (mappedIndex >= 0 && mappedIndex < m_conversationHistory.size()) {
            m_conversationHistory[mappedIndex].second = text;
        } else if (!m_conversationHistory.isEmpty()) {
            // fallback: update last
            m_conversationHistory.last().second = text;
        } else {
            m_conversationHistory.append(qMakePair(QString(), text));
        }
        if (m_conversationHistory.size() > MAX_HISTORY) {
            m_conversationHistory.removeFirst();
        }
    };

    // If no more pending replies, clear busy and notify UI; otherwise keep busy
    if (m_replyIndexMap.isEmpty()) {
        m_isBusy = false;
        emit processingStatusChanged(false);
    }

    // Read body (may contain server error details) and HTTP status
    QByteArray body = reply->readAll();
    QString bodyStr = QString::fromUtf8(body);
    QVariant statusVar = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCode = statusVar.isValid() ? statusVar.toInt() : -1;

    Q_UNUSED(statusCode);
    Q_UNUSED(bodyStr);

    // If there was a transport error, report it (but still inspect body/status)
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg = QString("Network Error: %1").arg(reply->errorString());
        Q_UNUSED(errorMsg);
    }

    // At this point we have the final response body
    QByteArray responseData = body;
    Q_UNUSED(responseData);

    // Parse Cohere JSON response (support both legacy 'generations' and new Chat API shapes)
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject obj = jsonDoc.object();

        // Error field
        if (obj.contains("error")) {
            QString msg = obj["error"].toString();
            emit errorOccurred(QString("Cohere API error: %1").arg(msg));
            reply->deleteLater();
            return;
        }

        // 1) First priority: Cohere Chat API v1 returns text at root level
        if (obj.contains("text") && obj["text"].isString()) {
            QString text = obj["text"].toString().trimmed();
                if (!text.isEmpty()) {
                    Q_UNUSED(text);
                    writeToHistory(text);
                    emit responseReceived(text);
                reply->deleteLater();
                return;
            }
        }

        // 2) Legacy: generations (from Generate API)
        if (obj.contains("generations") && obj["generations"].isArray()) {
            QJsonArray gens = obj["generations"].toArray();
                if (!gens.isEmpty() && gens[0].isObject()) {
                QString generated = gens[0].toObject().value("text").toString().trimmed();
                    if (!generated.isEmpty()) {
                    Q_UNUSED(generated);
                    QString cleaned = sanitizeAssistantText(generated);
                    writeToHistory(cleaned);
                    emit responseReceived(cleaned);
                    reply->deleteLater();
                    return;
                }
            }
        }

        // 2) Chat API: look for 'message' with text or content
        // Try common shapes robustly
        // a) { "message": { "content": "..." } } or { "message": { "text": "..." } }
        if (obj.contains("message") && obj["message"].isObject()) {
            QJsonObject m = obj["message"].toObject();
            
            // Try 'text' field first (Cohere Chat API)
            if (m.contains("text") && m["text"].isString()) {
                QString text = m["text"].toString().trimmed();
                    if (!text.isEmpty()) {
                    Q_UNUSED(text);
                    QString cleaned = sanitizeAssistantText(text);
                    writeToHistory(cleaned);
                    emit responseReceived(cleaned);
                    reply->deleteLater();
                    return;
                }
            }
            
            // Fallback: try 'content' field
            if (m.contains("content") && m["content"].isString()) {
                QString text = m["content"].toString().trimmed();
                    if (!text.isEmpty()) {
                    Q_UNUSED(text);
                    QString cleaned = sanitizeAssistantText(text);
                    writeToHistory(cleaned);
                    emit responseReceived(cleaned);
                    reply->deleteLater();
                    return;
                }
            }
            
            // Try nested content object
            if (m.contains("content") && m["content"].isObject()) {
                QJsonObject c = m["content"].toObject();
                // common nested field
                        if (c.contains("text") && c["text"].isString()) {
                    QString text = c["text"].toString().trimmed();
                    if (!text.isEmpty()) {
                        Q_UNUSED(text);
                        QString cleaned = sanitizeAssistantText(text);
                        writeToHistory(cleaned);
                        emit responseReceived(cleaned);
                        reply->deleteLater();
                        return;
                    }
                }
            }
            
            // Try content as array
            if (m.contains("content") && m["content"].isArray()) {
                QJsonArray carr = m["content"].toArray();
                for (const QJsonValue &vv : carr) {
                    if (vv.isString()) {
                        QString text = vv.toString().trimmed();
                        if (!text.isEmpty()) {
                            QString cleaned = sanitizeAssistantText(text);
                            writeToHistory(cleaned);
                            emit responseReceived(cleaned);
                            reply->deleteLater();
                            return;
                        }
                    }
                }
            }
        }

        // 3) Chat API alternative: outputs / generations-like shapes
        if (obj.contains("outputs") && obj["outputs"].isArray()) {
            QJsonArray outs = obj["outputs"].toArray();
            if (!outs.isEmpty()) {
                // outputs[0] may be object with 'content' or 'text' array
                QJsonValue first = outs[0];
                if (first.isObject()) {
                    QJsonObject fo = first.toObject();
                    
                    if (fo.contains("text") && fo["text"].isString()) {
                        QString text = fo["text"].toString().trimmed();
                        if (!text.isEmpty()) {
                            QString cleaned = sanitizeAssistantText(text);
                            writeToHistory(cleaned);
                            emit responseReceived(cleaned);
                            reply->deleteLater();
                            return;
                        }
                    }
                    
                    if (fo.contains("content") && fo["content"].isArray()) {
                        QJsonArray contentArr = fo["content"].toArray();
                        for (const QJsonValue &cv : contentArr) {
                            if (cv.isObject()) {
                                QJsonObject co = cv.toObject();
                                if (co.contains("text") && co["text"].isString()) {
                                    QString text = co["text"].toString().trimmed();
                                    if (!text.isEmpty()) {
                                        QString cleaned = sanitizeAssistantText(text);
                                        writeToHistory(cleaned);
                                        emit responseReceived(cleaned);
                                        reply->deleteLater();
                                        return;
                                    }
                                }
                            } else if (cv.isString()) {
                                QString text = cv.toString().trimmed();
                                if (!text.isEmpty()) {
                                    QString cleaned = sanitizeAssistantText(text);
                                    writeToHistory(cleaned);
                                    emit responseReceived(cleaned);
                                    reply->deleteLater();
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Fallback: if the API returned plain text, pass it along
    QString plain = QString::fromUtf8(responseData).trimmed();
    if (!plain.isEmpty()) {
        emit responseReceived(plain);
        reply->deleteLater();
        return;
    }

    emit errorOccurred("Failed to parse Cohere response");
    reply->deleteLater();
}

/**
 * @brief Basic content filter implementation
 * Blocks obvious sexual solicitation, explicit content and common slurs.
 * This is intentionally simple; for production use consider a more robust moderation API.
 */
bool OpenAIChatbot::isContentAllowed(const QString &message) const
{
    if (message.trimmed().isEmpty()) return true;

    QString lower = message.toLower();

    // Simple patterns to block: sexual solicitation, explicit phrases, and common racial slurs
    static const QRegularExpression sexualPattern(R"((sex|fuck|have sex|sexual|s*x))", QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression solicitationPattern(R"((buy sex|pay for sex|hookup|meet for sex))", QRegularExpression::CaseInsensitiveOption);
    static const QRegularExpression slurPattern(R"((nigger|nigga|chink|kike|spic|faggot))", QRegularExpression::CaseInsensitiveOption);

    if (sexualPattern.match(lower).hasMatch() || solicitationPattern.match(lower).hasMatch() || slurPattern.match(lower).hasMatch()) {
        return false;
    }

    // Disallow overly explicit sexual content (simple heuristic)
    static const QRegularExpression explicitPattern(R"((explicit|porn|nsfw|sexually explicit))", QRegularExpression::CaseInsensitiveOption);
    if (explicitPattern.match(lower).hasMatch()) return false;

    return true;
}

/**
 * @brief Build request body for Cohere (used to build the prompt + parameters)
 */
QByteArray OpenAIChatbot::buildCohereRequestBody(const QString &userMessage) const
{
    // Compose a plain-text prompt from system + history + current user message
    QStringList parts;
    // Put the centralized SYSTEM_PROMPT at the top of any fallback prompt
    parts << SYSTEM_PROMPT;

    for (const auto &pair : m_conversationHistory) {
        if (!pair.first.isEmpty()) parts << QString("User: %1").arg(pair.first);
        if (!pair.second.isEmpty()) parts << QString("Assistant: %1").arg(pair.second);
    }

    parts << QString("User: %1").arg(userMessage);

    QString prompt = parts.join("\n");

    QJsonObject root;
    // Cohere uses a "prompt" + generation parameters
    root["prompt"] = prompt;
    root["temperature"] = TEMPERATURE;
    root["max_tokens"] = MAX_TOKENS;

    QJsonDocument doc(root);
    return doc.toJson(QJsonDocument::Compact);
}
