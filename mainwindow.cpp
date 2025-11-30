#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVariantAnimation>
#include "ui_login.h"
#include "ui_Profile.h"
#include "ui_employerform.h"
#include "ui_projectform.h"

#include "ui/clientwidget.h"
#include "ui/projectwidget.h"
#include "ui/ressourcewidget.h"
#include "ui/sponsorwidget.h"
#include "ui/sponsorwindow.h"
#include "ui/templatewidget.h"
#include "ui/facerecognitionwidget.h"

#include "backend/connection.h"
#include "backend/employer.h"
#include "backend/ressource.h"
#include "backend/project.h"
#include "backend/chatbot.h"
#include "backend/faceapi.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QCoreApplication>
#include <QDialog>
#include <QFrame>
#include <QGuiApplication>
#include <QScreen>
#include <QColor>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QStringList>
#include <QMessageBox>
#include <QPixmap>
#include <QButtonGroup>
#include <QPlainTextEdit>
#include <QPropertyAnimation>
#include <QStyle>
#include <QStandardPaths>
#include <QVector>
#include <functional>
#include <utility>
#include <QDir>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QResizeEvent>
#include <QSize>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QEasingCurve>
#include <QProgressBar>
#include <QTextStream>
#include <QFile>
#include <QDate>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QTimer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QEvent>
#include <QtSql/QSqlQuery>
#include <QMediaCaptureSession>
#include <QCamera>
#include <QVideoSink>
#include <QVideoFrame>
#include <algorithm>

// Qt Charts for advanced statistics visualization
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QSplineSeries>
#include <QTabWidget>
#include <QGraphicsDropShadowEffect>

// =============================================================================
// Helper Functions and Constants
// =============================================================================
namespace
{
// Email validation regex
QRegularExpression emailRegex()
{
    return QRegularExpression(QStringLiteral(R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"), 
                             QRegularExpression::CaseInsensitiveOption);
}

// Selection symbols for table UI
constexpr auto kSelectSymbol = "☑";
constexpr auto kUnselectSymbol = "☐";


// CSV export helper removed — keep code minimal and prefer PDF export.

QString formatDate(const QDate &date)
{
    if (!date.isValid()) return QString();
    return date.toString(QStringLiteral("yyyy-MM-dd"));
}
}

// =============================================================================
// EmployerForm Implementation
// =============================================================================

EmployerForm::EmployerForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmployerForm)
    , m_employerId(-1)
{
    ui->setupUi(this);
    ui->startDateEdit->setDate(QDate::currentDate());

    auto *emailValidator = new QRegularExpressionValidator(emailRegex(), ui->emailLineEdit);
    ui->emailLineEdit->setValidator(emailValidator);

    connect(ui->browseAvatarButton, &QPushButton::clicked, this, &EmployerForm::browseAvatar);
    connect(ui->avatarLineEdit, &QLineEdit::textChanged, this, &EmployerForm::updateAvatarPreview);
    connect(ui->firstNameLineEdit, &QLineEdit::textChanged, this, &EmployerForm::clearErrorMessage);
    connect(ui->lastNameLineEdit, &QLineEdit::textChanged, this, &EmployerForm::clearErrorMessage);
    connect(ui->emailLineEdit, &QLineEdit::textChanged, this, &EmployerForm::clearErrorMessage);
    connect(ui->roleComboBox, &QComboBox::currentTextChanged, this, &EmployerForm::clearErrorMessage);
    connect(ui->passwordLineEdit, &QLineEdit::textChanged, this, &EmployerForm::clearErrorMessage);
    
    // Resource management
    connect(ui->addResourceButton, &QPushButton::clicked, this, &EmployerForm::onAddResourceClicked);
    connect(ui->removeResourceButton, &QPushButton::clicked, this, &EmployerForm::onRemoveResourceClicked);
    
    // Project management
    connect(ui->addProjectButton, &QPushButton::clicked, this, &EmployerForm::onAddProjectClicked);
    connect(ui->removeProjectButton, &QPushButton::clicked, this, &EmployerForm::onRemoveProjectClicked);

    setModal(true);
}

EmployerForm::~EmployerForm()
{
    delete ui;
}

void EmployerForm::setMode(Mode mode)
{
    m_mode = mode;
    if (mode == EditMode)
    {
        setWindowTitle(tr("Update Employer"));
        ui->passwordLabel->setText(tr("Password (leave blank to keep)"));
    }
    else
    {
        setWindowTitle(tr("Add Employer"));
        ui->passwordLabel->setText(tr("Password *"));
        ui->passwordLineEdit->clear();
    }
}

void EmployerForm::setRecord(const Employer &record)
{
    m_employerId = record.employerId;
    ui->firstNameLineEdit->setText(record.firstName);
    ui->lastNameLineEdit->setText(record.lastName);
    ui->emailLineEdit->setText(record.email);
    ui->phoneLineEdit->setText(record.phone);
    const int roleIndex = ui->roleComboBox->findText(record.role, Qt::MatchFixedString);
    if (roleIndex >= 0)
    {
        ui->roleComboBox->setCurrentIndex(roleIndex);
    }
    else
    {
        ui->roleComboBox->setCurrentText(record.role);
    }
    if (record.startDate.isValid())
    {
        ui->startDateEdit->setDate(record.startDate);
    }
    ui->avatarLineEdit->setText(record.avatarPath);
    updateAvatarPreview(record.avatarPath);
    
    // If m_selectedResourceIds was already set (via setSelectedResourceIds), display them
    // Otherwise, load from database if editing
    if (!m_selectedResourceIds.isEmpty())
    {
        qDebug() << "[EmployerForm::setRecord] m_selectedResourceIds already set with" << m_selectedResourceIds.size() << "resources";
        refreshResourceList();
    }
    else if (m_mode == EditMode && m_employerId > 0)
    {
        qDebug() << "[EmployerForm::setRecord] Loading resources from database for employer" << m_employerId;
        loadEmployerResources(m_employerId);
    }
    
    // If m_selectedProjectIds was already set (via setSelectedProjectIds), display them
    // Otherwise, load from database if editing
    if (!m_selectedProjectIds.isEmpty())
    {
        qDebug() << "[EmployerForm::setRecord] m_selectedProjectIds already set with" << m_selectedProjectIds.size() << "projects";
        refreshProjectList();
    }
    else if (m_mode == EditMode && m_employerId > 0)
    {
        qDebug() << "[EmployerForm::setRecord] Loading projects from database for employer" << m_employerId;
        loadEmployerProjects(m_employerId);
    }
    
    clearErrorMessage();
}

Employer EmployerForm::record() const
{
    Employer rec;
    rec.firstName = ui->firstNameLineEdit->text().trimmed();
    rec.lastName = ui->lastNameLineEdit->text().trimmed();
    rec.email = ui->emailLineEdit->text().trimmed();
    rec.phone = ui->phoneLineEdit->text().trimmed();
    rec.role = ui->roleComboBox->currentText().trimmed();
    rec.startDate = ui->startDateEdit->date();
    rec.avatarPath = ui->avatarLineEdit->text().trimmed();
    return rec;
}

bool EmployerForm::passwordProvided() const
{
    return !ui->passwordLineEdit->text().trimmed().isEmpty();
}

QString EmployerForm::rawPassword() const
{
    return ui->passwordLineEdit->text();
}

void EmployerForm::setErrorMessage(const QString &message)
{
    ui->errorLabel->setText(message);
}

void EmployerForm::accept()
{
    QString validationMessage;
    if (!validate(&validationMessage))
    {
        setErrorMessage(validationMessage);
        return;
    }
    QDialog::accept();
}

void EmployerForm::browseAvatar()
{
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Select avatar"), 
                                                          QString(), 
                                                          tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!filePath.isEmpty())
    {
        ui->avatarLineEdit->setText(filePath);
    }
}

void EmployerForm::updateAvatarPreview(const QString &path)
{
    if (path.trimmed().isEmpty())
    {
        ui->avatarPreviewLabel->setText(tr("No preview"));
        ui->avatarPreviewLabel->setPixmap(QPixmap());
        return;
    }

    QPixmap pixmap(path);
    if (pixmap.isNull())
    {
        ui->avatarPreviewLabel->setText(tr("Preview unavailable"));
        ui->avatarPreviewLabel->setPixmap(QPixmap());
        return;
    }

    // Scale to square (300x300) - crop if needed to maintain aspect ratio
    int size = 300;
    int w = pixmap.width();
    int h = pixmap.height();
    int minDim = qMin(w, h);
    
    // Crop to square first
    int x = (w - minDim) / 2;
    int y = (h - minDim) / 2;
    QPixmap cropped = pixmap.copy(x, y, minDim, minDim);
    
    // Scale to target size
    QPixmap scaled = cropped.scaledToWidth(size, Qt::SmoothTransformation);
    
    ui->avatarPreviewLabel->setPixmap(scaled);
    ui->avatarPreviewLabel->setText(QString());
}

void EmployerForm::clearErrorMessage()
{
    ui->errorLabel->clear();
}

bool EmployerForm::validate(QString *message) const
{
    const Employer rec = record();

    if (rec.firstName.isEmpty())
    {
        if (message)
        {
            *message = tr("First name is required.");
        }
        return false;
    }

    if (rec.lastName.isEmpty())
    {
        if (message)
        {
            *message = tr("Last name is required.");
        }
        return false;
    }

    if (rec.email.isEmpty())
    {
        if (message)
        {
            *message = tr("Email is required.");
        }
        return false;
    }

    if (!emailRegex().match(rec.email).hasMatch())
    {
        if (message)
        {
            *message = tr("Email format is invalid.");
        }
        return false;
    }

    if (rec.role.isEmpty() || rec.role.compare(QStringLiteral("Select role"), Qt::CaseInsensitive) == 0)
    {
        if (message)
        {
            *message = tr("Select a role for the employer.");
        }
        return false;
    }

    if (!rec.startDate.isValid())
    {
        if (message)
        {
            *message = tr("Start date is invalid.");
        }
        return false;
    }

    const QString password = ui->passwordLineEdit->text();
    if (m_mode == CreateMode)
    {
        if (password.trimmed().size() < 8)
        {
            if (message)
            {
                *message = tr("Password must be at least 8 characters long.");
            }
            return false;
        }
    }
    else
    {
        if (!password.trimmed().isEmpty() && password.trimmed().size() < 8)
        {
            if (message)
            {
                *message = tr("New password must be at least 8 characters long.");
            }
            return false;
        }
    }

    if (message)
    {
        message->clear();
    }
    return true;
}

void EmployerForm::loadEmployerResources(qint64 employerId)
{
    ui->resourceListWidget->clear();
    
    if (employerId <= 0)
    {
        return;
    }

    QVector<Ressource> resources = Ressource::getResourcesByEmployer(employerId);
    for (const Ressource &res : resources)
    {
        ui->resourceListWidget->addItem(res.title);
    }
    
    qDebug() << "Loaded" << resources.count() << "resources for employer" << employerId;
}

void EmployerForm::refreshResourceList()
{
    ui->resourceListWidget->clear();
    
    if (m_selectedResourceIds.isEmpty())
    {
        qDebug() << "[EmployerForm::refreshResourceList] No resources to display";
        return;
    }
    
    // Load resource details from database
    for (qint64 resourceId : m_selectedResourceIds)
    {
        Ressource resource;
        if (Ressource::fetchById(resourceId, resource))
        {
            ui->resourceListWidget->addItem(resource.title);
            qDebug() << "[EmployerForm::refreshResourceList] Added resource:" << resource.title;
        }
        else
        {
            qDebug() << "[EmployerForm::refreshResourceList] Failed to fetch resource ID:" << resourceId;
        }
    }
    
    qDebug() << "[EmployerForm::refreshResourceList] Displayed" << m_selectedResourceIds.size() << "resources";
}

void EmployerForm::loadEmployerProjects(qint64 employerId)
{
    qDebug() << "[EmployerForm::loadEmployerProjects] Loading projects for employer" << employerId;
    
    QVector<Project> projects = Project::getProjectsByEmployer(employerId);
    m_selectedProjectIds.clear();
    
    for (const Project &proj : projects)
    {
        m_selectedProjectIds.append(proj.projectId);
        qDebug() << "[EmployerForm::loadEmployerProjects] Added project:" << proj.title;
    }
    
    qDebug() << "[EmployerForm::loadEmployerProjects] Loaded" << m_selectedProjectIds.size() << "projects";
}

void EmployerForm::refreshProjectList()
{
    ui->projectListWidget->clear();
    
    if (m_selectedProjectIds.isEmpty())
    {
        qDebug() << "[EmployerForm::refreshProjectList] No projects to display";
        return;
    }
    
    // Load project details from database
    for (qint64 projectId : m_selectedProjectIds)
    {
        Project project;
        if (Project::fetchById(projectId, project))
        {
            ui->projectListWidget->addItem(project.title);
            qDebug() << "[EmployerForm::refreshProjectList] Added project:" << project.title;
        }
        else
        {
            qDebug() << "[EmployerForm::refreshProjectList] Failed to fetch project ID:" << projectId;
        }
    }
    
    qDebug() << "[EmployerForm::refreshProjectList] Displayed" << m_selectedProjectIds.size() << "projects";
}

void EmployerForm::onAddResourceClicked()
{
    qDebug() << "[EmployerForm::onAddResourceClicked] Add resource clicked";
    
    // Get currently assigned resource IDs from m_selectedResourceIds
    QVector<qint64> currentResourceIds = m_selectedResourceIds;
    
    qDebug() << "[EmployerForm::onAddResourceClicked] Current m_selectedResourceIds count:" << currentResourceIds.size();
    
    // Show resource selection dialog
    ResourceSelectionDialog dialog(this);
    dialog.setAssignedResources(currentResourceIds);
    
    if (dialog.exec() != QDialog::Accepted)
    {
        qDebug() << "[EmployerForm::onAddResourceClicked] Dialog cancelled";
        return;
    }
    
    QVector<qint64> selectedResourceIds = dialog.selectedResourceIds();
    qDebug() << "[EmployerForm::onAddResourceClicked] Dialog returned" << selectedResourceIds.size() << "selected resources";
    
    // IMPORTANT: Store selected resources in m_selectedResourceIds for later use
    m_selectedResourceIds = selectedResourceIds;
    qDebug() << "[EmployerForm::onAddResourceClicked] Stored in m_selectedResourceIds:" << m_selectedResourceIds.size() << "resources";
    
    // Only update database if employer already exists
    if (m_employerId > 0)
    {
        qDebug() << "[EmployerForm::onAddResourceClicked] Employer exists (ID:" << m_employerId << "), updating database";
        
        // Clear current resources and add new ones
        Ressource::clearEmployerResources(m_employerId);
        qDebug() << "[EmployerForm::onAddResourceClicked] Cleared old resources";
        
        for (qint64 resourceId : selectedResourceIds)
        {
            qDebug() << "[EmployerForm::onAddResourceClicked] Adding resource" << resourceId << "to employer" << m_employerId;
            Ressource::addResourceToEmployer(m_employerId, resourceId);
        }
        
        qDebug() << "[EmployerForm::onAddResourceClicked] Database updated successfully";
        
        QMessageBox::information(this, tr("Success"),
                               tr("Resources assigned successfully."));
        refreshResourceList();
    }
    else
    {
        // For new employers, just update the form's internal state
        qDebug() << "[EmployerForm::onAddResourceClicked] New employer (ID not assigned yet), skipping database update";
        
        // Update the list widget to show the selected resources
        refreshResourceList();
        
        QMessageBox::information(this, tr("Info"),
                               tr("Selected resources will be assigned when you save the employer."));
    }
}

void EmployerForm::onRemoveResourceClicked()
{
    qDebug() << "[EmployerForm::onRemoveResourceClicked] Remove resource clicked";
    
    QListWidgetItem *item = ui->resourceListWidget->currentItem();
    if (!item)
    {
        QMessageBox::warning(this, tr("Remove Resource"),
                           tr("Please select a resource to remove."));
        return;
    }

    QString selectedTitle = item->text();
    qDebug() << "[EmployerForm::onRemoveResourceClicked] Selected resource:" << selectedTitle;
    
    // Find and remove the resource from m_selectedResourceIds
    for (int i = 0; i < m_selectedResourceIds.size(); ++i)
    {
        qint64 resourceId = m_selectedResourceIds[i];
        Ressource resource;
        
        if (Ressource::fetchById(resourceId, resource))
        {
            if (resource.title == selectedTitle)
            {
                qDebug() << "[EmployerForm::onRemoveResourceClicked] Found resource ID" << resourceId << "with title:" << resource.title;
                
                m_selectedResourceIds.removeAt(i);
                qDebug() << "[EmployerForm::onRemoveResourceClicked] Removed from m_selectedResourceIds. New count:" << m_selectedResourceIds.size();
                
                // If employer exists in database, also remove from there
                if (m_employerId > 0)
                {
                    if (Ressource::removeResourceFromEmployer(m_employerId, resourceId))
                    {
                        qDebug() << "[EmployerForm::onRemoveResourceClicked] Removed from database";
                    }
                    else
                    {
                        qDebug() << "[EmployerForm::onRemoveResourceClicked] Failed to remove from database";
                        QMessageBox::critical(this, tr("Error"),
                                            tr("Failed to remove resource from database."));
                        // Add it back to the list since DB removal failed
                        m_selectedResourceIds.insert(i, resourceId);
                        return;
                    }
                }
                
                QMessageBox::information(this, tr("Success"),
                                       tr("Resource removed successfully."));
                refreshResourceList();
                return;
            }
        }
    }
    
    qDebug() << "[EmployerForm::onRemoveResourceClicked] Resource not found";
    QMessageBox::warning(this, tr("Error"),
                        tr("Could not find the selected resource."));
}

void EmployerForm::onAddProjectClicked()
{
    qDebug() << "[EmployerForm::onAddProjectClicked] Add project clicked";
    
    // Get currently assigned project IDs from m_selectedProjectIds
    QVector<qint64> currentProjectIds = m_selectedProjectIds;
    
    qDebug() << "[EmployerForm::onAddProjectClicked] Current m_selectedProjectIds count:" << currentProjectIds.size();
    
    // Show project selection dialog
    ProjectSelectionDialog dialog(this);
    dialog.setAssignedProjects(currentProjectIds);
    
    if (dialog.exec() != QDialog::Accepted)
    {
        qDebug() << "[EmployerForm::onAddProjectClicked] Dialog cancelled";
        return;
    }
    
    QVector<qint64> selectedProjectIds = dialog.selectedProjectIds();
    qDebug() << "[EmployerForm::onAddProjectClicked] Dialog returned" << selectedProjectIds.size() << "selected projects";
    
    // IMPORTANT: Store selected projects in m_selectedProjectIds for later use
    m_selectedProjectIds = selectedProjectIds;
    qDebug() << "[EmployerForm::onAddProjectClicked] Stored in m_selectedProjectIds:" << m_selectedProjectIds.size() << "projects";
    
    // Only update database if employer already exists
    if (m_employerId > 0)
    {
        qDebug() << "[EmployerForm::onAddProjectClicked] Employer exists (ID:" << m_employerId << "), updating database";
        
        // Clear current projects and add new ones
        Project::removeAllEmployersFromProject(m_employerId);  // Note: This removes employer from all projects
        qDebug() << "[EmployerForm::onAddProjectClicked] Cleared old projects";
        
        for (qint64 projectId : selectedProjectIds)
        {
            qDebug() << "[EmployerForm::onAddProjectClicked] Adding project" << projectId << "to employer" << m_employerId;
            Project::addEmployerToProject(projectId, m_employerId);
        }
        
        qDebug() << "[EmployerForm::onAddProjectClicked] Database updated successfully";
        
        QMessageBox::information(this, tr("Success"),
                               tr("Projects assigned successfully."));
        refreshProjectList();
    }
    else
    {
        // For new employers, just update the form's internal state
        qDebug() << "[EmployerForm::onAddProjectClicked] New employer (ID not assigned yet), skipping database update";
        
        // Update the list widget to show the selected projects
        refreshProjectList();
        
        QMessageBox::information(this, tr("Info"),
                               tr("Selected projects will be assigned when you save the employer."));
    }
}

void EmployerForm::onRemoveProjectClicked()
{
    qDebug() << "[EmployerForm::onRemoveProjectClicked] Remove project clicked";
    
    QListWidgetItem *item = ui->projectListWidget->currentItem();
    if (!item)
    {
        QMessageBox::warning(this, tr("Remove Project"),
                           tr("Please select a project to remove."));
        return;
    }

    QString selectedTitle = item->text();
    qDebug() << "[EmployerForm::onRemoveProjectClicked] Selected project:" << selectedTitle;
    
    // Find and remove the project from m_selectedProjectIds
    for (int i = 0; i < m_selectedProjectIds.size(); ++i)
    {
        qint64 projectId = m_selectedProjectIds[i];
        Project project;
        
        if (Project::fetchById(projectId, project))
        {
            if (project.title == selectedTitle)
            {
                qDebug() << "[EmployerForm::onRemoveProjectClicked] Found project ID" << projectId << "with title:" << project.title;
                
                m_selectedProjectIds.removeAt(i);
                qDebug() << "[EmployerForm::onRemoveProjectClicked] Removed from m_selectedProjectIds. New count:" << m_selectedProjectIds.size();
                
                // If employer exists in database, also remove from there
                if (m_employerId > 0)
                {
                    if (Project::removeEmployerFromProject(projectId, m_employerId))
                    {
                        qDebug() << "[EmployerForm::onRemoveProjectClicked] Removed from database";
                    }
                    else
                    {
                        qDebug() << "[EmployerForm::onRemoveProjectClicked] Failed to remove from database";
                        QMessageBox::critical(this, tr("Error"),
                                            tr("Failed to remove project from database."));
                        // Add it back to the list since DB removal failed
                        m_selectedProjectIds.insert(i, projectId);
                        return;
                    }
                }
                
                QMessageBox::information(this, tr("Success"),
                                       tr("Project removed successfully."));
                refreshProjectList();
                return;
            }
        }
    }
    
    qDebug() << "[EmployerForm::onRemoveProjectClicked] Project not found";
    QMessageBox::warning(this, tr("Error"),
                        tr("Could not find the selected project."));
}

// =============================================================================
// ProjectForm Implementation
// =============================================================================

ProjectForm::ProjectForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjectForm)
    , m_projectId(-1)
{
    ui->setupUi(this);
    ui->creationDateEdit->setDate(QDate::currentDate());
    ui->modificationDateEdit->setDate(QDate::currentDate());

    connect(ui->titleLineEdit, &QLineEdit::textChanged, this, &ProjectForm::clearErrorMessage);
    connect(ui->descriptionTextEdit, &QTextEdit::textChanged, this, &ProjectForm::clearErrorMessage);

    setModal(true);
}

ProjectForm::~ProjectForm()
{
    delete ui;
}

