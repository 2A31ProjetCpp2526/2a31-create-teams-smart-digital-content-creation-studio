#include "projectwidget.h"
#include "ui_project.h"
#include <QMessageBox>
#include <QDate>
#include <QDebug>

ProjectWidget::ProjectWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);
    
    // Initialize dates to current date
    ui->addCreationDateEdit->setDate(QDate::currentDate());
    ui->addModificationDateEdit->setDate(QDate::currentDate());
    
    // Connect buttons
    // List tab
    connect(ui->btnSortByName, &QPushButton::clicked, this, &ProjectWidget::onRefreshProjectsClicked);
    
    // Add tab (also used for updates)
    connect(ui->addServiceBtn, &QPushButton::clicked, this, &ProjectWidget::onAddProjectClicked);
    
    // Table buttons
    connect(ui->btnEditService, &QPushButton::clicked, this, &ProjectWidget::onEditFromTableClicked);
    connect(ui->btnDeleteService, &QPushButton::clicked, this, &ProjectWidget::onDeleteFromTableClicked);
    
    // Load initial projects
    loadAllProjects();
    
    qDebug() << "ProjectWidget initialized successfully";
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::loadAllProjects()
{
    qDebug() << "ProjectWidget::loadAllProjects() - Loading all projects...";
    
    // Clear table
    ui->projectTableWidget->setRowCount(0);
    
    // Get all projects from database
    QVector<Project> projects = Project::selectAll();
    
    qDebug() << "ProjectWidget::loadAllProjects() - Found" << projects.count() << "projects";
    
    if (projects.count() == 0) {
        qDebug() << "ProjectWidget::loadAllProjects() - No projects found";
        return;
    }
    
    // Populate table
    for (int i = 0; i < projects.count(); ++i) {
        const Project &project = projects.at(i);
        int row = ui->projectTableWidget->rowCount();
        ui->projectTableWidget->insertRow(row);
        
        // ID_PROJECT
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(project.projectId));
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        ui->projectTableWidget->setItem(row, 0, idItem);
        
        // TITLE
        QTableWidgetItem *titleItem = new QTableWidgetItem(project.title);
        idItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 1, titleItem);
        
        // DESCRIPTION
        QTableWidgetItem *descItem = new QTableWidgetItem(project.description);
        descItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 2, descItem);
        
        // ID_CLIENT - Display empty if -1 (NULL)
        QString clientIdStr = (project.clientId > 0) ? QString::number(project.clientId) : "-";
        QTableWidgetItem *clientItem = new QTableWidgetItem(clientIdStr);
        clientItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 3, clientItem);
        
        // ID_SERVICE - Display empty if -1 (NULL)
        QString serviceIdStr = (project.serviceId > 0) ? QString::number(project.serviceId) : "-";
        QTableWidgetItem *serviceItem = new QTableWidgetItem(serviceIdStr);
        serviceItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 4, serviceItem);
        
        // CREATION_DATE
        QTableWidgetItem *creationItem = new QTableWidgetItem(project.creationDate.toString("yyyy-MM-dd"));
        creationItem->setFlags(creationItem->flags() & ~Qt::ItemIsEditable);
        creationItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 5, creationItem);
        
        // MODIFICATION_DATE
        QTableWidgetItem *modItem = new QTableWidgetItem(project.modificationDate.toString("yyyy-MM-dd"));
        modItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 6, modItem);
        
        // OWNER_ID - Display empty if -1 (NULL)
        QString ownerIdStr = (project.ownerId > 0) ? QString::number(project.ownerId) : "-";
        QTableWidgetItem *ownerItem = new QTableWidgetItem(ownerIdStr);
        ownerItem->setForeground(QBrush(Qt::black));
        ui->projectTableWidget->setItem(row, 7, ownerItem);
        
        qDebug() << "ProjectWidget::loadAllProjects() - Added row:" << row << "- Project:" << project.title;
    }
}

void ProjectWidget::refreshTable()
{
    qDebug() << "ProjectWidget::refreshTable()";
    loadAllProjects();
}

void ProjectWidget::onRefreshProjectsClicked()
{
    qDebug() << "ProjectWidget::onRefreshProjectsClicked()";
    refreshTable();
}

