#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "=== Oracle QODBC Connection Test ===";
    qDebug() << "";
    
    // Test 1: List available drivers
    qDebug() << "Available SQL drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    for (const QString &driver : drivers) {
        qDebug() << "  -" << driver;
    }
    qDebug() << "";
    
    // Test 2: Try to connect with explicit connection string
    qDebug() << "Attempting connection with DSN=EmployerDB;Uid=system;Pwd=123456789;";
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    
    // Use explicit connection string
    QString connStr = "DSN=EmployerDB;Uid=system;Pwd=123456789;";
    db.setDatabaseName(connStr);
    
    qDebug() << "Opening connection...";
    
    if (!db.open()) {
        qCritical() << "";
        qCritical() << "❌ CONNECTION FAILED!";
        qCritical() << "Error code:" << db.lastError().nativeErrorCode();
        qCritical() << "Error type:" << db.lastError().type();
        qCritical() << "Error text:" << db.lastError().text();
        qCritical() << "Driver text:" << db.lastError().driverText();
        qCritical() << "Database text:" << db.lastError().databaseText();
        qCritical() << "";
        qCritical() << "Possible causes:";
        qCritical() << "1. DSN 'EmployerDB' does not exist in Windows ODBC Data Source Administrator";
        qCritical() << "2. Oracle ODBC driver is not installed";
        qCritical() << "3. DSN bitness (32-bit vs 64-bit) doesn't match Qt build";
        qCritical() << "4. Credentials are incorrect";
        qCritical() << "5. Oracle service is not running";
        qCritical() << "";
        return 1;
    }
    
    qDebug() << "";
    qDebug() << "✅ Connected successfully to Oracle!";
    qDebug() << "";
    
    // Test 3: Try a simple query
    qDebug() << "Testing query: SELECT COUNT(*) FROM EMPLOYER";
    
    QSqlQuery query(db);
    if (!query.exec("SELECT COUNT(*) FROM EMPLOYER")) {
        qCritical() << "❌ Query failed:" << query.lastError().text();
        db.close();
        return 2;
    }
    
    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "✅ Query successful! Found" << count << "employers in database.";
    }
    
    qDebug() << "";
    qDebug() << "=== All tests passed! ===";
    
    db.close();
    return 0;
}