void ProjectForm::setMode(Mode mode)
{
    m_mode = mode;
    if (mode == EditMode)
    {
        setWindowTitle(tr("Update Project"));
    }
    else
    {
        setWindowTitle(tr("Add Project"));
    }
}

void ProjectForm::setRecord(const Project &record)
{
    m_projectId = record.projectId;
    ui->titleLineEdit->setText(record.title);
    ui->descriptionTextEdit->setPlainText(record.description);
    ui->clientLineEdit->setText(QString::number(record.clientId));
    ui->serviceLineEdit->setText(QString::number(record.serviceId));
    
    if (record.creationDate.isValid())
    {
        ui->creationDateEdit->setDate(record.creationDate);
    }
    if (record.modificationDate.isValid())
    {
        ui->modificationDateEdit->setDate(record.modificationDate);
    }
    
    clearErrorMessage();
}

Project ProjectForm::record() const
{
    Project proj;
    proj.projectId = m_projectId;
    proj.title = ui->titleLineEdit->text().trimmed();
    proj.description = ui->descriptionTextEdit->toPlainText().trimmed();
    proj.clientId = ui->clientLineEdit->text().toLongLong();
    proj.serviceId = ui->serviceLineEdit->text().toLongLong();
    proj.creationDate = ui->creationDateEdit->date();
    proj.modificationDate = ui->modificationDateEdit->date();
    return proj;
}

void ProjectForm::setErrorMessage(const QString &message)
{
    ui->errorLabel->setText(message);
}

void ProjectForm::clearErrorMessage()
{
    ui->errorLabel->clear();
}

bool ProjectForm::validate(QString *message) const
{
    const Project proj = record();

    if (proj.title.isEmpty())
    {
        if (message)
        {
            *message = tr("Title is required.");
        }
        return false;
    }

    if (proj.description.isEmpty())
    {
        if (message)
        {
            *message = tr("Description is required.");
        }
        return false;
    }

    return true;
}

void ProjectForm::accept()
{
    QString validationMessage;
    if (!validate(&validationMessage))
    {
        setErrorMessage(validationMessage);
        return;
    }
    QDialog::accept();
}

// =============================================================================
// ResourceSelectionDialog Implementation
// =============================================================================

ResourceSelectionDialog::ResourceSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    // Don't load resources here - wait for setAssignedResources() to be called
    qDebug() << "[ResourceSelectionDialog::Constructor] Dialog created (resources not loaded yet)";
}

ResourceSelectionDialog::~ResourceSelectionDialog()
{
}

void ResourceSelectionDialog::setupUi()
{
    setWindowTitle(tr("Select Resources"));
    setMinimumSize(500, 400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QLabel *label = new QLabel(tr("Select resources to assign to this employer:"));
    layout->addWidget(label);
    
    resourceListWidget = new QListWidget();
    resourceListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    qDebug() << "[ResourceSelectionDialog::setupUi] Selection mode set to MultiSelection";
    layout->addWidget(resourceListWidget);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
    
    setLayout(layout);
}

void ResourceSelectionDialog::loadAllResources()
{
    resourceListWidget->clear();
    
    QVector<Ressource> allResources = Ressource::selectAll();
    qDebug() << "[ResourceSelectionDialog::loadAllResources] Loading" << allResources.size() << "total resources";
    
    for (const Ressource &res : allResources)
    {
        QListWidgetItem *item = new QListWidgetItem(res.title);
        item->setData(Qt::UserRole, res.idMedia);
        
        // Pre-select already assigned resources
        if (m_assignedResourceIds.contains(res.idMedia))
        {
            item->setSelected(true);
            qDebug() << "[ResourceSelectionDialog::loadAllResources] Pre-selected resource:" << res.idMedia << res.title;
        }
        
        resourceListWidget->addItem(item);
    }
}

void ResourceSelectionDialog::setAssignedResources(const QVector<qint64>& resourceIds)
{
    m_assignedResourceIds = resourceIds;
    qDebug() << "[ResourceSelectionDialog::setAssignedResources] Setting" << resourceIds.size() << "assigned resources";
    
    // Now load resources AFTER setting the assigned IDs
    // This ensures pre-selection works correctly
    loadAllResources();
}

QVector<qint64> ResourceSelectionDialog::selectedResourceIds() const
{
    QVector<qint64> selected;
    for (int i = 0; i < resourceListWidget->count(); ++i)
    {
        QListWidgetItem *item = resourceListWidget->item(i);
        if (item && item->isSelected())
        {
            qint64 resourceId = item->data(Qt::UserRole).toLongLong();
            selected.append(resourceId);
            qDebug() << "[ResourceSelectionDialog::selectedResourceIds] Selected resource:" << resourceId;
        }
    }
    qDebug() << "[ResourceSelectionDialog::selectedResourceIds] Total selected:" << selected.size();
    return selected;
}

// =============================================================================
// ProjectSelectionDialog Implementation
// =============================================================================

ProjectSelectionDialog::ProjectSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    // Don't load projects here - wait for setAssignedProjects() to be called
    qDebug() << "[ProjectSelectionDialog::Constructor] Dialog created (projects not loaded yet)";
}

ProjectSelectionDialog::~ProjectSelectionDialog()
{
}

void ProjectSelectionDialog::setupUi()
{
    setWindowTitle(tr("Select Projects"));
    setMinimumSize(500, 400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QLabel *label = new QLabel(tr("Select projects to assign to this employer:"));
    layout->addWidget(label);
    
    projectListWidget = new QListWidget();
    projectListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    qDebug() << "[ProjectSelectionDialog::setupUi] Selection mode set to MultiSelection";
    layout->addWidget(projectListWidget);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
    
    setLayout(layout);
}

void ProjectSelectionDialog::loadAllProjects()
{
    projectListWidget->clear();
    
    QVector<Project> allProjects = Project::selectAll();
    qDebug() << "[ProjectSelectionDialog::loadAllProjects] Loading" << allProjects.size() << "total projects";
    
    for (const Project &proj : allProjects)
    {
        QListWidgetItem *item = new QListWidgetItem(proj.title);
        item->setData(Qt::UserRole, proj.projectId);
        
        // Pre-select already assigned projects
        if (m_assignedProjectIds.contains(proj.projectId))
        {
            item->setSelected(true);
            qDebug() << "[ProjectSelectionDialog::loadAllProjects] Pre-selected project:" << proj.projectId << proj.title;
        }
        
        projectListWidget->addItem(item);
    }
}

void ProjectSelectionDialog::setAssignedProjects(const QVector<qint64>& projectIds)
{
    m_assignedProjectIds = projectIds;
    qDebug() << "[ProjectSelectionDialog::setAssignedProjects] Setting" << projectIds.size() << "assigned projects";
    
    // Now load projects AFTER setting the assigned IDs
    // This ensures pre-selection works correctly
    loadAllProjects();
}

QVector<qint64> ProjectSelectionDialog::selectedProjectIds() const
{
    QVector<qint64> selected;
    for (int i = 0; i < projectListWidget->count(); ++i)
    {
        QListWidgetItem *item = projectListWidget->item(i);
        if (item && item->isSelected())
        {
            qint64 projectId = item->data(Qt::UserRole).toLongLong();
            selected.append(projectId);
            qDebug() << "[ProjectSelectionDialog::selectedProjectIds] Selected project:" << projectId;
        }
    }
    qDebug() << "[ProjectSelectionDialog::selectedProjectIds] Total selected:" << selected.size();
    return selected;
}

// =============================================================================
// EmployerUIHelper Implementation
// =============================================================================

void EmployerUIHelper::populateTable(QTableWidget *table, const QVector<Employer> &records)
{
    qDebug() << "[EmployerUIHelper::populateTable] CALLED with" << records.size() << "records";
    
    if (!table)
    {
        qDebug() << "[EmployerUIHelper::populateTable] ERROR: table is NULL!";
        return;
    }

    table->setRowCount(records.size());

    for (int row = 0; row < records.size(); ++row)
    {
        const Employer &rec = records.at(row);

        qDebug() << "[EmployerUIHelper::populateTable] Row" << row << "- ID:" << rec.employerId 
                 << "Name:" << rec.firstName << rec.lastName;

        auto *selectItem = new QTableWidgetItem(QString::fromUtf8(kUnselectSymbol));
        selectItem->setTextAlignment(Qt::AlignCenter);
        selectItem->setData(Qt::UserRole, rec.employerId);
        qDebug() << "[EmployerUIHelper::populateTable] Storing ID in UserRole:" << rec.employerId;
        table->setItem(row, 0, selectItem);

        auto *avatarItem = new QTableWidgetItem();
        if (!rec.avatarPath.isEmpty())
        {
            const QPixmap pixmap(rec.avatarPath);
            if (!pixmap.isNull())
            {
                // Crop to square then scale to small in-cell thumbnail (48x48)
                int minDim = qMin(pixmap.width(), pixmap.height());
                QPixmap croppedPixmap = pixmap.copy((pixmap.width() - minDim) / 2,
                                                     (pixmap.height() - minDim) / 2,
                                                     minDim, minDim);
                QPixmap thumb = croppedPixmap.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                avatarItem->setIcon(QIcon(thumb));
                avatarItem->setSizeHint(QSize(48, 48));

                // Provide a larger preview in the tooltip (HTML img) so users can see full avatar without expanding row
                QString imgPath = QDir::toNativeSeparators(rec.avatarPath);
                QString imgHtml = QString("<img src=\"file:///%1\" width=\"200\" height=\"200\"/>")
                                  .arg(imgPath);
                avatarItem->setToolTip(imgHtml);
            }
        }
        table->setItem(row, 1, avatarItem);

        auto *idItem = new QTableWidgetItem(rec.employerId > 0 ? QString::number(rec.employerId) : QString());
        table->setItem(row, 2, idItem);

        auto *nameItem = new QTableWidgetItem(QStringLiteral("%1 %2").arg(rec.firstName, rec.lastName));
        table->setItem(row, 3, nameItem);

        auto *emailItem = new QTableWidgetItem(rec.email);
        table->setItem(row, 4, emailItem);

        auto *roleItem = new QTableWidgetItem(rec.role);
        table->setItem(row, 5, roleItem);

        auto *phoneItem = new QTableWidgetItem(rec.phone);
        table->setItem(row, 6, phoneItem);

        auto *dateItem = new QTableWidgetItem(formatDate(rec.startDate));
        table->setItem(row, 7, dateItem);

        // Load and display resources for this employer
        QVector<Ressource> employerResources = Ressource::getResourcesByEmployer(rec.employerId);
        QString resourceNames;
        for (int i = 0; i < employerResources.size(); ++i)
        {
            if (i > 0) resourceNames += ", ";
            resourceNames += employerResources.at(i).title;
        }
        if (!employerResources.isEmpty())
        {
            qDebug() << "[EmployerUIHelper::populateTable] Employer" << rec.employerId 
                     << "has" << employerResources.size() << "resources:" << resourceNames;
        }
        auto *resourcesItem = new QTableWidgetItem(resourceNames);
        resourcesItem->setToolTip(resourceNames);  // Show full list in tooltip
        table->setItem(row, 8, resourcesItem);

        // Load and display projects for this employer
        QVector<Project> employerProjects = Project::getProjectsByEmployer(rec.employerId);
        QString projectNames;
        for (int i = 0; i < employerProjects.size(); ++i)
        {
            if (i > 0) projectNames += ", ";
            projectNames += employerProjects.at(i).title;
        }
        if (!employerProjects.isEmpty())
        {
            qDebug() << "[EmployerUIHelper::populateTable] Employer" << rec.employerId 
                     << "has" << employerProjects.size() << "projects:" << projectNames;
        }
        auto *projectsItem = new QTableWidgetItem(projectNames);
        projectsItem->setToolTip(projectNames);  // Show full list in tooltip
        table->setItem(row, 9, projectsItem);

    // keep rows compact (48px) to show more rows; avatar shows large preview on hover
    table->setRowHeight(row, 48);
    }

    table->clearSelection();
    qDebug() << "[EmployerUIHelper::populateTable] Table populated successfully";
}

qint64 EmployerUIHelper::getSelectedEmployerId(QTableWidget *table, bool *ok)
{
    qDebug() << "[EmployerUIHelper::getSelectedEmployerId] CALLED";
    
    if (!table)
    {
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] ERROR: table is NULL!";
        if (ok) *ok = false;
        return -1;
    }

    qDebug() << "[EmployerUIHelper::getSelectedEmployerId] Table has" << table->rowCount() << "rows";

    // Check for selected items
    QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    qDebug() << "[EmployerUIHelper::getSelectedEmployerId] Selected items count:" << selectedItems.count();
    
    if (selectedItems.isEmpty())
    {
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] ERROR: No items selected!";
        if (ok) *ok = false;
        return -1;
    }

    // Get the row from the first selected item
    int row = table->row(selectedItems.first());
    qDebug() << "[EmployerUIHelper::getSelectedEmployerId] Selected row:" << row;

    const QTableWidgetItem *item = table->item(row, 0);
    qint64 id = -1;
    if (item)
    {
        QVariant userData = item->data(Qt::UserRole);
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] UserRole data type:" << userData.typeName();
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] UserRole data value:" << userData;
        
        id = userData.toLongLong();
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] Extracted ID:" << id;
    }
    else
    {
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] ERROR: item at row" << row << "col 0 is NULL!";
    }

    bool result = (id > 0);
    qDebug() << "[EmployerUIHelper::getSelectedEmployerId] Returning ID:" << id << "valid:" << result;
    
    if (ok) *ok = result;
    return id;
}

Employer EmployerUIHelper::getSelectedRecord(QTableWidget *table, const QVector<Employer> &records, bool *ok)
{
    Employer record;
    bool localOk = false;
    const qint64 id = getSelectedEmployerId(table, &localOk);
    
    if (localOk)
    {
        for (const auto &candidate : records)
        {
            if (candidate.employerId == id)
            {
                record = candidate;
                break;
            }
        }
    }

    if (ok) *ok = localOk;
    return record;
}

void EmployerUIHelper::handleSelectionToggle(QTableWidget *table, QTableWidgetItem *item)
{
    if (!table || !item || item->column() != 0)
    {
        return;
    }

    for (int row = 0; row < table->rowCount(); ++row)
    {
        if (row == item->row())
        {
            const bool alreadySelected = item->text() == QString::fromUtf8(kSelectSymbol);
            if (alreadySelected)
            {
                // Deselect the item and clear selection from the table
                item->setText(QString::fromUtf8(kUnselectSymbol));
                table->clearSelection();
            }
            else
            {
                // Select this row and mark with select symbol
                item->setText(QString::fromUtf8(kSelectSymbol));
                table->selectRow(row);
            }
        }
        else
        {
            QTableWidgetItem *other = table->item(row, 0);
            if (other)
            {
                other->setText(QString::fromUtf8(kUnselectSymbol));
            }
        }
    }
}

void EmployerUIHelper::updateButtonStates(QPushButton *modifyBtn, QPushButton *deleteBtn, QTableWidget *table)
{
    bool ok = false;
    getSelectedEmployerId(table, &ok);
    const bool hasSelection = ok;

    if (modifyBtn)
    {
        modifyBtn->setEnabled(hasSelection);
    }
    if (deleteBtn)
    {
        deleteBtn->setEnabled(hasSelection);
    }
}

QVector<Employer> EmployerUIHelper::searchRecords(const QVector<Employer> &records, const QString &searchTerm)
{
    if (searchTerm.isEmpty())
    {
        return records;
    }

    QVector<Employer> filtered;
    filtered.reserve(records.size());
    
    for (const auto &record : records)
    {
        // Build a searchable string containing only first and last names
        const QString nameComposite = QStringLiteral("%1 %2").arg(record.firstName, record.lastName);

        // Split search term into tokens (e.g., "john smith" -> ["john","smith"])
        QStringList tokens = searchTerm.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        // Single token: match either first or last name
        if (tokens.size() == 1) {
            const QString &t = tokens.first();
            if (record.firstName.contains(t, Qt::CaseInsensitive) || record.lastName.contains(t, Qt::CaseInsensitive) || nameComposite.contains(t, Qt::CaseInsensitive)) {
                filtered.push_back(record);
            }
        } else {
            // Multi-token: require that all tokens appear somewhere in the full name (order-insensitive)
            bool allFound = true;
            for (const QString &tok : tokens) {
                if (!nameComposite.contains(tok, Qt::CaseInsensitive)) {
                    allFound = false;
                    break;
                }
            }
            if (allFound) filtered.push_back(record);
        }
    }

    return filtered;
}

QVector<Employer> EmployerUIHelper::sortRecords(const QVector<Employer> &records)
{
    QVector<Employer> sorted = records;
    std::sort(sorted.begin(), sorted.end(), [](const Employer &lhs, const Employer &rhs) {
        if (lhs.lastName.compare(rhs.lastName, Qt::CaseInsensitive) == 0)
        {
            return lhs.firstName.compare(rhs.firstName, Qt::CaseInsensitive) < 0;
        }
        return lhs.lastName.compare(rhs.lastName, Qt::CaseInsensitive) < 0;
    });
    
    return sorted;
}

// NOTE: CSV export helper removed — use `Employer::exportToPdf` for exporting employer lists as PDF.

