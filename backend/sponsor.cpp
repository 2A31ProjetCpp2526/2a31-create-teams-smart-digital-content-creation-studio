#include "sponsor.h"
#include <QRegularExpression>
#include <QSqlQuery>
#include <QVariant>

/**
 * @brief Default constructor
 */
Sponsor::Sponsor()
    : m_id(0),
    m_dateDebut(QDate::currentDate()),
    m_dateFin(QDate::currentDate())
{
}

/**
 * @brief Parameterized constructor
 */
Sponsor::Sponsor(int id, const QString &nom, const QString &email,
                 const QDate &dateDebut, const QDate &dateFin, const QString &status)
    : m_id(id),
    m_nom(nom),
    m_email(email),
    m_dateDebut(dateDebut),
    m_dateFin(dateFin),
    m_status(status)
{
}

// ========== VALIDATION METHODS ==========

bool Sponsor::validateId(const QString &idText, QString &errorMsg) {
    if (idText.isEmpty()) {
        errorMsg = "L'ID ne peut pas être vide.";
        return false;
    }

    QRegularExpression regex("^[0-9]+$");
    if (!regex.match(idText).hasMatch()) {
        errorMsg = "L'ID doit contenir uniquement des chiffres.";
        return false;
    }

    return true;
}

bool Sponsor::validateNom(const QString &nom, QString &errorMsg) {
    if (nom.isEmpty()) {
        errorMsg = "Le nom ne peut pas être vide.";
        return false;
    }

    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ ]{4,}$");
    if (!regex.match(nom).hasMatch()) {
        errorMsg = "Le nom doit contenir uniquement des lettres et au minimum 4 caractères.";
        return false;
    }

    return true;
}

bool Sponsor::validateEmail(const QString &email, QString &errorMsg) {
    if (email.isEmpty()) {
        errorMsg = "L'email ne peut pas être vide.";
        return false;
    }

    QRegularExpression regex("^[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}$");
    if (!regex.match(email).hasMatch()) {
        errorMsg = "Veuillez entrer un email valide.";
        return false;
    }

    return true;
}

bool Sponsor::validateDates(const QDate &debut, const QDate &fin, QString &errorMsg) {
    if (!debut.isValid() || !fin.isValid()) {
        errorMsg = "Les dates ne sont pas valides.";
        return false;
    }

    if (debut > fin) {
        errorMsg = "La date de début doit être antérieure à la date de fin.";
        return false;
    }

    return true;
}

bool Sponsor::validateStatus(const QString &status, QString &errorMsg) {
    if (status.isEmpty() || status == "Selectionner...") {
        errorMsg = "Veuillez sélectionner un status valide.";
        return false;
    }

    return true;
}

bool Sponsor::validate(QString &errorMsg) const {
    QString idText = QString::number(m_id);

    if (!validateId(idText, errorMsg)) return false;
    if (!validateNom(m_nom, errorMsg)) return false;
    if (!validateEmail(m_email, errorMsg)) return false;
    if (!validateDates(m_dateDebut, m_dateFin, errorMsg)) return false;
    if (!validateStatus(m_status, errorMsg)) return false;

    return true;
}

// ========== DATABASE OPERATIONS ==========

bool Sponsor::add(const Sponsor &sponsor, QString &errorMsg) {
    // Validate first
    if (!sponsor.validate(errorMsg)) {
        return false;
    }

    // Check if ID already exists
    if (exists(sponsor.getId())) {
        errorMsg = "Cet ID existe déjà !";
        return false;
    }

    // Insert into database
    QSqlQuery query;
    query.prepare("INSERT INTO SPONSORS (ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS) "
                  "VALUES (:id, :nom, :email, :dd, :df, :status)");

    query.bindValue(":id", sponsor.getId());
    query.bindValue(":nom", sponsor.getNom());
    query.bindValue(":email", sponsor.getEmail());
    query.bindValue(":dd", sponsor.getDateDebut());
    query.bindValue(":df", sponsor.getDateFin());
    query.bindValue(":status", sponsor.getStatus());

    if (!query.exec()) {
        errorMsg = "Erreur lors de l'insertion : " + query.lastError().text();
        return false;
    }

    return true;
}

bool Sponsor::update(const Sponsor &sponsor, QString &errorMsg) {
    // Validate first
    if (!sponsor.validate(errorMsg)) {
        return false;
    }

    // Update in database
    QSqlQuery query;
    query.prepare("UPDATE SPONSORS SET NOM_SPONS = :nom, EMAIL = :email, "
                  "DATE_DEBUT = :dd, DATE_FIN = :df, STATUS = :status "
                  "WHERE ID_SPONS = :id");

    query.bindValue(":id", sponsor.getId());
    query.bindValue(":nom", sponsor.getNom());
    query.bindValue(":email", sponsor.getEmail());
    query.bindValue(":dd", sponsor.getDateDebut());
    query.bindValue(":df", sponsor.getDateFin());
    query.bindValue(":status", sponsor.getStatus());

    if (!query.exec()) {
        errorMsg = "Erreur lors de la mise à jour : " + query.lastError().text();
        return false;
    }

    return true;
}

bool Sponsor::remove(int id, QString &errorMsg) {
    QSqlQuery query;
    query.prepare("DELETE FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        errorMsg = "Erreur lors de la suppression : " + query.lastError().text();
        return false;
    }

    return true;
}

bool Sponsor::exists(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

Sponsor Sponsor::getById(int id, bool &found) {
    QSqlQuery query;
    query.prepare("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
                  "FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        found = true;
        return Sponsor(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDate(),
            query.value(4).toDate(),
            query.value(5).toString()
            );
    }

    found = false;
    return Sponsor();
}

QList<Sponsor> Sponsor::getAll() {
    QList<Sponsor> sponsors;
    QSqlQuery query("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS FROM SPONSORS");

    while (query.next()) {
        sponsors.append(Sponsor(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toDate(),
            query.value(4).toDate(),
            query.value(5).toString()
            ));
    }

    return sponsors;
}

QList<Sponsor> Sponsor::search(const QString &criteria, const QString &value) {
    QList<Sponsor> sponsors;
    QSqlQuery query;

    QString sql = QString("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
                          "FROM SPONSORS WHERE %1 = :value").arg(criteria);

    query.prepare(sql);
    query.bindValue(":value", value);

    if (query.exec()) {
        while (query.next()) {
            sponsors.append(Sponsor(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toDate(),
                query.value(4).toDate(),
                query.value(5).toString()
                ));
        }
    }

    return sponsors;
}

QMap<QString, int> Sponsor::getStatusStatistics() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT STATUS, COUNT(*) FROM SPONSORS GROUP BY STATUS");

    while (query.next()) {
        stats[query.value(0).toString()] = query.value(1).toInt();
    }

    return stats;
}
