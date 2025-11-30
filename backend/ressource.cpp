#include "ressource.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QRegularExpression>

Ressource::Ressource() : idMedia(0), uploadDate(QDateTime::currentDateTime()) {}

Ressource::Ressource(qint64 idMedia, const QString &title, const QString &path,
                     const QString &owner, const QString &format, 
                     const QString &accessLevel, const QDateTime &uploadDate)
    : idMedia(idMedia), title(title), path(path), owner(owner), 
      format(format), accessLevel(accessLevel), uploadDate(uploadDate) {}

bool Ressource::isTitleValid(const QString &title, QString &errorMsg)
{
    if (title.trimmed().isEmpty()) {
        errorMsg = "Title cannot be empty";
        return false;
    }

    QRegularExpression specialCharsRegex("[\\@\\;\\!\\/\\\\\\#\\$\\%\\^\\&\\*\\(\\)\\?\\<\\>\\,\\.\\\"\\'\\'\\{\\}\\[\\]\\|\\~]");
    
    if (specialCharsRegex.match(title).hasMatch()) {
        errorMsg = "Title contains forbidden special characters: @ ; ! / \\\\ # $ % ^ & * ( ) ? < > , . \" ' { } [ ] | ~";
        return false;
    }

    errorMsg = "";
    return true;
}

bool Ressource::isTitleUnique(const QString &title, qint64 excludeId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for title uniqueness check";
        return false;
    }

    QString escapedTitle = title;
    escapedTitle.replace("'", "''");
    
    QString sql;
    
    if (excludeId >= 0) {
        sql = "SELECT COUNT(*) FROM RESSOURCE WHERE UPPER(TITLE) = UPPER('" + escapedTitle + "') AND ID != " + QString::number(excludeId);
    } else {
        sql = "SELECT COUNT(*) FROM RESSOURCE WHERE UPPER(TITLE) = UPPER('" + escapedTitle + "')";
    }

    QSqlQuery query(db);

    qDebug() << "[isTitleUnique] Executing:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to execute title uniqueness check:" << query.lastError().text();
        qDebug() << "Driver error:" << query.lastError().driverText();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
bool isUnique = (count == 0);
        qDebug() << "Title uniqueness check result: count=" << count << ", isUnique=" << isUnique;
        return isUnique;
    }

    return false;
}

bool Ressource::insert(const Ressource &ressource)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for insert";
        return false;
    }

    QString errorMsg;
    if (!isTitleValid(ressource.title, errorMsg)) {
        qDebug() << "❌ Title validation failed:" << errorMsg;
        return false;
    }

    if (!isTitleUnique(ressource.title)) {
        qDebug() << "❌ Duplicate title detected:" << ressource.title;
        return false;
    }

    QString escapedTitle = ressource.title;
    escapedTitle.replace("'", "''");
    QString escapedPath = ressource.path;
    escapedPath.replace("'", "''");
    QString escapedOwner = ressource.owner;
    escapedOwner.replace("'", "''");
    QString escapedFormat = ressource.format;
    escapedFormat.replace("'", "''");
    QString escapedAccess = ressource.accessLevel.isEmpty() ? QString("Public") : ressource.accessLevel;
    escapedAccess.replace("'", "''");

    QString sql = QString("INSERT INTO RESSOURCE (ID, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE) "
                          "VALUES (SEQ_RESSOURCE.NEXTVAL, '%1', '%2', '%3', '%4', '%5', SYSDATE)")
                      .arg(escapedTitle, escapedPath, escapedOwner, escapedFormat, escapedAccess);

    QSqlQuery query(db);

    qDebug() << "========================================";
    qDebug() << "[Ressource::insert] Attempting insertion...";
    qDebug() << "  Title:" << ressource.title;
    qDebug() << "  Path:" << ressource.path;
    qDebug() << "  Owner:" << ressource.owner;
    qDebug() << "  Format:" << ressource.format;
    qDebug() << "  Access:" << (ressource.accessLevel.isEmpty() ? QString("Public") : ressource.accessLevel);
    qDebug() << "  SQL:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ INSERTION FAILED";
        qDebug() << "Error:" << query.lastError().text();
        qDebug() << "Driver error:" << query.lastError().driverText();
        qDebug() << "DB error:" << query.lastError().databaseText();
        qDebug() << "========================================";
        return false;
    }

    qDebug() << "✅ Ressource insérée avec succès:" << ressource.title;
    qDebug() << "========================================";
    return true;
}

