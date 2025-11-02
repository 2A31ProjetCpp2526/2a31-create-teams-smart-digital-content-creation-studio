#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QDate>
#include <QVector>

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
    
    // Update - Modify existing employer
    static bool update(qint64 employerId, const Employer &employer, 
                      const QString &password = QString(), bool replacePassword = false);
    
    // Delete - Remove employer from database
    static bool remove(qint64 employerId);
    
    // Delete with cascade - Remove employer and all related records
    static bool removeCascade(qint64 employerId);
    
    // Check if employer has foreign key dependencies
    static bool hasRelatedRecords(qint64 employerId, QString *details = nullptr);
    
private:
    // Helper function to hash passwords
    static QString hashPassword(const QString &password);
};

#endif // EMPLOYER_H
