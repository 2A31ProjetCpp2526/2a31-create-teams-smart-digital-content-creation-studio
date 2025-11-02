#include "employer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QCryptographicHash>

QString Employer::hashPassword(const QString &password)
{
    const QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString::fromLatin1(hashed.toHex());
}

bool Employer::insert(const Employer &employer, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    // Get next ID using MAX() + 1
    QSqlQuery queryId(db);
    if (!queryId.exec("SELECT NVL(MAX(ID_EMP), 0) + 1 FROM EMPLOYER")) {
        return false;
    }
    
    qint64 nextId = 1;
    if (queryId.next()) {
        nextId = queryId.value(0).toLongLong();
    }
    
    // Prepare INSERT query
    QString queryStr = QString(
        "INSERT INTO EMPLOYER (ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, STATUS, HIRE_DATE, AVATAR_PATH) "
        "VALUES (%1, :first_name, :last_name, :email, :phone, :role, :password, :status, :hire_date, :avatar_path)").arg(nextId);
    
    QSqlQuery query(db);
    query.prepare(queryStr);
    
    query.bindValue(":first_name", employer.firstName);
    query.bindValue(":last_name", employer.lastName);
    query.bindValue(":email", employer.email);
    query.bindValue(":phone", employer.phone.toInt());
    query.bindValue(":role", employer.role);
    query.bindValue(":password", password);
    query.bindValue(":status", "ACTIVE");
    query.bindValue(":hire_date", employer.startDate);
    query.bindValue(":avatar_path", employer.avatarPath);
    
    if (!db.transaction()) return false;
    
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return true;
}

QVector<Employer> Employer::selectAll()
{
    QVector<Employer> records;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = "SELECT ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, HIRE_DATE, AVATAR_PATH "
                       "FROM EMPLOYER ORDER BY ID_EMP";
    
    if (!query.exec(queryStr)) {
        return records;
    }
    
    while (query.next()) {
        Employer record;
        record.employerId = query.value(0).toLongLong();
        record.firstName = query.value(1).toString();
        record.lastName = query.value(2).toString();
        record.email = query.value(3).toString();
        record.phone = QString::number(query.value(4).toInt());
        record.role = query.value(5).toString();
        record.passwordHash = query.value(6).toString();
        record.startDate = query.value(7).toDate();
        record.avatarPath = query.value(8).toString();
        records.append(record);
    }
    
    return records;
}

bool Employer::fetchById(qint64 id, Employer &employer)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = QString(
        "SELECT ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, HIRE_DATE, AVATAR_PATH "
        "FROM EMPLOYER WHERE ID_EMP = %1").arg(id);
    
    if (!query.exec(queryStr)) {
        return false;
    }
    
    if (query.next()) {
        employer.employerId = query.value(0).toLongLong();
        employer.firstName = query.value(1).toString();
        employer.lastName = query.value(2).toString();
        employer.email = query.value(3).toString();
        employer.phone = QString::number(query.value(4).toInt());
        employer.role = query.value(5).toString();
        employer.passwordHash = query.value(6).toString();
        employer.startDate = query.value(7).toDate();
        employer.avatarPath = query.value(8).toString();
        return true;
    }
    
    return false;
}

bool Employer::update(qint64 employerId, const Employer &employer, 
                      const QString &password, bool replacePassword)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    QString sql = "UPDATE EMPLOYER SET FIRST_NAME = :first_name, LAST_NAME = :last_name, EMAIL = :email, "
                  "PHONE = :phone, ROLE = :role, HIRE_DATE = :hire_date, AVATAR_PATH = :avatar_path";
    
    if (replacePassword) {
        sql.append(", PASSWORD = :password");
    }
    
    sql.append(QString(" WHERE ID_EMP = %1").arg(employerId));
    
    QSqlQuery query(db);
    query.prepare(sql);
    
    query.bindValue(":first_name", employer.firstName);
    query.bindValue(":last_name", employer.lastName);
    query.bindValue(":email", employer.email);
    query.bindValue(":phone", employer.phone.toInt());
    query.bindValue(":role", employer.role);
    query.bindValue(":hire_date", employer.startDate);
    query.bindValue(":avatar_path", employer.avatarPath);
    
    if (replacePassword) {
        query.bindValue(":password", password);
    }
    
    if (!db.transaction()) return false;
    
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return true;
}