QVector<Ressource> Ressource::selectAll()
{
    QVector<Ressource> records;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for selectAll";
        return records;
    }

    QString sql = "SELECT ID, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE "
                  "FROM RESSOURCE ORDER BY ID";
    
    QSqlQuery query(db);
    
    qDebug() << "========================================";
    qDebug() << "[Ressource::selectAll] Executing SQL:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to execute selectAll query";
        qDebug() << "Error Text:" << query.lastError().text();
        qDebug() << "Driver Error:" << query.lastError().driverText();
        qDebug() << "Database Error:" << query.lastError().databaseText();
        qDebug() << "========================================";
        return records;
    }

    qDebug() << "[Ressource::selectAll] Fetching resources...";
    
    while (query.next()) {
        Ressource record;
        record.idMedia = query.value(0).toLongLong();
        record.title = query.value(1).toString();
        record.path = query.value(2).toString();
        record.owner = query.value(3).toString();
        record.format = query.value(4).toString();
        record.accessLevel = query.value(5).toString();
        record.uploadDate = query.value(6).toDateTime();
        records.append(record);
        
        qDebug() << "  Resource:" << record.idMedia << record.title;
    }

    qDebug() << "✅ selectAll() returned" << records.size() << "records";
    qDebug() << "========================================";
    return records;
}

bool Ressource::update(const Ressource &ressource)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for update";
        return false;
    }

    QString errorMsg;
    if (!isTitleValid(ressource.title, errorMsg)) {
        qDebug() << "❌ Title validation failed:" << errorMsg;
        return false;
    }

    if (!isTitleUnique(ressource.title, ressource.idMedia)) {
        qDebug() << "❌ Duplicate title detected:" << ressource.title;
        return false;
    }

    QString escapedTitle = ressource.title;
    escapedTitle.replace("'", "''");
    QString escapedPath = ressource.path;
    escapedPath.replace("'", "''");
    QString escapedOwner = ressource.owner;
    escapedOwner.replace("'", "''");
    QString escapedFormat = ressource.format;
    escapedFormat.replace("'", "''");
    QString escapedAccess = ressource.accessLevel;
    escapedAccess.replace("'", "''");

    QString sql = QString("UPDATE RESSOURCE SET TITLE = '%1', PATH = '%2', OWNER = '%3', "
                          "FORMAT = '%4', ACCESS_LEVEL = '%5' WHERE ID = %6")
                      .arg(escapedTitle, escapedPath, escapedOwner, escapedFormat, escapedAccess)
                      .arg(ressource.idMedia);

    QSqlQuery query(db);

    qDebug() << "========================================";
    qDebug() << "[Ressource::update] Updating resource ID:" << ressource.idMedia;
    qDebug() << "  New Title:" << ressource.title;
    qDebug() << "  SQL:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ UPDATE FAILED";
        qDebug() << "Error:" << query.lastError().text();
        qDebug() << "Driver error:" << query.lastError().driverText();
        qDebug() << "DB error:" << query.lastError().databaseText();
        qDebug() << "========================================";
        return false;
    }

    qDebug() << "✅ Ressource mise à jour avec succès, ID:" << ressource.idMedia;
    qDebug() << "========================================";
    return true;
}

