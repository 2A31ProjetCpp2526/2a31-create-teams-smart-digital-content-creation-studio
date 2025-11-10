#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QVector>
#include <QSqlQueryModel>

class Client
{
public:
    // Attributes
    qint64 clientId;
    QString firstName;
    QString lastName;
    QString email;
    QString preferences;

    // Constructors
    Client();
    Client(qint64 id, const QString &fName, const QString &lName, 
           const QString &mail, const QString &prefs);

    // CRUD Operations
    static bool insert(const Client &client);
    static QVector<Client> selectAll();
    static bool fetchById(qint64 id, Client &client);
    static bool update(qint64 clientId, const Client &client);
    static bool remove(qint64 clientId);
    static bool removeCascade(qint64 clientId);
    
    // Utility
    static bool hasRelatedRecords(qint64 clientId, QString *details = nullptr);
    static QSqlQueryModel* getQueryModel();
    static QSqlQueryModel* search(const QString &keyword);
};

#endif // CLIENT_H
