#ifndef SPONSOR_H
#define SPONSOR_H

#include <QString>
#include <QDate>
#include <QMap>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief The Sponsor class - Represents a sponsor entity with CRUD operations
 *
 * This class encapsulates all sponsor-related data and database operations
 * to provide a clean separation of concerns and easy integration.
 */
class Sponsor {
public:
    // Constructors
    Sponsor();
    Sponsor(int id, const QString &nom, const QString &email,
            const QDate &dateDebut, const QDate &dateFin, const QString &status);

    // Getters
    int getId() const { return m_id; }
    QString getNom() const { return m_nom; }
    QString getEmail() const { return m_email; }
    QDate getDateDebut() const { return m_dateDebut; }
    QDate getDateFin() const { return m_dateFin; }
    QString getStatus() const { return m_status; }

    // Setters
    void setId(int id) { m_id = id; }
    void setNom(const QString &nom) { m_nom = nom; }
    void setEmail(const QString &email) { m_email = email; }
    void setDateDebut(const QDate &date) { m_dateDebut = date; }
    void setDateFin(const QDate &date) { m_dateFin = date; }
    void setStatus(const QString &status) { m_status = status; }

    // Validation methods
    static bool validateId(const QString &idText, QString &errorMsg);
    static bool validateNom(const QString &nom, QString &errorMsg);
    static bool validateEmail(const QString &email, QString &errorMsg);
    static bool validateDates(const QDate &debut, const QDate &fin, QString &errorMsg);
    static bool validateStatus(const QString &status, QString &errorMsg);

    bool validate(QString &errorMsg) const;

    // Database operations (Static methods for CRUD)
    static bool add(const Sponsor &sponsor, QString &errorMsg);
    static bool update(const Sponsor &sponsor, QString &errorMsg);
    static bool remove(int id, QString &errorMsg);
    static bool exists(int id);
    static Sponsor getById(int id, bool &found);
    static QList<Sponsor> getAll();
    static QList<Sponsor> search(const QString &criteria, const QString &value);

    // Statistics
    static QMap<QString, int> getStatusStatistics();

private:
    int m_id;
    QString m_nom;
    QString m_email;
    QDate m_dateDebut;
    QDate m_dateFin;
    QString m_status;
};

#endif // SPONSOR_H