void ProjectWidget::onAddProjectClicked()
{
    qDebug() << "ProjectWidget::onAddProjectClicked()";
    
    // Validate inputs
    QString title = ui->addTitleEdit->text().trimmed();
    QString description = ui->addDescriptionEdit->toPlainText().trimmed();
    
    if (title.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le titre est obligatoire");
        qDebug() << "ProjectWidget::onAddProjectClicked() - Title is empty";
        return;
    }
    
    if (description.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "La description est obligatoire");
        qDebug() << "ProjectWidget::onAddProjectClicked() - Description is empty";
        return;
    }
    
    // Create project object
    Project project;
    project.title = title;
    project.description = description;
    
    // Handle optional fields - convert empty to -1
    project.clientId = ui->addClientIdEdit->text().trimmed().isEmpty() ? -1 : ui->addClientIdEdit->text().toLongLong();
    project.serviceId = ui->addServiceIdEdit->text().trimmed().isEmpty() ? -1 : ui->addServiceIdEdit->text().toLongLong();
    project.creationDate = ui->addCreationDateEdit->date();
    project.modificationDate = ui->addModificationDateEdit->date();
    project.ownerId = -1; // Default to -1
    
    qDebug() << "ProjectWidget::onAddProjectClicked() - Creating project:" << project.title 
             << "clientId:" << project.clientId 
             << "serviceId:" << project.serviceId;
    
    // Insert into database
    if (Project::insert(project)) {
        qDebug() << "ProjectWidget::onAddProjectClicked() - Project inserted successfully";
        QMessageBox::information(this, "Succès", "Projet ajouté avec succès!");
        clearAddForm();
        refreshTable();
        
        // Switch to list tab
        ui->projectTabWidget->setCurrentIndex(0);
    } else {
        qDebug() << "ProjectWidget::onAddProjectClicked() - Failed to insert project";
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du projet à la base de données");
    }
}

void ProjectWidget::onUpdateProjectClicked(qint64 projectId)
{
    qDebug() << "ProjectWidget::onUpdateProjectClicked() - Updating project ID:" << projectId;
    
    if (projectId <= 0) {
        QMessageBox::critical(this, "Erreur", "ID de projet invalide");
        qDebug() << "ProjectWidget::onUpdateProjectClicked() - Invalid project ID:" << projectId;
        return;
    }
    
    // Get updated values from form
    QString title = ui->addTitleEdit->text().trimmed();
    QString description = ui->addDescriptionEdit->toPlainText().trimmed();
    
    if (title.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le titre est obligatoire");
        return;
    }
    
    if (description.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "La description est obligatoire");
        return;
    }
    
    // Create project object
    Project project;
    project.projectId = projectId;
    project.title = title;
    project.description = description;
    
    // Handle optional fields - convert empty to -1
    project.clientId = ui->addClientIdEdit->text().trimmed().isEmpty() ? -1 : ui->addClientIdEdit->text().toLongLong();
    project.serviceId = ui->addServiceIdEdit->text().trimmed().isEmpty() ? -1 : ui->addServiceIdEdit->text().toLongLong();
    project.creationDate = ui->addCreationDateEdit->date();
    project.modificationDate = ui->addModificationDateEdit->date();
    project.ownerId = -1;
    
    qDebug() << "ProjectWidget::onUpdateProjectClicked() - Updating:" << project.title 
             << "clientId:" << project.clientId 
             << "serviceId:" << project.serviceId;
    
    // Update in database
    if (Project::update(project)) {
        qDebug() << "ProjectWidget::onUpdateProjectClicked() - Project updated successfully";
        QMessageBox::information(this, "Succès", "Projet mis à jour avec succès!");
        clearAddForm();
        refreshTable();
        
        // Switch to list tab
        ui->projectTabWidget->setCurrentIndex(0);
        
        // Restore add functionality
        disconnect(ui->addServiceBtn, nullptr, this, nullptr);
        connect(ui->addServiceBtn, &QPushButton::clicked, this, &ProjectWidget::onAddProjectClicked);
        ui->addServiceBtn->setText("Ajouter");
        isEditingMode = false;
        currentEditingProjectId = -1;
        
        qDebug() << "ProjectWidget::onUpdateProjectClicked() - Editing mode disabled";
    } else {
        qDebug() << "ProjectWidget::onUpdateProjectClicked() - Failed to update project";
        QMessageBox::critical(this, "Erreur", "Erreur lors de la mise à jour du projet");
    }
}

void ProjectWidget::clearAddForm()
{
    ui->addTitleEdit->clear();
    ui->addDescriptionEdit->clear();
    ui->addClientIdEdit->clear();
    ui->addServiceIdEdit->clear();
    ui->addCreationDateEdit->setDate(QDate::currentDate());
    ui->addModificationDateEdit->setDate(QDate::currentDate());
}

