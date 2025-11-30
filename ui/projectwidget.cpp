#include "projectwidget.h"
#include "ui_project.h"
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QComboBox>
#include <algorithm>
#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QUrl>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QUrl>
#include <QPixmap>
#include <QLabel>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

// Local dialog for project statistics
class ProjectStatisticsDialog : public QDialog
{
public:
    explicit ProjectStatisticsDialog(QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Project Statistics");
        resize(700, 420);

        QVBoxLayout *layout = new QVBoxLayout(this);
        summaryLabel = new QLabel(this);
        summaryLabel->setWordWrap(true);
        layout->addWidget(summaryLabel);

        // Sorting/filters
        QHBoxLayout *topControls = new QHBoxLayout();
        QLabel *sortLabel = new QLabel("Sort by:", this);
        topControls->addWidget(sortLabel);
        sortCombo = new QComboBox(this);
        sortCombo->addItem("ID (desc)");
        sortCombo->addItem("Title (asc)");
        sortCombo->addItem("Creation date (desc)");
        sortCombo->addItem("Age (desc)");
        topControls->addWidget(sortCombo);
        topControls->addStretch();
        layout->addLayout(topControls);

        table = new QTableWidget(this);
        table->setColumnCount(7);
        QStringList headers;
        headers << "ID" << "Title" << "Creation Date" << "Modification Date" << "Age (days)" << "Owner ID" << "Description";
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setStretchLastSection(true);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSortingEnabled(true);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layout->addWidget(table);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch();
        QPushButton *closeBtn = new QPushButton("Close", this);
        connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
        buttonLayout->addWidget(closeBtn);
        QPushButton *exportBtn = new QPushButton("Export CSV", this);
        connect(exportBtn, &QPushButton::clicked, this, [this]() {
            QString fileName = QFileDialog::getSaveFileName(this, "Export Statistics to CSV", "", "CSV Files (*.csv)");
            if (fileName.isEmpty()) return;
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier !");
                return;
            }
                QTextStream out(&file);
            out << "ID,Title,CreationDate,ModificationDate,AgeDays,OwnerId,Description\n";
            QVector<Project::ProjectOnlyStats> stats2 = Project::selectProjectOnlyStats();
            for (const auto &s : stats2) {
                QString escTitle = s.title;
                escTitle.replace("\"", "\"\"");
                out << s.projectId << ",\"" << escTitle << "\"," 
                    << s.creationDate.toString("yyyy-MM-dd") << ","
                    << s.modificationDate.toString("yyyy-MM-dd") << ","
                    << s.ageDays << ","
                    << (s.ownerId > 0 ? QString::number(s.ownerId) : QString("")) << ",\""
                    << s.description.left(200).replace("\"", "\"\"") << "\"\n";
            }
            file.close();
            QMessageBox::information(this, "Succès", "Statistiques exportées vers CSV !");
        });
        buttonLayout->addWidget(exportBtn);
        layout->addLayout(buttonLayout);

        populate();
        connect(sortCombo, &QComboBox::currentIndexChanged, this, [this](){
            // Re-fetch and repopulate with new order
            populate();
        });
    }

