#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

// Initialization of the instance pointer to nullptr
Connection * Connection::p_instance = nullptr;

// Private constructor
Connection::Connection() 
{
    qDebug() << "[Connection] Constructor called";
}

// Private destructor to close the database connection
Connection::~Connection()
{
    qDebug() << "[Connection] Destructor - closing connection";
    closeConnect();
}

// Static method to obtain the unique instance of the Connection class
Connection* Connection::instance()
{
    if (p_instance == nullptr) {
        p_instance = new Connection();
        qDebug() << "[Connection] Singleton instance created";
    }
    return p_instance;
}

// Method to initialize the database connection
bool Connection::createConnect()
{
    qDebug() << "========================================";
    qDebug() << "[Connection] CREATE CONNECTION STARTED";
    qDebug() << "========================================";

    const QString dsn = "projet_2A2526";
    const QString username = "molka";
    const QString password = "123";
    const QString driverType = "QODBC";
    
    qDebug() << "[Connection] Configuration:";
    qDebug() << "[Connection]   Driver: " << driverType;
    qDebug() << "[Connection]   DSN:    " << dsn;
    qDebug() << "[Connection]   User:   " << username;
    
    // Check if QODBC driver is available
    QStringList availableDrivers = QSqlDatabase::drivers();
    qDebug() << "[Connection] Available SQL drivers:" << availableDrivers;
    
    if (!availableDrivers.contains(driverType)) {
        qCritical() << "[Connection] ERROR: QODBC driver not found!";
        qCritical() << "[Connection] Available drivers are:" << availableDrivers;
        return false;
    }
    qDebug() << "[Connection] ✓ QODBC driver is available";
    
    // Remove existing connection if present
    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        qDebug() << "[Connection] Removing existing default connection";
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
    
    // Add database driver
    db = QSqlDatabase::addDatabase(driverType);
    
    if (!db.isValid()) {
        qCritical() << "[Connection] ERROR: Failed to add database driver";
        return false;
    }
    qDebug() << "[Connection] ✓ Database driver added successfully";
    
    // Set database connection parameters using DSN
    db.setDatabaseName(dsn);
    db.setUserName(username);
    db.setPassword(password);
    
    qDebug() << "[Connection] Using DSN connection";
    qDebug() << "[Connection] Connection parameters set";
    qDebug() << "[Connection] Attempting to open database connection...";
    
    // Attempt to open the connection
    if (!db.open()) {
        qCritical() << "========================================";
        qCritical() << "[Connection] ✗✗✗ CONNECTION FAILED! ✗✗✗";
        qCritical() << "========================================";
        
        QSqlError error = db.lastError();
        qCritical() << "[Connection] Error type:    " << error.type();
        qCritical() << "[Connection] Driver error:  " << error.driverText();
        qCritical() << "[Connection] Database error:" << error.databaseText();
        qCritical() << "[Connection] Native error:  " << error.nativeErrorCode();
        qCritical() << "[Connection] Full error:    " << error.text();
        
        // Provide troubleshooting hints
        if (error.text().contains("IM002") || error.text().contains("Data source name not found")) {
            qCritical() << "[Connection] HINT: DSN 'EmployerDB' not found in ODBC Data Source Administrator";
            qCritical() << "[Connection] HINT: Check System DSN in odbcad32.exe";
        } else if (error.text().contains("ORA-01017")) {
            qCritical() << "[Connection] HINT: Invalid username/password";
        } else if (error.text().contains("ORA-12154") || error.text().contains("TNS")) {
            qCritical() << "[Connection] HINT: TNS listener issue - check Oracle services";
        }
        
        qCritical() << "========================================";
        return false;
    }
    
    // Connection successful
    qDebug() << "========================================";
    qDebug() << "[Connection] ✓✓✓ CONNECTION SUCCESSFUL! ✓✓✓";
    qDebug() << "========================================";
    qDebug() << "[Connection] Database is OPEN and READY";
    qDebug() << "[Connection] Driver name:      " << db.driverName();
    qDebug() << "[Connection] Database name:    " << db.databaseName();
    qDebug() << "[Connection] Connection valid: " << db.isValid();
    qDebug() << "[Connection] Connection open:  " << db.isOpen();
    qDebug() << "========================================";
    
    return true;
}

// Method to close the database connection
void Connection::closeConnect()
{
    if (db.isOpen()) {
        qDebug() << "[Connection] Closing database connection...";
        db.close();
        qDebug() << "[Connection] ✓ Connection closed";
    }
    
    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        qDebug() << "[Connection] ✓ Database connection removed";
    }
}
