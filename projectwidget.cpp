#include "projectwidget.h"
#include "ui_project.h"
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
ProjectWidget::ProjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);

    connect(ui->addproj, &QPushButton::clicked,
            this, &ProjectWidget::onAddProjClicked);
    connect(ui->edit, &QPushButton::clicked,
            this, &ProjectWidget::onEditProjClicked);
    connect(ui->deleteproj, &QPushButton::clicked,
            this, &ProjectWidget::onDeleteProjClicked);
    connect(ui->viewproj, &QPushButton::clicked,
            this, &ProjectWidget::onViewProjClicked);

}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::onAddProjClicked()
{
    QString pid = ui->pid->text().trimmed();
    QString titre = ui->titre->text().trimmed();
    QString desc = ui->desc->text().trimmed();
    QString status = ui->status->currentText().trimmed();

    emit addProjectRequested(pid, titre, desc, status);
}
void ProjectWidget::onEditProjClicked()
{
    // Database connection check
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open!");
        return;
    }

    QString pid = ui->pid->text().trimmed();
    if (pid.isEmpty()) {
        QMessageBox::warning(this, "Missing ID", "Please enter a Project ID to edit.");
        return;
    }

    // --- Fetch project info from DB ---
    QSqlQuery fetchQuery;
    fetchQuery.prepare(R"(
        SELECT TITRE, DESCRIPTION, STATUS, DATE_CREATION
        FROM PROJET
        WHERE PROJET_ID = :id
    )");
    fetchQuery.bindValue(":id", pid);

    if (!fetchQuery.exec()) {
        QMessageBox::critical(this, "Database Error", fetchQuery.lastError().text());
        return;
    }

    if (!fetchQuery.next()) {
        QMessageBox::warning(this, "Not Found", "No project found with this ID.");
        return;
    }

    // Extract current project data
    QString currentTitre = fetchQuery.value("TITRE").toString();
    QString currentDesc = fetchQuery.value("DESCRIPTION").toString();
    QString currentStatus = fetchQuery.value("STATUS").toString();
    QString currentDate = fetchQuery.value("DATE_CREATION").toString();

    // --- Create edit dialog ---
    QDialog dialog(this);
    dialog.setWindowTitle("Edit Project");

    QFormLayout *formLayout = new QFormLayout(&dialog);

    QLineEdit *idEdit = new QLineEdit(pid, &dialog);
    idEdit->setReadOnly(true);

    QLineEdit *titleEdit = new QLineEdit(currentTitre, &dialog);
    QLineEdit *descEdit = new QLineEdit(currentDesc, &dialog);
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems({"ACTIVE", "ARCHIVED", "PUBLISHED"});
    statusCombo->setCurrentText(currentStatus);

    QLineEdit *dateEdit = new QLineEdit(currentDate, &dialog);
    dateEdit->setReadOnly(true);

    formLayout->addRow("Project ID:", idEdit);
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Description:", descEdit);
    formLayout->addRow("Status:", statusCombo);
    formLayout->addRow("Date Created:", dateEdit);

    QDialogButtonBox *buttons =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    formLayout->addWidget(buttons);

    QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // --- If user clicks OK ---
    if (dialog.exec() == QDialog::Accepted)
    {
        QString newTitre = titleEdit->text().trimmed();
        QString newDesc = descEdit->text().trimmed();
        QString newStatus = statusCombo->currentText().trimmed();

        if (newTitre.isEmpty() || newDesc.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Please fill all fields before saving.");
            return;
        }

        QSqlQuery updateQuery;
        updateQuery.prepare(R"(
            UPDATE PROJET
            SET TITRE = :titre,
                DESCRIPTION = :desc,
                STATUS = :status
            WHERE PROJET_ID = :id
        )");

        updateQuery.bindValue(":titre", newTitre);
        updateQuery.bindValue(":desc", newDesc);
        updateQuery.bindValue(":status", newStatus);
        updateQuery.bindValue(":id", pid);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Success", "Project updated successfully!");

            // update your UI fields too
            ui->titre->setText(newTitre);
            ui->desc->setText(newDesc);
            ui->status->setCurrentText(newStatus);

            emit editProjectRequested(pid, newTitre, newDesc, newStatus);
        } else {
            QMessageBox::critical(this, "Database Error",
                                  updateQuery.lastError().text() +
                                      "\nQuery: " + updateQuery.lastQuery());
        }
    }
}

void ProjectWidget::onDeleteProjClicked()
{
    QString pid = ui->pid->text().trimmed();

    if (pid.isEmpty()) {
        QMessageBox::warning(this, "Missing ID", "Please enter the Project ID to delete.");
        return;
    }

    // Confirm deletion
    QMessageBox::StandardButton confirm = QMessageBox::question(
        this,
        "Confirm Deletion",
        "Are you sure you want to delete project with ID " + pid + "?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (confirm != QMessageBox::Yes)
        return;

    // Check database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open!");
        return;
    }

    // Verify project exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM PROJET WHERE PROJET_ID = :id");
    checkQuery.bindValue(":id", pid);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        return;
    }

    checkQuery.next();
    int count = checkQuery.value(0).toInt();

    if (count == 0) {
        QMessageBox::warning(this, "Not Found", "No project with this ID exists.");
        return;
    }

    // Perform deletion
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM PROJET WHERE PROJET_ID = :id");
    deleteQuery.bindValue(":id", pid);

    if (deleteQuery.exec()) {
        QMessageBox::information(this, "Success", "Project deleted successfully!");

        // Clear UI fields
        ui->pid->clear();
        ui->titre->clear();
        ui->desc->clear();
        ui->status->setCurrentIndex(0);

        emit deleteProjectRequested(pid);
    } else {
        QMessageBox::critical(this, "Database Error",
                              deleteQuery.lastError().text() +
                                  "\nQuery: " + deleteQuery.lastQuery());
    }
}

void ProjectWidget::onViewProjClicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open!");
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT PROJET_ID, TITRE, DESCRIPTION, STATUS, DATE_CREATION FROM PROJET")) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    ui->twp->setRowCount(0);
    ui->twp->setColumnCount(5);
    ui->twp->setHorizontalHeaderLabels({"ID", "Title", "Description", "Status", "Date Created"});

    int row = 0;
    while (query.next()) {
        ui->twp->insertRow(row);
        ui->twp->setItem(row, 0, new QTableWidgetItem(query.value("PROJET_ID").toString()));
        ui->twp->setItem(row, 1, new QTableWidgetItem(query.value("TITRE").toString()));
        ui->twp->setItem(row, 2, new QTableWidgetItem(query.value("DESCRIPTION").toString()));
        ui->twp->setItem(row, 3, new QTableWidgetItem(query.value("STATUS").toString()));
        ui->twp->setItem(row, 4, new QTableWidgetItem(query.value("DATE_CREATION").toString()));
        row++;
    }
}
