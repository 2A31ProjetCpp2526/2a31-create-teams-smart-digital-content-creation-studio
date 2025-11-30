#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QSqlQueryModel>
#include <QMap>
#include <Qt>

/**
 * @brief RessourceStatistics - Structure to hold resource statistics
 */
struct RessourceStatistics
{
    int totalResources = 0;
    int publicResources = 0;
    int privateResources = 0;
    int newResourcesThisMonth = 0;
    int newResourcesThisYear = 0;
    QString mostCommonFormat;
    QString mostActiveOwner;
    int totalFormats = 0;
    int totalOwners = 0;
    qint64 totalFileSize = 0;  // If you track file sizes
    QMap<int, int> uploadsPerYear;
    QMap<int, int> uploadsPerMonth;  // Current year
    QMap<QString, int> formatDistribution;
    QMap<QString, int> ownerDistribution;
    QMap<QString, int> accessLevelDistribution;
};

class Ressource
{
public:
qint64 idMedia;
QString title;
QString path;
QString owner;
QString format;
QString accessLevel;
QDateTime uploadDate;

    Ressource();
    Ressource(qint64 idMedia, const QString &title, const QString &path,
              const QString &owner, const QString &format, 
              const QString &accessLevel, const QDateTime &uploadDate = QDateTime::currentDateTime());

    static bool insert(const Ressource &ressource);
    static QVector<Ressource> selectAll();
    static bool update(const Ressource &ressource);
    static bool remove(qint64 id);
    static bool fetchById(qint64 id, Ressource &ressource);
    static bool clearAllReferencesForResource(qint64 resourceId);

    static bool isTitleValid(const QString &title, QString &errorMsg);
    static bool isTitleUnique(const QString &title, qint64 excludeId = -1);

    static QVector<Ressource> getResourcesByEmployer(qint64 employerId);
    static bool addResourceToEmployer(qint64 employerId, qint64 resourceId);
    static bool removeResourceFromEmployer(qint64 employerId, qint64 resourceId);
    static bool clearEmployerResources(qint64 employerId);

    static QSqlQueryModel* displayAll();
    static QSqlQueryModel* search(const QString &keyword);
    static QSqlQueryModel* sortBy(const QString &columnName, Qt::SortOrder order = Qt::AscendingOrder);

    static bool exportToCsv(const QString &filePath);
    
    // Compute aggregated statistics about resources
    static RessourceStatistics computeStatistics();
};

#endif