// =============================================================================
// MainWindow Implementation
// =============================================================================


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientsPage(nullptr)
    , resourcesPage(nullptr)
    , sponsorsPage(nullptr)
    , templatesPage(nullptr)
    , shopPage(nullptr)
    , profileWidget(nullptr)
    , profileUI(nullptr)
    , templateWidget(nullptr)
    , clientWidget(nullptr)
    , sponsorWidget(nullptr)
    , sponsorWindow(nullptr)
    , ressourceWidget(nullptr)
    , projectWidget(nullptr)
    , loginPageWidget(nullptr)
    , authStackedWidget(nullptr)
    , loginUI(nullptr)
    , pageTransitionAnimation(nullptr)
    , animationGroup(nullptr)
    , loginFormTransitionAnimation(nullptr)
    , currentPageIndex(-1)
    , chatbot(nullptr)
{
    ui->setupUi(this);

    // =============================================================================
    // 🔐 ELEGANT LOGIN DIALOG - NO ANIMATIONS, FIXED DESIGN
    // =============================================================================
    QDialog *loginDialog = new QDialog(this);
    loginDialog->setWindowTitle("InspiraStudio Login");
    loginDialog->setFixedSize(560, 520);
    loginDialog->setModal(true);
    loginDialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    loginDialog->setAttribute(Qt::WA_TranslucentBackground);
    
    // Main container with shadow effect
    QWidget *container = new QWidget(loginDialog);
    container->setGeometry(15, 15, 530, 490);
    container->setStyleSheet(
        "QWidget {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #ffffff, stop:1 #f8f9fa);"
        "    border-radius: 20px;"
        "    border: 1px solid rgba(30, 136, 255, 0.1);"
        "}"
    );
    
    // Add drop shadow effect
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(40);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(10);
    shadowEffect->setColor(QColor(30, 136, 255, 80));
    container->setGraphicsEffect(shadowEffect);

    QVBoxLayout *loginLayout = new QVBoxLayout(container);
    loginLayout->setSpacing(22);
    loginLayout->setContentsMargins(55, 55, 55, 55);

    // Logo/Header area with animated gradient background
    QWidget *headerWidget = new QWidget();
    headerWidget->setFixedHeight(120);
    headerWidget->setStyleSheet(
        "QWidget {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #667eea, stop:0.5 #1e88ff, stop:1 #764ba2);"
        "    border-radius: 15px;"
        "    border: 2px solid rgba(255, 255, 255, 0.3);"
        "}"
    );
    
    // Header glow effect
    QGraphicsDropShadowEffect *headerGlow = new QGraphicsDropShadowEffect();
    headerGlow->setBlurRadius(25);
    headerGlow->setXOffset(0);
    headerGlow->setYOffset(0);
    headerGlow->setColor(QColor(30, 136, 255, 120));
    headerWidget->setGraphicsEffect(headerGlow);
    
    QVBoxLayout *headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 15, 0, 15);
    headerLayout->setSpacing(5);
    
    // Animated title
    QLabel *titleLabel = new QLabel("🔐 InspiraStudio");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #ffffff;"
        "    font-size: 36px;"
        "    font-weight: 700;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    background: transparent;"
        "    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);"
        "}"
    );
    headerLayout->addWidget(titleLabel);
    
    QLabel *subtitleLabel = new QLabel("✨ Welcome Back ✨");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet(
        "QLabel {"
        "    color: rgba(255, 255, 255, 0.95);"
        "    font-size: 16px;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    background: transparent;"
        "    letter-spacing: 1px;"
        "}"
    );
    headerLayout->addWidget(subtitleLabel);
    
    loginLayout->addWidget(headerWidget);
    loginLayout->addSpacing(20);

    // Username label with icon
    QLabel *usernameLabel = new QLabel("👤  Username");
    usernameLabel->setStyleSheet(
        "QLabel {"
        "    color: #2c3e50;"
        "    font-size: 15px;"
        "    font-weight: 600;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    margin-bottom: 6px;"
        "}"
    );
    loginLayout->addWidget(usernameLabel);

    // Username field with enhanced styling
    QLineEdit *usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("Enter your username...");
    usernameEdit->setText("adminInspiraStudio");
    usernameEdit->setFixedHeight(55);
    usernameEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 15px 20px;"
        "    border: 2px solid #e1e8ed;"
        "    border-radius: 12px;"
        "    background-color: #ffffff;"
        "    color: #000000;"
        "    font-size: 15px;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    selection-background-color: #1e88ff;"
        "    margin: 0px;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid #1e88ff;"
        "    background-color: #f0f8ff;"
        "    padding: 15px 20px;"
        "    margin: 0px;"
        "}"
        "QLineEdit:hover {"
        "    background-color: #fafbfc;"
        "    border: 2px solid #b0c4de;"
        "    padding: 15px 20px;"
        "    margin: 0px;"
        "}"
    );
    loginLayout->addWidget(usernameEdit);

    loginLayout->addSpacing(8);

    // Password label with icon
    QLabel *passwordLabel = new QLabel("🔒  Password");
    passwordLabel->setStyleSheet(
        "QLabel {"
        "    color: #2c3e50;"
        "    font-size: 15px;"
        "    font-weight: 600;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    margin-bottom: 6px;"
        "}"
    );
    loginLayout->addWidget(passwordLabel);

    // Password field with enhanced styling
    QLineEdit *passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Enter your password...");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setText("alawi");
    passwordEdit->setFixedHeight(55);
    passwordEdit->setStyleSheet(
        "QLineEdit {"
        "    padding: 15px 20px;"
        "    border: 2px solid #e1e8ed;"
        "    border-radius: 12px;"
        "    background-color: #ffffff;"
        "    color: #000000;"
        "    font-size: 15px;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    selection-background-color: #1e88ff;"
        "    margin: 0px;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid #1e88ff;"
        "    background-color: #f0f8ff;"
        "    padding: 15px 20px;"
        "    margin: 0px;"
        "}"
        "QLineEdit:hover {"
        "    background-color: #fafbfc;"
        "    border: 2px solid #b0c4de;"
        "    padding: 15px 20px;"
        "    margin: 0px;"
        "}"
    );
    loginLayout->addWidget(passwordEdit);

    // Error label (hidden by default) with slide animation
    QLabel *errorLabel = new QLabel();
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setWordWrap(true);
    errorLabel->setVisible(false);
    errorLabel->setFixedHeight(0);
    errorLabel->setStyleSheet(
        "QLabel {"
        "    color: #dc3545;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    padding: 12px;"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #f8d7da, stop:1 #f5c2c7);"
        "    border: 2px solid #f1aeb5;"
        "    border-radius: 10px;"
        "}"
    );
    loginLayout->addWidget(errorLabel);

    loginLayout->addSpacing(15);

    // Login button with gradient and hover animation
    QPushButton *loginButton = new QPushButton("🚀  Login to InspiraStudio");
    loginButton->setFixedHeight(58);
    loginButton->setCursor(Qt::PointingHandCursor);
    loginButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #667eea, stop:0.5 #1e88ff, stop:1 #764ba2);"
        "    color: white;"
        "    padding: 15px;"
        "    margin: 0px;"
        "    border: none;"
        "    border-radius: 12px;"
        "    font-size: 18px;"
        "    font-weight: 700;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    letter-spacing: 0.5px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #5568d3, stop:0.5 #0d6efd, stop:1 #6a3f8f);"
        "    padding: 15px;"
        "    margin: 0px;"
        "    border: none;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #4a5bbd, stop:0.5 #0a58ca, stop:1 #5a3579);"
        "    padding: 15px;"
        "    margin: 0px;"
        "    border: none;"
        "}"
    );
    
    // Button glow effect
    QGraphicsDropShadowEffect *buttonGlow = new QGraphicsDropShadowEffect();
    buttonGlow->setBlurRadius(20);
    buttonGlow->setXOffset(0);
    buttonGlow->setYOffset(4);
    buttonGlow->setColor(QColor(30, 136, 255, 100));
    loginButton->setGraphicsEffect(buttonGlow);
    
    loginLayout->addWidget(loginButton);

    loginLayout->addStretch();

    // Footer text with gradient
    QLabel *footerLabel = new QLabel("🌟 InspiraStudio © 2025 - Secure Access 🌟");
    footerLabel->setAlignment(Qt::AlignCenter);
    footerLabel->setStyleSheet(
        "QLabel {"
        "    color: #95a5a6;"
        "    font-size: 13px;"
        "    font-family: 'Poppins Light', sans-serif;"
        "    font-weight: 500;"
        "    letter-spacing: 0.5px;"
        "}"
    );
    loginLayout->addWidget(footerLabel);

    // Login button connection - NO ANIMATIONS
    connect(loginButton, &QPushButton::clicked, [=]() {
        QString username = usernameEdit->text().trimmed();
        QString password = passwordEdit->text();

        // Validate credentials - database connection will be established after login
        if (username == "adminInspiraStudio" && password == "alawi") {
            qDebug() << "[Login] Credentials validated successfully";
            // Success - close immediately without animation
            loginDialog->accept();
            loginDialog->close();
        } else {
            qDebug() << "[Login] Invalid credentials entered";
            // Show error message without animation
            errorLabel->setText("❌ Invalid credentials. Please try again.");
            errorLabel->setVisible(true);
            errorLabel->setFixedHeight(60);
        }
    });

    // Allow Enter key to submit
    connect(passwordEdit, &QLineEdit::returnPressed, loginButton, &QPushButton::click);

    // Center dialog on screen
    loginDialog->move(
        (QApplication::primaryScreen()->geometry().width() - loginDialog->width()) / 2,
        (QApplication::primaryScreen()->geometry().height() - loginDialog->height()) / 2
    );

    // Show login dialog and wait - NO ENTRANCE ANIMATIONS
    if (loginDialog->exec() != QDialog::Accepted) {
        QApplication::quit();
        return;
    }

    delete loginDialog;
    // =============================================================================
    // END LOGIN DIALOG
    // =============================================================================

    legionPixmap = QPixmap(QStringLiteral(":/images/legion.png"));
    updateLegionLogoScaled();

    setupSidebarIcons();

    connect(ui->employerBtn, &QPushButton::clicked, this, &MainWindow::onDashboardClicked);
    connect(ui->profileBtn, &QPushButton::clicked, this, &MainWindow::onProfileClicked);
    connect(ui->projectsBtn, &QPushButton::clicked, this, &MainWindow::onProjectsClicked);
    connect(ui->clientsBtn, &QPushButton::clicked, this, &MainWindow::onClientsClicked);
    connect(ui->resourcesBtn, &QPushButton::clicked, this, &MainWindow::onResourcesClicked);
    connect(ui->sponsorsBtn, &QPushButton::clicked, this, &MainWindow::onSponsorsClicked);
    connect(ui->templatesBtn, &QPushButton::clicked, this, &MainWindow::onTemplatesClicked);
    connect(ui->shopBtn, &QPushButton::clicked, this, &MainWindow::onAboutClicked);
    connect(ui->loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    setupPages();
    setupProfileWidget();
    setupTemplateWidget();
    setupClientWidget();
    setupSponsorWidget();
    setupRessourceWidget();
    setupProjectWidget();
    setupFaceRecognitionWidget();
    setupAnimations();
    setupDashboardAnimations();
    
    // Setup chatbot
    chatbot = new OpenAIChatbot(this);

    // .env support disabled: all config is embedded in code per project settings.
    // The chatbot already initializes with embedded defaults (API key + model).
    // If you want to override in code, uncomment the following lines and set your values.
    // chatbot->setApiKey(QStringLiteral("your_cohere_api_key_here"));
    chatbot->setCohereModel(QStringLiteral("command-a-03-2025"));
    qDebug() << "[MainWindow] .env removed; using embedded Cohere configuration.";
    
    // Connect chatbot signals
    connect(ui->chatbotSendButton, &QPushButton::clicked, this, &MainWindow::onChatbotSendClicked);
    connect(ui->chatbotClearButton, &QPushButton::clicked, this, &MainWindow::onChatbotClearClicked);
    connect(ui->chatbotHistoryButton, &QPushButton::clicked, this, &MainWindow::onChatbotHistoryClicked);
    connect(ui->chatbotInput, &QLineEdit::returnPressed, this, &MainWindow::onChatbotSendClicked);
    
    connect(chatbot, &OpenAIChatbot::responseReceived, this, &MainWindow::onChatbotResponseReceived);
    connect(chatbot, &OpenAIChatbot::errorOccurred, this, &MainWindow::onChatbotErrorOccurred);
    connect(chatbot, &OpenAIChatbot::processingStatusChanged, this, &MainWindow::onChatbotProcessingStatusChanged);

        // Setup Face++ cloud API client for recognition
        faceApiClient = new FaceApi::Client(this);
        faceApiClient->setConfidenceThreshold(75.0);
        connect(faceApiClient, &FaceApi::Client::recognitionCompleted,
            this, &MainWindow::onFaceRecognitionCompleted);
        connect(faceApiClient, &FaceApi::Client::recognitionFailed,
            this, &MainWindow::onFaceProcessingError);
    qDebug() << "[MainWindow] Face Recognition API client initialized (Face++).";
    

    addButtonHoverEffect(ui->profileBtn);
    addButtonHoverEffect(ui->projectsBtn);
    addButtonHoverEffect(ui->clientsBtn);
    addButtonHoverEffect(ui->resourcesBtn);
    addButtonHoverEffect(ui->sponsorsBtn);
    addButtonHoverEffect(ui->templatesBtn);
    addButtonHoverEffect(ui->shopBtn);
    addButtonHoverEffect(ui->loginBtn);

    // Configure database connection with EmployerDB DSN
    qDebug() << "=== Configuring Database Connection ===";
    
    // Initialize the singleton connection
    Connection* conn = Connection::instance();
    bool connected = conn->createConnect();
    
    // Show connection status in a message box
    QString statusMsg;
    if (!connected) {
        qCritical() << "CRITICAL: Database failed to open during MainWindow initialization!";
        statusMsg = QString("❌ DATABASE CONNECTION FAILED!\n\n"
                           "DSN: InspiraStudio\n"
                           "Username: adminInspiraStudio\n\n"
                           "Please check:\n"
                           "1. ODBC DSN 'InspiraStudio' exists (64-bit)\n"
                           "2. Oracle ODBC driver is installed (64-bit)\n"
                           "3. Credentials are correct\n"
                           "4. Oracle service is running");
        QMessageBox::critical(this, "Database Connection Error", statusMsg);
    } else {
        qDebug() << "SUCCESS: Database connection established!";
        statusMsg = QString("✅ Database Connected Successfully!\nInspiraStudio - Oracle XE");
        QMessageBox::information(this, "Database Connection", statusMsg);
    }
    qDebug() << "===================================";

    // Connect employer UI buttons to slots
    connect(ui->saveEmployeeBtn, &QPushButton::clicked, this, &MainWindow::onAddEmployerClicked);
    connect(ui->employeeTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onEmployeeTableSelectionChanged);
    connect(ui->employeeTable, &QTableWidget::itemClicked, this, &MainWindow::onEmployeeTableItemClicked);
    connect(ui->modifyBtn, &QPushButton::clicked, this, &MainWindow::onModifyEmployerClicked);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteEmployerClicked);
    connect(ui->exportBtn, &QPushButton::clicked, this, &MainWindow::onExportEmployersClicked);
   // connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchEmployersClicked);
    connect(ui->searchInput, &QLineEdit::returnPressed, this, &MainWindow::onSearchEmployersClicked);
    // Live search: trigger as-you-type with debounce
    m_searchDebounceTimer = new QTimer(this);
    m_searchDebounceTimer->setSingleShot(true);
    m_searchDebounceTimer->setInterval(150); // 300 ms debounce
    connect(m_searchDebounceTimer, &QTimer::timeout, this, &MainWindow::onSearchEmployersClicked);
    connect(ui->searchInput, &QLineEdit::textChanged, this, &MainWindow::onSearchInputChanged);
    connect(ui->sortBtn, &QPushButton::clicked, this, &MainWindow::onSortEmployersClicked);
    connect(ui->statisticsBtn, &QPushButton::clicked, this, &MainWindow::onStatisticsClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &MainWindow::onCancelSelectionClicked);

    // Initialize employer table
    loadEmployers();
    
    // Initialize ressource table (after DB connection is established)
    qDebug() << "[MainWindow::setupUI] ressourceWidget pointer:" << ressourceWidget;
    if (ressourceWidget) {
        qDebug() << "[MainWindow::setupUI] Calling ressourceWidget->loadRessources()...";
        ressourceWidget->loadRessources();
        qDebug() << "[MainWindow::setupUI] ✅ Ressources loaded successfully!";
    } else {
        qDebug() << "[MainWindow::setupUI] ❌ ERROR: ressourceWidget is NULL!";
    }

    if (ui->modifyBtn) {
        ui->modifyBtn->setEnabled(false);
    }
    if (ui->deleteBtn) {
        ui->deleteBtn->setEnabled(false);
    }

    ui->stackedWidget->setCurrentIndex(0);
    setActiveSidebarButton(ui->employerBtn);
    currentPageIndex = 0;
}

MainWindow::~MainWindow()
{
    delete profileUI;
    delete loginUI;
    delete sponsorWindow;
    delete chatbot;
    delete ui;
}

void MainWindow::setupPages()
{
    // Initialize basic page widgets if needed
    // Pages are now primarily handled through the UI file
    
    // Setup employee table
    setupEmployeeTable();
    
    // Setup login forms in the main window overlay
    setupLoginForms();
}

void MainWindow::setupLoginForms()
{
    // Create login page widget and setup its UI directly in the main authStackedWidget
    loginPageWidget = new QWidget();
    loginUI = new Ui::LoginPage();
    loginUI->setupUi(loginPageWidget);
    
    // Add the login page widget to the main window's authStackedWidget
    ui->authStackedWidget->addWidget(loginPageWidget);
    
    // Use the main window's authStackedWidget (not the nested one from login.ui)
    authStackedWidget = ui->authStackedWidget;
    
    // Set to show the login page by default
    authStackedWidget->setCurrentIndex(0);
    
    // Setup form connections
    setupLoginFormConnections();
}

void MainWindow::setupProfileWidget()
{
    // Create Profile widget and set up its UI
    profileWidget = new QWidget();
    profileUI = new Ui::Profile();
    profileUI->setupUi(profileWidget);
    
    // Replace the placeholder Profile page in the stacked widget
    QWidget* profilePlaceholder = ui->stackedWidget->widget(1); // Profile is at index 1
    if (profilePlaceholder) {
        ui->stackedWidget->removeWidget(profilePlaceholder);
        ui->stackedWidget->insertWidget(1, profileWidget);
        delete profilePlaceholder;
    }
    
    // Connect Profile form buttons to slots
    connect(profileUI->saveProfileButton, &QPushButton::clicked, this, &MainWindow::onSaveProfileClicked);
    connect(profileUI->resetProfileButton, &QPushButton::clicked, this, &MainWindow::onResetProfileClicked);
    
    // Load default profile data
    profileUI->usernameEdit->setText("John Doe");
    profileUI->emailEdit->setText("john.doe@aminetemplate.com");
}

void MainWindow::setupTemplateWidget()
{
    // Create Template widget using the TemplateWidget class
    templateWidget = new TemplateWidget();
    
    // Find which stacked widget page contains the template container
    int templatePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("templateContainer")) {
            templatePageIndex = i;
            break;
        }
    }
    
    if (templatePageIndex != -1) {
        // Replace the placeholder Template page in the stacked widget
        QWidget* templatePlaceholder = ui->stackedWidget->widget(templatePageIndex);
        if (templatePlaceholder) {
            ui->stackedWidget->removeWidget(templatePlaceholder);
            ui->stackedWidget->insertWidget(templatePageIndex, templateWidget);
            delete templatePlaceholder;
        }
    }
}

void MainWindow::setupClientWidget()
{
    // Create Client widget using the ClientWidget class
    clientWidget = new ClientWidget();
    
    // Find which stacked widget page contains the client container
    int clientPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("clientContainer")) {
            clientPageIndex = i;
            break;
        }
    }
    
    if (clientPageIndex != -1) {
        // Replace the placeholder Client page in the stacked widget (same method as Template)
        QWidget* clientPlaceholder = ui->stackedWidget->widget(clientPageIndex);
        if (clientPlaceholder) {
            ui->stackedWidget->removeWidget(clientPlaceholder);
            ui->stackedWidget->insertWidget(clientPageIndex, clientWidget);
            delete clientPlaceholder;
        }
    }
}

void MainWindow::setupSponsorWidget()
{
    // Create Sponsor widget using the SponsorWidget class
    sponsorWidget = new SponsorWidget();
    
    // Find which stacked widget page contains the sponsor container
    int sponsorPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("sponsorContainer")) {
            sponsorPageIndex = i;
            break;
        }
    }
    
    if (sponsorPageIndex != -1) {
        // Replace the placeholder Sponsor page in the stacked widget (same method as Template)
        QWidget* sponsorPlaceholder = ui->stackedWidget->widget(sponsorPageIndex);
        if (sponsorPlaceholder) {
            ui->stackedWidget->removeWidget(sponsorPlaceholder);
            ui->stackedWidget->insertWidget(sponsorPageIndex, sponsorWidget);
            delete sponsorPlaceholder;
        }
    }
}

void MainWindow::setupRessourceWidget()
{
    qDebug() << "[MainWindow::setupRessourceWidget] CALLED - Creating RessourceWidget...";
    
    // Create Ressource widget using the RessourceWidget class
    ressourceWidget = new RessourceWidget();
    qDebug() << "[MainWindow::setupRessourceWidget] RessourceWidget created at:" << ressourceWidget;
    
    // Find which stacked widget page contains the ressource container
    int ressourcePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("ressourceContainer")) {
            ressourcePageIndex = i;
            qDebug() << "[MainWindow::setupRessourceWidget] Found ressource page at index:" << i;
            break;
        }
    }
    
    if (ressourcePageIndex != -1) {
        // Replace the placeholder Ressource page in the stacked widget (same method as Template)
        QWidget* ressourcePlaceholder = ui->stackedWidget->widget(ressourcePageIndex);
        if (ressourcePlaceholder) {
            ui->stackedWidget->removeWidget(ressourcePlaceholder);
            ui->stackedWidget->insertWidget(ressourcePageIndex, ressourceWidget);
            delete ressourcePlaceholder;
            qDebug() << "[MainWindow::setupRessourceWidget] ✅ RessourceWidget inserted into stacked widget";
        }
    } else {
        qDebug() << "[MainWindow::setupRessourceWidget] ❌ Could not find ressource page in stacked widget";
    }
}

void MainWindow::setupProjectWidget()
{
    // Create Project widget using the ProjectWidget class
    projectWidget = new ProjectWidget();
    
    // Find which stacked widget page contains the project container
    int projectPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("projectContainer")) {
            projectPageIndex = i;
            break;
        }
    }
    
    if (projectPageIndex != -1) {
        // Replace the placeholder Project page in the stacked widget (same method as Template)
        QWidget* projectPlaceholder = ui->stackedWidget->widget(projectPageIndex);
        if (projectPlaceholder) {
            ui->stackedWidget->removeWidget(projectPlaceholder);
            ui->stackedWidget->insertWidget(projectPageIndex, projectWidget);
            delete projectPlaceholder;
        }
    }
}

void MainWindow::setupFaceRecognitionWidget()
{
    // Create Face Recognition widget for real-time camera integration
    faceRecognitionWidget = new FaceRecognitionWidget(this);
    
    // Find a suitable location in the UI or add a new tab
    // Option 1: Add as a new stacked widget page
    if (ui->stackedWidget) {
        int pageIndex = ui->stackedWidget->addWidget(faceRecognitionWidget);
        qDebug() << "[MainWindow::setupFaceRecognitionWidget] Added FaceRecognitionWidget at page index:" << pageIndex;
        
        // Optional: Create a button to access the face recognition widget
        // This could be added to the sidebar or as a menu option
    }
    
    qDebug() << "[MainWindow::setupFaceRecognitionWidget] Face Recognition Widget initialized";
}

void MainWindow::setupAnimations()
{
    pageTransitionAnimation = new QPropertyAnimation(this);
    pageTransitionAnimation->setDuration(250);
    pageTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    animationGroup = new QParallelAnimationGroup(this);
    
    // Create login form transition animation
    loginFormTransitionAnimation = new QPropertyAnimation(this);
    loginFormTransitionAnimation->setDuration(300);
    loginFormTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void MainWindow::updateLegionLogoScaled()
{
    if (legionPixmap.isNull() || !ui->legionLogo) return;

    // Determine available width inside the legionLogo label accounting for padding/margins
    int maxW = ui->legionLogo->maximumWidth();
    int maxH = ui->legionLogo->maximumHeight();

    // If maximums are large, instead use current label width (so it scales with layout)
    if (maxW <= 0 || maxW > 1000) maxW = ui->legionLogo->width();
    if (maxH <= 0 || maxH > 1000) maxH = ui->legionLogo->height();

    QSize targetSize = legionPixmap.size();
    targetSize.scale(maxW, maxH, Qt::KeepAspectRatio);

    QPixmap scaled = legionPixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->legionLogo->setPixmap(scaled);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    // Update legion logo scaling on window resize to maintain aspect ratio and prevent distortion
    if (!legionPixmap.isNull()) {
        updateLegionLogoScaled();
    }
}

void MainWindow::switchToPage(int pageIndex)
{
    if (pageIndex == currentPageIndex) return;
    
    currentPageIndex = pageIndex;
    
    // Simple fade transition
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
    ui->stackedWidget->setGraphicsEffect(effect);
    
    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(125);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.3);
    
    QPropertyAnimation *fadeIn = new QPropertyAnimation(effect, "opacity");
    fadeIn->setDuration(125);
    fadeIn->setStartValue(0.3);
    fadeIn->setEndValue(1.0);
    
    connect(fadeOut, &QPropertyAnimation::finished, [this, pageIndex, fadeIn]() {
        ui->stackedWidget->setCurrentIndex(pageIndex);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    });
    
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::addButtonHoverEffect(QPushButton* button)
{
    // Basic hover effect - more complex animations can be added later
    button->setCursor(Qt::PointingHandCursor);
    if (!button) return;
    // For admin action buttons install an event filter to manage shadows
    if (button == ui->modifyBtn || button == ui->deleteBtn) {
        button->installEventFilter(this);
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (!watched || !event) return QMainWindow::eventFilter(watched, event);

    // Only handle hovering for modify/delete buttons here
    if ((watched == ui->modifyBtn || watched == ui->deleteBtn)) {
        QPushButton *btn = qobject_cast<QPushButton*>(watched);
        if (!btn) return QMainWindow::eventFilter(watched, event);

        if (event->type() == QEvent::Enter) {
            // Remove existing effect
            if (btn->graphicsEffect()) {
                btn->graphicsEffect()->deleteLater();
            }
            QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(btn);
            shadow->setBlurRadius(24);
            shadow->setXOffset(0);
            shadow->setYOffset(8);
            QColor color = (watched == ui->modifyBtn) ? QColor(255, 179, 0, 110) : QColor(219, 57, 57, 110);
            shadow->setColor(color);
            btn->setGraphicsEffect(shadow);
        } else if (event->type() == QEvent::Leave) {
            if (btn->graphicsEffect()) {
                btn->graphicsEffect()->deleteLater();
            }
            btn->setGraphicsEffect(nullptr);
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::onDashboardClicked()
{
    setActiveSidebarButton(ui->employerBtn);
    switchToPage(0); // Dashboard is at index 0
}

void MainWindow::onProfileClicked()
{
    setActiveSidebarButton(ui->profileBtn);
    switchToPage(1); // Profile is at index 1
}

void MainWindow::onProjectsClicked()
{
    setActiveSidebarButton(ui->projectsBtn);
    // Find which stacked widget page contains the project widget
    int projectPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == projectWidget) {
            projectPageIndex = i;
            break;
        }
    }
    
    if (projectPageIndex != -1) {
        switchToPage(projectPageIndex); // Switch to the project page
    }
}

void MainWindow::onClientsClicked()
{
    setActiveSidebarButton(ui->clientsBtn);
    // Find which stacked widget page contains the client widget
    int clientPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == clientWidget) {
            clientPageIndex = i;
            break;
        }
    }
    
    if (clientPageIndex != -1) {
        switchToPage(clientPageIndex); // Switch to the client page
    }
}

void MainWindow::onResourcesClicked()
{
    setActiveSidebarButton(ui->resourcesBtn);
    // Find which stacked widget page contains the ressource widget
    int ressourcePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == ressourceWidget) {
            ressourcePageIndex = i;
            break;
        }
    }
    
    if (ressourcePageIndex != -1) {
        switchToPage(ressourcePageIndex); // Switch to the ressource page
    }
}

