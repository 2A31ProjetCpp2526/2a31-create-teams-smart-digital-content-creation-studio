#include "employer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QCryptographicHash>
#include <QFile>
#include <QTextDocument>
#include <QPrinter>
#include <QFontDatabase>

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

EmployerStatistics Employer::computeStatistics()
{
    EmployerStatistics stats;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Total employees
    if (query.exec("SELECT COUNT(*) FROM EMPLOYER") && query.next()) {
        stats.totalEmployees = query.value(0).toInt();
    }

    // Active employees (if STATUS column exists)
    if (query.exec("SELECT COUNT(*) FROM EMPLOYER WHERE STATUS = 'ACTIVE'") && query.next()) {
        stats.activeEmployees = query.value(0).toInt();
    }

    // Average salary (best-effort: if SALARY column missing, this may return NULL)
    if (query.exec("SELECT AVG(SALARY) FROM EMPLOYER") && query.next()) {
        stats.averageSalary = query.value(0).toDouble();
    } else {
        stats.averageSalary = 0.0;
    }

    // Hires per year - adapt to driver (SQLite vs Oracle-like)
    QString driver = db.driverName().toLower();
    if (driver.contains("sqlite")) {
        if (query.exec("SELECT strftime('%Y', HIRE_DATE) AS yr, COUNT(*) FROM EMPLOYER GROUP BY yr ORDER BY yr DESC")) {
            while (query.next()) {
                QString yearStr = query.value(0).toString();
                int count = query.value(1).toInt();
                if (!yearStr.isEmpty()) stats.hiresPerYear[yearStr.toInt()] = count;
            }
        }
    } else {
        // Try EXTRACT (Oracle) then TO_CHAR fallback
        if (query.exec("SELECT EXTRACT(YEAR FROM HIRE_DATE) AS yr, COUNT(*) FROM EMPLOYER GROUP BY EXTRACT(YEAR FROM HIRE_DATE) ORDER BY yr DESC")) {
            while (query.next()) {
                int year = query.value(0).toInt();
                int count = query.value(1).toInt();
                stats.hiresPerYear[year] = count;
            }
        } else if (query.exec("SELECT TO_CHAR(HIRE_DATE,'YYYY') AS yr, COUNT(*) FROM EMPLOYER GROUP BY TO_CHAR(HIRE_DATE,'YYYY') ORDER BY yr DESC")) {
            while (query.next()) {
                QString yearStr = query.value(0).toString();
                int count = query.value(1).toInt();
                if (!yearStr.isEmpty()) stats.hiresPerYear[yearStr.toInt()] = count;
            }
        }
    }

    // Role distribution
    if (query.exec("SELECT ROLE, COUNT(*) FROM EMPLOYER GROUP BY ROLE")) {
        while (query.next()) {
            QString role = query.value(0).toString();
            int count = query.value(1).toInt();
            stats.roleDistribution[role] = count;
        }
    }

    // New employees this year & month (best-effort queries depending on driver)
    QDate now = QDate::currentDate();
    QString yearStr = QString::number(now.year());
    QString monthStr = QString("%1").arg(now.month(), 2, 10, QChar('0'));
    if (driver.contains("sqlite")) {
        QString q1 = QString("SELECT COUNT(*) FROM EMPLOYER WHERE strftime('%Y', HIRE_DATE) = '%1'").arg(yearStr);
        if (query.exec(q1) && query.next()) stats.newEmployeesThisYear = query.value(0).toInt();

        QString q2 = QString("SELECT COUNT(*) FROM EMPLOYER WHERE strftime('%Y', HIRE_DATE) = '%1' AND strftime('%m', HIRE_DATE) = '%2'")
                         .arg(yearStr).arg(monthStr);
        if (query.exec(q2) && query.next()) stats.newEmployeesThisMonth = query.value(0).toInt();
    } else {
        QString q1 = QString("SELECT COUNT(*) FROM EMPLOYER WHERE TO_CHAR(HIRE_DATE,'YYYY') = '%1'").arg(yearStr);
        if (!query.exec(q1)) {
            q1 = QString("SELECT COUNT(*) FROM EMPLOYER WHERE EXTRACT(YEAR FROM HIRE_DATE) = %1").arg(yearStr);
        }
        if (query.exec(q1) && query.next()) stats.newEmployeesThisYear = query.value(0).toInt();

        QString q2 = QString("SELECT COUNT(*) FROM EMPLOYER WHERE TO_CHAR(HIRE_DATE,'YYYY') = '%1' AND TO_CHAR(HIRE_DATE,'MM') = '%2'")
                         .arg(yearStr).arg(monthStr);
        if (!query.exec(q2)) {
            q2 = QString("SELECT COUNT(*) FROM EMPLOYER WHERE EXTRACT(YEAR FROM HIRE_DATE) = %1 AND EXTRACT(MONTH FROM HIRE_DATE) = %2").arg(yearStr).arg(now.month());
        }
        if (query.exec(q2) && query.next()) stats.newEmployeesThisMonth = query.value(0).toInt();
    }

    // Most common role
    if (!stats.roleDistribution.isEmpty()) {
        int best = -1;
        for (auto it = stats.roleDistribution.constBegin(); it != stats.roleDistribution.constEnd(); ++it) {
            if (it.value() > best) {
                best = it.value();
                stats.mostCommonRole = it.key();
            }
        }
    }

    // department count: distinct ROLE count
    if (query.exec("SELECT COUNT(DISTINCT ROLE) FROM EMPLOYER") && query.next()) {
        stats.departmentCount = query.value(0).toInt();
    }

    if (stats.totalEmployees > 0) {
        stats.retentionRate = (double)stats.activeEmployees / stats.totalEmployees * 100.0;
    } else {
        stats.retentionRate = 0.0;
    }

    // Min and Max Salary
    if (query.exec("SELECT MIN(SALARY), MAX(SALARY) FROM EMPLOYER") && query.next()) {
        stats.minSalary = query.value(0).toDouble();
        stats.maxSalary = query.value(1).toDouble();
    }

    // Hires per month in current year
    if (driver.contains("sqlite")) {
        QString qMonth = QString("SELECT strftime('%m', HIRE_DATE) AS mon, COUNT(*) FROM EMPLOYER WHERE strftime('%Y', HIRE_DATE) = '%1' GROUP BY mon ORDER BY mon").arg(yearStr);
        if (query.exec(qMonth)) {
            while (query.next()) {
                QString monStr = query.value(0).toString();
                int count = query.value(1).toInt();
                if (!monStr.isEmpty()) stats.hiresPerMonth[monStr.toInt()] = count;
            }
        }
    } else {
        QString qMonth = QString("SELECT TO_CHAR(HIRE_DATE,'MM') AS mon, COUNT(*) FROM EMPLOYER WHERE TO_CHAR(HIRE_DATE,'YYYY') = '%1' GROUP BY TO_CHAR(HIRE_DATE,'MM') ORDER BY mon").arg(yearStr);
        if (!query.exec(qMonth)) {
            qMonth = QString("SELECT EXTRACT(MONTH FROM HIRE_DATE) AS mon, COUNT(*) FROM EMPLOYER WHERE EXTRACT(YEAR FROM HIRE_DATE) = %1 GROUP BY EXTRACT(MONTH FROM HIRE_DATE) ORDER BY mon").arg(now.year());
        }
        if (query.exec(qMonth)) {
            while (query.next()) {
                int mon = query.value(0).toInt();
                int count = query.value(1).toInt();
                stats.hiresPerMonth[mon] = count;
            }
        }
    }

    // Top Projects managed by employers
    if (query.exec("SELECT PROJECT_NAME, COUNT(*) FROM PROJECTS GROUP BY PROJECT_NAME ORDER BY COUNT(*) DESC LIMIT 10")) {
        while (query.next()) {
            QString projName = query.value(0).toString();
            int count = query.value(1).toInt();
            stats.topProjects[projName] = count;
        }
    }

    // Top Resources used by employers
    if (query.exec("SELECT RESOURCE_NAME, COUNT(*) FROM RESSOURCE GROUP BY RESOURCE_NAME ORDER BY COUNT(*) DESC LIMIT 10")) {
        while (query.next()) {
            QString resName = query.value(0).toString();
            int count = query.value(1).toInt();
            stats.topResources[resName] = count;
        }
    }

    return stats;
}

