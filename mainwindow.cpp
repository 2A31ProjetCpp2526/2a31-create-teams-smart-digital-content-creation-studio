#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCalendarWidget>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlRecord>
#include <QPrinter>
#include <QTextDocument>
#include <QTextCursor>
#include <QSqlQueryModel>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCharFormat>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //Initialisation des buttons
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addSponsor);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateSponsor);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSelectedSponsor);
    connect(ui->afficherButton, &QPushButton::clicked, this, &MainWindow::loadSponsoring);
    connect(ui->search1_2, &QPushButton::clicked, this, &MainWindow:: searchSponsorById);
    connect(ui->pdfexport, &QPushButton::clicked, this, &MainWindow::on_pdfexport_clicked);
    connect(ui->sort,&QPushButton::clicked, this, &MainWindow::on_sort_clicked);



}

void MainWindow::addSponsor() {
    int id = ui->ID->text().toInt();
    QString nom = ui->Nom->text();
    QString email = ui->EM->text();
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();
    QString status = ui->STS->currentText();



    // Validate address selection
    if (status == "Selectionner...") {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un status valide.");
        return;}
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM SPONSORING WHERE ID_SPONS = :id");
    checkQuery.bindValue(":id", id);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Erreur", checkQuery.lastError().text());
        return; // stop execution if query fails
    }
    if (ui->ID->text().isEmpty() || nom.isEmpty() || email.isEmpty() || !dd.isValid() || !df.isValid() || status.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return; // stop execution
    }
    checkQuery.next();
    int count = checkQuery.value(0).toInt();

    if (count > 0) {
        QMessageBox::warning(this, "Erreur", "Cet ID existe déjà !");
        return; // stop execution if ID exists
    }


        QSqlQuery query;
        query.prepare("INSERT INTO SPONSORING (ID_SPONS, NOM_SPONS, EMAIL, DATE_DÉBUT, DATE_FIN, STATUS) "
                      "VALUES (:id, :nom, :email, :dd, :df, :status)");

        // Bind values
        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":email", email);
        query.bindValue(":dd", dd.toString("yyyy-MM-dd")); // convert QDate to string for SQL
        query.bindValue(":df", df.toString("yyyy-MM-dd"));
        query.bindValue(":status", status);


        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Sponsor ajouté avec succès.");

        }

}

void MainWindow::loadSponsoring() {
    QSqlQuery query("SELECT * FROM SPONSORING"); // fetch all rows from SPONSORING

    // Clear the table first
    ui->affiche->clear();
    ui->affiche->setRowCount(0);
    ui->affiche->setColumnCount(6); // ID_SPONS, NOM_SPONS, EMAIL, DATE_DÉBUT, DATE_FIN, STATUS

    // Set headers
    QStringList headers = {"ID", "Nom", "Email", "Date Début", "Date Fin", "Status"};
    ui->affiche->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);

        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DÉBUT").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));

        row++;
    }

    // Make columns stretch to fill available space
    ui->affiche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::deleteSelectedSponsor() {
    // 1️⃣ Check if a row is selected
    int row = ui->affiche->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un sponsor à supprimer !");
        return;
    }

    // 2️⃣ Get the ID from the first column (ID_SPONS)
    QString id = ui->affiche->item(row, 0)->text();

    // 3️⃣ Ask for confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer la suppression",
                                  "Voulez-vous vraiment supprimer ce sponsor ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    // 4️⃣ Execute DELETE query
    QSqlQuery query;
    query.prepare("DELETE FROM SPONSORING WHERE ID_SPONS = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor supprimé avec succès.");
        loadSponsoring(); // Refresh the table after deletion
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}
void MainWindow::updateSponsor()
{
    int id = ui->ID->text().toInt(); // ID cannot be changed
    QString nom = ui->Nom->text();
    QString email = ui->EM->text();
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();
    QString status = ui->STS->currentText();

    // Validate input (no empty fields, valid dates)
    if (nom.isEmpty() || email.isEmpty() || !dd.isValid() || !df.isValid() || status.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement !");
        return;
    }

    // Execute UPDATE query
    QSqlQuery query;
    query.prepare("UPDATE SPONSORING SET NOM_SPONS = :nom, EMAIL = :email, DATE_DÉBUT = :dd, DATE_FIN = :df, STATUS = :status "
                  "WHERE ID_SPONS = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":dd", dd.toString("yyyy-MM-dd"));
    query.bindValue(":df", df.toString("yyyy-MM-dd"));
    query.bindValue(":status", status);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor mis à jour avec succès.");
        loadSponsoring(); // Refresh the table
        ui->ID->setDisabled(false); // Re-enable ID field after update
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}
void MainWindow::searchSponsorById()
{
    QString searchId = ui->search1->text().trimmed(); // get text from QLineEdit

    if (searchId.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à rechercher !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORING WHERE ID_SPONS = :id");
    query.bindValue(":id", searchId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        return;
    }

    // Clear table before showing search results
    ui->affiche->clear();
    ui->affiche->setRowCount(0);
    ui->affiche->setColumnCount(6);
    QStringList headers = {"ID", "Nom", "Email", "Date Début", "Date Fin", "Status"};
    ui->affiche->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DÉBUT").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        row++;
    }

    ui->affiche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::on_pdfexport_clicked()
{
    // ✅ 1. Check DB connection
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "Erreur", "Base de données non connectée !");
        return;
    }

    // ✅ 2. Choose file
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty())
        return;

    // ✅ 3. Load data into model
    QSqlQueryModel model;
    model.setQuery("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DÉBUT, DATE_FIN, STATUS FROM SPONSORING");

    if (model.rowCount() == 0) {
        QMessageBox::information(this, "Info", "Aucune donnée trouvée dans la table SPONSORING.");
        return;
    }

    // ✅ 4. Build HTML from model
    QString html;
    html += "<html><head><style>"
            "body { font-family: Arial; margin: 20px; }"
            "table { width: 100%; border-collapse: collapse; }"
            "th, td { border: 1px solid #000; padding: 8px; text-align: center; }"
            "th { background-color: #f2f2f2; }"
            "</style></head><body>";
    html += "<h2 align='center'>Liste des Sponsors</h2><br>";
    html += "<table><tr>";

    // ✅ Table headers
    for (int col = 0; col < model.columnCount(); col++) {
        html += "<th>" + model.headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // ✅ Table data
    for (int row = 0; row < model.rowCount(); row++) {
        html += "<tr>";
        for (int col = 0; col < model.columnCount(); col++) {
            html += "<td>" + model.data(model.index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table></body></html>";

    // ✅ 5. Export to PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this, "Succès ✅", "Le fichier PDF a été généré avec succès !");
}
void MainWindow::on_sort_clicked()
{
    // ✅ Prepare SQL query (sorted by ID_SPONS ascending)
    QSqlQuery query;
    if (!query.exec("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DÉBUT, DATE_FIN, STATUS FROM SPONSORING ORDER BY ID_SPONS ASC")) {
        QMessageBox::critical(this, "Erreur SQL", "Échec du tri : " + query.lastError().text());
        return;
    }

    // ✅ Clear old data from table
    ui->affiche->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DÉBUT").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        row++;
    }

    QMessageBox::information(this, "Tri effectué", "Les sponsors ont été triés par ID_SPONS (ordre croissant).");
}