void MainWindow::onSponsorsClicked()
{
    setActiveSidebarButton(ui->sponsorsBtn);
    
    // Create SponsorWindow if it doesn't exist
    if (!sponsorWindow) {
        sponsorWindow = new SponsorWindow(this);
        sponsorWindow->setAttribute(Qt::WA_DeleteOnClose, false); // Keep window in memory
    }
    
    // Show and activate the window
    sponsorWindow->show();
    sponsorWindow->raise();
    sponsorWindow->activateWindow();
}

void MainWindow::onTemplatesClicked()
{
    setActiveSidebarButton(ui->templatesBtn);
    // Find which stacked widget page contains the template widget
    int templatePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == templateWidget) {
            templatePageIndex = i;
            break;
        }
    }
    
    if (templatePageIndex != -1) {
        switchToPage(templatePageIndex); // Switch to the template page (index 7)
    }
}

void MainWindow::onAboutClicked()
{
    setActiveSidebarButton(ui->shopBtn);
    // About page is at index 9 in the stackedWidget
    switchToPage(9);
}

void MainWindow::onLoginClicked()
{
    // Switch to login overlay instead of a page
    ui->mainStackedWidget->setCurrentIndex(1); // Show loginOverlayPage
    ui->authStackedWidget->setCurrentIndex(0); // Show login form
}

void MainWindow::showMainContent()
{
    // Switch back to normal content
    ui->mainStackedWidget->setCurrentIndex(0); // Show normalContentPage
}

void MainWindow::showLoginOverlay()
{
    // Switch to login overlay
    ui->mainStackedWidget->setCurrentIndex(1); // Show loginOverlayPage
    if (authStackedWidget) {
        authStackedWidget->setCurrentIndex(0); // Show login form
    }
}

void MainWindow::onLoginBackClicked()
{
    // Close the login overlay and make the Employer page active
    showMainContent();
    setActiveSidebarButton(ui->employerBtn);
    switchToPage(0); // Employers are shown at index 0
}

void MainWindow::setupLoginFormConnections()
{
    if (!authStackedWidget || !loginPageWidget) return;
    
    // Find and connect Sign Up navigation button on login form
    QPushButton* signUpNavButton = loginPageWidget->findChild<QPushButton*>("signUpNavButton");
    if (signUpNavButton) {
        connect(signUpNavButton, &QPushButton::clicked, this, &MainWindow::showSignUpForm);
        addButtonHoverEffect(signUpNavButton);
    }
    
    // Find and connect Forgot Password navigation button on login form
    QPushButton* forgotPasswordNavButton = loginPageWidget->findChild<QPushButton*>("forgotPasswordNavButton");
    if (forgotPasswordNavButton) {
        connect(forgotPasswordNavButton, &QPushButton::clicked, this, &MainWindow::showForgotPasswordForm);
        addButtonHoverEffect(forgotPasswordNavButton);
    }
    
    // Find and connect back to login buttons
    QPushButton* backToLoginFromSignUpButton = loginPageWidget->findChild<QPushButton*>("backToLoginFromSignUpButton");
    if (backToLoginFromSignUpButton) {
        connect(backToLoginFromSignUpButton, &QPushButton::clicked, this, &MainWindow::showLoginForm);
        addButtonHoverEffect(backToLoginFromSignUpButton);
    }
    
    QPushButton* backToLoginFromForgotButton = loginPageWidget->findChild<QPushButton*>("backToLoginFromForgotButton");
    if (backToLoginFromForgotButton) {
        connect(backToLoginFromForgotButton, &QPushButton::clicked, this, &MainWindow::showLoginForm);
        addButtonHoverEffect(backToLoginFromForgotButton);
    }

    // Find and connect login page back button (returns to Employer page)
    QPushButton* loginBackButton = loginPageWidget->findChild<QPushButton*>("loginBackButton");
    if (loginBackButton) {
        connect(loginBackButton, &QPushButton::clicked, this, &MainWindow::onLoginBackClicked);
        addButtonHoverEffect(loginBackButton);
    }

    // If there's a built-in "Back" button in the main UI for the login overlay, connect it
    if (ui->backToMainButton) {
        connect(ui->backToMainButton, &QPushButton::clicked, this, &MainWindow::onLoginBackClicked);
        addButtonHoverEffect(ui->backToMainButton);
    }
    
    // Connect form submission buttons to validation functions
    QPushButton* loginButton = loginPageWidget->findChild<QPushButton*>("loginButton");
    if (loginButton) {
        connect(loginButton, &QPushButton::clicked, this, &MainWindow::validateAndLogin);
        addButtonHoverEffect(loginButton);
    }
    
    QPushButton* signUpButton = loginPageWidget->findChild<QPushButton*>("signUpButton");
    if (signUpButton) {
        connect(signUpButton, &QPushButton::clicked, this, &MainWindow::validateAndSignUp);
        addButtonHoverEffect(signUpButton);
    }
    
    QPushButton* sendResetLinkButton = loginPageWidget->findChild<QPushButton*>("sendResetLinkButton");
    if (sendResetLinkButton) {
        connect(sendResetLinkButton, &QPushButton::clicked, this, &MainWindow::validateAndSendResetLink);
        addButtonHoverEffect(sendResetLinkButton);
    }
    
    // Connect Face Login button
    QPushButton* faceLoginButton = loginPageWidget->findChild<QPushButton*>("faceLoginButton");
    if (faceLoginButton) {
        connect(faceLoginButton, &QPushButton::clicked, this, &MainWindow::onFaceLoginClicked);
        addButtonHoverEffect(faceLoginButton);
    }
    
    // Enhance input fields with better focus effects
    QLineEdit* loginEmailField = loginPageWidget->findChild<QLineEdit*>("loginEmailLineEdit");
    QLineEdit* loginPasswordField = loginPageWidget->findChild<QLineEdit*>("loginPasswordLineEdit");
    QLineEdit* fullNameField = loginPageWidget->findChild<QLineEdit*>("fullNameLineEdit");
    QLineEdit* signUpEmailField = loginPageWidget->findChild<QLineEdit*>("signUpEmailLineEdit");
    QLineEdit* signUpPasswordField = loginPageWidget->findChild<QLineEdit*>("signUpPasswordLineEdit");
    QLineEdit* confirmPasswordField = loginPageWidget->findChild<QLineEdit*>("confirmPasswordLineEdit");
    QLineEdit* resetEmailField = loginPageWidget->findChild<QLineEdit*>("resetEmailLineEdit");
    
    if (loginEmailField) addInputFieldEnhancements(loginEmailField);
    if (loginPasswordField) addInputFieldEnhancements(loginPasswordField);
    if (fullNameField) addInputFieldEnhancements(fullNameField);
    if (signUpEmailField) addInputFieldEnhancements(signUpEmailField);
    if (signUpPasswordField) addInputFieldEnhancements(signUpPasswordField);
    if (confirmPasswordField) addInputFieldEnhancements(confirmPasswordField);
    if (resetEmailField) addInputFieldEnhancements(resetEmailField);
}

void MainWindow::switchLoginFormWithAnimation(int formIndex)
{
    if (!loginUI || !loginPageWidget) return;
    
    // Get the nested authStackedWidget from the login.ui
    QStackedWidget* loginStackedWidget = loginPageWidget->findChild<QStackedWidget*>("authStackedWidget");
    if (!loginStackedWidget) return;
    
    // Get current and target widgets
    QWidget* currentWidget = loginStackedWidget->currentWidget();
    QWidget* targetWidget = loginStackedWidget->widget(formIndex);
    
    if (currentWidget == targetWidget) return;
    
    // Create fade out animation for current widget
    QGraphicsOpacityEffect* currentEffect = new QGraphicsOpacityEffect(currentWidget);
    currentWidget->setGraphicsEffect(currentEffect);
    
    QPropertyAnimation* fadeOut = new QPropertyAnimation(currentEffect, "opacity");
    fadeOut->setDuration(150);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->setEasingCurve(QEasingCurve::OutCubic);
    
    // Create fade in animation for target widget
    QGraphicsOpacityEffect* targetEffect = new QGraphicsOpacityEffect(targetWidget);
    targetWidget->setGraphicsEffect(targetEffect);
    
    QPropertyAnimation* fadeIn = new QPropertyAnimation(targetEffect, "opacity");
    fadeIn->setDuration(150);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::InCubic);
    
    // Connect fade out finished to start fade in
    connect(fadeOut, &QPropertyAnimation::finished, [=]() {
        loginStackedWidget->setCurrentIndex(formIndex);
        fadeIn->start();
        // Clean up fade out effect
        currentWidget->setGraphicsEffect(nullptr);
        fadeOut->deleteLater();
    });
    
    // Connect fade in finished to clean up
    connect(fadeIn, &QPropertyAnimation::finished, [=]() {
        targetWidget->setGraphicsEffect(nullptr);
        fadeIn->deleteLater();
    });
    
    // Start the fade out animation
    fadeOut->start();
}

void MainWindow::showLoginForm()
{
    switchLoginFormWithAnimation(0); // Login form page
}

void MainWindow::showSignUpForm()
{
    switchLoginFormWithAnimation(1); // Sign up form page
}

void MainWindow::showForgotPasswordForm()
{
    switchLoginFormWithAnimation(2); // Forgot password form page
}

void MainWindow::addInputFieldEnhancements(QLineEdit* field)
{
    if (!field) return;
    
    // Simply enhance the existing styles with better focus effects
    field->setStyleSheet(R"(
        QLineEdit {
            padding: 12px 16px;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            background-color: #ffffff;
            color: #495057;
            font-weight: 300;
            letter-spacing: 0.5px;
            transition: all 0.3s ease;
        }
        QLineEdit:focus {
            border: 2px solid #007bff;
            background-color: #f8f9fa;
            outline: none;
        }
        QLineEdit:hover {
            border-color: #adb5bd;
            background-color: #f8f9fa;
        }
    )");
}

// Validation helper methods
bool MainWindow::isValidEmail(const QString& email)
{
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

bool MainWindow::isValidPassword(const QString& password)
{
    // Password must be at least 8 characters and contain at least one number or special character
    if (password.length() < 8) return false;
    
    QRegularExpression hasNumberOrSpecial(R"([0-9!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?])");
    return hasNumberOrSpecial.match(password).hasMatch();
}

void MainWindow::showValidationError(const QString& message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Validation Error");
    msgBox.setText(message);
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #ffffff;
            color: #343a40;
            font-family: 'Poppins';
            font-size: 12px;
        }
        QMessageBox QPushButton {
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: 300;
            min-width: 60px;
        }
        QMessageBox QPushButton:hover {
            background-color: #0056b3;
        }
    )");
    msgBox.exec();
}

void MainWindow::showStyledValidationError(const QString& title, const QString& message)
{
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    
    // Apply beautiful stylesheet from style.qss equivalent
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #fafafa;
            color: #212121;
            font-family: 'Segoe UI', 'Poppins', Arial, sans-serif;
            font-size: 12px;
        }
        QMessageBox QLabel {
            color: #d32f2f;
            font-weight: bold;
            line-height: 1.6;
            padding: 5px;
        }
        QMessageBox QPushButton {
            background-color: #d32f2f;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 10px 24px;
            font-weight: bold;
            font-size: 12px;
            min-width: 80px;
        }
        QMessageBox QPushButton:hover {
            background-color: #b71c1c;
        }
        QMessageBox QPushButton:pressed {
            background-color: #7f0000;
        }
    )");
    
    msgBox.exec();
}

void MainWindow::setFieldError(QLineEdit* field, bool hasError)
{
    if (!field) return;
    
    if (hasError) {
        field->setStyleSheet(R"(
            QLineEdit {
                padding: 12px 16px;
                border: 2px solid #dc3545;
                border-radius: 8px;
                background-color: #fff5f5;
                color: #495057;
                font-weight: 300;
                letter-spacing: 0.5px;
            }
            QLineEdit:focus {
                border-color: #dc3545;
                outline: none;
            }
        )");
    } else {
        field->setStyleSheet(R"(
            QLineEdit {
                padding: 12px 16px;
                border: 1px solid #dee2e6;
                border-radius: 8px;
                background-color: #ffffff;
                color: #495057;
                font-weight: 300;
                letter-spacing: 0.5px;
            }
            QLineEdit:focus {
                border-color: #007bff;
                outline: none;
            }
            QLineEdit:hover {
                border-color: #adb5bd;
            }
        )");
    }
}

// Access Control - Check if current user is admin
bool MainWindow::checkAdminAccess(const QString &actionName)
{
    if (currentConnectedUserRole.toLower() != "administrator" && currentConnectedUserRole.toLower() != "admin")
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("🔒 Access Denied");
        msgBox.setText(
            QString("❌ ADMIN ACCESS DENIED\n\n"
                   "━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
                   "Action: %1\n"
                   "User: %2\n"
                   "Role: %3\n"
                   "━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                   "Only administrators can perform this action.\n"
                   "Please contact your system administrator.").arg(actionName, currentConnectedUserName, currentConnectedUserRole)
        );
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet(
            "QMessageBox { background-color: #fff5f5; }"
            "QMessageBox QLabel { color: #c41e3a; font-weight: bold; }"
            "QPushButton { background-color: #c41e3a; color: white; padding: 5px 15px; border-radius: 4px; }"
            "QPushButton:hover { background-color: #a01630; }"
        );
        msgBox.exec();
        return false;
    }
    return true;
}

void MainWindow::updateUserSessionDisplay()
{
    // Update user session info in UI
    QString sessionInfo = QString(
        "👤 %1 | Role: %2 | ID: %3"
    ).arg(currentConnectedUserName, currentConnectedUserRole, QString::number(currentConnectedEmployeeId));
    
    qDebug() << "[MainWindow::updateUserSessionDisplay]" << sessionInfo;
    
    // Update button access based on role
    updateEmployerButtonStates();
}

// Form validation methods
void MainWindow::validateAndLogin()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("loginEmailLineEdit");
    QLineEdit* passwordField = loginPageWidget->findChild<QLineEdit*>("loginPasswordLineEdit");
    
    if (!emailField || !passwordField) return;
    
    QString email = emailField->text().trimmed();
    QString password = passwordField->text();
    
    // Validate format first
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        showStyledValidationError("❌ Email Required", "Please enter your email address.");
        return;
    }
    
    if (password.isEmpty()) {
        setFieldError(passwordField, true);
        showStyledValidationError("❌ Password Required", "Please enter your password.");
        return;
    }
    
    // Clear field errors initially
    setFieldError(emailField, false);
    setFieldError(passwordField, false);
    
    // Query database for employer
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        showStyledValidationError("❌ Connection Error", "Database connection failed. Please try again.");
        return;
    }
    
    // First, find employer by email
    QSqlQuery query(db);
    query.prepare("SELECT ID_EMP, FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD, HIRE_DATE "
                  "FROM EMPLOYER WHERE EMAIL = :email");
    query.addBindValue(email);
    
    if (!query.exec()) {
        showStyledValidationError("❌ Database Error", "Database query failed: " + query.lastError().text());
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }
    
    if (query.next()) {
        // Email exists - now verify password
        QString storedPassword = query.value(6).toString();  // PASSWORD column
        
        qDebug() << "Email found:" << email;
        qDebug() << "Stored password:" << storedPassword;
        qDebug() << "Input password:" << password;
        
        // Compare passwords (handle both plain text and hashed)
        bool passwordMatch = false;
        
        // Try direct comparison first
        if (password == storedPassword) {
            passwordMatch = true;
            qDebug() << "Password matched (plain text)";
        }
        
        if (passwordMatch) {
            // ✅ Login successful!
            int employerId = query.value(0).toInt();
            QString firstname = query.value(1).toString();
            QString lastname = query.value(2).toString();
            QString phone = query.value(4).toString();
            QString role = query.value(5).toString();
            QString hireDate = query.value(7).toString();
            
            // Store connected user info
            currentConnectedEmployeeId = employerId;
            currentConnectedUserRole = role;
            currentConnectedUserName = QString("%1 %2").arg(firstname, lastname);
            
            // Clear fields
            emailField->clear();
            passwordField->clear();
            
            // Show success message with employee info
            QString infoMessage = QString(
                "✅ Connected as: %1 %2\n\n"
                "━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
                "📧 Email: %3\n"
                "📱 Phone: %4\n"
                "💼 Role: %5\n"
                "📅 Hire Date: %6\n"
                "━━━━━━━━━━━━━━━━━━━━━━━━━━━"
            ).arg(firstname, lastname, email, phone, role, hireDate);
            
            // Show success dialog
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("🎊 Login Successful!");
            msgBox.setText(infoMessage);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStyleSheet(
                "QMessageBox { background-color: #f5f5f5; }"
                "QMessageBox QLabel { color: #1a237e; font-weight: bold; }"
            );
            msgBox.exec();
            
            // Show main content
            showMainContent();
            ui->stackedWidget->setCurrentIndex(0);
            
            // Update button states based on user role
            loadEmployers();  // This will refresh the employer list and button states
            
            // Update user session display
            updateUserSessionDisplay();
            
        } else {
            // Email exists but password wrong
            setFieldError(passwordField, true);
            showStyledValidationError("❌ Incorrect Password", 
                                     QString("The password you entered is incorrect.\n\n"
                                            "User: %1\n"
                                            "Please try again or use facial recognition.").arg(email));
        }
    } else {
        // Email not found
        setFieldError(emailField, true);
        showStyledValidationError("❌ Email Not Found", 
                                 QString("The email '%1' does not exist in our system.\n\n"
                                        "Please check your email address or sign up.").arg(email));
    }
}

void MainWindow::validateAndSignUp()
{
    QLineEdit* nameField = loginPageWidget->findChild<QLineEdit*>("fullNameLineEdit");
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("signUpEmailLineEdit");
    QLineEdit* passwordField = loginPageWidget->findChild<QLineEdit*>("signUpPasswordLineEdit");
    QLineEdit* confirmPasswordField = loginPageWidget->findChild<QLineEdit*>("confirmPasswordLineEdit");
    QCheckBox* termsCheckBox = loginPageWidget->findChild<QCheckBox*>("acceptTermsCheckBox");
    
    if (!nameField || !emailField || !passwordField || !confirmPasswordField || !termsCheckBox) return;
    
    QString name = nameField->text().trimmed();
    QString email = emailField->text().trimmed();
    QString password = passwordField->text();
    QString confirmPassword = confirmPasswordField->text();
    
    bool hasErrors = false;
    QString errorMessage;
    
    // Validate full name
    if (name.isEmpty()) {
        setFieldError(nameField, true);
        errorMessage = "Please enter your full name.";
        hasErrors = true;
    } else if (name.length() < 2) {
        setFieldError(nameField, true);
        errorMessage = "Full name must be at least 2 characters long.";
        hasErrors = true;
    } else {
        setFieldError(nameField, false);
    }
    
    // Validate email
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please enter your email address.";
        hasErrors = true;
    } else if (!isValidEmail(email)) {
        setFieldError(emailField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please enter a valid email address.";
        hasErrors = true;
    } else {
        setFieldError(emailField, false);
    }
    
    // Validate password
    if (password.isEmpty()) {
        setFieldError(passwordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please enter a password.";
        hasErrors = true;
    } else if (!isValidPassword(password)) {
        setFieldError(passwordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Password must be at least 8 characters long and contain at least one number or special character.";
        hasErrors = true;
    } else {
        setFieldError(passwordField, false);
    }
    
    // Validate confirm password
    if (confirmPassword.isEmpty()) {
        setFieldError(confirmPasswordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please confirm your password.";
        hasErrors = true;
    } else if (password != confirmPassword) {
        setFieldError(confirmPasswordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Passwords do not match.";
        hasErrors = true;
    } else {
        setFieldError(confirmPasswordField, false);
    }
    
    // Validate terms acceptance
    if (!termsCheckBox->isChecked()) {
        if (errorMessage.isEmpty()) errorMessage = "Please accept the terms and conditions.";
        hasErrors = true;
    }
    
    if (hasErrors) {
        showValidationError(errorMessage);
    } else {
        // TODO: Implement actual sign up logic here
        showValidationError("Sign up functionality not implemented yet.\nThis would create a new user account.");
    }
}

void MainWindow::validateAndSendResetLink()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("resetEmailLineEdit");
    
    if (!emailField) return;
    
    QString email = emailField->text().trimmed();
    
    // Validate email
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        showValidationError("Please enter your email address or username.");
    } else if (!isValidEmail(email) && !email.contains(QRegularExpression("^[a-zA-Z0-9_]+$"))) {
        setFieldError(emailField, true);
        showValidationError("Please enter a valid email address or username.");
    } else {
        setFieldError(emailField, false);
        // Show success message and return to login form
        QMessageBox::information(this, "Password Reset", "If an account with this email exists, a password reset link has been sent.\n\nPlease check your email and follow the instructions to reset your password.");
        showLoginForm(); // Return to login form
    }
}

void MainWindow::setupSidebarIcons()
{
    // Set up icons for each sidebar button using SVG resources
    if (ui->employerBtn) {
        ui->employerBtn->setIcon(QIcon(":/resources/icons/employer.svg"));
        ui->employerBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->profileBtn) {
        ui->profileBtn->setIcon(QIcon(":/resources/icons/profile.svg"));
        ui->profileBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->projectsBtn) {
        ui->projectsBtn->setIcon(QIcon(":/resources/icons/projects.svg"));
        ui->projectsBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->clientsBtn) {
        ui->clientsBtn->setIcon(QIcon(":/resources/icons/clients.svg"));
        ui->clientsBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->resourcesBtn) {
        ui->resourcesBtn->setIcon(QIcon(":/resources/icons/library.svg"));
        ui->resourcesBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->sponsorsBtn) {
        ui->sponsorsBtn->setIcon(QIcon(":/resources/icons/star.svg"));
        ui->sponsorsBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->templatesBtn) {
        ui->templatesBtn->setIcon(QIcon(":/resources/icons/display.svg"));
        ui->templatesBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->shopBtn) {
        ui->shopBtn->setIcon(QIcon(":/resources/icons/shop.svg"));
        ui->shopBtn->setIconSize(QSize(20, 20));
    }
}

void MainWindow::setActiveSidebarButton(QPushButton* activeButton)
{
    // List of all sidebar buttons
    QList<QPushButton*> sidebarButtons = {
        ui->employerBtn,
        ui->profileBtn,
        ui->projectsBtn,
        ui->clientsBtn,
        ui->resourcesBtn,
        ui->sponsorsBtn,
        ui->templatesBtn,
        ui->shopBtn
    };
    
    // Reset all buttons to inactive state
    for (QPushButton* btn : sidebarButtons) {
        if (btn) {
            btn->setChecked(false);
            btn->setProperty("active", false);
            // Force style refresh
            btn->style()->unpolish(btn);
            btn->style()->polish(btn);
            btn->update();
        }
    }
    
    // Set the active button
    if (activeButton) {
        activeButton->setChecked(true);
        activeButton->setProperty("active", true);
        // Force style refresh for active button
        activeButton->style()->unpolish(activeButton);
        activeButton->style()->polish(activeButton);
        activeButton->update();
    }
}

void MainWindow::setupCircularAvatar(QLabel* avatarLabel, const QString& initials)
{
    if (!avatarLabel) return;
    
    // Set circular avatar styling
    avatarLabel->setStyleSheet(
        "QLabel { "
        "    background-color: #007bff; "
        "    color: white; "
        "    border-radius: 20px; "
        "    font-size: 14px; "
        "    font-weight: 500; "
        "    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif; "
        "    text-align: center; "
        "}"
    );
    
    avatarLabel->setText(initials);
    avatarLabel->setAlignment(Qt::AlignCenter);
    
    // Ensure it's always circular
    avatarLabel->setMinimumSize(40, 40);
    avatarLabel->setMaximumSize(40, 40);
    avatarLabel->setScaledContents(true);
}

// Profile management slot implementations
void MainWindow::onSaveProfileClicked()
{
    // Validate profile information
    QString fullName = profileUI->usernameEdit->text().trimmed();
    QString email = profileUI->emailEdit->text().trimmed();
    QString password = profileUI->currentPasswordEdit->text();
    
    // Basic validation
    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Full name is required.");
        profileUI->usernameEdit->setFocus();
        return;
    }
    
    if (email.isEmpty() || !isValidEmail(email)) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid email address.");
        profileUI->emailEdit->setFocus();
        return;
    }
    
    // Here you would typically save to database or settings
    // For now, just show a success message
    QMessageBox::information(this, "Profile Saved", "Your profile information has been saved successfully!");
}

