#include "faceapi.h"
#include "employer.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QBuffer>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>
#include <QVector>

namespace FaceApi {

namespace {
    constexpr const char *kDefaultEndpoint = "https://api-us.faceplusplus.com/facepp/v3/compare";
    constexpr double kDefaultConfidence = 75.0; // percent
    constexpr const char *kDefaultApiKey = "";
    constexpr const char *kDefaultApiSecret = "";
}

Client::Client(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_apiKey(QString::fromUtf8(kDefaultApiKey))
    , m_apiSecret(QString::fromUtf8(kDefaultApiSecret))
    , m_endpointUrl(QString::fromUtf8(kDefaultEndpoint))
    , m_minConfidence(kDefaultConfidence)
    , m_currentIndex(-1)
    , m_busy(false)
{
}

void Client::setCredentials(const QString &apiKey, const QString &apiSecret)
{
    if (!apiKey.isEmpty()) {
        m_apiKey = apiKey;
    }
    if (!apiSecret.isEmpty()) {
        m_apiSecret = apiSecret;
    }
}

void Client::setEndpoint(const QString &endpointUrl)
{
    if (!endpointUrl.isEmpty()) {
        m_endpointUrl = endpointUrl;
    }
}

void Client::setConfidenceThreshold(double confidence)
{
    if (confidence > 0.0) {
        m_minConfidence = confidence;
    }
}

void Client::recognizeAgainstEmployees(const QImage &probeImage)
{
    if (m_busy) {
        emit recognitionFailed("Face++ request already running");
        return;
    }

    if (probeImage.isNull()) {
        emit recognitionFailed("Camera frame is empty");
        return;
    }

    m_probeImage = probeImage;
    resetState();
    loadEligibleEmployees();

    if (m_candidates.isEmpty()) {
        emit recognitionFailed("No employee reference images are available for Face++ comparison");
        return;
    }

    m_busy = true;
    compareNextCandidate();
}

void Client::resetState()
{
    m_candidates.clear();
    m_currentIndex = -1;
    m_bestResult = CloudResult{};
    m_bestResult.employeeId = -1;
    m_bestResult.recognized = false;
}

void Client::loadEligibleEmployees()
{
    const QVector<Employer> allEmployers = Employer::selectAll();
    for (const Employer &emp : allEmployers) {
        if (emp.avatarPath.isEmpty()) {
            continue;
        }
        QImage ref(emp.avatarPath);
        if (ref.isNull()) {
            qWarning() << "[FaceApi] Unable to load avatar for" << emp.email << "at" << emp.avatarPath;
            continue;
        }
        CandidateContext context;
        context.employer = emp;
        context.referenceImage = ref.scaled(512, 512, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_candidates.append(context);
    }
}

void Client::compareNextCandidate()
{
    m_currentIndex++;
    if (m_currentIndex >= m_candidates.size()) {
        finalize();
        return;
    }

    const CandidateContext context = m_candidates.at(m_currentIndex);

    QByteArray probeBase64 = imageToBase64(m_probeImage);
    QByteArray referenceBase64 = imageToBase64(context.referenceImage);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    auto appendField = [multiPart](const QString &name, const QByteArray &value) {
        QHttpPart part;
        part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QStringLiteral("form-data; name=\"%1\"").arg(name)));
        part.setBody(value);
        multiPart->append(part);
    };

    appendField(QStringLiteral("api_key"), m_apiKey.toUtf8());
    appendField(QStringLiteral("api_secret"), m_apiSecret.toUtf8());
    appendField(QStringLiteral("image_base64_1"), probeBase64);
    appendField(QStringLiteral("image_base64_2"), referenceBase64);

    QNetworkRequest request{QUrl(m_endpointUrl)};
    request.setHeader(QNetworkRequest::UserAgentHeader, QStringLiteral("AmineTemplar-FaceClient/1.0"));

    QNetworkReply *reply = m_networkManager->post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, [this, reply, context]() {
        handleCompareReply(reply, context);
    });
}

void Client::handleCompareReply(QNetworkReply *reply, const CandidateContext &context)
{
    const QByteArray payload = reply->readAll();
    const bool hasNetworkError = (reply->error() != QNetworkReply::NoError);
    const QString networkErrorMessage = reply->errorString();
    reply->deleteLater();

    if (hasNetworkError) {
        qWarning() << "[FaceApi] Network error for" << context.employer.email << ":" << networkErrorMessage;
        compareNextCandidate();
        return;
    }

    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(payload, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[FaceApi] Invalid JSON response for" << context.employer.email << ":" << parseError.errorString();
        compareNextCandidate();
        return;
    }

    const QJsonObject obj = doc.object();

    if (obj.contains(QStringLiteral("error_message"))) {
        const QString apiError = obj.value(QStringLiteral("error_message")).toString();
        qWarning() << "[FaceApi] API error for" << context.employer.email << ":" << apiError;
        compareNextCandidate();
        return;
    }

    CloudResult current;
    current.employeeId = static_cast<int>(context.employer.employerId);
    current.employeeName = QString("%1 %2").arg(context.employer.firstName, context.employer.lastName).trimmed();
    current.confidence = obj.value(QStringLiteral("confidence")).toDouble();
    current.thresholds.oneE3 = obj.value(QStringLiteral("thresholds")).toObject().value(QStringLiteral("1e-3")).toDouble();
    current.thresholds.oneE4 = obj.value(QStringLiteral("thresholds")).toObject().value(QStringLiteral("1e-4")).toDouble();
    current.thresholds.oneE5 = obj.value(QStringLiteral("thresholds")).toObject().value(QStringLiteral("1e-5")).toDouble();
    current.requestId = obj.value(QStringLiteral("request_id")).toString();

    if (current.confidence > m_bestResult.confidence) {
        current.recognized = current.confidence >= m_minConfidence;
        m_bestResult = current;
    }

    compareNextCandidate();
}

QByteArray Client::imageToBase64(const QImage &image) const
{
    QByteArray bufferBytes;
    QBuffer buffer(&bufferBytes);
    buffer.open(QIODevice::WriteOnly);
    QImage scaled = image;
    if (scaled.width() > 512) {
        scaled = image.scaled(512, 512, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    scaled.save(&buffer, "JPG", 90);
    return bufferBytes.toBase64();
}

void Client::finalize()
{
    const bool recognized = m_bestResult.recognized && m_bestResult.employeeId != -1;

    if (!recognized) {
        m_bestResult.recognized = false;
        m_bestResult.employeeId = -1;
    }

    m_busy = false;
    m_candidates.clear();
    m_probeImage = QImage();

    emit recognitionCompleted(m_bestResult);
}

} // namespace FaceApi