bool Ressource::remove(qint64 id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for remove";
        return false;
    }

    qDebug() << "========================================";
    qDebug() << "[Ressource::remove] Attempting to delete resource with ID:" << id;

    qDebug() << "[Ressource::remove] Clearing all references in UTILISER table...";
    if (!clearAllReferencesForResource(id)) {
        qDebug() << "[Ressource::remove] WARNING: Failed to clear references, continuing...";
    }

    QString sql = QString("DELETE FROM RESSOURCE WHERE ID = %1").arg(id);
    QSqlQuery query(db);

    qDebug() << "Executing DELETE SQL:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ DELETE FAILED";
        qDebug() << "Error:" << query.lastError().text();
        qDebug() << "Database error:" << query.lastError().databaseText();
        qDebug() << "Driver error:" << query.lastError().driverText();
        qDebug() << "========================================";
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "✅ Ressource supprimée avec succès, ID:" << id;
    qDebug() << "Rows affected:" << rowsAffected;
    qDebug() << "========================================";
    return true;
}

bool Ressource::clearAllReferencesForResource(qint64 resourceId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for clearAllReferencesForResource";
        return false;
    }

    qDebug() << "[Ressource::clearAllReferencesForResource] Clearing all references for resource ID:" << resourceId;

    QString sql = QString("DELETE FROM UTILISER WHERE ID_MEDIA = %1").arg(resourceId);
    QSqlQuery query(db);

    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to clear references for resource" << resourceId;
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "✅ All references cleared for resource" << resourceId << "- Rows affected:" << rowsAffected;
    return true;
}

bool Ressource::fetchById(qint64 id, Ressource &ressource)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for fetchById";
        return false;
    }

    QString sql = QString("SELECT ID, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE "
                          "FROM RESSOURCE WHERE ID = %1").arg(id);
    
    QSqlQuery query(db);

    qDebug() << "[Ressource::fetchById] Executing:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to execute fetchById query:" << query.lastError().text();
        qDebug() << "Driver error:" << query.lastError().driverText();
        qDebug() << "DB error:" << query.lastError().databaseText();
        return false;
    }

    if (query.next()) {
        ressource.idMedia = query.value(0).toLongLong();
        ressource.title = query.value(1).toString();
        ressource.path = query.value(2).toString();
        ressource.owner = query.value(3).toString();
        ressource.format = query.value(4).toString();
        ressource.accessLevel = query.value(5).toString();
        ressource.uploadDate = query.value(6).toDateTime();
        
        qDebug() << "✅ fetchById() found resource with ID:" << id;
        return true;
    }

    qDebug() << "❌ fetchById() resource not found with ID:" << id;
    return false;
}

QSqlQueryModel* Ressource::displayAll()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE FROM RESSOURCE ORDER BY ID", QSqlDatabase::database());

    if (model->lastError().isValid()) {
        qDebug() << "❌ displayAll() model error:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Path"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Owner"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Format"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Access"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Upload Date"));

    qDebug() << "✅ displayAll() model created successfully";
    return model;
}

QSqlQueryModel* Ressource::search(const QString &keyword)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString searchQuery = QString(
        "SELECT ID, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE FROM RESSOURCE "
        "WHERE UPPER(TITLE) LIKE UPPER('%%1%') "
        "OR UPPER(OWNER) LIKE UPPER('%%1%') "
        "OR UPPER(FORMAT) LIKE UPPER('%%1%')").arg(keyword);

    model->setQuery(searchQuery, QSqlDatabase::database());

    if (model->lastError().isValid()) {
        qDebug() << "❌ search() model error:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Path"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Owner"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Format"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Access"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Upload Date"));

    qDebug() << "✅ search() found results for keyword:" << keyword;
    return model;
}