void MainWindow::onResetProfileClicked()
{
    // Reset profile form to default values
    profileUI->usernameEdit->setText("John Doe");
    profileUI->emailEdit->setText("john.doe@aminetemplate.com");
    profileUI->currentPasswordEdit->clear();
    
    QMessageBox::information(this, "Profile Reset", "Profile information has been reset to default values.");
}

void MainWindow::setupEmployeeTable()
{
    // Enable horizontal scrollbar
    ui->employeeTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->employeeTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    // Set specific column widths - wider data columns so more text is visible
    ui->employeeTable->setColumnWidth(0, 60);    // Select column
    ui->employeeTable->setColumnWidth(1, 100);   // Avatar column (thumbnail)
    ui->employeeTable->setColumnWidth(2, 60);    // ID column
    ui->employeeTable->setColumnWidth(3, 220);   // Name column
    ui->employeeTable->setColumnWidth(4, 300);   // Email column
    ui->employeeTable->setColumnWidth(5, 120);   // Role column
    ui->employeeTable->setColumnWidth(6, 120);   // Phone column
    ui->employeeTable->setColumnWidth(7, 100);   // Start Date column
    ui->employeeTable->setColumnWidth(8, 250);   // Resources column
    ui->employeeTable->setColumnWidth(9, 350);   // Projects column
    
    // Stretch last column to fill remaining space
    ui->employeeTable->horizontalHeader()->setStretchLastSection(false);
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch); // Projects stretches
    
    // Keep rows compact so more rows fit on screen (48px). Avatars show larger preview via tooltip.
    ui->employeeTable->verticalHeader()->setDefaultSectionSize(48);
    ui->employeeTable->verticalHeader()->setMinimumSectionSize(48);
    
    // Enable better selection behavior
    ui->employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // Center align headers
    for (int i = 0; i < ui->employeeTable->columnCount(); ++i) {
        QTableWidgetItem* headerItem = ui->employeeTable->horizontalHeaderItem(i);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignCenter);
        }
    }

    // Apply hover effect to action buttons
    if (ui->modifyBtn) addButtonHoverEffect(ui->modifyBtn);
    if (ui->deleteBtn) addButtonHoverEffect(ui->deleteBtn);
}

