#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QDateTime>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    initializeUI();
    applyShadowEffects();
    connectSignals();
    populateSampleData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeUI()
{
    // Setup client table headers and resize
    ui->clientsTable->horizontalHeader()->setStretchLastSection(true);
    ui->clientsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Initialize modify form as empty and read-only
    // Modify tab removed - no modify form to initialize
    
    // Set icons programmatically to ensure they appear at runtime
    ui->exportCsvBtn->setIcon(QIcon(":/resources/icons/export.svg"));
    ui->btnSortByName->setIcon(QIcon(":/resources/icons/sort.svg"));
    ui->btnEditService->setIcon(QIcon(":/resources/icons/modify.svg"));
    ui->btnDeleteService->setIcon(QIcon(":/resources/icons/delete.svg"));
    ui->addServiceBtn->setIcon(QIcon(":/resources/icons/add.svg"));
    
    // Set tab icons programmatically
    ui->clientTabWidget->setTabIcon(0, QIcon(":/resources/icons/clients.svg"));
    // Tab 1 is now AI Recommendations - use chatbot icon
    ui->clientTabWidget->setTabIcon(1, QIcon(":/resources/icons/chatbot.svg"));
    ui->clientTabWidget->setTabIcon(2, QIcon(":/resources/icons/add.svg"));
    ui->clientTabWidget->setTabIcon(3, QIcon(":/resources/icons/star.svg"));
    
    qDebug() << "UI initialized successfully";
}

void MainWindow::connectSignals()
{
    // Connect CSV export button
    connect(ui->exportCsvBtn, &QPushButton::clicked, this, &MainWindow::onExportCsv);
    
    // Connect service management buttons
    connect(ui->addServiceBtn, &QPushButton::clicked, this, &MainWindow::onAddClient);
    
    // Connect table selection change
    connect(ui->clientsTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onClientTableSelectionChanged);
    
    qDebug() << "Signals connected successfully";
}

void MainWindow::populateSampleData()
{
    // Initialize client table as empty - no sample data
    ui->clientsTable->setRowCount(0);
    
    qDebug() << "Sample data populated - client table empty";
}

// Slot implementations
void MainWindow::onExportCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        tr("Export Services as CSV"), 
    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/services_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm") + ".csv",
        tr("CSV Files (*.csv)"));
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            
            // Write headers (reflect current table columns)
            stream << "Service ID,Name,Description,Category,Price,Date Created\n";
            
            // Write data rows
            for (int row = 0; row < ui->clientsTable->rowCount(); ++row) {
                QStringList rowData;
                for (int col = 0; col < ui->clientsTable->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->clientsTable->item(row, col);
                    rowData << (item ? item->text() : "");
                }
                stream << rowData.join(",") << "\n";
            }
            
            file.close();
            QMessageBox::information(this, "Export Successful", "Service data exported to: " + fileName);
        } else {
            QMessageBox::warning(this, "Export Failed", "Could not write to file: " + fileName);
        }
    }
}

void MainWindow::onAddClient()
{
    // Read new service-style add form
    QString name = ui->addNameEdit->text().trimmed();
    QString description = ui->addDescriptionEdit->toPlainText().trimmed();
    QString category = ui->addCategoryCombo->currentText().trimmed();
    QString price = ui->addPriceEdit->text().trimmed();
    QDateTime dateCreated = ui->addDateEdit->dateTime();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Name is a required field.");
        return;
    }

    // Generate new Service ID
    int newId = ui->clientsTable->rowCount() + 1;
    QString idStr = QString("%1").arg(newId, 3, 10, QChar('0'));

    // Add new row to table (Service ID, Name, Description, Category, Price, Date Created)
    int row = ui->clientsTable->rowCount();
    ui->clientsTable->insertRow(row);

    ui->clientsTable->setItem(row, 0, new QTableWidgetItem(idStr));
    ui->clientsTable->setItem(row, 1, new QTableWidgetItem(name));
    ui->clientsTable->setItem(row, 2, new QTableWidgetItem(description));
    ui->clientsTable->setItem(row, 3, new QTableWidgetItem(category));
    ui->clientsTable->setItem(row, 4, new QTableWidgetItem(price));
    ui->clientsTable->setItem(row, 5, new QTableWidgetItem(dateCreated.toString("yyyy-MM-dd HH:mm")));

    // Clear form fields
    ui->addNameEdit->clear();
    ui->addDescriptionEdit->clear();
    ui->addCategoryCombo->setCurrentIndex(0);
    ui->addPriceEdit->clear();
    ui->addDateEdit->setDateTime(QDateTime::currentDateTime());
    
    // Switch to display tab to show the new client
    ui->clientTabWidget->setCurrentIndex(0);
    
    QMessageBox::information(this, "Service Added", "Service '" + name + "' has been added successfully.");
}

void MainWindow::onDisplayClients()
{
    // TODO: Implement client display functionality
    // This could refresh data from a database
    QMessageBox::information(this, "Display Clients", "Client display functionality - placeholder implementation");
}

void MainWindow::onClientTableSelectionChanged()
{
    // Get the selected row
    int currentRow = ui->clientsTable->currentRow();
    if (currentRow >= 0) {
        // Selection changed - we keep the selection but no modify form exists now
    }
}

void MainWindow::applyShadowEffects()
{
    // Apply shadow effects to all QLineEdit elements
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits) {
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
        // Subtle shadow: small blur and low alpha
        shadow->setBlurRadius(4);
        shadow->setColor(QColor(0, 0, 0, 30));
        shadow->setOffset(0, 1);
        lineEdit->setGraphicsEffect(shadow);
    }
    
    // Apply shadow effects to all QPushButton elements
    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
        // Subtle shadow for buttons
        shadow->setBlurRadius(4);
        shadow->setColor(QColor(0, 0, 0, 36));
        shadow->setOffset(0, 1);
        button->setGraphicsEffect(shadow);
    }
    
    // Apply shadow effects to the main table
    QGraphicsDropShadowEffect* tableShadow = new QGraphicsDropShadowEffect();
    tableShadow->setBlurRadius(6);
    tableShadow->setColor(QColor(0, 0, 0, 30));
    tableShadow->setOffset(0, 1);
    ui->clientsTable->setGraphicsEffect(tableShadow);
}