private:
    void populate()
    {
        QVector<Project::ProjectOnlyStats> stats = Project::selectProjectOnlyStats();
        // Client-side sort depending on sortCombo
        int metric = sortCombo->currentIndex();
        if (metric == 0) {
            // ID (desc)
            std::sort(stats.begin(), stats.end(), [](auto &a, auto &b){ return a.projectId > b.projectId; });
        } else if (metric == 1) {
            // Title (asc)
            std::sort(stats.begin(), stats.end(), [](auto &a, auto &b){ return a.title < b.title; });
        } else if (metric == 2) {
            // Creation date (desc)
            std::sort(stats.begin(), stats.end(), [](auto &a, auto &b){ return a.creationDate > b.creationDate; });
        } else if (metric == 3) {
            // Age (desc)
            std::sort(stats.begin(), stats.end(), [](auto &a, auto &b){ return a.ageDays > b.ageDays; });
        }
        table->setRowCount(0);

        int totalProjects = stats.size();
        int totalAge = 0;

        for (int i = 0; i < stats.size(); ++i) {
            const Project::ProjectOnlyStats &stat = stats.at(i);
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(QString::number(stat.projectId)));
            table->setItem(row, 1, new QTableWidgetItem(stat.title));
            table->setItem(row, 2, new QTableWidgetItem(stat.creationDate.toString("yyyy-MM-dd")));
            table->setItem(row, 3, new QTableWidgetItem(stat.modificationDate.toString("yyyy-MM-dd")));
            table->setItem(row, 4, new QTableWidgetItem(QString::number(stat.ageDays)));
            table->setItem(row, 5, new QTableWidgetItem(stat.ownerId > 0 ? QString::number(stat.ownerId) : QString("-")));
            table->setItem(row, 6, new QTableWidgetItem(stat.description.left(80)));

            totalAge += stat.ageDays;
        }

        double avgAge = totalProjects == 0 ? 0.0 : (double)totalAge / totalProjects;
        QString earliest = totalProjects ? stats.last().creationDate.toString("yyyy-MM-dd") : QString("-");
        QString latest = totalProjects ? stats.first().creationDate.toString("yyyy-MM-dd") : QString("-");
        summaryLabel->setText(QString("Total projects: %1    Avg age (days): %2    First creation: %3    Last creation: %4")
                  .arg(totalProjects)
                  .arg(QString::number(avgAge, 'f', 1))
                  .arg(earliest)
                  .arg(latest));
    }

    QComboBox *sortCombo;
    QTableWidget *table;
    QLabel *summaryLabel;
};

ProjectWidget::ProjectWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);
    
    // Initialize insertion and rollback handlers
    insertionHandler = new ProjectInsertion();
    rollbackHandler = new ProjectRollback();

    // Multimedia pointers init
    mediaPlayer = nullptr;
    videoWidget = nullptr;
    videoSlider = nullptr;
    playPauseBtn = nullptr;
    
    // Initialize dates to current date
    ui->addCreationDateEdit->setDate(QDate::currentDate());
    ui->addModificationDateEdit->setDate(QDate::currentDate());
    
    // Connect buttons
    // List tab
    connect(ui->btnSortByName, &QPushButton::clicked, this, &ProjectWidget::onRefreshProjectsClicked);
    // Search / sort / export buttons
    connect(ui->searchServices, &QLineEdit::textChanged, this, &ProjectWidget::onSearchProject);
    connect(ui->searchprojet, &QPushButton::clicked, this, &ProjectWidget::onSearchProjectClicked);
    connect(ui->sortbytitle, &QPushButton::clicked, this, &ProjectWidget::onSortByTitleClicked);
    connect(ui->exportexel, &QPushButton::clicked, this, &ProjectWidget::onExportExelClicked);
    connect(ui->statistics, &QPushButton::clicked, this, &ProjectWidget::onStatisticsClicked);
    
    // Add tab (also used for updates)
    connect(ui->addServiceBtn, &QPushButton::clicked, this, &ProjectWidget::onAddProjectClicked);
    
    // Table buttons
    connect(ui->btnEditService, &QPushButton::clicked, this, &ProjectWidget::onEditFromTableClicked);
    connect(ui->btnDeleteService, &QPushButton::clicked, this, &ProjectWidget::onDeleteFromTableClicked);

    // Connect insertion UI signals
    connect(ui->insertionAddBtn, &QPushButton::clicked, this, &ProjectWidget::onInsertionImportClicked);
    connect(ui->insertionRemoveBtn, &QPushButton::clicked, this, &ProjectWidget::onInsertionRemoveClicked);
    connect(ui->insertionClearBtn, &QPushButton::clicked, this, &ProjectWidget::onInsertionClearClicked);
    // open in default player button removed
    connect(ui->insertionList, &QListWidget::itemActivated, this, &ProjectWidget::onInsertionItemActivated);
    // also single click to preview immediately
    connect(ui->insertionList, &QListWidget::itemClicked, this, &ProjectWidget::onInsertionItemActivated);

    // Connect rollback UI signals (ensure visible and enabled)
    connect(ui->rollbackAddBtn, &QPushButton::clicked, this, &ProjectWidget::onRollbackAddClicked);
    connect(ui->rollbackDoBtn, &QPushButton::clicked, this, &ProjectWidget::onRollbackDoClicked);
    connect(ui->rollbackClearBtn, &QPushButton::clicked, this, &ProjectWidget::onRollbackClearClicked);
    // Make sure rollback buttons are visible and usable
    ui->rollbackAddBtn->setVisible(true);
    ui->rollbackDoBtn->setVisible(true);
    ui->rollbackClearBtn->setVisible(true);
    ui->rollbackAddBtn->setEnabled(true);
    ui->rollbackDoBtn->setEnabled(true);
    ui->rollbackClearBtn->setEnabled(true);
    // Force visible color (avoid invisible due to stylesheet)
    ui->rollbackAddBtn->setStyleSheet("background-color: #007bff; color: white;");
    ui->rollbackDoBtn->setStyleSheet("background-color: #17a2b8; color: white;");
    ui->rollbackClearBtn->setStyleSheet("background-color: #e53935; color: white;");
    
    // Load initial projects and media/rollback data
    loadAllProjects();
    // Load and show saved lists
    loadMediaListUI();
    loadRollbackHistoryUI();
    // Set UI references
    videoSlider = ui->insertionSlider;
    playPauseBtn = ui->insertionPlayBtn;
    setupVideoPlayer();
    
    qDebug() << "ProjectWidget initialized successfully";
}

