#include "project.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QVariant>
#include <QFile>
#include <QTextStream>

Project::Project(const QString &title)
    : title(title)
{
}

qint64 Project::insert(const Project &project)
{
    qDebug() << "[Project::insert] Starting insert for project:" << project.title;
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::insert] ERROR: Database not open";
        return false;
    }
    
    // Escape single quotes in text values
    QString escapedTitle = project.title;
    escapedTitle.replace("'", "''");
    QString escapedDescription = project.description;
    escapedDescription.replace("'", "''");
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("INSERT INTO PROJECTS (ID_PROJECT, ID_CLIENT, ID_SERVICE, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID) "
                          "VALUES (PROJECTS_SEQ.NEXTVAL, %1, %2, '%3', '%4', TO_DATE('%5', 'YYYY-MM-DD'), TO_DATE('%6', 'YYYY-MM-DD'), %7)")
                      .arg(project.clientId > 0 ? QString::number(project.clientId) : "NULL",
                           project.serviceId > 0 ? QString::number(project.serviceId) : "NULL",
                           escapedTitle,
                           escapedDescription,
                           project.creationDate.toString("yyyy-MM-dd"),
                           project.modificationDate.toString("yyyy-MM-dd"),
                           project.ownerId > 0 ? QString::number(project.ownerId) : "NULL");
    
    QSqlQuery query(db);

    qDebug() << "[Project::insert] SQL:" << sql;

    if (!query.exec(sql))
    {
        qDebug() << "[Project::insert] ERROR:" << query.lastError().text();
        return -1;
    }

    // Attempt to retrieve the generated id from the sequence we used for insertion.
    // With Oracle, CURRVAL is available in the same session after NEXTVAL was used.
    qint64 newId = -1;
    QSqlQuery idQuery(db);
    if (idQuery.exec("SELECT PROJECTS_SEQ.CURRVAL FROM DUAL")) {
        if (idQuery.next()) {
            newId = idQuery.value(0).toLongLong();
            qDebug() << "[Project::insert] New project id:" << newId;
        }
    } else {
        qDebug() << "[Project::insert] WARN: failed to read CURRVAL:" << idQuery.lastError().text();
    }

    return newId;
}

bool Project::update(const Project &project)
{
    qDebug() << "[Project::update] Updating project ID:" << project.projectId;
    
    // Validate only required field - projectId
    if (project.projectId <= 0)
    {
        qDebug() << "[Project::update] ERROR: Project ID is required";
        return false;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::update] ERROR: Database not open";
        return false;
    }
    
    // Escape single quotes in text values
    QString escapedTitle = project.title;
    escapedTitle.replace("'", "''");
    QString escapedDescription = project.description;
    escapedDescription.replace("'", "''");
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("UPDATE PROJECTS SET TITLE = '%1', DESCRIPTION = '%2', "
                          "ID_CLIENT = %3, ID_SERVICE = %4, "
                          "CREATION_DATE = TO_DATE('%5', 'YYYY-MM-DD'), "
                          "MODIFICATION_DATE = TO_DATE('%6', 'YYYY-MM-DD'), "
                          "OWNER_ID = %7 "
                          "WHERE ID_PROJECT = %8")
                      .arg(escapedTitle,
                           escapedDescription,
                           project.clientId > 0 ? QString::number(project.clientId) : "NULL",
                           project.serviceId > 0 ? QString::number(project.serviceId) : "NULL",
                           project.creationDate.toString("yyyy-MM-dd"),
                           project.modificationDate.toString("yyyy-MM-dd"),
                           project.ownerId > 0 ? QString::number(project.ownerId) : "NULL",
                           QString::number(project.projectId));
    
    QSqlQuery query(db);
    
    qDebug() << "[Project::update] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::update] ERROR:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "[Project::update] SUCCESS";
    return true;
}

