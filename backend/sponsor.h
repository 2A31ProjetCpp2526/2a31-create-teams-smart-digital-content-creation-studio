#ifndef SPONSOR_H
#define SPONSOR_H

#include <QString>
#include <QDate>
#include <QVector>

/**
 * @brief Sponsor - Unified sponsor class combining data and CRUD operations
 * Fields: ID_SPONS, NOM_SPONS, EMAIL, DATE_DÉBUT, DATE_FIN, STATUS
 */
class Sponsor
{
public:
    // =========================================================================
    // Data Members
    // =========================================================================
    qint64 sponsorId = -1;
    QString name;
    QString email;
    QDate dateDebut;  // Date de début du partenariat
    QDate dateFin;    // Date de fin du partenariat
    QString status;   // Actif, Inactif, Suspendu, etc.
    
    // =========================================================================
    // Constructors
    // =========================================================================
    
    // Default constructor
    Sponsor() = default;
    
    // Constructor with basic fields
    Sponsor(qint64 id, const QString &n, const QString &e)
        : sponsorId(id), name(n), email(e)
    {}
    
    // Full constructor
    Sponsor(qint64 id, const QString &n, const QString &e,
            const QDate &dd, const QDate &df, const QString &st)
        : sponsorId(id), name(n), email(e), dateDebut(dd), dateFin(df), status(st)
    {}
    
    // =========================================================================
    // Static CRUD Operations
    // =========================================================================
    
    // Create - Insert new sponsor into database
    static bool insert(const Sponsor &sponsor);
    
    // Read - Get all sponsors from database
    static QVector<Sponsor> selectAll();
    
    // Read - Get single sponsor by ID
    static bool fetchById(qint64 id, Sponsor &sponsor);
    
    // Update - Modify existing sponsor
    static bool update(qint64 sponsorId, const Sponsor &sponsor);
    
    // Delete - Remove sponsor from database
    static bool remove(qint64 sponsorId);
    
    // Delete with cascade - Remove sponsor and all related records
    static bool removeCascade(qint64 sponsorId);
    
    // Search sponsor by name
    static QVector<Sponsor> searchByName(const QString &name);
    
    // Get sponsors with specific status
    static QVector<Sponsor> getByStatus(const QString &status);
};

#endif // SPONSOR_H
