#include "ressource.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QRegularExpression>

// ========================================
// CONSTRUCTORS
// ========================================

Ressource::Ressource() : idMedia(0), uploadDate(QDateTime::currentDateTime()) {}

Ressource::Ressource(qint64 idMedia, const QString &title, const QString &path,
                     const QString &owner, const QString &format, 
                     const QString &accessLevel, const QDateTime &uploadDate)
    : idMedia(idMedia), title(title), path(path), owner(owner), 
      format(format), accessLevel(accessLevel), uploadDate(uploadDate) {}

// ========================================
// VALIDATION METHODS
// ========================================

bool Ressource::isTitleValid(const QString &title, QString &errorMsg)
{
    // Check if title is empty
    if (title.trimmed().isEmpty()) {
        errorMsg = "Title cannot be empty";
        return false;
    }

    // Special characters forbidden: @ ; ! / \ # $ % ^ & * ( ) ? < > , . " ' { } [ ] | ~
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

    // Use direct SQL string instead of bind values (QODBC compatibility issue)
    // Escape single quotes in text values
    QString escapedTitle = title;
    escapedTitle.replace("'", "''");
    
    QString sql;
    
    // If we're updating, exclude the current record's ID_MEDIA
    if (excludeId >= 0) {
        sql = "SELECT COUNT(*) FROM RESSOURCES WHERE UPPER(TITLE) = UPPER('" + escapedTitle + "') AND ID_MEDIA != " + QString::number(excludeId);
    } else {
        sql = "SELECT COUNT(*) FROM RESSOURCES WHERE UPPER(TITLE) = UPPER('" + escapedTitle + "')";
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
        bool isUnique = (count == 0); // Title is unique if count is 0
        qDebug() << "Title uniqueness check result: count=" << count << ", isUnique=" << isUnique;
        return isUnique;
    }

    return false;
}

// ========================================
// CRUD OPERATIONS
// ========================================

bool Ressource::insert(const Ressource &ressource)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for insert";
        return false;
    }

    //  VALIDATION 1: Check title validity (no special characters)
    QString errorMsg;
    if (!isTitleValid(ressource.title, errorMsg)) {
        qDebug() << "❌ Title validation failed:" << errorMsg;
        return false;
    }

    //  VALIDATION 2: Check title uniqueness
    if (!isTitleUnique(ressource.title)) {
        qDebug() << "❌ Duplicate title detected:" << ressource.title;
        return false;
    }

    // Use direct SQL string instead of bind values (QODBC compatibility issue)
    // Escape single quotes in text values
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

    // Oracle 11g XE - Use SEQ_RESSOURCES.NEXTVAL for ID_MEDIA
    QString sql = QString("INSERT INTO RESSOURCES (ID_MEDIA, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE) "
                          "VALUES (SEQ_RESSOURCES.NEXTVAL, '%1', '%2', '%3', '%4', '%5', SYSDATE)")
                      .arg(escapedTitle, escapedPath, escapedOwner, escapedFormat, escapedAccess);

    QSqlQuery query(db);

    // DEBUG: Print what we're inserting
    qDebug() << "========================================";
    qDebug() << "[Ressource::insert] Attempting insertion...";
    qDebug() << "  Title:" << ressource.title;
    qDebug() << "  Path:" << ressource.path;
    qDebug() << "  Owner:" << ressource.owner;
    qDebug() << "  Format:" << ressource.format;
    qDebug() << "  Access:" << (ressource.accessLevel.isEmpty() ? QString("Public") : ressource.accessLevel);
    qDebug() << "  SQL:" << sql;

    // Execute insert
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

    QString sql = "SELECT ID_MEDIA, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE "
                  "FROM RESSOURCES ORDER BY ID_MEDIA";
    
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

    //  VALIDATION 1: Check title validity
    QString errorMsg;
    if (!isTitleValid(ressource.title, errorMsg)) {
        qDebug() << "❌ Title validation failed:" << errorMsg;
        return false;
    }

    //  VALIDATION 2: Check title uniqueness (exclude current record)
    if (!isTitleUnique(ressource.title, ressource.idMedia)) {
        qDebug() << "❌ Duplicate title detected:" << ressource.title;
        return false;
    }

    // Use direct SQL string instead of bind values (QODBC compatibility issue)
    // Escape single quotes in text values
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

    QString sql = QString("UPDATE RESSOURCES SET TITLE = '%1', PATH = '%2', OWNER = '%3', "
                          "FORMAT = '%4', ACCESS_LEVEL = '%5' WHERE ID_MEDIA = %6")
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
    qDebug() << "[Ressource::remove] Attempting to delete resource with ID_MEDIA:" << id;

    // Use direct SQL string instead of bind values (QODBC compatibility issue)
    QString sql = QString("DELETE FROM RESSOURCES WHERE ID_MEDIA = %1").arg(id);
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
    qDebug() << "✅ Ressource supprimée avec succès, ID_MEDIA:" << id;
    qDebug() << "Rows affected:" << rowsAffected;
    qDebug() << "========================================";
    return true;
}

bool Ressource::fetchById(qint64 id, Ressource &ressource)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Database not open for fetchById";
        return false;
    }

    // Use direct SQL string instead of bind values (QODBC compatibility issue)
    QString sql = QString("SELECT ID_MEDIA, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE "
                          "FROM RESSOURCES WHERE ID_MEDIA = %1").arg(id);
    
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
        
        qDebug() << "✅ fetchById() found resource with ID_MEDIA:" << id;
        return true;
    }

    qDebug() << "❌ fetchById() resource not found with ID_MEDIA:" << id;
    return false;
}

// ========================================
// DISPLAY & QUERY METHODS
// ========================================

QSqlQueryModel* Ressource::displayAll()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_MEDIA, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE FROM RESSOURCES ORDER BY ID_MEDIA", QSqlDatabase::database());

    if (model->lastError().isValid()) {
        qDebug() << "❌ displayAll() model error:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    // Set proper header labels
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
        "SELECT ID_MEDIA, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE FROM RESSOURCES "
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
        "SELECT ID_MEDIA, TITLE, PATH, OWNER, FORMAT, ACCESS_LEVEL, UPLOAD_DATE FROM RESSOURCES ORDER BY %1 %2")
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