bool Project::deleteProject(qint64 projectId)
{
    qDebug() << "========================================";
    qDebug() << "[Project::deleteProject] Deleting project ID:" << projectId;
    
    if (projectId <= 0)
    {
        qDebug() << "[Project::deleteProject] ERROR: Invalid project ID";
        qDebug() << "========================================";
        return false;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::deleteProject] ERROR: Database not open";
        qDebug() << "========================================";
        return false;
    }
    
    // First, remove all employer associations (GERER table)
    qDebug() << "[Project::deleteProject] Removing all employer associations...";
    if (!removeAllEmployersFromProject(projectId))
    {
        qDebug() << "[Project::deleteProject] WARNING: Failed to remove employer associations, but continuing...";
        // Continue anyway as the project might have no associations
    }
    
    // Then delete the project itself
    qDebug() << "[Project::deleteProject] Executing DELETE FROM PROJECTS...";
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("DELETE FROM PROJECTS WHERE ID_PROJECT = %1").arg(projectId);
    QSqlQuery query(db);
    
    qDebug() << "[Project::deleteProject] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::deleteProject] ERROR:" << query.lastError().text();
        qDebug() << "[Project::deleteProject] Driver error:" << query.lastError().driverText();
        qDebug() << "========================================";
        return false;
    }
    
    int rowsAffected = query.numRowsAffected();
    qDebug() << "[Project::deleteProject] SUCCESS - Rows affected:" << rowsAffected;
    qDebug() << "========================================";
    return true;
}

Project Project::selectById(qint64 projectId)
{
    Project project;
    fetchById(projectId, project);
    return project;
}

QVector<Project> Project::selectAll()
{
    qDebug() << "[Project::selectAll] Fetching all projects...";
    
    QVector<Project> projects;
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.isOpen())
    {
        qDebug() << "[Project::selectAll] ERROR: Database not open";
        return projects;
    }
    
    QSqlQuery query(db);
    
    if (!query.exec("SELECT ID_PROJECT, ID_CLIENT, ID_SERVICE, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID FROM PROJECTS ORDER BY ID_PROJECT DESC"))
    {
        qDebug() << "[Project::selectAll] ERROR:" << query.lastError().text();
        return projects;
    }
    
    while (query.next())
    {
        Project project;
        project.projectId = query.value(0).toLongLong();
        project.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
        project.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
        project.title = query.value(3).toString();
        project.description = query.value(4).toString();
        project.creationDate = query.value(5).toDate();
        project.modificationDate = query.value(6).toDate();
        project.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();
        
        projects.append(project);
    }
    
    qDebug() << "[Project::selectAll] Found" << projects.size() << "projects";
    return projects;
}

QVector<Project> Project::selectAllSortedByTitle(bool ascending)
{
    QVector<Project> projects;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return projects;

    QString order = ascending ? "ASC" : "DESC";
    QString sql = QString("SELECT ID_PROJECT, ID_CLIENT, ID_SERVICE, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID FROM PROJECTS ORDER BY UPPER(TITLE) %1").arg(order);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "[Project::selectAllSortedByTitle] ERROR:" << query.lastError().text();
        return projects;
    }

    while (query.next()) {
        Project project;
        project.projectId = query.value(0).toLongLong();
        project.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
        project.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
        project.title = query.value(3).toString();
        project.description = query.value(4).toString();
        project.creationDate = query.value(5).toDate();
        project.modificationDate = query.value(6).toDate();
        project.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();
        projects.append(project);
    }

    return projects;
}