bool Employer::exportToPdf(const QString &filePath, QString *errorMessage)
{
    QVector<Employer> employees = Employer::selectAll();

    if (employees.isEmpty()) {
        if (errorMessage) *errorMessage = "Aucun employé à exporter.";
        return false;
    }

    EmployerStatistics stats = Employer::computeStatistics();

    // Ensure Poppins is available for the document; it is added at application start in main.
    const QString poppinsRcc = ":/resources/fonts/Poppins-Light.ttf";
    static QString poppinsFamily;
    if (poppinsFamily.isEmpty()) {
        int fontId = QFontDatabase::addApplicationFont(poppinsRcc);
        if (fontId != -1) {
            QStringList families = QFontDatabase::applicationFontFamilies(fontId);
            if (!families.isEmpty()) poppinsFamily = families.first();
        }
    }

    QString html = "<html><head><style>";
    html += "@page { margin: 48px 30px 70px 30px; }"; // top/bottom margins for title & footer
    html += "body{font-family: 'Poppins', Arial, sans-serif; margin: 0px; font-size: 12px; color:#222;}";
    html += "table{width:100%; border-collapse:collapse; table-layout:fixed;}";
    html += "thead{display: table-header-group;}";
    html += "tr{page-break-inside: avoid;}";
    html += "th, td{border:1px solid #ddd; padding:8px; text-align:left; vertical-align:top;}";
    html += "th{background:#f7f7f7; font-weight:700; font-size:12px;}";
    html += "tr:nth-child(even){background:#fbfbfb;}";
    html += "thead th{background:#e9eefc; border-bottom:2px solid #d6ddf6;}";
    html += "td{overflow-wrap:break-word; word-break:break-word; hyphens:auto; white-space:normal;}";
    html += ".email{max-width:260px; overflow-wrap:break-word; text-align:left;}";
    html += "</style></head><body>";
    html += "<h1 align='center' style='font-size:20px; margin:10px 0; font-weight:700;'>Liste des employés</h1>";
    html += "<div style='text-align:center; margin-bottom:8px;color:#666;'>Comprehensive list of employees and analytics</div>";

    // Table of employees
    // Use colgroup to control widths; table-layout:fixed for consistent column sizing
    html += "<div style='display:flex; justify-content:space-between; gap:10px; margin-bottom:8px;'>";
    html += "<div style='flex:1; padding:8px; border-radius:6px; background:#f4f8ff; text-align:center; font-weight:600;'>Total: " + QString::number(stats.totalEmployees) + "</div>";
    html += "<div style='flex:1; padding:8px; border-radius:6px; background:#f4fff4; text-align:center; font-weight:600;'>Active: " + QString::number(stats.activeEmployees) + "</div>";
    html += "<div style='flex:1; padding:8px; border-radius:6px; background:#fff8f0; text-align:center; font-weight:600;'>Retention: " + QString::number(stats.retentionRate, 'f', 1) + "%</div>";
    html += "</div>";

    html += "<table><colgroup>";
    html += "<col style='width:6%'/><col style='width:14%'/><col style='width:14%'/><col style='width:26%'/><col style='width:12%'/><col style='width:18%'/><col style='width:10%'/></colgroup>";
    html += "<thead><tr><th style='text-align:center;'>ID</th><th>Prénom</th><th>Nom</th><th>Email</th><th>Téléphone</th><th>Rôle</th><th style='text-align:center;'>Date Embauche</th></tr></thead>";
    html += "<tbody>";

    for (const Employer &e : employees) {
        html += "<tr>";
        html += "<td>" + QString::number(e.employerId) + "</td>";
        html += "<td>" + e.firstName.toHtmlEscaped() + "</td>";
        html += "<td>" + e.lastName.toHtmlEscaped() + "</td>";
        html += "<td class='email'>" + e.email.toHtmlEscaped() + "</td>";
        html += "<td>" + e.phone.toHtmlEscaped() + "</td>";
        html += "<td>" + e.role.toHtmlEscaped() + "</td>";
        html += "<td>" + e.startDate.toString("yyyy-MM-dd") + "</td>";
        html += "</tr>";
    }
    html += "</tbody></table><br>";

    // Statistics section
    html += "<h2 style='margin-top: 18px; margin-bottom:4px;'>Statistiques</h2>";
    html += "<ul>";
    html += "<li>Total employés: " + QString::number(stats.totalEmployees) + "</li>";
    html += "<li>Employés actifs: " + QString::number(stats.activeEmployees) + "</li>";
    html += "<li>Nouvel(s) embauché(s) ce mois: " + QString::number(stats.newEmployeesThisMonth) + "</li>";
    html += "<li>Nouvel(s) embauché(s) cette année: " + QString::number(stats.newEmployeesThisYear) + "</li>";
    html += "<li>Salaire moyen: " + QString::number(stats.averageSalary, 'f', 2) + "</li>";
    html += "<li>Min salaire: " + QString::number(stats.minSalary, 'f', 2) + "</li>";
    html += "<li>Max salaire: " + QString::number(stats.maxSalary, 'f', 2) + "</li>";
    html += "<li>Taux de rétention: " + QString::number(stats.retentionRate, 'f', 2) + "%</li>";
    if (!stats.mostCommonRole.isEmpty()) {
        html += "<li>Rôle le plus courant: " + stats.mostCommonRole.toHtmlEscaped() + "</li>";
    }
    html += "</ul>";
    html += "<div style='margin-top:10px;'><strong>Top roles</strong></div>";

    // Role distribution (simple list)
    if (!stats.roleDistribution.isEmpty()) {
        html += "<h3>Distribution par rôle</h3>";
        html += "<table><tr><th>Rôle</th><th>Count</th></tr>";
        for (auto it = stats.roleDistribution.constBegin(); it != stats.roleDistribution.constEnd(); ++it) {
            html += "<tr>";
            html += "<td>" + it.key().toHtmlEscaped() + "</td>";
            html += "<td>" + QString::number(it.value()) + "</td>";
            html += "</tr>";
        }
        html += "</table>";
    }

    // Footer: centered text only (no image) — subtle separator line and small caption
    html += "<div style='position:fixed; left:0; right:0; bottom:6px; text-align:center;'>";
    html += "<div style='display:inline-block; margin:0 auto; padding-top:8px; border-top:1px solid #eee; width:100%;'>";
    html += "<div style='font-size:11px; color:#666; margin-top:6px;'>Inspira Studio — Rapport des employés • Generated " + QDate::currentDate().toString("yyyy-MM-dd") + "</div>";
    html += "</div></div>";

    html += "</body></html>";

    // Use QTextDocument + QPrinter to generate PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QTextDocument doc;
    // Explicitly set default font to Poppins if available; otherwise fallback
    if (!poppinsFamily.isEmpty()) {
        QFont defaultFont(poppinsFamily, 11);
        doc.setDefaultFont(defaultFont);
    } else {
        QFont f("Arial", 11);
        doc.setDefaultFont(f);
    }
    doc.setHtml(html);

    // Make sure the doc fits the page size (help with text flow/table wrapping)
    const QSizeF pageRect = printer.pageRect(QPrinter::Point).size();
    doc.setPageSize(pageRect);

    // Try printing to PDF; handle errors if thrown
    try {
        doc.print(&printer);
    } catch (...) {
        if (errorMessage) *errorMessage = "Erreur lors de la génération du PDF.";
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