bool Employer::remove(qint64 employerId)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString queryStr = QString("DELETE FROM EMPLOYER WHERE ID_EMP = %1").arg(employerId);
    
    if (!db.transaction()) return false;
    
    if (!query.exec(queryStr)) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return query.numRowsAffected() > 0;
}

bool Employer::hasRelatedRecords(qint64 employerId, QString *details)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    
    QString detailsMsg;
    bool hasRelated = false;
    
    QStringList relatedTables = {"PROJECTS", "SPONSORS", "SERVICES", "RESOURCES"};
    
    for (const QString &tableName : relatedTables) {
        QString countQuery = QString("SELECT COUNT(*) FROM %1 WHERE ID_EMP = %2")
                                .arg(tableName).arg(employerId);
        
        if (query.exec(countQuery) && query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                hasRelated = true;
                QString msg = QString("%1 (%2 records)").arg(tableName).arg(count);
                
                if (!detailsMsg.isEmpty()) {
                    detailsMsg += ", ";
                }
                detailsMsg += msg;
            }
        }
    }
    
    if (details) {
        *details = detailsMsg;
    }
    
    return hasRelated;
}

bool Employer::removeCascade(qint64 employerId)
{
    QSqlDatabase db = QSqlDatabase::database();
    
    if (!db.transaction()) return false;
    
    QStringList deleteOrder = {"RESOURCES", "SERVICES", "SPONSORS", "PROJECTS"};
    QSqlQuery query(db);
    
    for (const QString &tableName : deleteOrder) {
        QString deleteQuery = QString("DELETE FROM %1 WHERE ID_EMP = %2")
                                 .arg(tableName).arg(employerId);
        query.exec(deleteQuery);
    }
    
    QString deleteEmployer = QString("DELETE FROM EMPLOYER WHERE ID_EMP = %1").arg(employerId);
    
    if (!query.exec(deleteEmployer)) {
        db.rollback();
        return false;
    }
    
    if (!db.commit()) {
        db.rollback();
        return false;
    }
    
    return true;
}

// =============================================================================
// EXEMPLES D'UTILISATION POUR LE PROFESSEUR
// Ces exemples montrent comment utiliser le CRUD Employer dans un projet Qt
// =============================================================================

