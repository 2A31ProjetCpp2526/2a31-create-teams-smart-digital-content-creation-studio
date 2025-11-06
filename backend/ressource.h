#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QSqlQueryModel>
#include <Qt>

class Ressource
{
public:
    // Attributes - NEW STRUCTURE (Oracle 11g XE compatible)
    qint64 idMedia;             // Primary key from SEQ_RESSOURCES.NEXTVAL
    QString title;              // Unique, no special characters
    QString path;               // File path or URL
    QString owner;              // Resource owner name
    QString format;             // File format (.pdf, .png, etc.)
    QString accessLevel;        // Access rights (Public, Private, etc.)
    QDateTime uploadDate;       // Upload timestamp

    // Constructors
    Ressource();
    Ressource(qint64 idMedia, const QString &title, const QString &path,
              const QString &owner, const QString &format, 
              const QString &accessLevel, const QDateTime &uploadDate = QDateTime::currentDateTime());

    // CRUD Operations
    static bool insert(const Ressource &ressource);
    static QVector<Ressource> selectAll();
    static bool update(const Ressource &ressource);
    static bool remove(qint64 id);
    static bool fetchById(qint64 id, Ressource &ressource);

    // Validation
    static bool isTitleValid(const QString &title, QString &errorMsg);
    static bool isTitleUnique(const QString &title, qint64 excludeId = -1);

    // Display & Query Methods
    static QSqlQueryModel* displayAll();
    static QSqlQueryModel* search(const QString &keyword);
    static QSqlQueryModel* sortBy(const QString &columnName, Qt::SortOrder order = Qt::AscendingOrder);

    // Export
    static bool exportToCsv(const QString &filePath);
};

#endif // RESSOURCE_H
