#include "clientwidget.h"
#include "ui_client.h"
#include "backend/client.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

ClientWidget::ClientWidget(QWidget *parent) 
    : QWidget(parent), ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    
    // Connect signals
    connect(ui->addServiceBtn, &QPushButton::clicked, this, &ClientWidget::onAddClient);
    connect(ui->btnEditService, &QPushButton::clicked, this, &ClientWidget::onEditClient);
    connect(ui->btnDeleteService, &QPushButton::clicked, this, &ClientWidget::onDeleteClient);
    connect(ui->searchServices, &QLineEdit::textChanged, this, &ClientWidget::onSearchClient);
    connect(ui->exportCsvBtn, &QPushButton::clicked, this, &ClientWidget::onExportCsv);
    connect(ui->btnSortByName, &QPushButton::clicked, this, &ClientWidget::onSortByName);
    
    // Load initial data
    loadClients();
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::loadClients()
{
    QVector<Client> clients = Client::selectAll();
    
    ui->clientsTable->setRowCount(0);
    
    for (const Client &client : clients) {
        int row = ui->clientsTable->rowCount();
        ui->clientsTable->insertRow(row);
        
        ui->clientsTable->setItem(row, 0, new QTableWidgetItem(QString::number(client.clientId)));
        ui->clientsTable->setItem(row, 1, new QTableWidgetItem(client.firstName + " " + client.lastName));
        ui->clientsTable->setItem(row, 2, new QTableWidgetItem(client.email));
        ui->clientsTable->setItem(row, 3, new QTableWidgetItem("")); // Adresse (not in DB)
        ui->clientsTable->setItem(row, 4, new QTableWidgetItem(client.preferences));
        ui->clientsTable->setItem(row, 5, new QTableWidgetItem("")); // Date (not in DB)
    }
}

void ClientWidget::onAddClient()
{
    QString firstName = ui->lineEdit_firstName->text().trimmed();
    QString lastName = ui->lineEdit_lastName->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString preferences = ui->lineEdit_preferences->text().trimmed();
    
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || preferences.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields are required!");
        return;
    }
    
    Client newClient;
    newClient.firstName = firstName;
    newClient.lastName = lastName;
    newClient.email = email;
    newClient.preferences = preferences;
    
    if (Client::insert(newClient)) {
        QMessageBox::information(this, "Success", "Client added successfully!");
        clearAddForm();
        loadClients();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add client!");
    }
}

void ClientWidget::onEditClient()
{
    int currentRow = ui->clientsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a client to edit!");
        return;
    }
    
    qint64 clientId = ui->clientsTable->item(currentRow, 0)->text().toLongLong();
    
    Client client;
    if (!Client::fetchById(clientId, client)) {
        QMessageBox::critical(this, "Error", "Failed to fetch client!");
        return;
    }
    
    // Populate form
    ui->lineEdit_firstName->setText(client.firstName);
    ui->lineEdit_lastName->setText(client.lastName);
    ui->lineEdit_email->setText(client.email);
    ui->lineEdit_preferences->setText(client.preferences);
    
    // Switch to Add tab for editing
    ui->clientTabWidget->setCurrentIndex(1);
    
    // Disconnect and reconnect for update
    disconnect(ui->addServiceBtn, &QPushButton::clicked, this, &ClientWidget::onAddClient);
    connect(ui->addServiceBtn, &QPushButton::clicked, this, [this, clientId]() {
        onUpdateClient(clientId);
    });
}

void ClientWidget::onUpdateClient(qint64 clientId)
{
    QString firstName = ui->lineEdit_firstName->text().trimmed();
    QString lastName = ui->lineEdit_lastName->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString preferences = ui->lineEdit_preferences->text().trimmed();
    
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || preferences.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "All fields are required!");
        return;
    }
    
    Client updatedClient;
    updatedClient.firstName = firstName;
    updatedClient.lastName = lastName;
    updatedClient.email = email;
    updatedClient.preferences = preferences;
    
    if (Client::update(clientId, updatedClient)) {
        QMessageBox::information(this, "Success", "Client updated successfully!");
        clearAddForm();
        loadClients();
        ui->clientTabWidget->setCurrentIndex(0);
        
        // Restore add functionality
        disconnect(ui->addServiceBtn, nullptr, this, nullptr);
        connect(ui->addServiceBtn, &QPushButton::clicked, this, &ClientWidget::onAddClient);
    } else {
        QMessageBox::critical(this, "Error", "Failed to update client!");
    }
}

void ClientWidget::onDeleteClient()
{
    int currentRow = ui->clientsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a client to delete!");
        return;
    }
    
    qint64 clientId = ui->clientsTable->item(currentRow, 0)->text().toLongLong();
    QString clientName = ui->clientsTable->item(currentRow, 1)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete", 
        QString("Are you sure you want to delete client: %1?").arg(clientName),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        if (Client::remove(clientId)) {
            QMessageBox::information(this, "Success", "Client deleted successfully!");
            loadClients();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete client!");
        }
    }
}

void ClientWidget::onSearchClient(const QString &keyword)
{
    if (keyword.isEmpty()) {
        loadClients();
        return;
    }
    
    ui->clientsTable->setRowCount(0);
    QVector<Client> clients = Client::selectAll();
    
    for (const Client &client : clients) {
        QString fullName = client.firstName + " " + client.lastName;
        if (fullName.contains(keyword, Qt::CaseInsensitive) ||
            client.email.contains(keyword, Qt::CaseInsensitive) ||
            client.preferences.contains(keyword, Qt::CaseInsensitive)) {
            
            int row = ui->clientsTable->rowCount();
            ui->clientsTable->insertRow(row);
            
            ui->clientsTable->setItem(row, 0, new QTableWidgetItem(QString::number(client.clientId)));
            ui->clientsTable->setItem(row, 1, new QTableWidgetItem(fullName));
            ui->clientsTable->setItem(row, 2, new QTableWidgetItem(client.email));
            ui->clientsTable->setItem(row, 3, new QTableWidgetItem(""));
            ui->clientsTable->setItem(row, 4, new QTableWidgetItem(client.preferences));
            ui->clientsTable->setItem(row, 5, new QTableWidgetItem(""));
        }
    }
}

void ClientWidget::onExportCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to create file!");
        return;
    }
    
    QTextStream out(&file);
    out << "ID,First Name,Last Name,Email,Preferences\n";
    
    QVector<Client> clients = Client::selectAll();
    for (const Client &client : clients) {
        out << client.clientId << ","
            << client.firstName << ","
            << client.lastName << ","
            << client.email << ","
            << client.preferences << "\n";
    }
    
    file.close();
    QMessageBox::information(this, "Success", "Data exported successfully!");
}

void ClientWidget::onSortByName()
{
    ui->clientsTable->sortItems(1, Qt::AscendingOrder);
}

void ClientWidget::clearAddForm()
{
    ui->lineEdit_firstName->clear();
    ui->lineEdit_lastName->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_preferences->clear();
}
