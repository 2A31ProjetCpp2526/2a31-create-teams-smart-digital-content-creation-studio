#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>

Client::Client() : clientId(0) {}

Client::Client(qint64 id, const QString &fName, const QString &lName, 
               const QString &mail, const QString &prefs)
    : clientId(id), firstName(fName), lastName(lName), 
      email(mail), preferences(prefs) {}

bool Client::insert(const Client &client)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    
    // Get next ID using MAX() + 1
    QSqlQuery queryId(db);
    if (!queryId.exec("SELECT NVL(MAX(ID_CLIENT), 0) + 1 FROM CLIENT")) {
        return false;
    }
    
    qint64 nextId = 1;
    if (queryId.next()) {
        nextId = queryId.value(0).toLongLong();
    }
    
    // Prepare INSERT query
    QString queryStr = QString(
        "INSERT INTO CLIENT (ID_CLIENT, FIRST_NAME, LAST_NAME, EMAIL, PREFERENCES) "
        "VALUES (%1, :first_name, :last_name, :email, :preferences)").arg(nextId);
    
    QSqlQuery query(db);
    if (!query.prepare(queryStr)) return false;
    
    query.bindValue(":first_name", client.firstName);
    query.bindValue(":last_name", client.lastName);
    query.bindValue(":email", client.email);
    query.bindValue(":preferences", client.preferences);
    
    if (!db.transaction()) return false;
    
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return true;
}

QVector<Client> Client::selectAll()
{
    QVector<Client> records;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return records;
    
    QSqlQuery query(db);
    QString queryStr = "SELECT ID_CLIENT, FIRST_NAME, LAST_NAME, EMAIL, PREFERENCES "
                       "FROM CLIENT ORDER BY ID_CLIENT";
    
    if (!query.exec(queryStr)) {
        return records;
    }
    
    while (query.next()) {
        Client record;
        record.clientId = query.value(0).toLongLong();
        record.firstName = query.value(1).toString();
        record.lastName = query.value(2).toString();
        record.email = query.value(3).toString();
        record.preferences = query.value(4).toString();
        records.append(record);
    }
    
    return records;
}

bool Client::fetchById(qint64 id, Client &client)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    
    QSqlQuery query(db);
    QString queryStr = QString(
        "SELECT ID_CLIENT, FIRST_NAME, LAST_NAME, EMAIL, PREFERENCES "
        "FROM CLIENT WHERE ID_CLIENT = %1").arg(id);
    
    if (!query.exec(queryStr)) {
        return false;
    }
    
    if (query.next()) {
        client.clientId = query.value(0).toLongLong();
        client.firstName = query.value(1).toString();
        client.lastName = query.value(2).toString();
        client.email = query.value(3).toString();
        client.preferences = query.value(4).toString();
        return true;
    }
    
    return false;
}

bool Client::update(qint64 clientId, const Client &client)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    
    QString sql = QString(
        "UPDATE CLIENT SET FIRST_NAME = :first_name, LAST_NAME = :last_name, "
        "EMAIL = :email, PREFERENCES = :preferences WHERE ID_CLIENT = %1").arg(clientId);
    
    QSqlQuery query(db);
    if (!query.prepare(sql)) return false;
    
    query.bindValue(":first_name", client.firstName);
    query.bindValue(":last_name", client.lastName);
    query.bindValue(":email", client.email);
    query.bindValue(":preferences", client.preferences);
    
    if (!db.transaction()) return false;
    
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return true;
}

bool Client::remove(qint64 clientId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    
    QSqlQuery query(db);
    QString queryStr = QString("DELETE FROM CLIENT WHERE ID_CLIENT = %1").arg(clientId);
    
    if (!db.transaction()) return false;
    
    if (!query.exec(queryStr)) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return query.numRowsAffected() > 0;
}

bool Client::removeCascade(qint64 clientId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    
    if (!db.transaction()) return false;
    
    // Add related tables if needed (e.g., ORDERS, RESERVATIONS)
    QStringList deleteOrder = {"ORDERS", "RESERVATIONS"};
    QSqlQuery query(db);
    
    for (const QString &tableName : deleteOrder) {
        QString deleteQuery = QString("DELETE FROM %1 WHERE ID_CLIENT = %2")
                                 .arg(tableName).arg(clientId);
        query.exec(deleteQuery);
    }
    
    QString deleteClient = QString("DELETE FROM CLIENT WHERE ID_CLIENT = %1").arg(clientId);
    
    if (!query.exec(deleteClient)) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return true;
}

bool Client::hasRelatedRecords(qint64 clientId, QString *details)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return false;
    
    QSqlQuery query(db);
    QString detailsMsg;
    bool hasRelated = false;
    
    QStringList relatedTables = {"ORDERS", "RESERVATIONS"};
    
    for (const QString &tableName : relatedTables) {
        QString countQuery = QString("SELECT COUNT(*) FROM %1 WHERE ID_CLIENT = %2")
                                .arg(tableName).arg(clientId);
        
        if (query.exec(countQuery) && query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                hasRelated = true;
                QString msg = QString("%1 (%2 records)").arg(tableName).arg(count);
                
                if (!detailsMsg.isEmpty()) {
                    detailsMsg += ", ";
                }
                detailsMsg += msg;
            }
        }
    }
    
    if (details) {
        *details = detailsMsg;
    }
    
    return hasRelated;
}

QSqlQueryModel* Client::getQueryModel()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return model;
    
    model->setQuery("SELECT ID_CLIENT, FIRST_NAME, LAST_NAME, EMAIL, PREFERENCES "
                    "FROM CLIENT ORDER BY ID_CLIENT", db);
    
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    model->setHeaderData(4, Qt::Horizontal, "Preferences");
    
    return model;
}

QSqlQueryModel* Client::search(const QString &keyword)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return model;
    
    QString searchQuery = QString(
        "SELECT ID_CLIENT, FIRST_NAME, LAST_NAME, EMAIL, PREFERENCES "
        "FROM CLIENT WHERE "
        "UPPER(FIRST_NAME) LIKE UPPER('%%%1%%') OR "
        "UPPER(LAST_NAME) LIKE UPPER('%%%1%%') OR "
        "UPPER(EMAIL) LIKE UPPER('%%%1%%') OR "
        "UPPER(PREFERENCES) LIKE UPPER('%%%1%%') "
        "ORDER BY ID_CLIENT").arg(keyword);
    
    model->setQuery(searchQuery, db);
    
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    model->setHeaderData(4, Qt::Horizontal, "Preferences");
    
    return model;
}