/*
 * ============================================================================
 * EXEMPLE COMPLET D'UTILISATION DANS MainWindow
 * ============================================================================
 * 
 * #include "mainwindow.h"
 * #include "ui_mainwindow.h"
 * #include "employer.h"
 * #include <QMessageBox>
 * #include <QDate>
 * 
 * MainWindow::MainWindow(QWidget *parent)
 *     : QMainWindow(parent), ui(new Ui::MainWindow)
 * {
 *     ui->setupUi(this);
 *     loadEmployers(); // Charger les données au démarrage
 * }
 * 
 * MainWindow::~MainWindow()
 * {
 *     delete ui;
 * }
 * 
 * // ========== FONCTION AJOUTER ==========
 * void MainWindow::on_pushButton_ajouter_clicked()
 * {
 *     // 1. Récupérer les données du formulaire
 *     QString firstName = ui->lineEdit_firstName->text();
 *     QString lastName = ui->lineEdit_lastName->text();
 *     QString email = ui->lineEdit_email->text();
 *     QString phone = ui->lineEdit_phone->text();
 *     QString role = ui->comboBox_role->currentText();
 *     QString password = ui->lineEdit_password->text();
 *     QDate hireDate = ui->dateEdit_hire->date();
 * 
 *     // 2. Créer un objet Employer
 *     Employer emp;
 *     emp.firstName = firstName;
 *     emp.lastName = lastName;
 *     emp.email = email;
 *     emp.phone = phone;
 *     emp.role = role;
 *     emp.startDate = hireDate;
 *     emp.avatarPath = "";
 * 
 *     // 3. Appeler la méthode insert()
 *     bool test = Employer::insert(emp, password);
 * 
 *     // 4. Afficher le résultat
 *     if (test) {
 *         QMessageBox::information(this, "OK", "Ajout effectué ✅");
 *         loadEmployers(); // Recharger le tableau
 *         clearForm();     // Vider le formulaire
 *     } else {
 *         QMessageBox::critical(this, "Erreur", "Échec de l'ajout ❌");
 *     }
 * }
 * 
 * // ========== FONCTION MODIFIER ==========
 * void MainWindow::on_pushButton_modifier_clicked()
 * {
 *     // 1. Récupérer l'ID de l'employer à modifier
 *     qint64 id = ui->lineEdit_id->text().toLongLong();
 * 
 *     // 2. Récupérer les nouvelles données
 *     QString firstName = ui->lineEdit_firstName->text();
 *     QString lastName = ui->lineEdit_lastName->text();
 *     QString email = ui->lineEdit_email->text();
 *     QString phone = ui->lineEdit_phone->text();
 *     QString role = ui->comboBox_role->currentText();
 *     QString password = ui->lineEdit_password->text();
 *     QDate hireDate = ui->dateEdit_hire->date();
 * 
 *     // 3. Créer un objet Employer avec les nouvelles données
 *     Employer emp;
 *     emp.firstName = firstName;
 *     emp.lastName = lastName;
 *     emp.email = email;
 *     emp.phone = phone;
 *     emp.role = role;
 *     emp.startDate = hireDate;
 * 
 *     // 4. Appeler la méthode update()
 *     bool replacePassword = !password.isEmpty(); // Modifier le mot de passe seulement s'il est rempli
 *     bool test = Employer::update(id, emp, password, replacePassword);
 * 
 *     // 5. Afficher le résultat
 *     if (test) {
 *         QMessageBox::information(this, "OK", "Modification effectuée ✅");
 *         loadEmployers();
 *         clearForm();
 *     } else {
 *         QMessageBox::critical(this, "Erreur", "Échec de la modification ❌");
 *     }
 * }
 * 
 * // ========== FONCTION SUPPRIMER ==========
 * void MainWindow::on_pushButton_supprimer_clicked()
 * {
 *     // 1. Récupérer l'ID de l'employer à supprimer
 *     qint64 id = ui->lineEdit_id->text().toLongLong();
 * 
 *     // 2. Demander confirmation
 *     QMessageBox::StandardButton reply = QMessageBox::question(
 *         this, 
 *         "Confirmation", 
 *         "Voulez-vous vraiment supprimer cet employé ?",
 *         QMessageBox::Yes | QMessageBox::No
 *     );
 * 
 *     if (reply == QMessageBox::Yes) {
 *         // 3. Appeler la méthode remove()
 *         bool test = Employer::remove(id);
 * 
 *         // 4. Afficher le résultat
 *         if (test) {
 *             QMessageBox::information(this, "OK", "Suppression effectuée ✅");
 *             loadEmployers();
 *             clearForm();
 *         } else {
 *             QMessageBox::critical(this, "Erreur", "Échec de la suppression ❌");
 *         }
 *     }
 * }
 * 
 * // ========== FONCTION AFFICHER (CHARGER TABLEAU) ==========
 * void MainWindow::loadEmployers()
 * {
 *     // 1. Appeler selectAll() pour récupérer tous les employers
 *     QVector<Employer> employers = Employer::selectAll();
 * 
 *     // 2. Vider le tableau
 *     ui->tableWidget->setRowCount(0);
 * 
 *     // 3. Remplir le tableau avec les données
 *     for (const Employer &emp : employers) {
 *         int row = ui->tableWidget->rowCount();
 *         ui->tableWidget->insertRow(row);
 * 
 *         ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(emp.employerId)));
 *         ui->tableWidget->setItem(row, 1, new QTableWidgetItem(emp.firstName));
 *         ui->tableWidget->setItem(row, 2, new QTableWidgetItem(emp.lastName));
 *         ui->tableWidget->setItem(row, 3, new QTableWidgetItem(emp.email));
 *         ui->tableWidget->setItem(row, 4, new QTableWidgetItem(emp.phone));
 *         ui->tableWidget->setItem(row, 5, new QTableWidgetItem(emp.role));
 *         ui->tableWidget->setItem(row, 6, new QTableWidgetItem(emp.startDate.toString("dd/MM/yyyy")));
 *     }
 * }
 * 
 * // ========== FONCTION VIDER FORMULAIRE ==========
 * void MainWindow::clearForm()
 * {
 *     ui->lineEdit_id->clear();
 *     ui->lineEdit_firstName->clear();
 *     ui->lineEdit_lastName->clear();
 *     ui->lineEdit_email->clear();
 *     ui->lineEdit_phone->clear();
 *     ui->lineEdit_password->clear();
 *     ui->dateEdit_hire->setDate(QDate::currentDate());
 *     ui->comboBox_role->setCurrentIndex(0);
 * }
 * 
 * ============================================================================
 * FIN DES EXEMPLES
 * ============================================================================
 */