QVector<Project> Project::selectAllSortedByStatistic(bool ascending)
{
    // Statistic: number of employers associated with the project
    QVector<Project> projects;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return projects;

    QString order = ascending ? "ASC" : "DESC";
    QString sql = QString(
        "SELECT p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID, COUNT(g.ID_EMP) AS EMP_COUNT "
        "FROM PROJECTS p LEFT JOIN GERER g ON p.ID_PROJECT = g.ID_PROJECT "
        "GROUP BY p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID "
        "ORDER BY EMP_COUNT %1").arg(order);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "[Project::selectAllSortedByStatistic] ERROR:" << query.lastError().text();
        return projects;
    }

    while (query.next()) {
        Project project;
        project.projectId = query.value(0).toLongLong();
        project.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
        project.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
        project.title = query.value(3).toString();
        project.description = query.value(4).toString();
        project.creationDate = query.value(5).toDate();
        project.modificationDate = query.value(6).toDate();
        project.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();
        // note: EMP_COUNT is at index 8, but we don't store it in Project object for now
        projects.append(project);
    }

    return projects;
}

QVector<QPair<Project, int>> Project::selectAllWithEmployerCount(bool sortDesc)
{
    QVector<QPair<Project, int>> result;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return result;

    QString order = sortDesc ? "DESC" : "ASC";
    QString sql = QString(
        "SELECT p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID, COUNT(g.ID_EMP) AS EMP_COUNT "
        "FROM PROJECTS p LEFT JOIN GERER g ON p.ID_PROJECT = g.ID_PROJECT "
        "GROUP BY p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID "
        "ORDER BY EMP_COUNT %1").arg(order);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "[Project::selectAllWithEmployerCount] ERROR:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        Project p;
        p.projectId = query.value(0).toLongLong();
        p.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
        p.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
        p.title = query.value(3).toString();
        p.description = query.value(4).toString();
        p.creationDate = query.value(5).toDate();
        p.modificationDate = query.value(6).toDate();
        p.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();

        int count = query.value(8).toInt();
        result.append(qMakePair(p, count));
    }

    return result;
}

QVector<Project::ProjectStats> Project::selectProjectStatistics(bool sortByEmployerDesc)
{
    QVector<Project::ProjectStats> result;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return result;

    QString order = sortByEmployerDesc ? "DESC" : "ASC";

    // Use COUNT(DISTINCT ...) to avoid duplicates when joining multiple tables
    QString sql = QString(
        "SELECT p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID, "
        "COUNT(DISTINCT g.ID_EMP) AS EMP_COUNT, COUNT(DISTINCT r.ID_MEDIA) AS RES_COUNT, COUNT(DISTINCT f.ID_SPONSOR) AS SPONSOR_COUNT, NVL(SUM(r.FILE_SIZE),0) AS TOTAL_SIZE "
        "FROM PROJECTS p "
        "LEFT JOIN GERER g ON p.ID_PROJECT = g.ID_PROJECT "
        "LEFT JOIN RESSOURCES r ON p.ID_PROJECT = r.PROJECT_ID "
        "LEFT JOIN FINANCER f ON p.ID_PROJECT = f.ID_PROJECT "
        "GROUP BY p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID "
        "ORDER BY EMP_COUNT %1").arg(order);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "[Project::selectProjectStatistics] ERROR:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        Project::ProjectStats s;
        s.projectId = query.value(0).toLongLong();
        s.title = query.value(3).toString();
        s.creationDate = query.value(5).toDate();

        s.employerCount = query.value(8).toInt();
        s.resourceCount = query.value(9).toInt();
        s.sponsorCount = query.value(10).toInt();
        s.totalResourceSize = query.value(11).toDouble();
        s.ageDays = s.creationDate.daysTo(QDate::currentDate());

        result.append(s);
    }

    return result;
}

QVector<Project::ProjectOnlyStats> Project::selectProjectOnlyStats(const QString &orderBy)
{
    QVector<Project::ProjectOnlyStats> result;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return result;

    QString sql = QString("SELECT ID_PROJECT, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID FROM PROJECTS ORDER BY %1").arg(orderBy);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "[Project::selectProjectOnlyStats] ERROR:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        Project::ProjectOnlyStats s;
        s.projectId = query.value(0).toLongLong();
        s.title = query.value(1).toString();
        s.description = query.value(2).toString();
        s.creationDate = query.value(3).toDate();
        s.modificationDate = query.value(4).toDate();
        s.ownerId = query.value(5).isNull() ? -1 : query.value(5).toLongLong();
        s.ageDays = s.creationDate.daysTo(QDate::currentDate());
        result.append(s);
    }

    return result;
}

