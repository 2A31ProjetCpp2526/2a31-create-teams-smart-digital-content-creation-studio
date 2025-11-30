#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

// Initialize the static instance pointer
Connection* Connection::p_instance = nullptr;

// Private constructor
Connection::Connection() {}

// Private destructor
Connection::~Connection()
{
    closeConnect();
}

// Singleton instance getter
Connection* Connection::instance()
{
    if (p_instance == nullptr)
        p_instance = new Connection();

    return p_instance;
}

// Create the connection using ODBC DSN
bool Connection::createConnect()
{
    bool test = false;

    // EXACT SAME SYNTAX AS YOUR WORKING CODE
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("adminInspiraStudio");
    db.setUserName("adminInspiraStudio");
    db.setPassword("alawi");

    if (db.open())
    {
        qDebug() << "Connexion ODBC Oracle réussie !";
        test = true;
    }
    else
    {
        qDebug() << "Échec connexion :" << db.lastError().text();
    }

    return test;
}

// Close the connection
void Connection::closeConnect()
{
    if (db.isOpen())
    {
        db.close();
        qDebug() << "Connexion fermée.";
    }
}
