#ifndef FACEAPI_H
#define FACEAPI_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QString>

#include "backend/employer.h"

class QNetworkAccessManager;
class QNetworkReply;

namespace FaceApi {

struct Thresholds {
    double oneE3 = 0.0;
    double oneE4 = 0.0;
    double oneE5 = 0.0;
};

struct CloudResult {
    bool recognized = false;
    int employeeId = -1;
    QString employeeName;
    double confidence = 0.0; // 0-100 scale from Face++
    Thresholds thresholds;
    QString requestId;
    QString errorMessage;
};

struct CandidateContext {
    Employer employer;
    QImage referenceImage;
};

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void setCredentials(const QString &apiKey, const QString &apiSecret);
    void setEndpoint(const QString &endpointUrl);
    void setConfidenceThreshold(double confidence);

    bool isBusy() const { return m_busy; }

    void recognizeAgainstEmployees(const QImage &probeImage);

signals:
    void recognitionCompleted(const FaceApi::CloudResult &result);
    void recognitionFailed(const QString &message);

private:
    void resetState();
    void loadEligibleEmployees();
    void compareNextCandidate();
    void handleCompareReply(QNetworkReply *reply, const CandidateContext &context);
    QByteArray imageToBase64(const QImage &image) const;
    void finalize();

    QNetworkAccessManager *m_networkManager;
    QString m_apiKey;
    QString m_apiSecret;
    QString m_endpointUrl;
    double m_minConfidence;

    QList<CandidateContext> m_candidates;
    QImage m_probeImage;
    int m_currentIndex;
    CloudResult m_bestResult;
    bool m_busy;
};

} // namespace FaceApi

#endif // FACEAPI_H