QVector<Project> Project::search(const QString &keyword)
{
    qDebug() << "[Project::search] Searching for:" << keyword;
    QVector<Project> projects;

    if (keyword.trimmed().isEmpty()) {
        return selectAll();
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return projects;

    // Escape single quote
    QString kw = keyword;
    kw.replace("'", "''");
    QString sql = QString("SELECT ID_PROJECT, ID_CLIENT, ID_SERVICE, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID "
                          "FROM PROJECTS "
                          "WHERE UPPER(TITLE) LIKE UPPER('%%1%') OR UPPER(DESCRIPTION) LIKE UPPER('%%1%') "
                          "ORDER BY ID_PROJECT DESC").arg(kw);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "[Project::search] ERROR:" << query.lastError().text();
        return projects;
    }

    while (query.next()) {
        Project project;
        project.projectId = query.value(0).toLongLong();
        project.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
        project.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
        project.title = query.value(3).toString();
        project.description = query.value(4).toString();
        project.creationDate = query.value(5).toDate();
        project.modificationDate = query.value(6).toDate();
        project.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();
        projects.append(project);
    }

    qDebug() << "[Project::search] Found" << projects.size() << "matches";
    return projects;
}

bool Project::exportToCsv(const QString &filePath, const QVector<Project> &projects)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "[Project::exportToCsv] Failed to open file:" << filePath;
        return false;
    }

    QTextStream out(&file);
    // Write header
    out << "ID,Title,Description,ClientId,ServiceId,CreationDate,ModificationDate,OwnerId\n";

    for (const Project &p : projects) {
        // simple CSV; escape double quotes
        QString safeTitle = p.title;
        safeTitle.replace("\"", "\"\"");
        safeTitle = "\"" + safeTitle + "\"";

        QString safeDesc = p.description;
        safeDesc.replace("\"", "\"\"");
        safeDesc = "\"" + safeDesc + "\"";

        out << p.projectId << "," << safeTitle << "," << safeDesc << ","
            << (p.clientId > 0 ? QString::number(p.clientId) : QString("")) << ","
            << (p.serviceId > 0 ? QString::number(p.serviceId) : QString("")) << ","
            << p.creationDate.toString("yyyy-MM-dd") << ","
            << p.modificationDate.toString("yyyy-MM-dd") << ","
            << (p.ownerId > 0 ? QString::number(p.ownerId) : QString("")) << "\n";
    }

    file.close();
    qDebug() << "[Project::exportToCsv] Exported" << projects.count() << "projects to" << filePath;
    return true;
}

bool Project::addEmployerToProject(qint64 projectId, qint64 employerId)
{
    qDebug() << "[Project::addEmployerToProject] Adding employer" << employerId << "to project" << projectId;
    
    if (projectId <= 0 || employerId <= 0)
    {
        qDebug() << "[Project::addEmployerToProject] ERROR: Invalid IDs - projectId:" << projectId << "employerId:" << employerId;
        return false;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::addEmployerToProject] ERROR: Database not open";
        return false;
    }
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("INSERT INTO GERER (ID_PROJECT, ID_EMP) VALUES (%1, %2)")
                      .arg(projectId)
                      .arg(employerId);
    
    QSqlQuery query(db);
    
    qDebug() << "[Project::addEmployerToProject] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::addEmployerToProject] ERROR:" << query.lastError().text();
        qDebug() << "[Project::addEmployerToProject] Driver error:" << query.lastError().driverText();
        return false;
    }
    
    qDebug() << "[Project::addEmployerToProject] SUCCESS - Rows affected:" << query.numRowsAffected();
    return true;
}