QSqlQueryModel* Ressource::sortBy(const QString &columnName, Qt::SortOrder order)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString orderStr = (order == Qt::AscendingOrder) ? "ASC" : "DESC";
    QString sortQuery = QString(
        "SELECT ID, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE FROM RESSOURCE ORDER BY %1 %2")
        .arg(columnName, orderStr);

    model->setQuery(sortQuery, QSqlDatabase::database());

    if (model->lastError().isValid()) {
        qDebug() << "❌ sortBy() model error:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Path"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Owner"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Format"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Access"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Upload Date"));

    qDebug() << "✅ sortBy() sorted by:" << columnName;
    return model;
}

bool Ressource::exportToCsv(const QString &filePath)
{
    qDebug() << "ℹ️  exportToCsv() - Not yet implemented";
    Q_UNUSED(filePath);
    return false;
}

QVector<Ressource> Ressource::getResourcesByEmployer(qint64 employerId)
{
    QVector<Ressource> resources;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for getResourcesByEmployer";
        return resources;
    }

    QString sql = QString("SELECT r.ID, r.TITLE, r.PATH, r.OWNER, r.FORMAT, r.ACCESS_LEVEL, r.UPLOAD_DATE "
                         "FROM RESSOURCE r "
                         "INNER JOIN UTILISER u ON r.ID = u.ID_MEDIA "
                         "WHERE u.ID_EMP = %1 "
                         "ORDER BY r.TITLE").arg(employerId);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to get resources for employer" << employerId;
        qDebug() << "Error:" << query.lastError().text();
        return resources;
    }

    while (query.next()) {
        Ressource r;
        r.idMedia = query.value(0).toLongLong();
        r.title = query.value(1).toString();
        r.path = query.value(2).toString();
        r.owner = query.value(3).toString();
        r.format = query.value(4).toString();
        r.accessLevel = query.value(5).toString();
        r.uploadDate = query.value(6).toDateTime();
        resources.append(r);
    }

    qDebug() << "✅ Found" << resources.count() << "resources for employer" << employerId;
    return resources;
}

bool Ressource::addResourceToEmployer(qint64 employerId, qint64 resourceId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for addResourceToEmployer";
        return false;
    }

    QString checkSql = QString("SELECT COUNT(*) FROM UTILISER WHERE ID_EMP = %1 AND ID_MEDIA = %2")
                      .arg(employerId).arg(resourceId);
    QSqlQuery checkQuery(db);
    if (checkQuery.exec(checkSql) && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            qDebug() << "ℹ️  Resource" << resourceId << "already assigned to employer" << employerId;
return true;
        }
    }

    QString sql = QString("INSERT INTO UTILISER (ID_EMP, ID_MEDIA) VALUES (%1, %2)")
                      .arg(employerId).arg(resourceId);    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to add resource" << resourceId << "to employer" << employerId;
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Resource" << resourceId << "added to employer" << employerId;
    return true;
}

bool Ressource::removeResourceFromEmployer(qint64 employerId, qint64 resourceId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for removeResourceFromEmployer";
        return false;
    }

    QString sql = QString("DELETE FROM UTILISER WHERE ID_EMP = %1 AND ID_MEDIA = %2")
                      .arg(employerId).arg(resourceId);    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to remove resource" << resourceId << "from employer" << employerId;
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Resource" << resourceId << "removed from employer" << employerId;
    return true;
}

bool Ressource::clearEmployerResources(qint64 employerId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for clearEmployerResources";
        return false;
    }

    QString sql = QString("DELETE FROM UTILISER WHERE ID_EMP = %1").arg(employerId);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "❌ Failed to clear resources for employer" << employerId;
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ All resources cleared for employer" << employerId;
    return true;
}

