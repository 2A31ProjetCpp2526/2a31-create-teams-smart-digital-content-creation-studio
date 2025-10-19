#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCalendarWidget>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //Initialisation des buttons
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addAppointment);
   connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateSponsor);
   connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSelectedSponsor);
   connect(ui->afficherButton, &QPushButton::clicked, this, &MainWindow::loadSponsoring);

}

void MainWindow::addAppointment() {
    int id = ui->ID->text().toInt();
    QString nom = ui->Nom->text();
    QString email = ui->EM->text();
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();
    QString status = ui->STS->currentText();



    // Validate address selection
    if (status == "Selectionner...") {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une adresse valide.");
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