ProjectWidget::~ProjectWidget()
{
    // delete handlers created without parent
    delete insertionHandler;
    delete rollbackHandler;
    if (mediaPlayer) {
        mediaPlayer->stop();
    }
    delete ui;
}

void ProjectWidget::loadAllProjects()
{
    qDebug() << "ProjectWidget::loadAllProjects() - Loading all projects...";
    
    // Clear table
    ui->projectTableWidget->setRowCount(0);
    
    // Get all projects from database
    QVector<Project> projects = Project::selectAll();
    if (projects.count() == 0) {
        qDebug() << "ProjectWidget::loadAllProjects() - No projects found";
        return;
    }

    populateProjectTable(projects);
}

void ProjectWidget::populateProjectTable(const QVector<Project> &projects)
{
    qDebug() << "ProjectWidget::populateProjectTable - Populating" << projects.count() << "projects";
    ui->projectTableWidget->setRowCount(0);

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

void ProjectWidget::onSearchProject(const QString &keyword)
{
    // Triggered while typing
    if (keyword.trimmed().isEmpty()) {
        loadAllProjects();
        return;
    }

    QVector<Project> projects = Project::search(keyword);
    populateProjectTable(projects);
}

void ProjectWidget::onSearchProjectClicked()
{
    QString keyword = ui->searchServices->text().trimmed();
    onSearchProject(keyword);
}

void ProjectWidget::onSortByTitleClicked()
{
    QVector<Project> projects = Project::selectAllSortedByTitle(true);
    populateProjectTable(projects);
    QMessageBox::information(this, "Tri", "Tri effectué par titre (ordre ascendant)");
}

void ProjectWidget::onExportExelClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QVector<Project> projects = Project::selectAll();
    if (Project::exportToCsv(fileName, projects)) {
        QMessageBox::information(this, "Succès", "Données exportées vers CSV avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'exporter les données vers le fichier !");
    }
}