RessourceStatistics Ressource::computeStatistics()
{
    RessourceStatistics stats;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Total resources
    if (query.exec("SELECT COUNT(*) FROM RESSOURCE") && query.next()) {
        stats.totalResources = query.value(0).toInt();
    }

    // Public vs Private resources
    if (query.exec("SELECT COUNT(*) FROM RESSOURCE WHERE UPPER(ACCESS) = 'PUBLIC'") && query.next()) {
        stats.publicResources = query.value(0).toInt();
    }
    
    if (query.exec("SELECT COUNT(*) FROM RESSOURCE WHERE UPPER(ACCESS) = 'PRIVATE'") && query.next()) {
        stats.privateResources = query.value(0).toInt();
    }

    // Format distribution
    if (query.exec("SELECT FORMAT, COUNT(*) FROM RESSOURCE GROUP BY FORMAT")) {
        while (query.next()) {
            QString format = query.value(0).toString();
            int count = query.value(1).toInt();
            if (!format.isEmpty()) {
                stats.formatDistribution[format.toUpper()] = count;
            }
        }
        stats.totalFormats = stats.formatDistribution.size();
    }

    // Owner distribution
    if (query.exec("SELECT OWNER, COUNT(*) FROM RESSOURCE GROUP BY OWNER")) {
        while (query.next()) {
            QString owner = query.value(0).toString();
            int count = query.value(1).toInt();
            if (!owner.isEmpty()) {
                stats.ownerDistribution[owner] = count;
            }
        }
        stats.totalOwners = stats.ownerDistribution.size();
    }

    // Access level distribution
    if (query.exec("SELECT ACCESS, COUNT(*) FROM RESSOURCE GROUP BY ACCESS")) {
        while (query.next()) {
            QString access = query.value(0).toString();
            int count = query.value(1).toInt();
            stats.accessLevelDistribution[access] = count;
        }
    }

    // Uploads per year
    QString driver = db.driverName().toLower();
    if (driver.contains("sqlite")) {
        if (query.exec("SELECT strftime('%Y', UPLOAD_DATE) AS yr, COUNT(*) FROM RESSOURCE GROUP BY yr ORDER BY yr DESC")) {
            while (query.next()) {
                QString yearStr = query.value(0).toString();
                int count = query.value(1).toInt();
                if (!yearStr.isEmpty()) stats.uploadsPerYear[yearStr.toInt()] = count;
            }
        }
    } else {
        // Oracle-style queries
        if (query.exec("SELECT EXTRACT(YEAR FROM UPLOAD_DATE) AS yr, COUNT(*) FROM RESSOURCE GROUP BY EXTRACT(YEAR FROM UPLOAD_DATE) ORDER BY yr DESC")) {
            while (query.next()) {
                int year = query.value(0).toInt();
                int count = query.value(1).toInt();
                if (year > 0) stats.uploadsPerYear[year] = count;
            }
        } else if (query.exec("SELECT TO_CHAR(UPLOAD_DATE,'YYYY') AS yr, COUNT(*) FROM RESSOURCE GROUP BY TO_CHAR(UPLOAD_DATE,'YYYY') ORDER BY yr DESC")) {
            while (query.next()) {
                QString yearStr = query.value(0).toString();
                int count = query.value(1).toInt();
                if (!yearStr.isEmpty()) stats.uploadsPerYear[yearStr.toInt()] = count;
            }
        }
    }

    // Uploads per month (current year)
    QDate now = QDate::currentDate();
    QString yearStr = QString::number(now.year());
    
    if (driver.contains("sqlite")) {
        QString monthQuery = QString("SELECT strftime('%%m', UPLOAD_DATE) AS mn, COUNT(*) FROM RESSOURCE WHERE strftime('%%Y', UPLOAD_DATE) = '%1' GROUP BY mn ORDER BY mn").arg(yearStr);
        if (query.exec(monthQuery)) {
            while (query.next()) {
                QString monthStr = query.value(0).toString();
                int count = query.value(1).toInt();
                if (!monthStr.isEmpty()) stats.uploadsPerMonth[monthStr.toInt()] = count;
            }
        }
    } else {
        QString monthQuery = QString("SELECT EXTRACT(MONTH FROM UPLOAD_DATE) AS mn, COUNT(*) FROM RESSOURCE WHERE EXTRACT(YEAR FROM UPLOAD_DATE) = %1 GROUP BY EXTRACT(MONTH FROM UPLOAD_DATE) ORDER BY mn").arg(yearStr);
        if (query.exec(monthQuery)) {
            while (query.next()) {
                int month = query.value(0).toInt();
                int count = query.value(1).toInt();
                if (month > 0) stats.uploadsPerMonth[month] = count;
            }
        } else {
            monthQuery = QString("SELECT TO_CHAR(UPLOAD_DATE,'MM') AS mn, COUNT(*) FROM RESSOURCE WHERE TO_CHAR(UPLOAD_DATE,'YYYY') = '%1' GROUP BY TO_CHAR(UPLOAD_DATE,'MM') ORDER BY mn").arg(yearStr);
            if (query.exec(monthQuery)) {
                while (query.next()) {
                    QString monthStr = query.value(0).toString();
                    int count = query.value(1).toInt();
                    if (!monthStr.isEmpty()) stats.uploadsPerMonth[monthStr.toInt()] = count;
                }
            }
        }
    }

    // New resources this year & month
    QString monthStr = QString("%1").arg(now.month(), 2, 10, QChar('0'));
    if (driver.contains("sqlite")) {
        QString q1 = QString("SELECT COUNT(*) FROM RESSOURCE WHERE strftime('%%Y', UPLOAD_DATE) = '%1'").arg(yearStr);
        if (query.exec(q1) && query.next()) stats.newResourcesThisYear = query.value(0).toInt();

        QString q2 = QString("SELECT COUNT(*) FROM RESSOURCE WHERE strftime('%%Y', UPLOAD_DATE) = '%1' AND strftime('%%m', UPLOAD_DATE) = '%2'")
                         .arg(yearStr).arg(monthStr);
        if (query.exec(q2) && query.next()) stats.newResourcesThisMonth = query.value(0).toInt();
    } else {
        QString q1 = QString("SELECT COUNT(*) FROM RESSOURCE WHERE TO_CHAR(UPLOAD_DATE,'YYYY') = '%1'").arg(yearStr);
        if (!query.exec(q1)) {
            q1 = QString("SELECT COUNT(*) FROM RESSOURCE WHERE EXTRACT(YEAR FROM UPLOAD_DATE) = %1").arg(yearStr);
        }
        if (query.exec(q1) && query.next()) stats.newResourcesThisYear = query.value(0).toInt();

        QString q2 = QString("SELECT COUNT(*) FROM RESSOURCE WHERE TO_CHAR(UPLOAD_DATE,'YYYY') = '%1' AND TO_CHAR(UPLOAD_DATE,'MM') = '%2'")
                         .arg(yearStr).arg(monthStr);
        if (!query.exec(q2)) {
            q2 = QString("SELECT COUNT(*) FROM RESSOURCE WHERE EXTRACT(YEAR FROM UPLOAD_DATE) = %1 AND EXTRACT(MONTH FROM UPLOAD_DATE) = %2").arg(yearStr).arg(now.month());
        }
        if (query.exec(q2) && query.next()) stats.newResourcesThisMonth = query.value(0).toInt();
    }

    // Most common format
    if (!stats.formatDistribution.isEmpty()) {
        int best = -1;
        for (auto it = stats.formatDistribution.constBegin(); it != stats.formatDistribution.constEnd(); ++it) {
            if (it.value() > best) {
                best = it.value();
                stats.mostCommonFormat = it.key();
            }
        }
    }

    // Most active owner
    if (!stats.ownerDistribution.isEmpty()) {
        int best = -1;
        for (auto it = stats.ownerDistribution.constBegin(); it != stats.ownerDistribution.constEnd(); ++it) {
            if (it.value() > best) {
                best = it.value();
                stats.mostActiveOwner = it.key();
            }
        }
    }

    return stats;
}
