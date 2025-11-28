#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDate>
#include <QVector>
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
    static bool insert(const Project &project);
    static bool update(const Project &project);
    static bool deleteProject(qint64 projectId);
    static Project selectById(qint64 projectId);
    static QVector<Project> selectAll();
    
    // Project-Employer relationship (GERER table)
    static bool addEmployerToProject(qint64 projectId, qint64 employerId);
    static bool removeEmployerFromProject(qint64 projectId, qint64 employerId);
    static bool removeAllEmployersFromProject(qint64 projectId);
    static QVector<Project> getProjectsByEmployer(qint64 employerId);
    static QVector<qint64> getEmployersByProject(qint64 projectId);
    
    // Fetch by ID with error handling
    static bool fetchById(qint64 projectId, Project &project);
};

#endif // PROJECT_H