void ProjectWidget::onEditFromTableClicked()
{
    qDebug() << "ProjectWidget::onEditFromTableClicked()";
    
    // Get selected row
    int selectedRow = ui->projectTableWidget->currentRow();
    
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un projet à modifier");
        return;
    }
    
    qDebug() << "ProjectWidget::onEditFromTableClicked() - Selected row:" << selectedRow;
    
    // Get project ID from first column
    QTableWidgetItem *idItem = ui->projectTableWidget->item(selectedRow, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer l'ID du projet");
        qDebug() << "ProjectWidget::onEditFromTableClicked() - idItem is NULL";
        return;
    }
    
    QString projectIdStr = idItem->text();
    qDebug() << "ProjectWidget::onEditFromTableClicked() - projectIdStr:" << projectIdStr;
    
    bool ok = false;
    qint64 projectId = projectIdStr.toLongLong(&ok);
    
    if (!ok || projectId <= 0) {
        QMessageBox::critical(this, "Erreur", "ID de projet invalide: " + projectIdStr);
        qDebug() << "ProjectWidget::onEditFromTableClicked() - Invalid project ID:" << projectIdStr;
        return;
    }
    
    qDebug() << "ProjectWidget::onEditFromTableClicked() - Selected project ID:" << projectId;
    
    // Load project data
    Project project;
    if (!Project::fetchById(projectId, project)) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger le projet (ID: " + QString::number(projectId) + ")");
        qDebug() << "ProjectWidget::onEditFromTableClicked() - Failed to fetch project with ID:" << projectId;
        return;
    }
    
    qDebug() << "ProjectWidget::onEditFromTableClicked() - Project loaded successfully. Title:" << project.title;
    
    // Populate Add tab form for editing
    ui->addTitleEdit->setText(project.title);
    ui->addDescriptionEdit->setPlainText(project.description);
    
    if (project.clientId > 0)
        ui->addClientIdEdit->setText(QString::number(project.clientId));
    else
        ui->addClientIdEdit->clear();
    
    if (project.serviceId > 0)
        ui->addServiceIdEdit->setText(QString::number(project.serviceId));
    else
        ui->addServiceIdEdit->clear();
    
    ui->addCreationDateEdit->setDate(project.creationDate);
    ui->addModificationDateEdit->setDate(project.modificationDate);
    
    // Switch to Add tab (which doubles as edit)
    ui->projectTabWidget->setCurrentIndex(1);
    
    // Change mode to editing
    isEditingMode = true;
    currentEditingProjectId = projectId;
    
    qDebug() << "ProjectWidget::onEditFromTableClicked() - Editing mode enabled. currentEditingProjectId:" << currentEditingProjectId;
    
    // Disconnect add button and reconnect for update
    disconnect(ui->addServiceBtn, &QPushButton::clicked, this, &ProjectWidget::onAddProjectClicked);
    connect(ui->addServiceBtn, &QPushButton::clicked, this, [this]() {
        qDebug() << "ProjectWidget::onEditFromTableClicked() - Lambda triggered. currentEditingProjectId:" << currentEditingProjectId;
        onUpdateProjectClicked(currentEditingProjectId);
    });
    
    // Change button text
    ui->addServiceBtn->setText("Mettre à jour");
    
    QMessageBox::information(this, "Succès", "Projet chargé. Modifiez les champs et cliquez sur 'Mettre à jour'");
}

void ProjectWidget::onDeleteFromTableClicked()
{
    qDebug() << "ProjectWidget::onDeleteFromTableClicked()";
    
    // Get selected row
    int selectedRow = ui->projectTableWidget->currentRow();
    
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un projet à supprimer");
        return;
    }
    
    // Get project ID and title from table
    QTableWidgetItem *idItem = ui->projectTableWidget->item(selectedRow, 0);
    QTableWidgetItem *titleItem = ui->projectTableWidget->item(selectedRow, 1);
    
    if (!idItem || !titleItem) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données du projet");
        return;
    }
    
    QString projectIdStr = idItem->text();
    QString projectTitle = titleItem->text();
    qint64 projectId = projectIdStr.toLongLong();
    
    qDebug() << "ProjectWidget::onDeleteFromTableClicked() - Selected project ID:" << projectId << "Title:" << projectTitle;
    
    // Confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        QString("Êtes-vous sûr de vouloir supprimer ce projet ?\n\n"
                "Titre: %1\nID: %2").arg(projectTitle).arg(projectIdStr),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // Delete from database (with cascade handling)
        if (Project::deleteProject(projectId)) {
            qDebug() << "ProjectWidget::onDeleteFromTableClicked() - Project deleted successfully";
            QMessageBox::information(this, "Succès", "Projet supprimé avec succès!");
            refreshTable();
        } else {
            qDebug() << "ProjectWidget::onDeleteFromTableClicked() - Failed to delete project";
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression du projet");
        }
    }
}