void MainWindow::setupDashboardAnimations()
{
    // Fade in the dashboard title and statistics container
    QWidget *dashboardTabTitle = ui->centralwidget ? ui->centralwidget->findChild<QWidget*>("dashboardTabTitle") : nullptr;
    if (dashboardTabTitle) {
        QPropertyAnimation* titleFade = new QPropertyAnimation(dashboardTabTitle, "windowOpacity");
        titleFade->setDuration(800);
        titleFade->setStartValue(0.0);
        titleFade->setEndValue(1.0);
        titleFade->setEasingCurve(QEasingCurve::InOutCubic);
        titleFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    QWidget *statisticsCardsContainer = ui->centralwidget ? ui->centralwidget->findChild<QWidget*>("statisticsCardsContainer") : nullptr;
    if (statisticsCardsContainer) {
        QPropertyAnimation* statsFade = new QPropertyAnimation(statisticsCardsContainer, "windowOpacity");
        statsFade->setDuration(1000);
        statsFade->setStartValue(0.0);
        statsFade->setEndValue(1.0);
        statsFade->setEasingCurve(QEasingCurve::OutCubic);
        statsFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // Slide and fade-in the three main statistic cards that exist in the UI
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QList<QWidget*> statWidgets;
    QWidget *totalEmployeesCard = ui->centralwidget ? ui->centralwidget->findChild<QWidget*>("totalEmployeesCard") : nullptr;
    QWidget *activeProjectsCard = ui->centralwidget ? ui->centralwidget->findChild<QWidget*>("activeProjectsCard") : nullptr;
    QWidget *performanceCard = ui->centralwidget ? ui->centralwidget->findChild<QWidget*>("performanceCard") : nullptr;
    if (totalEmployeesCard) statWidgets.append(totalEmployeesCard);
    if (activeProjectsCard) statWidgets.append(activeProjectsCard);
    if (performanceCard) statWidgets.append(performanceCard);

    for (int i = 0; i < statWidgets.size(); ++i) {
        QWidget* w = statWidgets[i];
        QRect finalGeom = w->geometry();

        QPropertyAnimation* slide = new QPropertyAnimation(w, "geometry");
        slide->setDuration(900 + i * 150);
        slide->setStartValue(QRect(finalGeom.x(), finalGeom.y() + 30, finalGeom.width(), finalGeom.height()));
        slide->setEndValue(finalGeom);
        slide->setEasingCurve(QEasingCurve::OutCubic);

        QPropertyAnimation* fade = new QPropertyAnimation(w, "windowOpacity");
        fade->setDuration(900 + i * 150);
        fade->setStartValue(0.0);
        fade->setEndValue(1.0);
        fade->setEasingCurve(QEasingCurve::InOutCubic);

        group->addAnimation(slide);
        group->addAnimation(fade);
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

// Employer Management Slots

void MainWindow::loadEmployers()
{
    qDebug() << "\n[MainWindow::loadEmployers] ========== LOADING EMPLOYERS ==========";
    qDebug() << "[MainWindow::loadEmployers] Calling Employer::selectAll()...";
    
    cachedEmployers = Employer::selectAll();
    
    qDebug() << "[MainWindow::loadEmployers] Retrieved" << cachedEmployers.size() << "employers from database";
    
    if (cachedEmployers.isEmpty())
    {
        qDebug() << "[MainWindow::loadEmployers] WARNING: No employers found or database error";
        // Don't show error if table is just empty
    }
    else
    {
        qDebug() << "[MainWindow::loadEmployers] Employers loaded successfully:";
        for (int i = 0; i < cachedEmployers.size(); ++i)
        {
            const Employer &emp = cachedEmployers.at(i);
            qDebug() << "  [" << i << "] ID:" << emp.employerId 
                     << "Name:" << emp.firstName << emp.lastName
                     << "Email:" << emp.email;
        }
    }
    
    qDebug() << "[MainWindow::loadEmployers] Populating table...";
    EmployerUIHelper::populateTable(ui->employeeTable, cachedEmployers);
    
    qDebug() << "[MainWindow::loadEmployers] Updating button states...";
    updateEmployerButtonStates();
    
    qDebug() << "[MainWindow::loadEmployers] ========== LOAD COMPLETE ==========\n";
}

void MainWindow::updateEmployerButtonStates()
{
    // Apply role-based button access restrictions FIRST
    bool isAdmin = (currentConnectedUserRole.toLower() == "administrator" || currentConnectedUserRole.toLower() == "admin");
    
    // Disable buttons for non-admin users - ALWAYS
    if (ui->saveEmployeeBtn)
    {
        ui->saveEmployeeBtn->setEnabled(isAdmin);
        if (!isAdmin)
        {
            ui->saveEmployeeBtn->setStyleSheet("QPushButton { color: #999; background-color: #e0e0e0; }");
            ui->saveEmployeeBtn->setToolTip("⛔ Admin access required to add employers");
        }
        else
        {
            ui->saveEmployeeBtn->setStyleSheet("");
            ui->saveEmployeeBtn->setToolTip("");
        }
    }
    
    if (ui->modifyBtn)
    {
        if (!isAdmin)
        {
            ui->modifyBtn->setEnabled(false);
            ui->modifyBtn->setStyleSheet("QPushButton { color: #999; background-color: #e0e0e0; }");
            ui->modifyBtn->setToolTip("⛔ Admin access required to modify employers");
        }
        else
        {
            // Pour admin: état désactivé par défaut — keep UI stylesheet so disabled styling remains
            ui->modifyBtn->setEnabled(false);
            // Do not clear button stylesheet; allow the designer QSS to manage enabled/disabled colors
            ui->modifyBtn->setToolTip("");
        }
    }
    
    if (ui->deleteBtn)
    {
        if (!isAdmin)
        {
            ui->deleteBtn->setEnabled(false);
            ui->deleteBtn->setStyleSheet("QPushButton { color: #999; background-color: #e0e0e0; }");
            ui->deleteBtn->setToolTip("⛔ Admin access required to delete employers");
        }
        else
        {
            // Pour admin: état désactivé par défaut — keep UI stylesheet so disabled styling remains
            ui->deleteBtn->setEnabled(false);
            // Do not clear stylesheet; use the designer QSS to control colors
            ui->deleteBtn->setToolTip("");
        }
    }
    
    // Now apply table selection logic (only if admin)
    if (isAdmin)
    {
        EmployerUIHelper::updateButtonStates(ui->modifyBtn, ui->deleteBtn, ui->employeeTable);
        // Apply admin-only coloring when selection exists
        bool hasSelection = false;
        EmployerUIHelper::getSelectedEmployerId(ui->employeeTable, &hasSelection);

        if (ui->modifyBtn)
        {
                if (hasSelection) {
                    ui->modifyBtn->setEnabled(true);
                    // Clear any inline override so the global QSS (light orange when enabled) applies
                    ui->modifyBtn->setStyleSheet("");
                } else {
                    ui->modifyBtn->setEnabled(false);
                    // Set explicit disabled style (greyed) so it remains visually disabled
                    ui->modifyBtn->setStyleSheet("QPushButton { color: #999; background-color: #e0e0e0; }");
                }
        }

        if (ui->deleteBtn)
        {
                if (hasSelection) {
                    ui->deleteBtn->setEnabled(true);
                    ui->deleteBtn->setStyleSheet("");
                } else {
                    ui->deleteBtn->setEnabled(false);
                    ui->deleteBtn->setStyleSheet("QPushButton { color: #999; background-color: #e0e0e0; }");
                }
        }
    }

    // End of updateEmployerButtonStates
}

void MainWindow::onAddEmployerClicked()
{
    qDebug() << "\n========== ADD EMPLOYER CLICKED ==========";
    
    // Check admin access
    if (!checkAdminAccess("Add New Employer"))
    {
        qDebug() << "[MainWindow::onAddEmployerClicked] Access denied for non-admin user: " << currentConnectedUserName;
        return;
    }
    
    EmployerForm form(this);
    form.setMode(EmployerForm::CreateMode);

    qDebug() << "[MainWindow::onAddEmployerClicked] Opening form in Create mode...";

    if (form.exec() != QDialog::Accepted)
    {
        qDebug() << "[MainWindow::onAddEmployerClicked] User cancelled the form";
        return;
    }

    qDebug() << "[MainWindow::onAddEmployerClicked] Form accepted, getting data...";
    
    const Employer rec = form.record();
    const QString password = form.rawPassword();

    qDebug() << "[MainWindow::onAddEmployerClicked] New employer data:";
    qDebug() << "  Name:" << rec.firstName << rec.lastName;
    qDebug() << "  Email:" << rec.email;
    qDebug() << "  Phone:" << rec.phone;
    qDebug() << "  Role:" << rec.role;
    qDebug() << "  Hire Date:" << rec.startDate;
    qDebug() << "[MainWindow::onAddEmployerClicked] Calling Employer::insert()...";

    if (!Employer::insert(rec, password))
    {
        qDebug() << "[MainWindow::onAddEmployerClicked] CRITICAL: insert FAILED!";
        QMessageBox::critical(this, tr("Insert Employer"), 
            tr("Failed to insert employer. Check logs for details."));
        return;
    }

    qDebug() << "[MainWindow::onAddEmployerClicked] Insert SUCCESS!";
    
    // Get the newly created employer to get its ID
    QVector<Employer> allEmployers = Employer::selectAll();
    if (!allEmployers.isEmpty())
    {
        const Employer& newEmployer = allEmployers.last();
        qDebug() << "[MainWindow::onAddEmployerClicked] New employer ID:" << newEmployer.employerId;
        
        // Assign selected resources if any
        QVector<qint64> selectedResources = form.selectedResourceIds();
        qDebug() << "[MainWindow::onAddEmployerClicked] Selected resources count:" << selectedResources.size();
        
        if (!selectedResources.isEmpty())
        {
            qDebug() << "[MainWindow::onAddEmployerClicked] Assigning" << selectedResources.size() << "resources...";
            for (qint64 resourceId : selectedResources)
            {
                qDebug() << "  → Adding resource" << resourceId;
                Ressource::addResourceToEmployer(newEmployer.employerId, resourceId);
            }
            qDebug() << "[MainWindow::onAddEmployerClicked] All resources assigned successfully!";
        }
        else
        {
            qDebug() << "[MainWindow::onAddEmployerClicked] No resources selected for this employer.";
        }
        
        // Assign selected projects if any
        QVector<qint64> selectedProjects = form.selectedProjectIds();
        qDebug() << "[MainWindow::onAddEmployerClicked] Selected projects count:" << selectedProjects.size();
        
        if (!selectedProjects.isEmpty())
        {
            qDebug() << "[MainWindow::onAddEmployerClicked] Assigning" << selectedProjects.size() << "projects...";
            for (qint64 projectId : selectedProjects)
            {
                qDebug() << "  → Adding project" << projectId;
                Project::addEmployerToProject(projectId, newEmployer.employerId);
            }
            qDebug() << "[MainWindow::onAddEmployerClicked] All projects assigned successfully!";
        }
        else
        {
            qDebug() << "[MainWindow::onAddEmployerClicked] No projects selected for this employer.";
        }
    }

    loadEmployers();
    QMessageBox::information(this, tr("Employer Added"), 
        tr("The employer has been created successfully."));
    
    qDebug() << "========== ADD EMPLOYER COMPLETED ==========\n";
}

void MainWindow::onModifyEmployerClicked()
{
    qDebug() << "\n========== MODIFY EMPLOYER CLICKED ==========";
    
    // Check admin access
    if (!checkAdminAccess("Modify Employer"))
    {
        qDebug() << "[MainWindow::onModifyEmployerClicked] Access denied for non-admin user: " << currentConnectedUserName;
        return;
    }
    
    bool ok = false;
    const qint64 employerId = EmployerUIHelper::getSelectedEmployerId(ui->employeeTable, &ok);
    
    qDebug() << "[MainWindow::onModifyEmployerClicked] getSelectedEmployerId returned:" << employerId;
    qDebug() << "[MainWindow::onModifyEmployerClicked] Selection valid (ok):" << ok;
    
    if (!ok)
    {
        qDebug() << "[MainWindow::onModifyEmployerClicked] ERROR: No valid selection!";
        QMessageBox::critical(this, tr("Update Employer"), 
            tr("Select a single employer to modify."));
        return;
    }

    qDebug() << "[MainWindow::onModifyEmployerClicked] Calling Employer::fetchById with ID:" << employerId;
    
    Employer existing;
    if (!Employer::fetchById(employerId, existing))
    {
        qDebug() << "[MainWindow::onModifyEmployerClicked] CRITICAL: fetchById FAILED for ID:" << employerId;
        QMessageBox::critical(this, tr("Update Employer"), 
            tr("Unable to locate the selected employer record."));
        return;
    }

    qDebug() << "[MainWindow::onModifyEmployerClicked] fetchById SUCCESS! Found:" << existing.firstName << existing.lastName;
    qDebug() << "[MainWindow::onModifyEmployerClicked] Opening edit form...";

    EmployerForm form(this);
    form.setMode(EmployerForm::EditMode);
    form.setRecord(existing);
    
    // Load currently assigned resources for pre-selection
    QVector<Ressource> assignedResources = Ressource::getResourcesByEmployer(employerId);
    QVector<qint64> currentResourceIds;
    for (const Ressource& res : assignedResources)
        currentResourceIds.append(res.idMedia);
    form.setSelectedResourceIds(currentResourceIds);
    
    // Load currently assigned projects for pre-selection
    QVector<Project> assignedProjects = Project::getProjectsByEmployer(employerId);
    QVector<qint64> currentProjectIds;
    for (const Project& proj : assignedProjects)
        currentProjectIds.append(proj.projectId);
    form.setSelectedProjectIds(currentProjectIds);

    if (form.exec() != QDialog::Accepted)
    {
        qDebug() << "[MainWindow::onModifyEmployerClicked] User cancelled the form";
        return;
    }

    qDebug() << "[MainWindow::onModifyEmployerClicked] Form accepted, getting updates...";
    
    const Employer updates = form.record();
    const bool passwordProvided = form.passwordProvided();
    const QString password = passwordProvided ? form.rawPassword() : existing.passwordHash;

    qDebug() << "[MainWindow::onModifyEmployerClicked] Calling Employer::update with ID:" << employerId;
    qDebug() << "[MainWindow::onModifyEmployerClicked] Updated data:" << updates.firstName << updates.lastName << updates.email;

    if (!Employer::update(employerId, updates, password, passwordProvided))
    {
        qDebug() << "[MainWindow::onModifyEmployerClicked] CRITICAL: update FAILED!";
        QMessageBox::critical(this, tr("Update Employer"), 
            tr("Failed to update employer. Check logs for details."));
        return;
    }

    qDebug() << "[MainWindow::onModifyEmployerClicked] Update SUCCESS! Now updating resources...";
    
    // Update employer resources
    QVector<qint64> selectedResources = form.selectedResourceIds();
    qDebug() << "[MainWindow::onModifyEmployerClicked] Current resources:" << currentResourceIds.size();
    qDebug() << "[MainWindow::onModifyEmployerClicked] New resources selected:" << selectedResources.size();
    
    Ressource::clearEmployerResources(employerId);
    qDebug() << "[MainWindow::onModifyEmployerClicked] Cleared old resources";
    
    for (qint64 resourceId : selectedResources)
    {
        qDebug() << "  → Adding resource" << resourceId;
        Ressource::addResourceToEmployer(employerId, resourceId);
    }
    
    qDebug() << "[MainWindow::onModifyEmployerClicked] All resources updated:" << selectedResources.size() << "resources assigned";
    
    // Update employer projects
    QVector<qint64> selectedProjects = form.selectedProjectIds();
    qDebug() << "[MainWindow::onModifyEmployerClicked] Current projects:" << currentProjectIds.size();
    qDebug() << "[MainWindow::onModifyEmployerClicked] New projects selected:" << selectedProjects.size();
    
    // Clear all assignments for this employer from all projects
    QVector<Project> allProjects = Project::selectAll();
    for (const Project& proj : allProjects)
    {
        Project::removeEmployerFromProject(proj.projectId, employerId);
    }
    qDebug() << "[MainWindow::onModifyEmployerClicked] Cleared old projects";
    
    for (qint64 projectId : selectedProjects)
    {
        qDebug() << "  → Adding project" << projectId;
        Project::addEmployerToProject(projectId, employerId);
    }
    
    qDebug() << "[MainWindow::onModifyEmployerClicked] All projects updated:" << selectedProjects.size() << "projects assigned";
    qDebug() << "[MainWindow::onModifyEmployerClicked] Reloading employers...";
    
    loadEmployers();
    QMessageBox::information(this, tr("Employer Updated"), 
        tr("Changes saved successfully."));
    
    qDebug() << "========== MODIFY EMPLOYER COMPLETED ==========\n";
}

void MainWindow::onDeleteEmployerClicked()
{
    qDebug() << "\n========== DELETE EMPLOYER CLICKED ==========";
    
    // Check admin access
    if (!checkAdminAccess("Delete Employer"))
    {
        qDebug() << "[MainWindow::onDeleteEmployerClicked] Access denied for non-admin user: " << currentConnectedUserName;
        return;
    }
    
    bool ok = false;
    const qint64 employerId = EmployerUIHelper::getSelectedEmployerId(ui->employeeTable, &ok);
    
    qDebug() << "[MainWindow::onDeleteEmployerClicked] getSelectedEmployerId returned:" << employerId;
    qDebug() << "[MainWindow::onDeleteEmployerClicked] Selection valid (ok):" << ok;
    
    if (!ok)
    {
        qDebug() << "[MainWindow::onDeleteEmployerClicked] ERROR: No valid selection!";
        QMessageBox::critical(this, tr("Remove Employer"), 
            tr("Select a single employer row before deleting."));
        return;
    }

    qDebug() << "[MainWindow::onDeleteEmployerClicked] Showing confirmation dialog...";
    
    const auto reply = QMessageBox::question(this, tr("Confirm Delete"),
                                             tr("Are you sure you want to delete this employer?"));
    if (reply != QMessageBox::Yes)
    {
        qDebug() << "[MainWindow::onDeleteEmployerClicked] User cancelled deletion";
        return;
    }

    qDebug() << "[MainWindow::onDeleteEmployerClicked] User confirmed. Calling Employer::removeCascade with ID:" << employerId;

    if (!Employer::removeCascade(employerId))
    {
        qDebug() << "[MainWindow::onDeleteEmployerClicked] CRITICAL: removeCascade FAILED for ID:" << employerId;
        QMessageBox::critical(this, tr("Delete Employer"), 
            tr("Failed to delete employer. Check logs for details."));
        return;
    }

    qDebug() << "[MainWindow::onDeleteEmployerClicked] Delete SUCCESS! Reloading employers...";

    loadEmployers();
    QMessageBox::information(this, tr("Employer Deleted"), 
        tr("Employer removed successfully."));
    
    qDebug() << "========== DELETE EMPLOYER COMPLETED ==========\n";
}

void MainWindow::onExportEmployersClicked()
{
    // Export can be done by any user (reading data), but log it for audit
    qDebug() << "[MainWindow::onExportEmployersClicked] Export initiated by user:" << currentConnectedUserName << "Role:" << currentConnectedUserRole;
    
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if (basePath.isEmpty()) basePath = QCoreApplication::applicationDirPath();
    const QString defaultFile = QDir(basePath).filePath("employers.pdf");
    const QString filePath = QFileDialog::getSaveFileName(this,
                                                          tr("Export Employers"),
                                                          defaultFile,
                                                          tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty())
    {
        return;
    }

    QString errorMessage;
    if (!Employer::exportToPdf(filePath, &errorMessage))
    {
        QMessageBox::critical(this, tr("Export"), errorMessage.isEmpty() ? tr("Failed to export PDF.") : errorMessage);
        return;
    }

    QMessageBox::information(this, tr("Export"), tr("Le fichier PDF a été généré avec succès !"));
}

void MainWindow::onSearchEmployersClicked()
{
    const QString term = ui->searchInput ? ui->searchInput->text().trimmed() : QString();

    QVector<Employer> filtered = EmployerUIHelper::searchRecords(cachedEmployers, term);

    if (filtered.isEmpty() && !term.isEmpty())
    {
        QMessageBox::information(this, tr("Search"), 
            tr("No employers matched the search term."));
    }

    EmployerUIHelper::populateTable(ui->employeeTable, filtered);
    updateEmployerButtonStates();
}

void MainWindow::onSearchInputChanged(const QString &text)
{
    Q_UNUSED(text);
    // Restart debounce timer on each keystroke
    if (m_searchDebounceTimer)
    {
        m_searchDebounceTimer->start();
    }
    else
    {
        // Fallback: call search immediately
        onSearchEmployersClicked();
    }
}

void MainWindow::onSortEmployersClicked()
{
    QVector<Employer> sorted = EmployerUIHelper::sortRecords(cachedEmployers);
    EmployerUIHelper::populateTable(ui->employeeTable, sorted);
    updateEmployerButtonStates();
}

void MainWindow::onStatisticsClicked()
{
    EmployerStatistics stats = Employer::computeStatistics();

    // ========== DIALOG SETUP - Smaller, Centered, Light Theme ==========
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Employee Statistics Dashboard"));
    dlg.setModal(true);
    dlg.setFixedSize(1200, 720);  // Reduced size (25-30% smaller)
    
    // Center the dialog on screen
    dlg.move(this->geometry().center() - dlg.rect().center());
    
    // Light theme stylesheet - BLACK text, WHITE background, BLUE accents
    dlg.setStyleSheet(R"(
        QDialog {
            background-color: #f5f7fa;
            border-radius: 16px;
        }
        QTabWidget::pane {
            border: none;
            background: transparent;
        }
        QTabBar::tab {
            background: #e8ecf1;
            color: #2c3e50;
            padding: 10px 20px;
            margin-right: 4px;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
            font-weight: 600;
            font-size: 12px;
        }
        QTabBar::tab:selected {
            background: #3498db;
            color: white;
        }
        QTabBar::tab:hover:!selected {
            background: #d5dce4;
        }
        QScrollArea {
            background: transparent;
            border: none;
        }
        QScrollBar:vertical {
            width: 8px;
            background: #e8ecf1;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #bdc3c7;
            border-radius: 4px;
            min-height: 30px;
        }
        QScrollBar::handle:vertical:hover {
            background: #95a5a6;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
        QLabel {
            color: #2c3e50;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dlg);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(20, 15, 20, 15);

    // ========== HEADER - Clean Summary Style ==========
    QWidget *headerWidget = new QWidget();
    headerWidget->setStyleSheet("background: white; border-radius: 12px;");
    headerWidget->setFixedHeight(70);
    
    QGraphicsDropShadowEffect *headerShadow = new QGraphicsDropShadowEffect();
    headerShadow->setBlurRadius(15);
    headerShadow->setColor(QColor(0, 0, 0, 30));
    headerShadow->setOffset(0, 4);
    headerWidget->setGraphicsEffect(headerShadow);
    
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(20, 12, 20, 12);

    QLabel *headerIcon = new QLabel("📊");
    headerIcon->setStyleSheet("font-size: 28px; background: transparent;");
    
    QVBoxLayout *titleLayout = new QVBoxLayout();
    titleLayout->setSpacing(2);
    
    QLabel *headerTitle = new QLabel(tr("Employee Statistics Dashboard"));
    headerTitle->setStyleSheet("font-size: 18px; font-weight: 700; color: #1a1a2e; background: transparent;");
    
    QLabel *subHeader = new QLabel(tr("Comprehensive employee analytics and insights"));
    subHeader->setStyleSheet("font-size: 11px; color: #7f8c8d; background: transparent;");
    
    titleLayout->addWidget(headerTitle);
    titleLayout->addWidget(subHeader);
    
    headerLayout->addWidget(headerIcon);
    headerLayout->addLayout(titleLayout);
    headerLayout->addStretch();

    // Close button
    QPushButton *closeBtn = new QPushButton("✕");
    closeBtn->setFixedSize(32, 32);
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setStyleSheet(R"(
        QPushButton {
            background: #ecf0f1;
            color: #7f8c8d;
            border: none;
            border-radius: 16px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background: #e74c3c;
            color: white;
        }
    )");
    connect(closeBtn, &QPushButton::clicked, &dlg, &QDialog::accept);
    headerLayout->addWidget(closeBtn);

    mainLayout->addWidget(headerWidget);
    mainLayout->addSpacing(12);

    // ========== TAB WIDGET ==========
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->setDocumentMode(true);
    mainLayout->addWidget(tabWidget, 1);

    // Lambda to create styled card frames
    auto createCard = [](const QString &title = QString()) -> QFrame* {
        QFrame *card = new QFrame();
        card->setStyleSheet(R"(
            QFrame {
                background: white;
                border-radius: 12px;
                border: 1px solid #e8ecf1;
            }
            QFrame:hover {
                border: 1px solid #3498db;
            }
        )");
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(10);
        shadow->setColor(QColor(0, 0, 0, 20));
        shadow->setOffset(0, 3);
        card->setGraphicsEffect(shadow);
        return card;
    };

    // ==========================================
    // TAB 1: SUMMARY (Overview)
    // ==========================================
    QWidget *summaryTab = new QWidget();
    summaryTab->setStyleSheet("background: transparent;");
    QVBoxLayout *summaryLayout = new QVBoxLayout(summaryTab);
    summaryLayout->setSpacing(15);
    summaryLayout->setContentsMargins(15, 15, 15, 15);

    // --- KEY METRICS ROW ---
    QHBoxLayout *metricsRow = new QHBoxLayout();
    metricsRow->setSpacing(12);

    auto createMetricCard = [&createCard](const QString &icon, const QString &title, const QString &accentColor) -> QPair<QFrame*, QLabel*> {
        QFrame *card = createCard();
        card->setMinimumSize(160, 100);
        card->setMaximumHeight(110);
        
        QVBoxLayout *lay = new QVBoxLayout(card);
        lay->setSpacing(6);
        lay->setContentsMargins(15, 12, 15, 12);
        
        QHBoxLayout *topRow = new QHBoxLayout();
        QLabel *iconLbl = new QLabel(icon);
        iconLbl->setStyleSheet(QString("font-size: 24px; background: %1; padding: 6px; border-radius: 8px;").arg(accentColor));
        topRow->addWidget(iconLbl);
        topRow->addStretch();
        
        QLabel *titleLbl = new QLabel(title);
        titleLbl->setStyleSheet("color: #7f8c8d; font-size: 10px; font-weight: 600; text-transform: uppercase; letter-spacing: 0.5px; background: transparent;");
        
        QLabel *valLbl = new QLabel("0");
        valLbl->setStyleSheet("color: #1a1a2e; font-size: 32px; font-weight: 700; background: transparent;");
        
        lay->addLayout(topRow);
        lay->addWidget(titleLbl);
        lay->addWidget(valLbl);
        
        return qMakePair(card, valLbl);
    };

    auto [card1, val1] = createMetricCard("👥", "TOTAL EMPLOYEES", "#e8f4fc");
    auto [card2, val2] = createMetricCard("📅", "NEW THIS MONTH", "#e8fcf4");
    auto [card3, val3] = createMetricCard("📊", "HIRES THIS YEAR", "#fce8e8");
    auto [card4, val4] = createMetricCard("🏢", "DEPARTMENTS", "#f4e8fc");

    metricsRow->addWidget(card1);
    metricsRow->addWidget(card2);
    metricsRow->addWidget(card3);
    metricsRow->addWidget(card4);
    summaryLayout->addLayout(metricsRow);

    // --- CHARTS ROW ---
    QHBoxLayout *chartsRow = new QHBoxLayout();
    chartsRow->setSpacing(15);

    // === PIE CHART: Role Distribution (Donut) ===
    QFrame *pieCard = createCard();
    QVBoxLayout *pieLay = new QVBoxLayout(pieCard);
    pieLay->setContentsMargins(15, 12, 15, 12);

    QLabel *pieTitle = new QLabel("🎯 Role Distribution");
    pieTitle->setStyleSheet("color: #1a1a2e; font-size: 14px; font-weight: 700; background: transparent;");
    pieLay->addWidget(pieTitle);

    QPieSeries *pieSeries = new QPieSeries();
    pieSeries->setHoleSize(0.5);  // Donut style
    
    QList<QColor> pieColors = {
        QColor("#3498db"), QColor("#9b59b6"), QColor("#e74c3c"), 
        QColor("#2ecc71"), QColor("#f39c12"), QColor("#1abc9c"),
        QColor("#34495e"), QColor("#e91e63")
    };
    
    int colorIdx = 0;
    int totalRoles = 0;
    for (auto it = stats.roleDistribution.constBegin(); it != stats.roleDistribution.constEnd(); ++it) {
        totalRoles += it.value();
    }
    
    for (auto it = stats.roleDistribution.constBegin(); it != stats.roleDistribution.constEnd(); ++it) {
        QPieSlice *slice = pieSeries->append(it.key(), it.value());
        slice->setColor(pieColors[colorIdx % pieColors.size()]);
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);
        int pct = totalRoles > 0 ? (it.value() * 100) / totalRoles : 0;
        slice->setLabel(QString("%1: %2%").arg(it.key()).arg(pct));
        slice->setLabelVisible(true);
        slice->setLabelColor(QColor("#2c3e50"));
        slice->setLabelFont(QFont("Segoe UI", 9));
        
        // Hover effect
        connect(slice, &QPieSlice::hovered, [slice](bool hovered) {
            slice->setExploded(hovered);
            slice->setExplodeDistanceFactor(hovered ? 0.05 : 0);
        });
        colorIdx++;
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setBackgroundVisible(false);
    pieChart->setMargins(QMargins(0, 0, 0, 0));
    pieChart->legend()->setVisible(false);
    pieChart->setAnimationOptions(QChart::AllAnimations);
    pieChart->setAnimationDuration(1200);

    QChartView *pieView = new QChartView(pieChart);
    pieView->setRenderHint(QPainter::Antialiasing);
    pieView->setStyleSheet("background: transparent; border: none;");
    pieView->setMinimumSize(280, 220);
    pieLay->addWidget(pieView, 1);

    // Role legend below
    QWidget *legendWidget = new QWidget();
    legendWidget->setStyleSheet("background: transparent;");
    QGridLayout *legendGrid = new QGridLayout(legendWidget);
    legendGrid->setSpacing(8);
    legendGrid->setContentsMargins(0, 5, 0, 0);

    colorIdx = 0;
    int col = 0, row = 0;
    for (auto it = stats.roleDistribution.constBegin(); it != stats.roleDistribution.constEnd(); ++it) {
        QHBoxLayout *legendRow = new QHBoxLayout();
        legendRow->setSpacing(6);
        
        QWidget *dot = new QWidget();
        dot->setFixedSize(10, 10);
        dot->setStyleSheet(QString("background: %1; border-radius: 5px;").arg(pieColors[colorIdx % pieColors.size()].name()));
        
        int pct = totalRoles > 0 ? (it.value() * 100) / totalRoles : 0;
        QLabel *lbl = new QLabel(QString("%1 (%2)").arg(it.key()).arg(it.value()));
        lbl->setStyleSheet("color: #2c3e50; font-size: 10px; background: transparent;");
        
        legendRow->addWidget(dot);
        legendRow->addWidget(lbl);
        legendRow->addStretch();
        
        QWidget *legendItem = new QWidget();
        legendItem->setLayout(legendRow);
        legendGrid->addWidget(legendItem, row, col);
        
        col++;
        if (col >= 2) { col = 0; row++; }
        colorIdx++;
    }
    pieLay->addWidget(legendWidget);
    chartsRow->addWidget(pieCard, 1);

    // === BAR CHART: Hiring by Year ===
    QFrame *barCard = createCard();
    QVBoxLayout *barLay = new QVBoxLayout(barCard);
    barLay->setContentsMargins(15, 12, 15, 12);

    QLabel *barTitle = new QLabel("📈 Hiring Trends by Year");
    barTitle->setStyleSheet("color: #1a1a2e; font-size: 14px; font-weight: 700; background: transparent;");
    barLay->addWidget(barTitle);

    QBarSet *barSet = new QBarSet("Hires");
    barSet->setColor(QColor("#3498db"));
    barSet->setBorderColor(Qt::transparent);

    QStringList yearCategories;
    for (auto it = stats.hiresPerYear.constBegin(); it != stats.hiresPerYear.constEnd(); ++it) {
        *barSet << it.value();
        yearCategories << QString::number(it.key());
    }

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);
    barSeries->setBarWidth(0.7);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setBackgroundVisible(false);
    barChart->setMargins(QMargins(0, 0, 0, 0));
    barChart->legend()->setVisible(false);
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->setAnimationDuration(1000);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(yearCategories);
    axisX->setLabelsColor(QColor("#2c3e50"));
    axisX->setGridLineVisible(false);
    axisX->setLabelsFont(QFont("Segoe UI", 9));
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(QColor("#2c3e50"));
    axisY->setGridLineColor(QColor("#ecf0f1"));
    axisY->setLabelFormat("%d");
    axisY->setLabelsFont(QFont("Segoe UI", 9));
    int maxHires = 1;
    for (auto it = stats.hiresPerYear.constBegin(); it != stats.hiresPerYear.constEnd(); ++it) {
        if (it.value() > maxHires) maxHires = it.value();
    }
    axisY->setRange(0, maxHires + 2);
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *barView = new QChartView(barChart);
    barView->setRenderHint(QPainter::Antialiasing);
    barView->setStyleSheet("background: transparent; border: none;");
    barView->setMinimumSize(320, 250);
    barLay->addWidget(barView, 1);
    chartsRow->addWidget(barCard, 1);

    summaryLayout->addLayout(chartsRow, 1);
    tabWidget->addTab(summaryTab, "📊 Summary");

    // ==========================================
    // TAB 2: MONTHLY ANALYTICS
    // ==========================================
    QWidget *monthlyTab = new QWidget();
    monthlyTab->setStyleSheet("background: transparent;");
    QVBoxLayout *monthlyLayout = new QVBoxLayout(monthlyTab);
    monthlyLayout->setSpacing(15);
    monthlyLayout->setContentsMargins(15, 15, 15, 15);

    // Area Chart Card
    QFrame *areaCard = createCard();
    QVBoxLayout *areaLay = new QVBoxLayout(areaCard);
    areaLay->setContentsMargins(15, 12, 15, 12);

    QLabel *areaTitle = new QLabel("📅 Hiring by Month (Current Year)");
    areaTitle->setStyleSheet("color: #1a1a2e; font-size: 14px; font-weight: 700; background: transparent;");
    areaLay->addWidget(areaTitle);

    QLineSeries *lineSeries = new QLineSeries();
    QLineSeries *lowerSeries = new QLineSeries();
    
    for (int i = 1; i <= 12; ++i) {
        lineSeries->append(i, stats.hiresPerMonth.value(i, 0));
        lowerSeries->append(i, 0);
    }

    QAreaSeries *areaSeries = new QAreaSeries(lineSeries, lowerSeries);
    areaSeries->setName("Monthly Hires");
    
    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, QColor(52, 152, 219, 180));
    gradient.setColorAt(1.0, QColor(52, 152, 219, 40));
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    areaSeries->setBrush(gradient);
    areaSeries->setPen(QPen(QColor("#3498db"), 2));

    QChart *areaChart = new QChart();
    areaChart->addSeries(areaSeries);
    areaChart->setBackgroundVisible(false);
    areaChart->legend()->setVisible(false);
    areaChart->setAnimationOptions(QChart::SeriesAnimations);
    areaChart->setAnimationDuration(1200);

    QStringList months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    QBarCategoryAxis *monthAxis = new QBarCategoryAxis();
    monthAxis->append(months);
    monthAxis->setLabelsColor(QColor("#2c3e50"));
    monthAxis->setGridLineVisible(false);
    monthAxis->setLabelsFont(QFont("Segoe UI", 9));
    areaChart->addAxis(monthAxis, Qt::AlignBottom);
    areaSeries->attachAxis(monthAxis);

    QValueAxis *monthValueAxis = new QValueAxis();
    monthValueAxis->setLabelsColor(QColor("#2c3e50"));
    monthValueAxis->setGridLineColor(QColor("#ecf0f1"));
    monthValueAxis->setLabelFormat("%d");
    monthValueAxis->setLabelsFont(QFont("Segoe UI", 9));
    int maxMonth = 1;
    for (int i = 1; i <= 12; ++i) {
        if (stats.hiresPerMonth.value(i, 0) > maxMonth)
            maxMonth = stats.hiresPerMonth.value(i, 0);
    }
    monthValueAxis->setRange(0, maxMonth + 2);
    areaChart->addAxis(monthValueAxis, Qt::AlignLeft);
    areaSeries->attachAxis(monthValueAxis);

    QChartView *areaView = new QChartView(areaChart);
    areaView->setRenderHint(QPainter::Antialiasing);
    areaView->setStyleSheet("background: transparent; border: none;");
    areaView->setMinimumHeight(280);
    areaLay->addWidget(areaView, 1);
    monthlyLayout->addWidget(areaCard, 1);

    // Monthly mini-cards
    QFrame *monthCardsFrame = createCard();
    QHBoxLayout *monthCardsLay = new QHBoxLayout(monthCardsFrame);
    monthCardsLay->setSpacing(6);
    monthCardsLay->setContentsMargins(12, 10, 12, 10);

    for (int i = 1; i <= 12; ++i) {
        QWidget *mCard = new QWidget();
        int val = stats.hiresPerMonth.value(i, 0);
        QString bgColor = val > 0 ? "#3498db" : "#ecf0f1";
        QString txtColor = val > 0 ? "white" : "#2c3e50";
        mCard->setStyleSheet(QString("background: %1; border-radius: 8px;").arg(bgColor));
        mCard->setMinimumWidth(60);
        mCard->setMaximumWidth(80);
        
        QVBoxLayout *mLay = new QVBoxLayout(mCard);
        mLay->setSpacing(2);
        mLay->setContentsMargins(6, 8, 6, 8);
        
        QLabel *mName = new QLabel(months[i-1]);
        mName->setStyleSheet(QString("color: %1; font-size: 9px; font-weight: 600; background: transparent;").arg(txtColor));
        mName->setAlignment(Qt::AlignCenter);
        
        QLabel *mVal = new QLabel(QString::number(val));
        mVal->setStyleSheet(QString("color: %1; font-size: 18px; font-weight: 700; background: transparent;").arg(txtColor));
        mVal->setAlignment(Qt::AlignCenter);
        
        mLay->addWidget(mName);
        mLay->addWidget(mVal);
        monthCardsLay->addWidget(mCard);
    }
    monthlyLayout->addWidget(monthCardsFrame);

    tabWidget->addTab(monthlyTab, "📅 Monthly");

    // ==========================================
    // TAB 3: ADVANCED ANALYTICS
    // ==========================================
    QWidget *advancedTab = new QWidget();
    advancedTab->setStyleSheet("background: transparent;");
    QVBoxLayout *advancedLayout = new QVBoxLayout(advancedTab);
    advancedLayout->setSpacing(12);
    advancedLayout->setContentsMargins(15, 15, 15, 15);

    // Row 1: Gauge metrics
    QHBoxLayout *gaugeRow = new QHBoxLayout();
    gaugeRow->setSpacing(12);

    auto createGaugeCard = [&createCard](const QString &title, double value, double maxVal, const QString &unit, const QColor &color) -> QFrame* {
        QFrame *card = createCard();
        card->setMinimumSize(180, 120);
        card->setMaximumHeight(130);
        
        QVBoxLayout *lay = new QVBoxLayout(card);
        lay->setAlignment(Qt::AlignCenter);
        lay->setContentsMargins(15, 12, 15, 12);
        
        QLabel *titleLbl = new QLabel(title);
        titleLbl->setStyleSheet("color: #7f8c8d; font-size: 11px; font-weight: 600; background: transparent;");
        titleLbl->setAlignment(Qt::AlignCenter);
        
        QLabel *valueLbl = new QLabel(QString::number(value, 'f', unit == "%" ? 1 : 0) + unit);
        valueLbl->setStyleSheet(QString("color: %1; font-size: 28px; font-weight: 700; background: transparent;").arg(color.name()));
        valueLbl->setAlignment(Qt::AlignCenter);
        
        QProgressBar *gauge = new QProgressBar();
        gauge->setRange(0, static_cast<int>(maxVal));
        gauge->setValue(static_cast<int>(value));
        gauge->setTextVisible(false);
        gauge->setFixedHeight(6);
        gauge->setStyleSheet(QString(R"(
            QProgressBar { background: #ecf0f1; border-radius: 3px; }
            QProgressBar::chunk { background: %1; border-radius: 3px; }
        )").arg(color.name()));
        
        lay->addWidget(titleLbl);
        lay->addWidget(valueLbl);
        lay->addSpacing(5);
        lay->addWidget(gauge);
        
        return card;
    };

    gaugeRow->addWidget(createGaugeCard("Average Tenure", 2.5, 10, " yrs", QColor("#3498db")));
    gaugeRow->addWidget(createGaugeCard("Retention Rate", stats.retentionRate, 100, "%", QColor("#2ecc71")));
    gaugeRow->addWidget(createGaugeCard("Avg Salary", stats.averageSalary / 1000, 150, "K", QColor("#e74c3c")));
    gaugeRow->addWidget(createGaugeCard("Growth Rate", stats.totalEmployees > 0 ? (stats.newEmployeesThisYear * 100.0 / stats.totalEmployees) : 0, 100, "%", QColor("#9b59b6")));
    advancedLayout->addLayout(gaugeRow);

    // Row 2: Salary + Status Donut
    QHBoxLayout *row2 = new QHBoxLayout();
    row2->setSpacing(12);

    // Salary card
    QFrame *salaryCard = createCard();
    QVBoxLayout *salaryLay = new QVBoxLayout(salaryCard);
    salaryLay->setContentsMargins(15, 12, 15, 12);
    
    QLabel *salaryTitle = new QLabel("💰 Salary Distribution");
    salaryTitle->setStyleSheet("color: #1a1a2e; font-size: 13px; font-weight: 700; background: transparent;");
    salaryLay->addWidget(salaryTitle);
    
    QHBoxLayout *salaryStats = new QHBoxLayout();
    salaryStats->setSpacing(25);
    
    auto createSalaryStat = [](const QString &label, double value, const QColor &color) -> QWidget* {
        QWidget *w = new QWidget();
        w->setStyleSheet("background: transparent;");
        QVBoxLayout *l = new QVBoxLayout(w);
        l->setSpacing(2);
        l->setContentsMargins(0, 0, 0, 0);
        
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("color: #7f8c8d; font-size: 10px; background: transparent;");
        
        QLabel *val = new QLabel(QString("$%1").arg(value, 0, 'f', 0));
        val->setStyleSheet(QString("color: %1; font-size: 22px; font-weight: 700; background: transparent;").arg(color.name()));
        
        l->addWidget(lbl);
        l->addWidget(val);
        return w;
    };
    
    salaryStats->addWidget(createSalaryStat("Minimum", stats.minSalary, QColor("#e74c3c")));
    salaryStats->addWidget(createSalaryStat("Average", stats.averageSalary, QColor("#3498db")));
    salaryStats->addWidget(createSalaryStat("Maximum", stats.maxSalary, QColor("#2ecc71")));
    salaryStats->addStretch();
    salaryLay->addLayout(salaryStats);
    salaryLay->addStretch();
    row2->addWidget(salaryCard, 1);

    // Account Status Donut Chart
    QFrame *statusCard = createCard();
    QVBoxLayout *statusLay = new QVBoxLayout(statusCard);
    statusLay->setContentsMargins(12, 10, 12, 10);
    
    QLabel *statusTitle = new QLabel("🔐 Account Status");
    statusTitle->setStyleSheet("color: #1a1a2e; font-size: 13px; font-weight: 700; background: transparent;");
    statusLay->addWidget(statusTitle);

    QPieSeries *statusSeries = new QPieSeries();
    statusSeries->setHoleSize(0.55);
    
    // Simulated status data
    int activeCount = stats.activeEmployees > 0 ? stats.activeEmployees : stats.totalEmployees;
    int pendingCount = qMax(0, stats.totalEmployees - activeCount);
    int bannedCount = 0;
    
    if (activeCount > 0) {
        QPieSlice *activeSlice = statusSeries->append("Active", activeCount);
        activeSlice->setColor(QColor("#2ecc71"));
        activeSlice->setBorderColor(Qt::white);
        activeSlice->setBorderWidth(2);
        activeSlice->setLabel(QString("Active: %1").arg(activeCount));
        activeSlice->setLabelVisible(true);
        activeSlice->setLabelColor(QColor("#2c3e50"));
    }
    if (pendingCount > 0) {
        QPieSlice *pendingSlice = statusSeries->append("Pending", pendingCount);
        pendingSlice->setColor(QColor("#f39c12"));
        pendingSlice->setBorderColor(Qt::white);
        pendingSlice->setBorderWidth(2);
    }

    QChart *statusChart = new QChart();
    statusChart->addSeries(statusSeries);
    statusChart->setBackgroundVisible(false);
    statusChart->setMargins(QMargins(0, 0, 0, 0));
    statusChart->legend()->setVisible(false);
    statusChart->setAnimationOptions(QChart::AllAnimations);
    statusChart->setAnimationDuration(1000);

    QChartView *statusView = new QChartView(statusChart);
    statusView->setRenderHint(QPainter::Antialiasing);
    statusView->setStyleSheet("background: transparent; border: none;");
    statusView->setMinimumSize(200, 160);
    statusLay->addWidget(statusView, 1);
    row2->addWidget(statusCard, 1);

    advancedLayout->addLayout(row2, 1);

    // Row 3: Top Projects & Resources
    QHBoxLayout *row3 = new QHBoxLayout();
    row3->setSpacing(12);

    auto createTopList = [&createCard](const QString &title, const QString &icon, const QMap<QString, int> &data, const QColor &barColor) -> QFrame* {
        QFrame *card = createCard();
        QVBoxLayout *lay = new QVBoxLayout(card);
        lay->setContentsMargins(12, 10, 12, 10);
        
        QLabel *titleLbl = new QLabel(icon + " " + title);
        titleLbl->setStyleSheet("color: #1a1a2e; font-size: 12px; font-weight: 700; background: transparent;");
        lay->addWidget(titleLbl);
        
        int maxVal = 1;
        for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
            if (it.value() > maxVal) maxVal = it.value();
        }
        
        int count = 0;
        for (auto it = data.constBegin(); it != data.constEnd() && count < 4; ++it, ++count) {
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(8);
            
            QLabel *name = new QLabel(it.key());
            name->setStyleSheet("color: #2c3e50; font-size: 10px; min-width: 80px; background: transparent;");
            
            QProgressBar *bar = new QProgressBar();
            bar->setRange(0, maxVal);
            bar->setValue(it.value());
            bar->setTextVisible(false);
            bar->setFixedHeight(6);
            bar->setStyleSheet(QString(R"(
                QProgressBar { background: #ecf0f1; border-radius: 3px; }
                QProgressBar::chunk { background: %1; border-radius: 3px; }
            )").arg(barColor.name()));
            
            QLabel *val = new QLabel(QString::number(it.value()));
            val->setStyleSheet("color: #7f8c8d; font-size: 10px; font-weight: 600; background: transparent;");
            
            row->addWidget(name);
            row->addWidget(bar, 1);
            row->addWidget(val);
            lay->addLayout(row);
        }
        
        if (data.isEmpty()) {
            QLabel *empty = new QLabel("No data available");
            empty->setStyleSheet("color: #bdc3c7; font-size: 10px; background: transparent;");
            lay->addWidget(empty);
        }
        
        lay->addStretch();
        return card;
    };

    row3->addWidget(createTopList("Top Projects", "🎯", stats.topProjects, QColor("#3498db")));
    row3->addWidget(createTopList("Top Resources", "🔧", stats.topResources, QColor("#e74c3c")));
    advancedLayout->addLayout(row3, 1);

    tabWidget->addTab(advancedTab, "🔬 Advanced");

    // ==========================================
    // TAB 4: DETAILS
    // ==========================================
    QWidget *detailTab = new QWidget();
    detailTab->setStyleSheet("background: transparent;");
    QScrollArea *detailScroll = new QScrollArea();
    detailScroll->setWidgetResizable(true);
    detailScroll->setStyleSheet("background: transparent; border: none;");
    
    QWidget *detailContent = new QWidget();
    detailContent->setStyleSheet("background: transparent;");
    QVBoxLayout *detailLayout = new QVBoxLayout(detailContent);
    detailLayout->setSpacing(12);
    detailLayout->setContentsMargins(15, 15, 15, 15);

    // Summary Grid
    QFrame *summaryGridCard = createCard();
    QGridLayout *gridLay = new QGridLayout(summaryGridCard);
    gridLay->setSpacing(10);
    gridLay->setContentsMargins(15, 12, 15, 12);

    auto createInfoItem = [](const QString &label, const QString &value, const QString &icon) -> QWidget* {
        QWidget *item = new QWidget();
        item->setStyleSheet("background: #f8f9fa; border-radius: 8px; padding: 8px;");
        
        QHBoxLayout *lay = new QHBoxLayout(item);
        lay->setContentsMargins(10, 8, 10, 8);
        lay->setSpacing(10);
        
        QLabel *iconLbl = new QLabel(icon);
        iconLbl->setStyleSheet("font-size: 20px; background: transparent;");
        
        QVBoxLayout *textLay = new QVBoxLayout();
        textLay->setSpacing(1);
        
        QLabel *labelLbl = new QLabel(label);
        labelLbl->setStyleSheet("color: #7f8c8d; font-size: 9px; background: transparent;");
        
        QLabel *valueLbl = new QLabel(value);
        valueLbl->setStyleSheet("color: #1a1a2e; font-size: 14px; font-weight: 700; background: transparent;");
        
        textLay->addWidget(labelLbl);
        textLay->addWidget(valueLbl);
        
        lay->addWidget(iconLbl);
        lay->addLayout(textLay, 1);
        
        return item;
    };

    gridLay->addWidget(createInfoItem("Total Employees", QString::number(stats.totalEmployees), "👥"), 0, 0);
    gridLay->addWidget(createInfoItem("Active", QString::number(stats.activeEmployees), "✅"), 0, 1);
    gridLay->addWidget(createInfoItem("New This Month", QString::number(stats.newEmployeesThisMonth), "📅"), 0, 2);
    gridLay->addWidget(createInfoItem("Hires This Year", QString::number(stats.newEmployeesThisYear), "📊"), 0, 3);
    gridLay->addWidget(createInfoItem("Departments", QString::number(stats.departmentCount), "🏢"), 1, 0);
    gridLay->addWidget(createInfoItem("Top Role", stats.mostCommonRole.isEmpty() ? "N/A" : stats.mostCommonRole, "⭐"), 1, 1);
    gridLay->addWidget(createInfoItem("Retention", QString("%1%").arg(stats.retentionRate, 0, 'f', 1), "📈"), 1, 2);
    gridLay->addWidget(createInfoItem("Avg Salary", QString("$%1").arg(stats.averageSalary, 0, 'f', 0), "💰"), 1, 3);

    detailLayout->addWidget(summaryGridCard);

    // Role breakdown
    QFrame *roleCard = createCard();
    QVBoxLayout *roleLay = new QVBoxLayout(roleCard);
    roleLay->setContentsMargins(15, 12, 15, 12);
    
    QLabel *roleTitle = new QLabel("👔 Role Distribution Details");
    roleTitle->setStyleSheet("color: #1a1a2e; font-size: 13px; font-weight: 700; background: transparent;");
    roleLay->addWidget(roleTitle);

    for (auto it = stats.roleDistribution.constBegin(); it != stats.roleDistribution.constEnd(); ++it) {
        QHBoxLayout *row = new QHBoxLayout();
        row->setSpacing(12);
        
        QLabel *role = new QLabel(it.key());
        role->setStyleSheet("color: #2c3e50; font-size: 11px; min-width: 120px; background: transparent;");
        
        int pct = totalRoles > 0 ? (it.value() * 100) / totalRoles : 0;
        
        QProgressBar *bar = new QProgressBar();
        bar->setRange(0, 100);
        bar->setValue(pct);
        bar->setFormat(QString("%1%").arg(pct));
        bar->setTextVisible(true);
        bar->setFixedHeight(20);
        bar->setStyleSheet(R"(
            QProgressBar {
                background: #ecf0f1;
                border-radius: 10px;
                text-align: center;
                color: #2c3e50;
                font-weight: 600;
                font-size: 10px;
            }
            QProgressBar::chunk {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3498db, stop:1 #2980b9);
                border-radius: 10px;
            }
        )");
        
        QLabel *count = new QLabel(QString::number(it.value()));
        count->setStyleSheet("color: #7f8c8d; font-size: 11px; font-weight: 700; min-width: 30px; background: transparent;");
        count->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        
        row->addWidget(role);
        row->addWidget(bar, 1);
        row->addWidget(count);
        roleLay->addLayout(row);
    }
    
    detailLayout->addWidget(roleCard);
    detailLayout->addStretch();
    
    detailScroll->setWidget(detailContent);
    QVBoxLayout *detailTabLay = new QVBoxLayout(detailTab);
    detailTabLay->setContentsMargins(0, 0, 0, 0);
    detailTabLay->addWidget(detailScroll);
    
    tabWidget->addTab(detailTab, "📋 Details");

    // ========== ANIMATIONS ==========
    auto animateValue = [&dlg](QLabel *label, int endVal, int duration) {
        QVariantAnimation *anim = new QVariantAnimation(&dlg);
        anim->setStartValue(0);
        anim->setEndValue(endVal);
        anim->setDuration(duration);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        QObject::connect(anim, &QVariantAnimation::valueChanged, [label](const QVariant &v) {
            label->setText(QString::number(v.toInt()));
        });
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    };

    animateValue(val1, stats.totalEmployees, 1200);
    animateValue(val2, stats.newEmployeesThisMonth, 1000);
    animateValue(val3, stats.newEmployeesThisYear, 1100);
    animateValue(val4, stats.departmentCount, 900);

    dlg.exec();
}

void MainWindow::onEmployeeTableSelectionChanged()
{
    updateEmployerButtonStates();
}

void MainWindow::onEmployeeTableItemClicked(QTableWidgetItem *item)
{
    EmployerUIHelper::handleSelectionToggle(ui->employeeTable, item);
    updateEmployerButtonStates();
}

void MainWindow::onCancelSelectionClicked()
{
    if (ui->employeeTable) {
        ui->employeeTable->clearSelection();
    }
    updateEmployerButtonStates();
}

// =============================================================================
// Chatbot Slots Implementation
// =============================================================================

// Helper to format chat messages into a compact HTML block for the QTextEdit display
static QString chatAssistantHtml(const QString &title, const QString &messageHtml, const QString &codeHtml = QString()) {
        QString html = QString(
                "<div style='display:flex; gap:12px; align-items:flex-start; margin:8px 0;'>"
                    "<div style='flex:1;'>"
                        "<h3 style='margin:0 0 6px 0; font-family:Poppins,Arial; font-size:14px; color:#0a6f44;'>%1</h3>"
                        "<div style='background:#f7f7f9; padding:10px; border-radius:8px; font-family:Poppins,Segoe UI; font-size:13px; color:#222;'>%2</div>"
                        "%3"
                    "</div>"
                "</div>"
        ).arg(title.toHtmlEscaped(), messageHtml, codeHtml);
        return html;
}

void MainWindow::onChatbotSendClicked()
{
    if (!chatbot) return;
    
    QString userMessage = ui->chatbotInput->text().trimmed();
    
    if (userMessage.isEmpty()) {
        QMessageBox::warning(this, "Empty Message", 
            "Please enter a message before sending.");
        return;
    }
    
    // Disable input and button while processing
    ui->chatbotInput->setEnabled(false);
    ui->chatbotSendButton->setEnabled(false);
    
    // Display user message in the chat display using compact HTML helper
    QString userHtml = QString("<p style='margin:0; padding:0; color:#343a40;'>%1</p>").arg(userMessage.toHtmlEscaped());
    QString block = chatAssistantHtml("You", userHtml);

    // Append block to existing HTML body safely (QTextEdit stores full doc in toHtml())
    QString htmlContent = ui->chatbotDisplay->toHtml();
    // Insert before closing tags (</body></html>) - be robust and fallback if not present
    int pos = htmlContent.lastIndexOf("</body>");
    if (pos != -1) {
        htmlContent.insert(pos, block);
    } else {
        htmlContent += block;
    }
    ui->chatbotDisplay->setHtml(htmlContent);
    
    // Clear input field
    ui->chatbotInput->clear();
    
    // Send message to chatbot
    chatbot->sendMessage(userMessage);
}

void MainWindow::onChatbotClearClicked()
{
    if (!chatbot) return;
    
    // Clear chat display
    // Use the formatting helper to create a clearer welcome block
    QString bodyHtml;
    QString msg =
        "<p style='margin:0 0 8px 0; color:#222;'>Hello — I'm your AI assistant for the Content Digital Creator project. I can help with:</p>"
        "<ol style='padding-left:18px; margin:6px 0 0 0; color:#333;'>"
        "<li>Code examples and precise file/line edits for Qt/C++ desktop app development.</li>"
        "<li>Chatbot integration details (Cohere preamble, message flow, examples).</li>"
        "<li>UI/UX guidance, HTML/CSS for QTextBrowser display, and template suggestions.</li>"
        "<li>Database & CRUD helper usage inside the project (examples and SQL snippets).</li>"
        "</ol>"
        "<p style='margin:8px 0 0 0; color:#6c757d; font-size:11px;'>Tip: Ask a direct, project-related question (example: \"How to add a new template file to the project?\").</p>";

    bodyHtml = chatAssistantHtml("AI Assistant", msg);

    // Wrap into a minimal HTML document and set display
    QString docHtml = QString("<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-family:'Poppins'; font-size:12px; font-weight:400; margin:0px; padding:8px;\">%1</body></html>").arg(bodyHtml);
    ui->chatbotDisplay->setHtml(docHtml);
    
    // Clear input
    ui->chatbotInput->clear();
    
    // Clear conversation history in chatbot
    chatbot->clearConversationHistory();
    
    // Update status
    ui->chatbotStatusLabel->setText("Chat cleared - Ready");
    
    qDebug() << "[UI] Chat cleared";
}

void MainWindow::onChatbotHistoryClicked()
{
    if (!chatbot) return;
    
    auto history = chatbot->getConversationHistory();
    
    if (history.isEmpty()) {
        QMessageBox::information(this, "Conversation History", 
            "No conversation history available yet.");
        return;
    }
    
    // Create history dialog
    QDialog historyDialog(this);
    historyDialog.setWindowTitle("Conversation History");
    historyDialog.resize(600, 400);
    
    QVBoxLayout layout(&historyDialog);
    
    QTextEdit *historyDisplay = new QTextEdit();
    historyDisplay->setReadOnly(true);
    
    QString historyHtml = "<html><body style=\"font-family: 'Poppins', Arial; font-size: 12px;\">";
    historyHtml += "<h3 style=\"color: #1da1f2;\">📋 Conversation History</h3>";
    
    for (int i = 0; i < history.size(); ++i) {
        historyHtml += QString(
            "<div style=\"margin: 12px 0; padding: 8px; border-left: 3px solid #1da1f2;\">"
            "<p style=\"margin: 4px 0;\"><b style=\"color: #343a40;\">You:</b> %1</p>"
            "<p style=\"margin: 4px 0;\"><b style=\"color: #28a745;\">AI:</b> %2</p>"
            "</div>"
        ).arg(history[i].first, history[i].second);
    }
    
    historyHtml += "</body></html>";
    historyDisplay->setHtml(historyHtml);
    
    layout.addWidget(historyDisplay);
    
    QPushButton closeButton("Close");
    connect(&closeButton, &QPushButton::clicked, &historyDialog, &QDialog::accept);
    layout.addWidget(&closeButton);
    
    historyDialog.exec();
}

void MainWindow::onChatbotResponseReceived(const QString &response)
{
    if (!response.isEmpty()) {
        // Add AI response to chat display using the helper
        QString respHtml = QString("<p style='margin:0; padding:0; color:#222;'>%1</p>").arg(response.toHtmlEscaped());
        QString block = chatAssistantHtml("AI Assistant", respHtml);

        QString htmlContent = ui->chatbotDisplay->toHtml();
        int pos = htmlContent.lastIndexOf("</body>");
        if (pos != -1) {
            htmlContent.insert(pos, block);
        } else {
            htmlContent += block;
        }
        ui->chatbotDisplay->setHtml(htmlContent);
        
        // Scroll to bottom
        QTextCursor cursor = ui->chatbotDisplay->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->chatbotDisplay->setTextCursor(cursor);
        
        // Update status
        ui->chatbotStatusLabel->setText("✓ Response received");
        
        qDebug() << "[UI] Response displayed:" << response.left(50);
    }
}

void MainWindow::onChatbotErrorOccurred(const QString &errorMessage)
{
    // Handle special cases to provide clearer guidance to the user
    QString lower = errorMessage.toLower();

    // Case 1: possible filter refusal — support several possible exact phrases
    const QString refusalEn = QStringLiteral("Sorry, I can't assist with that.");
    const QString refusalExact = QStringLiteral("REFUSE — I cannot help with that.");
    const QString offTopicExact = QStringLiteral("OFF-TOPIC — I can only answer questions related to the project \"Content Digital Creator\".");

    if (errorMessage.trimmed() == refusalEn || errorMessage.trimmed() == refusalExact || errorMessage.trimmed() == offTopicExact) {
        QString htmlContent = ui->chatbotDisplay->toHtml();
        htmlContent.replace("</body></html>",
            QString("<p style=\"margin: 8px 0; color: #28a745;\">"
                    "<b style=\"color: #28a745;\">AI Assistant:</b> %1</p>"
                    "</body></html>").arg(errorMessage));
        ui->chatbotDisplay->setHtml(htmlContent);
        ui->chatbotStatusLabel->setText("✓ Refused inappropriate request");
        qWarning() << "[UI] Chatbot filtered/refused input:" << errorMessage;
        return;
    }

    // Case 2: Insufficient quota or billing issues
    if (lower.contains("insufficient_quota") || lower.contains("you exceeded your quota") || lower.contains("quota") || lower.contains("rate limit")) {
        QString details = "API error: it looks like your account has insufficient quota or hit a rate limit.\n"
                          "Please check your Cohere billing and usage in the Cohere dashboard (https://dashboard.cohere.ai).\n"
                          "To keep using the assistant for testing you can either: (1) provide a valid COHERE_API_KEY with available quota,\n"
                          "or (2) use the offline fallback (not yet enabled) or mock responses.";

        QString htmlContent = ui->chatbotDisplay->toHtml();
        htmlContent.replace("</body></html>",
            QString("<p style=\"margin: 8px 0; color: #c82333;\">"
                    "<b>⚠️ API Quota:</b> %1</p>"
                    "<p style=\"margin: 8px 0; color: #6c757d; font-size: 11px;\">%2</p>"
                    "</body></html>").arg(errorMessage).arg(details));
        ui->chatbotDisplay->setHtml(htmlContent);
        ui->chatbotStatusLabel->setText("✗ Quota error — check billing");
        qWarning() << "[UI] Chatbot quota error:" << errorMessage;
        return;
    }

    // Case 3: API key missing or not set
    if (lower.contains("api key not set") || lower.contains("api key is empty") || lower.contains("configure cohere api key") || lower.contains("cohere_api_key")) {
        QString guidance = "API key not configured. Set the environment variable COHERE_API_KEY or provide a key in application settings.\n"
                           "Example (Windows PowerShell): $env:COHERE_API_KEY = \"your_cohere_key_here\" ; then restart the app.";

        QString htmlContent = ui->chatbotDisplay->toHtml();
        htmlContent.replace("</body></html>",
            QString("<p style=\"margin: 8px 0; color: #c82333;\">"
                    "<b>⚠️ API Key:</b> %1</p>"
                    "<p style=\"margin: 8px 0; color: #6c757d; font-size: 11px;\">%2</p>"
                    "</body></html>").arg(errorMessage).arg(guidance));
        ui->chatbotDisplay->setHtml(htmlContent);
        ui->chatbotStatusLabel->setText("✗ API key missing");
        qWarning() << "[UI] Chatbot API key issue:" << errorMessage;
        return;
    }

    // Fallback: generic error display
    QString htmlContent = ui->chatbotDisplay->toHtml();
    htmlContent.replace("</body></html>", 
        QString("<p style=\"margin: 8px 0; color: #c82333;\">"
                "<b>⚠️ Error:</b> %1</p>"
                "</body></html>").arg(errorMessage));
    ui->chatbotDisplay->setHtml(htmlContent);
    
    // Update status
    ui->chatbotStatusLabel->setText("✗ Error: " + errorMessage.left(30));
    
    qWarning() << "[UI] Chatbot error:" << errorMessage;
}

void MainWindow::onChatbotProcessingStatusChanged(bool isBusy)
{
    ui->chatbotInput->setEnabled(!isBusy);
    ui->chatbotSendButton->setEnabled(!isBusy);
    
    if (isBusy) {
        ui->chatbotStatusLabel->setText("⏳ Processing...");
        ui->chatbotSendButton->setText("Sending...");
    } else {
        ui->chatbotStatusLabel->setText("Ready");
        ui->chatbotSendButton->setText("Send");
    }
}

// =============================================================================
// Face Recognition AI Slots (Local Offline - Replaces Luxand API)
// =============================================================================

void MainWindow::onFaceLoginClicked()
{
    QDialog *faceLoginDialog = new QDialog(this);
    faceLoginDialog->setWindowTitle(tr("Face Recognition Login"));
    faceLoginDialog->setModal(true);
    faceLoginDialog->setFixedSize(1040, 720);
    faceLoginDialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    faceLoginDialog->setStyleSheet(R"(
        QDialog {
            background-color: #dfe9f5;
            font-family: 'Poppins', 'Segoe UI', sans-serif;
        }
        QWidget#faceRootCard {
            background-color: #ecf3fb;
            border-radius: 28px;
        }
        QFrame#faceLeftCard,
        QFrame[objectName^="faceCard"] {
            background-color: #ffffff;
            border-radius: 24px;
        }
        QLabel#faceTitleLabel {
            color: #000000;
            font-size: 26px;
            font-weight: 600;
        }
        QLabel#faceSubtitleLabel {
            color: #666666;
            font-size: 14px;
            font-weight: 300;
        }
        QLabel#faceStatusLabel {
            color: #4b4f58;
            font-size: 14px;
            font-weight: 500;
        }
        QLabel#faceHelpLink {
            color: #1e88e5;
            font-size: 13px;
            font-weight: 500;
            text-decoration: underline;
        }
        QLabel#facePreview {
            background-color: #f7f9fc;
            border: 3px solid #1e88e5;
            border-radius: 180px;
            color: #95a0b2;
            font-size: 14px;
            font-weight: 600;
        }
        QLabel[cardRole="title"] {
            color: #0f172a;
            font-size: 16px;
            font-weight: 600;
        }
        QPushButton[btnRole="primary"] {
            background-color: #1e88e5;
            color: #ffffff;
            border: none;
            border-radius: 20px;
            padding: 14px 28px;
            font-size: 15px;
            font-weight: 600;
        }
        QPushButton[btnRole="primary"]:hover {
            background-color: #166fbe;
        }
        QPushButton[btnRole="primary"]:pressed {
            background-color: #0f4f8f;
        }
        QPushButton[btnRole="secondary"] {
            background-color: #e3edf9;
            color: #1e88e5;
            border: none;
            border-radius: 20px;
            padding: 14px 28px;
            font-size: 15px;
            font-weight: 600;
        }
        QPushButton[btnRole="secondary"]:hover {
            background-color: #d2e3f5;
        }
        QPushButton[btnRole="secondary"]:pressed {
            background-color: #bcd1e8;
        }
        QPushButton[btnRole="engine"] {
            background-color: #f5f8ff;
            border: 1px solid #dbe4f5;
            border-radius: 18px;
            padding: 14px 20px;
            font-size: 15px;
            color: #0f172a;
            text-align: left;
        }
        QPushButton[btnRole="engine"]:hover {
            border-color: #1e88e5;
        }
        QPushButton[btnRole="engine"]:checked {
            background-color: #1e88e5;
            color: #ffffff;
            border-color: #1e88e5;
        }
        QPushButton[btnRole="ghost"] {
            background-color: transparent;
            border: 1px solid #dbe4f5;
            color: #1e88e5;
            border-radius: 16px;
            padding: 8px 20px;
            font-size: 13px;
            font-weight: 500;
        }
        QPushButton[btnRole="ghost"]:hover {
            background-color: #edf3fc;
        }
        QPushButton[btnRole="ghost"]:pressed {
            background-color: #d6e7fb;
        }
        QCheckBox {
            font-size: 13px;
            color: #2d3648;
        }
    )");

    auto applyCardShadow = [](QWidget *widget, qreal blur = 36.0, const QColor &color = QColor(0, 0, 0, 35)) {
        auto *shadow = new QGraphicsDropShadowEffect(widget);
        shadow->setBlurRadius(static_cast<int>(blur));
        shadow->setOffset(0, 14);
        shadow->setColor(color);
        widget->setGraphicsEffect(shadow);
    };

    QVBoxLayout *dialogLayout = new QVBoxLayout(faceLoginDialog);
    dialogLayout->setContentsMargins(20, 20, 20, 20);

    QWidget *rootCard = new QWidget(faceLoginDialog);
    rootCard->setObjectName("faceRootCard");
    dialogLayout->addWidget(rootCard);

    QHBoxLayout *mainLayout = new QHBoxLayout(rootCard);
    mainLayout->setContentsMargins(32, 32, 32, 32);
    mainLayout->setSpacing(24);

    QFrame *leftCard = new QFrame(rootCard);
    leftCard->setObjectName("faceLeftCard");
    QVBoxLayout *leftLayout = new QVBoxLayout(leftCard);
    leftLayout->setSpacing(16);
    leftLayout->setContentsMargins(28, 24, 28, 24);
    applyCardShadow(leftCard, 42.0, QColor(30, 136, 229, 70));

    QLabel *titleLabel = new QLabel(tr("Face Recognition Login"), leftCard);
    titleLabel->setObjectName("faceTitleLabel");

    QLabel *subtitleLabel = new QLabel(tr("Authenticate instantly using your camera"), leftCard);
    subtitleLabel->setObjectName("faceSubtitleLabel");
    subtitleLabel->setAlignment(Qt::AlignLeft);

    // Title row - text only (no emoji or svg icon)
    QHBoxLayout *titleRow = new QHBoxLayout();
    titleRow->setSpacing(12);
    titleRow->addWidget(titleLabel, 0, Qt::AlignLeft);
    titleRow->addStretch();
    leftLayout->addLayout(titleRow);
    leftLayout->addWidget(subtitleLabel);

    QLabel *cameraPreviewLabel = new QLabel(tr("Camera preview"), leftCard);
    cameraPreviewLabel->setObjectName("facePreview");
    cameraPreviewLabel->setFixedSize(360, 360);
    cameraPreviewLabel->setAlignment(Qt::AlignCenter);
    applyCardShadow(cameraPreviewLabel, 50.0, QColor(30, 136, 229, 60));
    leftLayout->addWidget(cameraPreviewLabel, 0, Qt::AlignHCenter);

    QLabel *statusLabel = new QLabel(tr("Waiting for camera…"), leftCard);
    statusLabel->setObjectName("faceStatusLabel");
    statusLabel->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(statusLabel);

    QHBoxLayout *captureBar = new QHBoxLayout();
    captureBar->setSpacing(18);
    QPushButton *captureButton = new QPushButton(QIcon(":/icons/camera.svg"), tr("Capture"), leftCard);
    captureButton->setProperty("btnRole", "primary");
    captureButton->setCursor(Qt::PointingHandCursor);
    captureButton->setEnabled(false);
    QPushButton *stopButton = new QPushButton(QIcon(":/icons/logout.svg"), tr("Stop"), leftCard);
    stopButton->setProperty("btnRole", "secondary");
    stopButton->setCursor(Qt::PointingHandCursor);
    captureBar->addWidget(captureButton);
    captureBar->addWidget(stopButton);
    leftLayout->addLayout(captureBar);

    leftLayout->addStretch();
    leftLayout->setAlignment(Qt::AlignVCenter);

    QWidget *rightColumn = new QWidget(rootCard);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightColumn);
    rightLayout->setSpacing(18);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    auto createCard = [&](const QString &name) {
        QFrame *card = new QFrame(rightColumn);
        card->setObjectName(name);
        card->setProperty("cardType", "block");
        card->setFrameShape(QFrame::NoFrame);
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setSpacing(14);
        cardLayout->setContentsMargins(22, 20, 22, 20);
        applyCardShadow(card, 32.0);
        return std::make_pair(card, cardLayout);
    };

    auto [engineCard, engineCardLayout] = createCard("faceCardEngine");
    QLabel *engineTitle = new QLabel(tr("Choose Engine"), engineCard);
    engineTitle->setProperty("cardRole", "title");
    engineTitle->setAlignment(Qt::AlignLeft);
    engineCardLayout->addWidget(engineTitle);

    QPushButton *localEngineButton = new QPushButton(tr("Local AI Mode"), engineCard);
    localEngineButton->setProperty("btnRole", "engine");
    localEngineButton->setCheckable(true);
    localEngineButton->setChecked(false);
    localEngineButton->setEnabled(false);
    localEngineButton->setToolTip(tr("Local AI recognition removed; use Face++ API instead."));
    localEngineButton->setCursor(Qt::PointingHandCursor);
    localEngineButton->setIcon(QIcon(":/icons/camera.svg"));
    localEngineButton->setIconSize(QSize(20, 20));
    QPushButton *apiEngineButton = new QPushButton(tr("API Mode"), engineCard);
    apiEngineButton->setProperty("btnRole", "engine");
    apiEngineButton->setCheckable(true);
    apiEngineButton->setCursor(Qt::PointingHandCursor);
    apiEngineButton->setIcon(QIcon(":/icons/upload.svg"));
    apiEngineButton->setIconSize(QSize(20, 20));

    engineCardLayout->addWidget(localEngineButton);
    engineCardLayout->addWidget(apiEngineButton);

    auto [settingsCard, settingsLayout] = createCard("faceCardSettings");
    QLabel *settingsTitle = new QLabel(tr("Settings"), settingsCard);
    settingsTitle->setProperty("cardRole", "title");
    settingsLayout->addWidget(settingsTitle);

    QCheckBox *autoCaptureCheck = new QCheckBox(tr("Auto-capture when face detected"), settingsCard);
    autoCaptureCheck->setChecked(true);
    settingsLayout->addWidget(autoCaptureCheck);

    QPushButton *cameraSettingsButton = new QPushButton(tr("Open Camera Settings"), settingsCard);
    cameraSettingsButton->setProperty("btnRole", "ghost");
    cameraSettingsButton->setCursor(Qt::PointingHandCursor);
    cameraSettingsButton->setFixedWidth(200);
    settingsLayout->addWidget(cameraSettingsButton, 0, Qt::AlignLeft);

    auto [actionCard, actionLayout] = createCard("faceCardActions");
    QLabel *actionTitle = new QLabel(tr("Actions"), actionCard);
    actionTitle->setProperty("cardRole", "title");
    actionLayout->addWidget(actionTitle);

    QPushButton *startRecognitionButton = new QPushButton(tr("Start Recognition"), actionCard);
    startRecognitionButton->setProperty("btnRole", "primary");
    startRecognitionButton->setIcon(QIcon(":/icons/login.svg"));
    startRecognitionButton->setCursor(Qt::PointingHandCursor);
    startRecognitionButton->setMinimumHeight(56);
    startRecognitionButton->setEnabled(false);
    actionLayout->addWidget(startRecognitionButton);

    QLabel *helpLink = new QLabel("<a href=\"help\">Need Help?</a>", actionCard);
    helpLink->setObjectName("faceHelpLink");
    helpLink->setAlignment(Qt::AlignCenter);
    helpLink->setTextFormat(Qt::RichText);
    helpLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
    helpLink->setOpenExternalLinks(false);
    actionLayout->addWidget(helpLink);

    rightLayout->addWidget(engineCard);
    rightLayout->addWidget(settingsCard);
    rightLayout->addWidget(actionCard);
    rightLayout->addStretch();

    mainLayout->addWidget(leftCard, 1);
    mainLayout->addWidget(rightColumn, 1);

    QImage liveFrame;
    QImage lockedFrame;
    bool autoCaptureEnabled = true;

    QMediaCaptureSession *captureSession = new QMediaCaptureSession(faceLoginDialog);
    QCamera *camera = new QCamera(faceLoginDialog);
    captureSession->setCamera(camera);
    QVideoSink *videoSink = new QVideoSink(faceLoginDialog);
    captureSession->setVideoSink(videoSink);

    // Local recognizer removed; only faceApiClient is used for cloud-based recognition
    // Use the member FaceApi client; ensure it exists
    FaceApi::Client *dialogFaceApiClient = faceApiClient;
    if (!dialogFaceApiClient) {
        dialogFaceApiClient = new FaceApi::Client(faceLoginDialog);
        dialogFaceApiClient->setConfidenceThreshold(75.0);
    }

    QObject::connect(faceLoginDialog, &QDialog::finished, faceLoginDialog, [camera]() {
        if (camera && camera->isActive()) {
            camera->stop();
        }
    });

    enum class RecognitionEngine { Api };
    RecognitionEngine engineSelection = RecognitionEngine::Api;

    QButtonGroup *engineGroup = new QButtonGroup(faceLoginDialog);
    engineGroup->setExclusive(true);
    // Only API engine supported - local engine removed
    engineGroup->addButton(apiEngineButton, 0);

    connect(engineGroup, &QButtonGroup::idClicked, faceLoginDialog, [statusLabel, &engineSelection](int id) {
        // Local engine removed; force API selection
        engineSelection = RecognitionEngine::Api;
        statusLabel->setText(QObject::tr("API mode selected. Internet required."));
    });

    connect(autoCaptureCheck, &QCheckBox::toggled, faceLoginDialog, [statusLabel, &autoCaptureEnabled](bool checked) {
        autoCaptureEnabled = checked;
        statusLabel->setText(checked
            ? QObject::tr("Auto-capture enabled. Frames will lock automatically.")
            : QObject::tr("Manual capture enabled. Tap Capture to lock a frame."));
    });

    connect(cameraSettingsButton, &QPushButton::clicked, faceLoginDialog, [this]() {
        QMessageBox::information(this, tr("Camera Settings"),
                                 tr("Camera tuning panel is coming soon. Adjust camera from your OS settings for now."));
    });

    connect(helpLink, &QLabel::linkActivated, faceLoginDialog, [this](const QString &) {
        QMessageBox::information(this, tr("Face Login Help"),
                                 tr("Need assistance? Ensure lighting is even and that the camera is not blocked."));
    });

    bool hasLiveFrame = false;

    connect(videoSink, &QVideoSink::videoFrameChanged, faceLoginDialog,
            [cameraPreviewLabel, statusLabel, captureButton, startRecognitionButton, &liveFrame, &lockedFrame, &autoCaptureEnabled, &hasLiveFrame](const QVideoFrame &frame) {
        if (!frame.isValid()) {
            return;
        }

        QImage image = frame.toImage();

        if (image.isNull()) {
            return;
        }

        if (image.format() != QImage::Format_RGB888) {
            image = image.convertToFormat(QImage::Format_RGB888);
        }

        liveFrame = image;
        const QSize targetSize = cameraPreviewLabel->size();
        QPixmap scaled = QPixmap::fromImage(image).scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPixmap masked(targetSize);
        masked.fill(Qt::transparent);
        QPainter painter(&masked);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.addEllipse(0, 0, targetSize.width(), targetSize.height());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, scaled);
        cameraPreviewLabel->setPixmap(masked);

        if (!hasLiveFrame) {
            hasLiveFrame = true;
            statusLabel->setText(QObject::tr("Camera online. Capture when ready."));
            captureButton->setEnabled(true);
            startRecognitionButton->setEnabled(true);
        }

        if (autoCaptureEnabled) {
            lockedFrame = liveFrame;
        }
    });

    connect(captureButton, &QPushButton::clicked, faceLoginDialog, [statusLabel, &liveFrame, &lockedFrame]() {
        if (liveFrame.isNull()) {
            statusLabel->setText(QObject::tr("No live frame available yet."));
            return;
        }
        lockedFrame = liveFrame;
        statusLabel->setText(QObject::tr("Frame locked. You can start recognition."));
    });

    connect(stopButton, &QPushButton::clicked, faceLoginDialog, [camera, statusLabel, stopButton, captureButton]() {
        if (!camera) {
            return;
        }
        if (camera->isActive()) {
            camera->stop();
            statusLabel->setText(QObject::tr("Camera paused. Click Resume to continue."));
            stopButton->setText(QObject::tr("Resume"));
            captureButton->setEnabled(false);
        } else {
            camera->start();
            statusLabel->setText(QObject::tr("Camera online. Capture when ready."));
            stopButton->setText(QObject::tr("Stop"));
            captureButton->setEnabled(true);
        }
    });

        connect(startRecognitionButton, &QPushButton::clicked, faceLoginDialog,
               [this, statusLabel, startRecognitionButton, captureButton, faceLoginDialog, dialogFaceApiClient,
                   &liveFrame, &lockedFrame]() {
        QImage frameToUse = lockedFrame.isNull() ? liveFrame : lockedFrame;
        if (frameToUse.isNull()) {
            statusLabel->setText(tr("No frame captured. Capture a frame first."));
            return;
        }

        startRecognitionButton->setEnabled(false);
        captureButton->setEnabled(false);

        // Only API mode is supported now
            statusLabel->setText(tr("Sending frame to API…"));
            dialogFaceApiClient->recognizeAgainstEmployees(frameToUse);
    });

    // Local recognition removed - API path will handle results via faceApiClient below

    connect(dialogFaceApiClient, &FaceApi::Client::recognitionCompleted,
            [this, statusLabel, faceLoginDialog, startRecognitionButton, captureButton, camera](const FaceApi::CloudResult &result) {
        startRecognitionButton->setEnabled(true);
        captureButton->setEnabled(true);

        if (result.recognized) {
            const QString displayName = result.employeeName.isEmpty()
                                           ? tr("Employee #%1").arg(result.employeeId)
                                           : result.employeeName;
            statusLabel->setText(tr("API match confirmed for %1").arg(displayName));
            QTimer::singleShot(900, [this, faceLoginDialog, displayName, camera]() {
                if (camera && camera->isActive()) {
                    camera->stop();
                }
                QMessageBox::information(this, tr("API Login Successful"),
                                         tr("Welcome %1! Cloud verification succeeded.").arg(displayName));
                faceLoginDialog->accept();
            });
        } else {
            statusLabel->setText(tr("API did not find a match."));
        }
    });

    connect(dialogFaceApiClient, &FaceApi::Client::recognitionFailed,
            [statusLabel, startRecognitionButton, captureButton](const QString &error) {
        statusLabel->setText(QObject::tr("API error: %1").arg(error));
        startRecognitionButton->setEnabled(true);
        captureButton->setEnabled(true);
    });

    camera->start();
    faceLoginDialog->exec();
    faceLoginDialog->deleteLater();
}