void ProjectWidget::onStatisticsClicked()
{
    // Show a dialog with comprehensive statistics
    ProjectStatisticsDialog dlg(this);
    dlg.exec();
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
    
    // Insert into database and get the new project id
    qint64 newId = Project::insert(project);
    if (newId > 0) {
        qDebug() << "ProjectWidget::onAddProjectClicked() - Project inserted successfully";
        QMessageBox::information(this, "Succès", "Projet ajouté avec succès!");
        clearAddForm();
        refreshTable();
        
        // Switch to list tab
        ui->projectTabWidget->setCurrentIndex(0);
        // Create rollback entry to DELETE the newly inserted project
        QString actionText = QString("Added project: %1 - %2").arg(QString::number(newId)).arg(project.title);
        QString undoSql = QString("DELETE FROM PROJECTS WHERE ID_PROJECT = %1").arg(QString::number(newId));
        // current persisted history
        QStringList currentHistory = rollbackHandler->loadRollbackHistoryFromFile();
        rollbackHandler->addAction(actionText, undoSql, currentHistory);
        loadRollbackHistoryUI();
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
    
        // Build undo SQL from existing data (fetch previous state)
        Project previous = Project::selectById(projectId);
        // Escape single quotes
        auto escape = [](const QString &s){ QString r = s; r.replace("'", "''"); return r; };
        QString prevTitleEsc = escape(previous.title);
        QString prevDescEsc = escape(previous.description);
        QString prevCreation = previous.creationDate.toString("yyyy-MM-dd");
        QString prevModification = previous.modificationDate.toString("yyyy-MM-dd");
        QString prevClient = previous.clientId > 0 ? QString::number(previous.clientId) : QString("NULL");
        QString prevService = previous.serviceId > 0 ? QString::number(previous.serviceId) : QString("NULL");
        QString prevOwner = previous.ownerId > 0 ? QString::number(previous.ownerId) : QString("NULL");

        QString undoSql = QString("UPDATE PROJECTS SET TITLE = '%1', DESCRIPTION = '%2', ID_CLIENT = %3, ID_SERVICE = %4, CREATION_DATE = TO_DATE('%5', 'YYYY-MM-DD'), MODIFICATION_DATE = TO_DATE('%6', 'YYYY-MM-DD'), OWNER_ID = %7 WHERE ID_PROJECT = %8")
            .arg(prevTitleEsc, prevDescEsc, prevClient, prevService, prevCreation, prevModification, prevOwner, QString::number(projectId));

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
        
        // Record rollback action to restore previous values
        QString actionText = QString("Updated project: %1 - %2").arg(QString::number(projectId)).arg(project.title);
        QStringList currentHistory = rollbackHandler->loadRollbackHistoryFromFile();
        rollbackHandler->addAction(actionText, undoSql, currentHistory);
        loadRollbackHistoryUI();

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
        // Fetch current project to build undo SQL before deletion
        Project existing = Project::selectById(projectId);
        auto escape = [](const QString &s){ QString r = s; r.replace("'", "''"); return r; };
        QString titleEsc = escape(existing.title);
        QString descEsc = escape(existing.description);
        QString creation = existing.creationDate.toString("yyyy-MM-dd");
        QString modification = existing.modificationDate.toString("yyyy-MM-dd");
        QString client = existing.clientId > 0 ? QString::number(existing.clientId) : QString("NULL");
        QString service = existing.serviceId > 0 ? QString::number(existing.serviceId) : QString("NULL");
        QString owner = existing.ownerId > 0 ? QString::number(existing.ownerId) : QString("NULL");

        QString undoSql = QString("INSERT INTO PROJECTS (ID_PROJECT, ID_CLIENT, ID_SERVICE, TITLE, DESCRIPTION, CREATION_DATE, MODIFICATION_DATE, OWNER_ID) VALUES (%1, %2, %3, '%4', '%5', TO_DATE('%6','YYYY-MM-DD'), TO_DATE('%7','YYYY-MM-DD'), %8)")
            .arg(QString::number(projectId), client, service, titleEsc, descEsc, creation, modification, owner);

        // Delete from database (with cascade handling)
        if (Project::deleteProject(projectId)) {
            qDebug() << "ProjectWidget::onDeleteFromTableClicked() - Project deleted successfully";
            QMessageBox::information(this, "Succès", "Projet supprimé avec succès!");
            // Add rollback entry to re-insert the project if needed
            QString actionText = QString("Deleted project: %1 - %2").arg(QString::number(projectId)).arg(projectTitle);
            QStringList currentHistory = rollbackHandler->loadRollbackHistoryFromFile();
            rollbackHandler->addAction(actionText, undoSql, currentHistory);
            loadRollbackHistoryUI();

            refreshTable();
        } else {
            qDebug() << "ProjectWidget::onDeleteFromTableClicked() - Failed to delete project";
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression du projet");
        }
    }
}

// ============ Insertion (media) methods ============

