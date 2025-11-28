#include "sponsor.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

bool Sponsor::insert(const Sponsor &sponsor)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    // Get next ID using MAX() + 1
    QSqlQuery queryId(db);
    if (!queryId.exec("SELECT NVL(MAX(ID_SPONSOR), 0) + 1 FROM SPONSORS")) {
        qDebug() << "[Sponsor::insert] Failed to get next ID:" << queryId.lastError().text();
        return false;
    }
    
    qint64 nextId = 1;
    if (queryId.next()) {
        nextId = queryId.value(0).toLongLong();
    }
    
    // Prepare INSERT query - Use correct Oracle column names
    QString queryStr = QString(
        "INSERT INTO SPONSORS (ID_SPONSOR, NAME, EMAIL, DATE_DEBUT, DATE_FIN, STATUS, LAST_UPDATE) "
        "VALUES (%1, :name, :email, :date_debut, :date_fin, :status, SYSDATE)").arg(nextId);
    
    QSqlQuery query(db);
    query.prepare(queryStr);
    
    query.bindValue(":name", sponsor.name);
    query.bindValue(":email", sponsor.email);
    query.bindValue(":date_debut", sponsor.dateDebut);
    query.bindValue(":date_fin", sponsor.dateFin);
    query.bindValue(":status", sponsor.status);
    
    if (!db.transaction()) {
        qDebug() << "[Sponsor::insert] Failed to start transaction";
        return false;
    }
    
    if (!query.exec()) {
        qDebug() << "[Sponsor::insert] Insert failed:" << query.lastError().text();
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        qDebug() << "[Sponsor::insert] Failed to commit transaction";
        db.rollback();
        return false;
    }
    
    qDebug() << "[Sponsor::insert] SUCCESS - Sponsor inserted with ID:" << nextId;
    return true;
}

QVector<Sponsor> Sponsor::selectAll()
{
    QVector<Sponsor> records;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = "SELECT ID_SPONSOR, NAME, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
                       "FROM SPONSORS ORDER BY ID_SPONSOR";
    
    if (!query.exec(queryStr)) {
        qDebug() << "[Sponsor::selectAll] Failed:" << query.lastError().text();
        return records;
    }
    
    while (query.next()) {
        Sponsor record;
        record.sponsorId = query.value(0).toLongLong();
        record.name = query.value(1).toString();
        record.email = query.value(2).toString();
        record.dateDebut = query.value(3).toDate();
        record.dateFin = query.value(4).toDate();
        record.status = query.value(5).toString();
        records.append(record);
    }
    
    qDebug() << "[Sponsor::selectAll] Retrieved" << records.size() << "sponsors";
    return records;
}

bool Sponsor::fetchById(qint64 id, Sponsor &sponsor)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = QString(
        "SELECT ID_SPONSOR, NAME, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
        "FROM SPONSORS WHERE ID_SPONSOR = %1").arg(id);
    
    if (!query.exec(queryStr)) {
        qDebug() << "[Sponsor::fetchById] Failed:" << query.lastError().text();
        return false;
    }
    
    if (query.next()) {
        sponsor.sponsorId = query.value(0).toLongLong();
        sponsor.name = query.value(1).toString();
        sponsor.email = query.value(2).toString();
        sponsor.dateDebut = query.value(3).toDate();
        sponsor.dateFin = query.value(4).toDate();
        sponsor.status = query.value(5).toString();
        qDebug() << "[Sponsor::fetchById] Found sponsor:" << sponsor.name;
        return true;
    }
    
    qDebug() << "[Sponsor::fetchById] No sponsor found with ID:" << id;
    return false;
}

bool Sponsor::update(qint64 sponsorId, const Sponsor &sponsor)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    QString sql = QString(
        "UPDATE SPONSORS SET NAME = :name, EMAIL = :email, "
        "DATE_DEBUT = :date_debut, DATE_FIN = :date_fin, STATUS = :status, "
        "LAST_UPDATE = SYSDATE WHERE ID_SPONSOR = %1").arg(sponsorId);
    
    QSqlQuery query(db);
    query.prepare(sql);
    
    query.bindValue(":name", sponsor.name);
    query.bindValue(":email", sponsor.email);
    query.bindValue(":date_debut", sponsor.dateDebut);
    query.bindValue(":date_fin", sponsor.dateFin);
    query.bindValue(":status", sponsor.status);
    
    if (!db.transaction()) {
        qDebug() << "[Sponsor::update] Failed to start transaction";
        return false;
    }
    
    if (!query.exec()) {
        qDebug() << "[Sponsor::update] Update failed:" << query.lastError().text();
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        qDebug() << "[Sponsor::update] Failed to commit transaction";
        db.rollback();
        return false;
    }
    
    qDebug() << "[Sponsor::update] SUCCESS - Sponsor" << sponsorId << "updated";
    return true;
}

bool Sponsor::remove(qint64 sponsorId)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = QString(
        "DELETE FROM SPONSORS WHERE ID_SPONSOR = %1").arg(sponsorId);
    
    if (!db.transaction()) {
        qDebug() << "[Sponsor::remove] Failed to start transaction";
        return false;
    }
    
    if (!query.exec(queryStr)) {
        qDebug() << "[Sponsor::remove] Delete failed:" << query.lastError().text();
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        qDebug() << "[Sponsor::remove] Failed to commit transaction";
        db.rollback();
        return false;
    }
    
    qDebug() << "[Sponsor::remove] SUCCESS - Sponsor" << sponsorId << "deleted";
    return true;
}

bool Sponsor::removeCascade(qint64 sponsorId)
{
    // For sponsors, usually just a simple delete (no foreign key dependencies in typical design)
    // If needed, expand this to handle related records
    return remove(sponsorId);
}

QVector<Sponsor> Sponsor::searchByName(const QString &name)
{
    QVector<Sponsor> records;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = QString(
        "SELECT ID_SPONSOR, NAME, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
        "FROM SPONSORS WHERE NAME LIKE '%%1%' ORDER BY NAME").arg(name);
    
    if (!query.exec(queryStr)) {
        qDebug() << "[Sponsor::searchByName] Failed:" << query.lastError().text();
        return records;
    }
    
    while (query.next()) {
        Sponsor record;
        record.sponsorId = query.value(0).toLongLong();
        record.name = query.value(1).toString();
        record.email = query.value(2).toString();
        record.dateDebut = query.value(3).toDate();
        record.dateFin = query.value(4).toDate();
        record.status = query.value(5).toString();
        records.append(record);
    }
    
    qDebug() << "[Sponsor::searchByName] Found" << records.size() << "sponsors with name containing:" << name;
    return records;
}

QVector<Sponsor> Sponsor::getByStatus(const QString &status)
{
    QVector<Sponsor> records;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = QString(
        "SELECT ID_SPONSOR, NAME, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
        "FROM SPONSORS WHERE STATUS = :status ORDER BY ID_SPONSOR");
    
    QSqlQuery q(db);
    q.prepare(queryStr);
    q.bindValue(":status", status);
    
    if (!q.exec()) {
        qDebug() << "[Sponsor::getByStatus] Failed:" << q.lastError().text();
        return records;
    }
    
    while (q.next()) {
        Sponsor record;
        record.sponsorId = q.value(0).toLongLong();
        record.name = q.value(1).toString();
        record.email = q.value(2).toString();
        record.dateDebut = q.value(3).toDate();
        record.dateFin = q.value(4).toDate();
        record.status = q.value(5).toString();
        records.append(record);
    }
    
    qDebug() << "[Sponsor::getByStatus] Found" << records.size() << "sponsors with status:" << status;
    return records;
}