bool Project::removeEmployerFromProject(qint64 projectId, qint64 employerId)
{
    qDebug() << "[Project::removeEmployerFromProject] Removing employer" << employerId << "from project" << projectId;
    
    if (projectId <= 0 || employerId <= 0)
    {
        qDebug() << "[Project::removeEmployerFromProject] ERROR: Invalid IDs - projectId:" << projectId << "employerId:" << employerId;
        return false;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::removeEmployerFromProject] ERROR: Database not open";
        return false;
    }
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("DELETE FROM GERER WHERE ID_PROJECT = %1 AND ID_EMP = %2")
                      .arg(projectId)
                      .arg(employerId);
    
    QSqlQuery query(db);
    
    qDebug() << "[Project::removeEmployerFromProject] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::removeEmployerFromProject] ERROR:" << query.lastError().text();
        qDebug() << "[Project::removeEmployerFromProject] Driver error:" << query.lastError().driverText();
        return false;
    }
    
    qDebug() << "[Project::removeEmployerFromProject] SUCCESS - Rows affected:" << query.numRowsAffected();
    return true;
}

bool Project::removeAllEmployersFromProject(qint64 projectId)
{
    qDebug() << "[Project::removeAllEmployersFromProject] Removing all employers from project" << projectId;
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::removeAllEmployersFromProject] ERROR: Database not open";
        return false;
    }
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("DELETE FROM GERER WHERE ID_PROJECT = %1").arg(projectId);
    QSqlQuery query(db);
    
    qDebug() << "[Project::removeAllEmployersFromProject] Executing:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::removeAllEmployersFromProject] ERROR:" << query.lastError().text();
        qDebug() << "[Project::removeAllEmployersFromProject] Driver error:" << query.lastError().driverText();
        return false;
    }
    
    int rowsAffected = query.numRowsAffected();
    qDebug() << "[Project::removeAllEmployersFromProject] SUCCESS - Rows affected:" << rowsAffected;
    return true;
}

QVector<Project> Project::getProjectsByEmployer(qint64 employerId)
{
    qDebug() << "[Project::getProjectsByEmployer] Fetching projects for employer" << employerId;
    
    QVector<Project> projects;
    
    if (employerId <= 0)
    {
        qDebug() << "[Project::getProjectsByEmployer] ERROR: Invalid employer ID";
        return projects;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::getProjectsByEmployer] ERROR: Database not open";
        return projects;
    }
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    // Qualify all columns to avoid "column ambiguously defined" error
    QString sql = QString("SELECT p.ID_PROJECT, p.ID_CLIENT, p.ID_SERVICE, p.TITLE, p.DESCRIPTION, "
                          "p.CREATION_DATE, p.MODIFICATION_DATE, p.OWNER_ID "
                          "FROM PROJECTS p "
                          "INNER JOIN GERER g ON p.ID_PROJECT = g.ID_PROJECT "
                          "WHERE g.ID_EMP = %1").arg(employerId);
    
    QSqlQuery query(db);
    
    qDebug() << "[Project::getProjectsByEmployer] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::getProjectsByEmployer] ERROR:" << query.lastError().text();
        qDebug() << "[Project::getProjectsByEmployer] Driver error:" << query.lastError().driverText();
        return projects;
    }
    
    while (query.next())
    {
        Project project;
        project.projectId = query.value(0).toLongLong();
        project.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
        project.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
        project.title = query.value(3).toString();
        project.description = query.value(4).toString();
        project.creationDate = query.value(5).toDate();
        project.modificationDate = query.value(6).toDate();
        project.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();
        
        projects.append(project);
    }
    
    qDebug() << "[Project::getProjectsByEmployer] Found" << projects.size() << "projects";
    return projects;
}

