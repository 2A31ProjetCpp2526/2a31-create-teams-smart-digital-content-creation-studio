#include "databasemanager_new.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "========================================";
    qDebug() << "  Database Connection Test Application";
    qDebug() << "========================================\n";
    
    // Create database manager
    employer::DatabaseManager dbManager;
    
    // Initialize connection
    if (!dbManager.initialize()) {
        qCritical() << "\n❌ Database initialization failed!";
        qCritical() << "Application will exit.";
        return 1;
    }
    
    qDebug() << "\n========================================";
    qDebug() << "  Testing CRUD Operations";
    qDebug() << "========================================\n";
    
    // Test 1: SELECT all employees
    qDebug() << "\n--- Test 1: SELECT ALL EMPLOYERS ---";
    auto employees = dbManager.selectAllEmployers();
    qDebug() << "Current employee count:" << employees.size();
    
    // Test 2: INSERT new employee
    qDebug() << "\n--- Test 2: INSERT NEW EMPLOYER ---";
    bool insertSuccess = dbManager.insertEmployer(
        999,                    // ID
        "Test",                 // First name
        "User",                 // Last name
        "test@example.com",     // Email
        "1234567890",           // Phone
        "123 Test Street",      // Address
        "QA Tester",            // Position
        50000.0,                // Salary
        "ACTIVE",               // Status
        1                       // Department ID
    );
    
    if (insertSuccess) {
        qDebug() << "✓ Insert test passed";
    }
    
    // Test 3: UPDATE employee
    qDebug() << "\n--- Test 3: UPDATE EMPLOYER ---";
    bool updateSuccess = dbManager.updateEmployer(999, "Updated", "Name");
    
    if (updateSuccess) {
        qDebug() << "✓ Update test passed";
    }
    
    // Test 4: SELECT again to verify changes
    qDebug() << "\n--- Test 4: SELECT AFTER UPDATE ---";
    employees = dbManager.selectAllEmployers();
    
    // Test 5: DELETE employee
    qDebug() << "\n--- Test 5: DELETE EMPLOYER ---";
    bool deleteSuccess = dbManager.deleteEmployer(999);
    
    if (deleteSuccess) {
        qDebug() << "✓ Delete test passed";
    }
    
    // Test 6: Final SELECT to verify deletion
    qDebug() << "\n--- Test 6: SELECT AFTER DELETE ---";
    employees = dbManager.selectAllEmployers();
    
    qDebug() << "\n========================================";
    qDebug() << "  All Tests Completed!";
    qDebug() << "========================================\n";
    
    return 0;
}
