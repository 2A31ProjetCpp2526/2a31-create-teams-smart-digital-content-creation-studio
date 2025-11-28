#ifndef CHATBOT_H
#define CHATBOT_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QHash>

class Employer;

/**
 * @brief OpenAIChatbot - Integration with an inference provider (Cohere)
 * Handles asynchronous chat messages using the configured provider (Cohere).
 */
class OpenAIChatbot : public QObject
{
    Q_OBJECT

public:
    // Constructor and destructor
    explicit OpenAIChatbot(QObject *parent = nullptr);
    ~OpenAIChatbot();

    // Send a message to the inference provider (Cohere)
    void sendMessage(const QString &userMessage);

public slots:
    // Employer CRUD helpers that use existing Employer:: static methods
    // These slots allow UI code to ask the chatbot component to perform DB ops
    void fetchEmployerById(qint64 id);
    void listAllEmployers();
    void removeEmployerById(qint64 id);
    void insertEmployerFromFields(const QString &firstName,
                                  const QString &lastName,
                                  const QString &email,
                                  const QString &phone,
                                  const QString &role,
                                  const QString &password,
                                  const QString &hireDateIso,
                                  const QString &avatarPath);
    void updateEmployerFromFields(qint64 id,
                                  const QString &firstName,
                                  const QString &lastName,
                                  const QString &email,
                                  const QString &phone,
                                  const QString &role,
                                  const QString &password,
                                  bool replacePassword,
                                  const QString &hireDateIso,
                                  const QString &avatarPath);

    // Set API key for the inference provider (Cohere)
    void setApiKey(const QString &key);

    // Set the Cohere model to use (e.g. "command-xlarge")
    void setCohereModel(const QString &model);

    // Get conversation history
    QVector<QPair<QString, QString>> getConversationHistory() const;

    // Clear conversation history
    void clearConversationHistory();

    // Check if chatbot is busy processing
    bool isBusy() const { return m_isBusy; }

signals:
    // Emitted when AI response is received
    void responseReceived(const QString &response);

    // Emitted when an error occurs
    void errorOccurred(const QString &errorMessage);

    // Emitted when processing starts/stops
    void processingStatusChanged(bool isBusy);

private slots:
    // Handle network reply from the inference provider
    void onReplyFinished(QNetworkReply *reply);

private:
    // Build request body for Cohere (prompt + parameters)
    QByteArray buildCohereRequestBody(const QString &userMessage) const;

    // Basic content filtering to block disallowed requests (hate speech, sexual solicitation, etc.)
    bool isContentAllowed(const QString &message) const;

    // Try to load API key from environment or local .env files (debug-friendly fallback)
    void ensureApiKeyLoaded();

    // Validate selected Cohere model and apply fallback if needed
    void validateModel();

    // Attempt to parse a local command (CRUD) from the user's message and execute it
    // Returns true if the message was handled locally (no remote API call needed)
    bool parseAndExecuteLocalCommand(const QString &message);

    // Helper to find an employer by full name (first + last or last + first).
    // Returns true and fills 'out' if found, false otherwise.
    bool getEmployerByName(const QString &fullName, Employer &out) const;

    // Append diagnostic text to a local logfile in the application directory
    void appendDebugLog(const QString &text) const;

private:
    QNetworkAccessManager *m_networkManager;
    QString m_apiKey;
    bool m_isBusy;

    // Conversation history: pair of (user message, ai response)
    QVector<QPair<QString, QString>> m_conversationHistory;

    // Maximum number of messages to keep in history (for context)
    static constexpr int MAX_HISTORY = 10;

    // Cohere model name (modifiable at runtime)
    QString m_cohereModel;
    // Provider selection (kept for compatibility) - will be "cohere"
    QString m_provider;

    // Last request data for debugging / retry logic
    QString m_lastRequestUrl;
    QByteArray m_lastRequestBody;
    bool m_hasRetried;

    // Map active QNetworkReply* to the index in m_conversationHistory so replies
    // are applied to the correct user message when multiple requests are in flight.
    QHash<QNetworkReply*, int> m_replyIndexMap;

    // Provider accessors (readonly in practice)
    void setProvider(const QString &providerName) { m_provider = providerName.toLower(); }
    QString provider() const { return m_provider; }

    // Temperature for response generation (0.0 - 2.0)
    static constexpr double TEMPERATURE = 0.7;

    // Maximum tokens / max_new_tokens for HF
    static constexpr int MAX_TOKENS = 1000;
};

#endif // CHATBOT_H