QVector<qint64> Project::getEmployersByProject(qint64 projectId)
{
    qDebug() << "[Project::getEmployersByProject] Fetching employers for project" << projectId;
    
    QVector<qint64> employerIds;
    
    if (projectId <= 0)
    {
        qDebug() << "[Project::getEmployersByProject] ERROR: Invalid project ID";
        return employerIds;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::getEmployersByProject] ERROR: Database not open";
        return employerIds;
    }
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("SELECT ID_EMP FROM GERER WHERE ID_PROJECT = %1").arg(projectId);
    QSqlQuery query(db);
    
    qDebug() << "[Project::getEmployersByProject] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::getEmployersByProject] ERROR:" << query.lastError().text();
        qDebug() << "[Project::getEmployersByProject] Driver error:" << query.lastError().driverText();
        return employerIds;
    }
    
    while (query.next())
    {
        employerIds.append(query.value(0).toLongLong());
    }
    
    qDebug() << "[Project::getEmployersByProject] Found" << employerIds.size() << "employers";
    return employerIds;
}

bool Project::fetchById(qint64 projectId, Project &project)
{
    qDebug() << "[Project::fetchById] Fetching project ID:" << projectId;
    
    if (projectId <= 0)
    {
        qDebug() << "[Project::fetchById] ERROR: Invalid project ID";
        return false;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[Project::fetchById] ERROR: Database not open";
        return false;
    }
    
    // Use direct SQL string instead of bind values (QODBC compatibility)
    QString sql = QString("SELECT ID_PROJECT, ID_CLIENT, ID_SERVICE, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID "
                          "FROM PROJECTS WHERE ID_PROJECT = %1").arg(projectId);
    QSqlQuery query(db);
    
    qDebug() << "[Project::fetchById] SQL:" << sql;
    
    if (!query.exec(sql))
    {
        qDebug() << "[Project::fetchById] ERROR executing query:" << query.lastError().text();
        qDebug() << "[Project::fetchById] Driver error:" << query.lastError().driverText();
        return false;
    }
    
    if (!query.next())
    {
        qDebug() << "[Project::fetchById] Project not found with ID:" << projectId;
        return false;
    }
    
    // Initialize project object first
    project = Project();
    
    // Safely extract all values
    project.projectId = query.value(0).toLongLong();
    qDebug() << "[Project::fetchById] projectId:" << project.projectId;
    
    project.clientId = query.value(1).isNull() ? -1 : query.value(1).toLongLong();
    qDebug() << "[Project::fetchById] clientId:" << project.clientId;
    
    project.serviceId = query.value(2).isNull() ? -1 : query.value(2).toLongLong();
    qDebug() << "[Project::fetchById] serviceId:" << project.serviceId;
    
    project.title = query.value(3).toString();
    qDebug() << "[Project::fetchById] title:" << project.title;
    
    project.description = query.value(4).toString();
    qDebug() << "[Project::fetchById] description:" << project.description;
    
    QVariant creationDateVar = query.value(5);
    if (creationDateVar.isNull())
    {
        qDebug() << "[Project::fetchById] WARNING: creationDate is NULL, using today";
        project.creationDate = QDate::currentDate();
    }
    else
    {
        project.creationDate = creationDateVar.toDate();
        qDebug() << "[Project::fetchById] creationDate:" << project.creationDate;
    }
    
    QVariant modificationDateVar = query.value(6);
    if (modificationDateVar.isNull())
    {
        qDebug() << "[Project::fetchById] WARNING: modificationDate is NULL, using today";
        project.modificationDate = QDate::currentDate();
    }
    else
    {
        project.modificationDate = modificationDateVar.toDate();
        qDebug() << "[Project::fetchById] modificationDate:" << project.modificationDate;
    }
    
    project.ownerId = query.value(7).isNull() ? -1 : query.value(7).toLongLong();
    qDebug() << "[Project::fetchById] ownerId:" << project.ownerId;
    
    qDebug() << "[Project::fetchById] SUCCESS - Project:" << project.title;
    return true;
}
