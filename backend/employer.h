#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QMap>

/**
 * @brief EmployerStatistics - Structure to hold employer statistics
 */
struct EmployerStatistics
{
    int totalEmployees = 0;
    int activeEmployees = 0;
    int newEmployeesThisMonth = 0;
    int newEmployeesThisYear = 0;
    double averageSalary = 0.0;
    double minSalary = 0.0;
    double maxSalary = 0.0;
    QString mostCommonRole;
    int departmentCount = 0;
    double retentionRate = 0.0;  // Percentage
    QMap<int,int> hiresPerYear;
    QMap<int,int> hiresPerMonth;  // Current year
    QMap<QString,int> roleDistribution;
    QMap<QString,int> topProjects;  // Project name -> count
    QMap<QString,int> topResources;  // Resource name -> count
};

/**
 * @brief Employer - Unified employer class combining data and CRUD operations
 */
class Employer
{
public:
    // =========================================================================
    // Data Members
    // =========================================================================
    qint64 employerId = -1;
    QString firstName;
    QString lastName;
    QString email;
    QString phone;
    QString role;
    QString passwordHash;
    QDate startDate;
    QString avatarPath;
    
    // =========================================================================
    // Constructors
    // =========================================================================
    
    // Default constructor
    Employer() = default;
    
    // Constructor with basic fields
    Employer(qint64 id, const QString &first, const QString &last)
        : employerId(id), firstName(first), lastName(last)
    {}
    
    // Full constructor
    Employer(qint64 id, const QString &first, const QString &last,
             const QString &mail, const QString &ph, const QString &r,
             const QString &passHash, const QDate &start, const QString &avatar)
        : employerId(id), firstName(first), lastName(last), email(mail),
          phone(ph), role(r), passwordHash(passHash), startDate(start), avatarPath(avatar)
    {}
    
    // =========================================================================
    // Static CRUD Operations
    // =========================================================================
    
    // Create - Insert new employer into database
    static bool insert(const Employer &employer, const QString &password);
    
    // Read - Get all employers from database
    static QVector<Employer> selectAll();
    
    // Read - Get single employer by ID
    static bool fetchById(qint64 id, Employer &employer);

    // Backwards-compatible helper: return a pointer to an Employer object
    // Returns nullptr if not found. Caller does not own the pointer (but
    // historically code did not delete it). For simplicity this helper
    // creates a new object when found.
    static Employer* getEmployer(qint64 id)
    {
        Employer *e = new Employer();
        if (fetchById(id, *e)) return e;
        delete e;
        return nullptr;
    }
    
    // Update - Modify existing employer
    static bool update(qint64 employerId, const Employer &employer, 
                      const QString &password = QString(), bool replacePassword = false);
    
    // Delete - Remove employer from database
    static bool remove(qint64 employerId);
    
    // Delete with cascade - Remove employer and all related records
    static bool removeCascade(qint64 employerId);
    
    // Check if employer has foreign key dependencies
    static bool hasRelatedRecords(qint64 employerId, QString *details = nullptr);
    // Compute aggregated statistics about employers
    static EmployerStatistics computeStatistics();

    // Export all employers and calculated statistics to a PDF file. Returns true on
    // success and optionally writes an error message to errorMessage.
    static bool exportToPdf(const QString &filePath, QString *errorMessage = nullptr);
    
private:
    // Helper function to hash passwords
    static QString hashPassword(const QString &password);
};

#endif // EMPLOYER_H