void ProjectWidget::loadMediaListUI()
{
    ui->insertionList->clear();
    QStringList mediaPaths = insertionHandler->loadMediaListFromFile();

    for (const QString &path : mediaPaths) {
        QListWidgetItem *item = new QListWidgetItem(QFileInfo(path).fileName());
        item->setData(Qt::UserRole, path);
        
        QString ext = QFileInfo(path).suffix().toLower();
        if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp" || ext == "gif") {
            item->setIcon(QIcon(":/icons/camera.svg"));
        } else {
            item->setIcon(QIcon(":/icons/display.svg"));
        }
        ui->insertionList->addItem(item);
    }

    qDebug() << "ProjectWidget::loadMediaListUI() - Loaded" << mediaPaths.count() << "media items";
}

void ProjectWidget::onInsertionImportClicked()
{
    qDebug() << "ProjectWidget::onInsertionImportClicked()";
    
    QStringList files = QFileDialog::getOpenFileNames(this, "Select media files", QDir::homePath(),
                        "Media Files (*.png *.jpg *.jpeg *.bmp *.gif *.mp4 *.mkv *.webm *.avi);;All Files (*)");
    
    if (files.isEmpty()) {
        return;
    }

    // Get current media list
    QStringList currentList;
    for (int i = 0; i < ui->insertionList->count(); ++i) {
        currentList.append(ui->insertionList->item(i)->data(Qt::UserRole).toString());
    }

    // Add new files (avoid duplicates)
    for (const QString &path : files) {
        if (currentList.contains(path)) {
            qDebug() << "ProjectWidget::onInsertionImportClicked() - Skipping duplicate:" << path;
            continue;
        }

        currentList.append(path);
        QListWidgetItem *item = new QListWidgetItem(QFileInfo(path).fileName());
        item->setData(Qt::UserRole, path);
        
        QString ext = QFileInfo(path).suffix().toLower();
        if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp" || ext == "gif") {
            item->setIcon(QIcon(":/icons/camera.svg"));
        } else {
            item->setIcon(QIcon(":/icons/display.svg"));
        }
        ui->insertionList->addItem(item);
    }

    // Save to file
    insertionHandler->saveMediaListToFile(currentList);
    qDebug() << "ProjectWidget::onInsertionImportClicked() - Saved" << currentList.count() << "items";
}

void ProjectWidget::onInsertionRemoveClicked()
{
    qDebug() << "ProjectWidget::onInsertionRemoveClicked()";
    
    QListWidgetItem *current = ui->insertionList->currentItem();
    if (!current) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un média à supprimer");
        return;
    }

    // Get updated list without this item
    QStringList updatedList;
    for (int i = 0; i < ui->insertionList->count(); ++i) {
        QListWidgetItem *item = ui->insertionList->item(i);
        if (item != current) {
            updatedList.append(item->data(Qt::UserRole).toString());
        }
    }

    // stop video if it was playing
    QString currentPath = current->data(Qt::UserRole).toString();
    // get path before deleting item
    QString removedPath = current->data(Qt::UserRole).toString();
    delete current;
    if (mediaPlayer && mediaPlayer->source().isLocalFile() && mediaPlayer->source().toLocalFile() == currentPath) {
        mediaPlayer->stop();
        if (videoWidget) videoWidget->hide();
        ui->insertionPreview->show();
    }
    insertionHandler->saveMediaListToFile(updatedList);
    if (updatedList.isEmpty()) {
        QString filePath = insertionHandler->getMediaListFilePath();
        if (QFile::exists(filePath)) QFile::remove(filePath);
    }
    qDebug() << "ProjectWidget::onInsertionRemoveClicked() - Removed item" << removedPath;
}

void ProjectWidget::onInsertionClearClicked()
{
    qDebug() << "ProjectWidget::onInsertionClearClicked()";
    
    if (ui->insertionList->count() == 0) {
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmer", 
        "Êtes-vous sûr de vouloir vider toute la liste des médias?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        ui->insertionList->clear();
        insertionHandler->saveMediaListToFile(QStringList());
        if (mediaPlayer) mediaPlayer->stop();
        if (videoWidget) videoWidget->hide();
        ui->insertionPreview->show();
        // delete persisted file in project root
        QString path = insertionHandler->getMediaListFilePath();
        if (QFile::exists(path)) {
            QFile::remove(path);
            qDebug() << "ProjectWidget::onInsertionClearClicked() - Removed file:" << path;
        }
        qDebug() << "ProjectWidget::onInsertionClearClicked() - List cleared";
    }
}

