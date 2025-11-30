#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QPair>
#include <QSqlDatabase>

class Project
{
public:
    // Properties
    qint64 projectId = -1;
    qint64 clientId = -1;
    qint64 serviceId = -1;
    QString title;
    QString description;
    QDate creationDate;
    QDate modificationDate;
    qint64 ownerId = -1;

    // Constructors
    Project() = default;
    explicit Project(const QString &title);

    // Database operations
    // Insert returns the newly created project ID on success, or -1 on failure.
    static qint64 insert(const Project &project);
    static bool update(const Project &project);
    static bool deleteProject(qint64 projectId);
    static Project selectById(qint64 projectId);
    static QVector<Project> selectAll();
    // Advanced selection helpers
    static QVector<Project> selectAllSortedByTitle(bool ascending = true);
    static QVector<Project> selectAllSortedByStatistic(bool ascending = false);
    // Search projects by keyword in title or description
    static QVector<Project> search(const QString &keyword);
    // Export given projects to CSV file (Excel-friendly) - returns true on success
    static bool exportToCsv(const QString &filePath, const QVector<Project> &projects);
    
    // Project-Employer relationship (GERER table)
    static bool addEmployerToProject(qint64 projectId, qint64 employerId);
    static bool removeEmployerFromProject(qint64 projectId, qint64 employerId);
    static bool removeAllEmployersFromProject(qint64 projectId);
    static QVector<Project> getProjectsByEmployer(qint64 employerId);
    static QVector<qint64> getEmployersByProject(qint64 projectId);
    // Returns each project along with the number of assigned employers
    static QVector<QPair<Project, int>> selectAllWithEmployerCount(bool sortDesc = true);
    // Rich statistics per project
    struct ProjectStats {
        qint64 projectId = -1;
        QString title;
        int employerCount = 0;
        int resourceCount = 0;
        int sponsorCount = 0;
        double totalResourceSize = 0.0; // sum of FILE_SIZE in RESSOURCES (bytes)
        int ageDays = 0; // days since creation
        QDate creationDate;
    };

    static QVector<ProjectStats> selectProjectStatistics(bool sortByEmployerDesc = true);

    // Statistics restricted to PROJECTS only (no other entities)
    struct ProjectOnlyStats {
        qint64 projectId = -1;
        QString title;
        QString description;
        QDate creationDate;
        QDate modificationDate;
        qint64 ownerId = -1;
        int ageDays = 0;
    };

    static QVector<ProjectOnlyStats> selectProjectOnlyStats(const QString &orderBy = "ID_PROJECT DESC");
    
    // Fetch by ID with error handling
    static bool fetchById(qint64 projectId, Project &project);
};

#endif // PROJECT_H