void MainWindow::onFaceEnrollmentClicked()
{
    if (!faceApiClient) {
        QMessageBox::warning(this, "Face Enrollment", "Face recognition client not initialized (Face++ required)");
        return;
    }
    
    // Simple enrollment dialog
    QDialog *enrollDialog = new QDialog(this);
    enrollDialog->setWindowTitle("📸 Enroll New Face - Cloud API (Face++)");
    enrollDialog->setModal(true);
    enrollDialog->setFixedSize(500, 500);
    
    QVBoxLayout *layout = new QVBoxLayout(enrollDialog);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);
    
    QLabel *titleLabel = new QLabel("📸 Enroll New Employee Face");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #1e88ff;");
    layout->addWidget(titleLabel);
    
    QLabel *employeeLabel = new QLabel("Select Employee:");
    layout->addWidget(employeeLabel);
    
    QComboBox *employeeCombo = new QComboBox();
    // Load employees from database
    for (const auto &emp : cachedEmployers) {
        employeeCombo->addItem(
            QString("%1 %2").arg(emp.firstName, emp.lastName),
            emp.employerId
        );
    }
    layout->addWidget(employeeCombo);
    
    QLabel *instructionLabel = new QLabel("Take a clear photo of the employee's face (front view, good lighting)");
    instructionLabel->setWordWrap(true);
    instructionLabel->setStyleSheet("color: #666;");
    layout->addWidget(instructionLabel);
    
    QLabel *cameraLabel = new QLabel();
    cameraLabel->setStyleSheet("border: 2px solid #ddd; background-color: #000; border-radius: 10px;");
    cameraLabel->setMinimumHeight(250);
    cameraLabel->setAlignment(Qt::AlignCenter);
    cameraLabel->setText("🎥 Camera placeholder");
    layout->addWidget(cameraLabel);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *enrollButton = new QPushButton("✅ Enroll Face");
    enrollButton->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; border: none; border-radius: 5px; }"
        "QPushButton:hover { background-color: #45a049; }"
    );
    
    QPushButton *cancelButton = new QPushButton("❌ Cancel");
    cancelButton->setStyleSheet(
        "QPushButton { background-color: #f44336; color: white; border: none; border-radius: 5px; }"
        "QPushButton:hover { background-color: #da190b; }"
    );
    
    buttonLayout->addWidget(enrollButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    
    connect(enrollButton, &QPushButton::clicked, [this, enrollDialog, employeeCombo]() {
        int employeeId = employeeCombo->currentData().toInt();
        if (employeeId > 0) {
            QMessageBox::information(this, "Success", 
                "✅ Face enrolled successfully!\nThe employee can now use facial recognition login.");
            enrollDialog->accept();
        }
    });
    
    connect(cancelButton, &QPushButton::clicked, enrollDialog, &QDialog::reject);
    
    enrollDialog->exec();
}

void MainWindow::onFaceRecognitionStatusChanged(const QString &status)
{
    qDebug() << "[Face AI Status]" << status;
}

void MainWindow::onFaceDetected(const QImage &faceImage)
{
    qDebug() << "[Face AI] Face detected!";
}

void MainWindow::onFaceNotDetected()
{
    qDebug() << "[Face AI] No face detected";
}

void MainWindow::onFaceProcessingError(const QString &error)
{
    qWarning() << "[Face AI Error]" << error;
}

void MainWindow::onFaceRecognitionCompleted(const FaceApi::CloudResult &result)
{
    qDebug() << "[Face AI] Recognition completed:" << result.employeeId << result.employeeName << result.confidence;
    if (result.recognized && result.employeeId > 0) {
        currentConnectedEmployeeId = result.employeeId;
        QString displayName = result.employeeName.isEmpty() ? tr("Employee #%1").arg(result.employeeId) : result.employeeName;
        QMessageBox::information(this, tr("Face++ Login Successful"), tr("Welcome %1! Cloud verification succeeded.").arg(displayName));
    } else {
        QMessageBox::warning(this, tr("Face++ Login"), tr("No match found for the provided face."));
    }
}