// 'Open in default player' function removed - preview opens in app instead.

void ProjectWidget::onInsertionItemActivated(QListWidgetItem* item)
{
    if (!item) return;
    showMediaPreview(item->data(Qt::UserRole).toString());
}

void ProjectWidget::showMediaPreview(const QString &path)
{
    qDebug() << "ProjectWidget::showMediaPreview() - Path:" << path;
    
    if (path.isEmpty()) return;

    QString ext = QFileInfo(path).suffix().toLower();
    
    if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp" || ext == "gif") {
        // Show image in preview label
        QPixmap pix;
        if (!pix.load(path)) {
            QMessageBox::critical(this, "Erreur", "Impossible de charger l'image: " + path);
            qDebug() << "ProjectWidget::showMediaPreview() - Failed to load image";
            return;
        }

        QLabel *previewLabel = ui->insertionPreview;
        previewLabel->setPixmap(pix.scaled(previewLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            if (videoWidget) videoWidget->hide();
            previewLabel->show();
        qDebug() << "ProjectWidget::showMediaPreview() - Image displayed";
    } else {
        // For videos, play inside the app
        if (!QFile::exists(path)) {
            QMessageBox::critical(this, "Erreur", "Le fichier vidéo n'existe pas: " + path);
            qDebug() << "ProjectWidget::showMediaPreview() - Video path does not exist:" << path;
            return;
        }
        if (!videoWidget) setupVideoPlayer();
        ui->insertionPreview->hide();
        mediaPlayer->setSource(QUrl::fromLocalFile(path));
        mediaPlayer->setVideoOutput(videoWidget);
        videoWidget->show();
        mediaPlayer->play();
        ui->insertionPlayBtn->setText("Pause");
        // audio output created in setupVideoPlayer
        qDebug() << "ProjectWidget::showMediaPreview() - Playing video inside app";
    }
}

void ProjectWidget::setupVideoPlayer()
{
    if (mediaPlayer) return;
    mediaPlayer = new QMediaPlayer(this);
    // audio output should be created here to ensure audio will play for videos
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.8);
    videoWidget = new QVideoWidget(ui->insertionPreviewFrame);
    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->insertionPreviewFrame->layout()) {
        ui->insertionPreviewFrame->layout()->addWidget(videoWidget);
    }
    videoWidget->hide();
    ui->insertionSlider->setEnabled(false);
    ui->insertionPlayBtn->setEnabled(false);

    // connect player signals
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &ProjectWidget::onVideoPositionChanged);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &ProjectWidget::onVideoDurationChanged);
    connect(mediaPlayer, &QMediaPlayer::errorOccurred, this, [this](QMediaPlayer::Error error){
        Q_UNUSED(error);
        QString err = mediaPlayer->errorString();
        qDebug() << "ProjectWidget::setupVideoPlayer() - Media error:" << err;
        if (!err.isEmpty()) {
            QMessageBox::critical(this, "Erreur média", "Erreur lors de la lecture média: " + err);
        }
    });
    connect(ui->insertionSlider, &QSlider::sliderMoved, this, &ProjectWidget::onVideoSliderMoved);
    connect(ui->insertionPlayBtn, &QPushButton::clicked, this, &ProjectWidget::onPlayPauseClicked);
    // update play/pause button based on state
    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, [this](QMediaPlayer::PlaybackState state){
        if (state == QMediaPlayer::PlayingState) ui->insertionPlayBtn->setText("Pause"); else ui->insertionPlayBtn->setText("Play");
    });
}

void ProjectWidget::onPlayPauseClicked()
{
    if (!mediaPlayer) return;
    if (mediaPlayer->playbackState() == QMediaPlayer::PlayingState) {
        mediaPlayer->pause();
        ui->insertionPlayBtn->setText("Play");
    } else {
        mediaPlayer->play();
        ui->insertionPlayBtn->setText("Pause");
    }
}

void ProjectWidget::onVideoPositionChanged(qint64 position)
{
    ui->insertionSlider->setValue(static_cast<int>(position));
}

void ProjectWidget::onVideoDurationChanged(qint64 duration)
{
    ui->insertionSlider->setRange(0, static_cast<int>(duration));
    ui->insertionSlider->setEnabled(duration > 0);
    ui->insertionPlayBtn->setEnabled(duration > 0);
}

void ProjectWidget::onVideoSliderMoved(int value)
{
    if (!mediaPlayer) return;
    mediaPlayer->setPosition(static_cast<qint64>(value));
}

// ============ Rollback methods ============

void ProjectWidget::loadRollbackHistoryUI()
{
    ui->rollbackList->clear();
    QStringList history = rollbackHandler->loadRollbackHistoryFromFile();

    for (const QString &entry : history) {
        // Each entry may be a JSON object (new format) or plain text (legacy)
        QString display = entry;
        QJsonParseError perr;
        QJsonDocument doc = QJsonDocument::fromJson(entry.toUtf8(), &perr);
        if (perr.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            QString ts = obj.value("timestamp").toString();
            QString action = obj.value("action").toString();
            display = QString("[%1] %2").arg(ts).arg(action);
        }
        QListWidgetItem *item = new QListWidgetItem(display);
        item->setData(Qt::UserRole, entry); // keep original line (JSON or legacy) in user role
        ui->rollbackList->addItem(item);
    }

    qDebug() << "ProjectWidget::loadRollbackHistoryUI() - Loaded" << history.count() << "history entries";
}

void ProjectWidget::onRollbackAddClicked()
{
    qDebug() << "ProjectWidget::onRollbackAddClicked()";
    
    QString text = ui->rollbackNewEntryEdit->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez saisir une action d'historique");
        return;
    }

    // Get current persisted history so we append clean JSON entries
    QStringList currentHistory = rollbackHandler->loadRollbackHistoryFromFile();
    // Add new action via handler (manual entry, no undo SQL)
    rollbackHandler->addAction(text, QString(), currentHistory);
    
    // Update UI
    loadRollbackHistoryUI();
    ui->rollbackNewEntryEdit->clear();
    
    qDebug() << "ProjectWidget::onRollbackAddClicked() - Added action:" << text;
}

void ProjectWidget::onRollbackDoClicked()
{
    qDebug() << "ProjectWidget::onRollbackDoClicked()";
    
    int count = ui->rollbackList->count();
    if (count == 0) {
        QMessageBox::information(this, "Information", "Aucune action à rollback");
        return;
    }

    QString lastAction = ui->rollbackList->item(count - 1)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmer rollback",
        QString("Êtes-vous sûr de vouloir rollback l'action suivante?\n\n%1").arg(lastAction), 
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Load current persisted history and perform rollback
        QStringList currentHistory = rollbackHandler->loadRollbackHistoryFromFile();
        QString removedAction = rollbackHandler->rollbackLastAction(currentHistory);

        // Update UI from persisted history
        loadRollbackHistoryUI();
        
        if (removedAction.isEmpty()) {
            QMessageBox::critical(this, "Rollback échoué", "Échec lors de l'exécution du rollback. Voir logs.");
            qDebug() << "ProjectWidget::onRollbackDoClicked() - Rollback failed";
        } else {
            QMessageBox::information(this, "Rollback réussi", 
                QString("L'action a été rollbackée:\n%1").arg(removedAction));
            qDebug() << "ProjectWidget::onRollbackDoClicked() - Rolled back:" << removedAction;
        }
    }
}

void ProjectWidget::onRollbackClearClicked()
{
    qDebug() << "ProjectWidget::onRollbackClearClicked()";
    
    if (ui->rollbackList->count() == 0) {
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmer", 
        "Êtes-vous sûr de vouloir effacer l'historique?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        ui->rollbackList->clear();
        rollbackHandler->saveRollbackHistoryToFile(QStringList());
        // also remove the rollback file from project root
        QString rpath = rollbackHandler->getRollbackHistoryFilePath();
        if (QFile::exists(rpath)) QFile::remove(rpath);
        qDebug() << "ProjectWidget::onRollbackClearClicked() - History cleared";
    }
}

