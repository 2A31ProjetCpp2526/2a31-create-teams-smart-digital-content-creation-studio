#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_login.h"
#include "ui_Profile.h"
#include "ui_employerform.h"

#include "ui/clientwidget.h"
#include "ui/projectwidget.h"
#include "ui/ressourcewidget.h"
#include "ui/sponsorwidget.h"
#include "ui/templatewidget.h"

#include "backend/connection.h"
#include "backend/employer.h"
#include "backend/ressource.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QCoreApplication>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QResizeEvent>
#include <QSize>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QEasingCurve>
#include <QTextStream>
#include <QFile>
#include <QDate>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <algorithm>

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

// CSV formatting helpers
QString formatDate(const QDate &date)
{
    return date.isValid() ? date.toString(QStringLiteral("yyyy-MM-dd")) : QString();
}

QString escapeCsv(const QString &value)
{
    QString copy = value;
    copy.replace('"', "\"\"");
    return QStringLiteral("\"%1\"").arg(copy);
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
    
    // Load assigned resources if editing
    if (m_mode == EditMode && m_employerId > 0)
    {
        loadEmployerResources(m_employerId);
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
    if (m_employerId > 0)
    {
        loadEmployerResources(m_employerId);
    }
}

void EmployerForm::onAddResourceClicked()
{
    qDebug() << "Add resource clicked";
    
    // Get currently assigned resource IDs
    QVector<qint64> currentResourceIds;
    if (m_employerId > 0)
    {
        QVector<Ressource> currentResources = Ressource::getResourcesByEmployer(m_employerId);
        for (const Ressource &res : currentResources)
        {
            currentResourceIds.append(res.idMedia);
        }
    }
    
    // Show resource selection dialog
    ResourceSelectionDialog dialog(this);
    dialog.setAssignedResources(currentResourceIds);
    
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }
    
    QVector<qint64> selectedResourceIds = dialog.selectedResourceIds();
    
    // Only update if employer already exists in database
    if (m_employerId > 0)
    {
        // Clear current resources and add new ones
        Ressource::clearEmployerResources(m_employerId);
        
        for (qint64 resourceId : selectedResourceIds)
        {
            Ressource::addResourceToEmployer(m_employerId, resourceId);
        }
        
        QMessageBox::information(this, tr("Success"),
                               tr("Resources assigned successfully."));
        refreshResourceList();
    }
    else
    {
        // For new employers, just show info
        QMessageBox::information(this, tr("Info"),
                               tr("Save the employer first, then you can assign resources."));
    }
}

void EmployerForm::onRemoveResourceClicked()
{
    qDebug() << "Remove resource clicked";
    QListWidgetItem *item = ui->resourceListWidget->currentItem();
    if (!item)
    {
        QMessageBox::warning(this, tr("Remove Resource"),
                           tr("Please select a resource to remove."));
        return;
    }

    if (m_employerId <= 0)
    {
        return;
    }

    // Find the resource by title and remove it
    QVector<Ressource> resources = Ressource::getResourcesByEmployer(m_employerId);
    for (const Ressource &res : resources)
    {
        if (res.title == item->text())
        {
            if (Ressource::removeResourceFromEmployer(m_employerId, res.idMedia))
            {
                QMessageBox::information(this, tr("Success"),
                                       tr("Resource removed successfully."));
                refreshResourceList();
            }
            else
            {
                QMessageBox::critical(this, tr("Error"),
                                    tr("Failed to remove resource."));
            }
            return;
        }
    }
}

// =============================================================================
// ResourceSelectionDialog Implementation
// =============================================================================

ResourceSelectionDialog::ResourceSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    loadAllResources();
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
    for (const Ressource &res : allResources)
    {
        QListWidgetItem *item = new QListWidgetItem(res.title);
        item->setData(Qt::UserRole, res.idMedia);
        
        // Pre-select already assigned resources
        if (m_assignedResourceIds.contains(res.idMedia))
        {
            item->setSelected(true);
        }
        
        resourceListWidget->addItem(item);
    }
}

void ResourceSelectionDialog::setAssignedResources(const QVector<qint64>& resourceIds)
{
    m_assignedResourceIds = resourceIds;
}

QVector<qint64> ResourceSelectionDialog::selectedResourceIds() const
{
    QVector<qint64> selected;
    for (int i = 0; i < resourceListWidget->count(); ++i)
    {
        QListWidgetItem *item = resourceListWidget->item(i);
        if (item && item->isSelected())
        {
            selected.append(item->data(Qt::UserRole).toLongLong());
        }
    }
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
                avatarItem->setIcon(QIcon(pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            }
        }
        avatarItem->setToolTip(rec.avatarPath);
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
        auto *resourcesItem = new QTableWidgetItem(resourceNames);
        resourcesItem->setToolTip(resourceNames);  // Show full list in tooltip
        table->setItem(row, 8, resourcesItem);

        table->setRowHeight(row, 140);
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

    int row = table->currentRow();
    qDebug() << "[EmployerUIHelper::getSelectedEmployerId] currentRow():" << row;
    
    if (row < 0)
    {
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] No currentRow, searching for selected symbol...";
        for (int r = 0; r < table->rowCount(); ++r)
        {
            const QTableWidgetItem *item = table->item(r, 0);
            if (item && item->text() == QString::fromUtf8(kSelectSymbol))
            {
                qDebug() << "[EmployerUIHelper::getSelectedEmployerId] Found selected symbol at row" << r;
                row = r;
                break;
            }
        }
    }

    if (row < 0)
    {
        qDebug() << "[EmployerUIHelper::getSelectedEmployerId] ERROR: No row selected!";
        if (ok) *ok = false;
        return -1;
    }

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
            item->setText(alreadySelected ? QString::fromUtf8(kUnselectSymbol)
                                          : QString::fromUtf8(kSelectSymbol));
            table->selectRow(row);
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
        const QString composite = QStringLiteral("%1 %2 %3").arg(record.firstName, record.lastName, record.email);
        if (composite.contains(searchTerm, Qt::CaseInsensitive))
        {
            filtered.push_back(record);
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

bool EmployerUIHelper::exportToCsv(const QString &filePath, const QVector<Employer> &records, QString *errorMessage)
{
    if (records.isEmpty())
    {
        if (errorMessage) *errorMessage = QObject::tr("No employer data available for export.");
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        if (errorMessage) *errorMessage = QObject::tr("Cannot open file for writing.");
        return false;
    }

    QTextStream stream(&file);
    stream << "EMPLOYER_ID,FIRST_NAME,LAST_NAME,EMAIL,PHONE,ROLE,START_DATE,AVATAR_PATH" << '\n';
    
    for (const auto &rec : records)
    {
        stream << rec.employerId << ','
               << escapeCsv(rec.firstName) << ','
               << escapeCsv(rec.lastName) << ','
               << escapeCsv(rec.email) << ','
               << escapeCsv(rec.phone) << ','
               << escapeCsv(rec.role) << ','
               << escapeCsv(formatDate(rec.startDate)) << ','
               << escapeCsv(rec.avatarPath)
               << '\n';
    }

    return true;
}

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
    , ressourceWidget(nullptr)
    , projectWidget(nullptr)
    , loginPageWidget(nullptr)
    , authStackedWidget(nullptr)
    , loginUI(nullptr)
    , pageTransitionAnimation(nullptr)
    , animationGroup(nullptr)
    , loginFormTransitionAnimation(nullptr)
    , currentPageIndex(-1)
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
    setupAnimations();
    setupDashboardAnimations();

    addButtonHoverEffect(ui->employerBtn);
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
    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchEmployersClicked);
    connect(ui->searchInput, &QLineEdit::returnPressed, this, &MainWindow::onSearchEmployersClicked);
    connect(ui->sortBtn, &QPushButton::clicked, this, &MainWindow::onSortEmployersClicked);
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
    // Find which stacked widget page contains the sponsor widget
    int sponsorPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == sponsorWidget) {
            sponsorPageIndex = i;
            break;
        }
    }
    
    if (sponsorPageIndex != -1) {
        switchToPage(sponsorPageIndex); // Switch to the sponsor page
    }
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
        connect(faceLoginButton, &QPushButton::clicked, this, [this]() {
            QMessageBox::information(this, "Face Login", "Face login coming soon!\n\nThis feature will use advanced facial recognition technology for secure authentication.");
        });
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

// Form validation methods
void MainWindow::validateAndLogin()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("loginEmailLineEdit");
    QLineEdit* passwordField = loginPageWidget->findChild<QLineEdit*>("loginPasswordLineEdit");
    
    if (!emailField || !passwordField) return;
    
    QString email = emailField->text().trimmed();
    QString password = passwordField->text();
    
    bool hasErrors = false;
    
    // Validate email
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        showValidationError("Please enter your email or username.");
        hasErrors = true;
    } else if (!isValidEmail(email) && !email.contains(QRegularExpression("^[a-zA-Z0-9_]+$"))) {
        setFieldError(emailField, true);
        showValidationError("Please enter a valid email address or username.");
        hasErrors = true;
    } else {
        setFieldError(emailField, false);
    }
    
    // Validate password
    if (password.isEmpty()) {
        setFieldError(passwordField, true);
        if (!hasErrors) showValidationError("Please enter your password.");
        hasErrors = true;
    } else {
        setFieldError(passwordField, false);
    }
    
    if (!hasErrors) {
        // Successfully validated - redirect to main content
        showMainContent();
        // Switch to Employer (Dashboard) page by default
        ui->stackedWidget->setCurrentIndex(0);
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
    
    // Set specific column widths with better distribution - INCREASED FOR BETTER DISPLAY
    ui->employeeTable->setColumnWidth(0, 60);   // Select column
    ui->employeeTable->setColumnWidth(1, 140);  // Avatar column - INCREASED
    ui->employeeTable->setColumnWidth(2, 80);   // ID column - INCREASED
    ui->employeeTable->setColumnWidth(3, 200);  // Name column - INCREASED
    ui->employeeTable->setColumnWidth(4, 250);  // Email column - INCREASED
    ui->employeeTable->setColumnWidth(5, 150);  // Role column - INCREASED
    ui->employeeTable->setColumnWidth(6, 170);  // Phone column - INCREASED
    ui->employeeTable->setColumnWidth(7, 150);  // Start Date column - INCREASED
    ui->employeeTable->setColumnWidth(8, 250);  // Resources column - INCREASED
    
    // Stretch last column to fill remaining space
    ui->employeeTable->horizontalHeader()->setStretchLastSection(false);
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch); // Resources stretches
    
    // Increase row height for better avatar and content display
    ui->employeeTable->verticalHeader()->setDefaultSectionSize(140);
    ui->employeeTable->verticalHeader()->setMinimumSectionSize(140);
    
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
}

void MainWindow::setupDashboardAnimations()
{
    // Fade in the dashboard title and statistics container
    if (ui->dashboardTabTitle) {
        QPropertyAnimation* titleFade = new QPropertyAnimation(ui->dashboardTabTitle, "windowOpacity");
        titleFade->setDuration(800);
        titleFade->setStartValue(0.0);
        titleFade->setEndValue(1.0);
        titleFade->setEasingCurve(QEasingCurve::InOutCubic);
        titleFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if (ui->statisticsCardsContainer) {
        QPropertyAnimation* statsFade = new QPropertyAnimation(ui->statisticsCardsContainer, "windowOpacity");
        statsFade->setDuration(1000);
        statsFade->setStartValue(0.0);
        statsFade->setEndValue(1.0);
        statsFade->setEasingCurve(QEasingCurve::OutCubic);
        statsFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // Slide and fade-in the three main statistic cards that exist in the UI
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QList<QWidget*> statWidgets;
    if (ui->totalEmployeesCard) statWidgets.append(ui->totalEmployeesCard);
    if (ui->activeProjectsCard) statWidgets.append(ui->activeProjectsCard);
    if (ui->performanceCard) statWidgets.append(ui->performanceCard);

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
    EmployerUIHelper::updateButtonStates(ui->modifyBtn, ui->deleteBtn, ui->employeeTable);
}

void MainWindow::onAddEmployerClicked()
{
    qDebug() << "\n========== ADD EMPLOYER CLICKED ==========";
    
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
        if (!selectedResources.isEmpty())
        {
            qDebug() << "[MainWindow::onAddEmployerClicked] Assigning" << selectedResources.size() << "resources...";
            for (qint64 resourceId : selectedResources)
            {
                Ressource::addResourceToEmployer(newEmployer.employerId, resourceId);
            }
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
    Ressource::clearEmployerResources(employerId);
    for (qint64 resourceId : selectedResources)
    {
        Ressource::addResourceToEmployer(employerId, resourceId);
    }
    
    qDebug() << "[MainWindow::onModifyEmployerClicked] Resources updated:" << selectedResources.size() << "resources assigned";
    qDebug() << "[MainWindow::onModifyEmployerClicked] Reloading employers...";
    
    loadEmployers();
    QMessageBox::information(this, tr("Employer Updated"), 
        tr("Changes saved successfully."));
    
    qDebug() << "========== MODIFY EMPLOYER COMPLETED ==========\n";
}

void MainWindow::onDeleteEmployerClicked()
{
    qDebug() << "\n========== DELETE EMPLOYER CLICKED ==========";
    
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

    qDebug() << "[MainWindow::onDeleteEmployerClicked] User confirmed. Calling Employer::remove with ID:" << employerId;

    if (!Employer::remove(employerId))
    {
        qDebug() << "[MainWindow::onDeleteEmployerClicked] CRITICAL: remove FAILED for ID:" << employerId;
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
    const QString basePath = QCoreApplication::applicationDirPath();
    const QString filePath = QFileDialog::getSaveFileName(this,
                                                          tr("Export Employers"),
                                                          basePath + QStringLiteral("/employers.csv"),
                                                          tr("CSV Files (*.csv)"));
    if (filePath.isEmpty())
    {
        return;
    }

    QString errorMessage;
    if (!EmployerUIHelper::exportToCsv(filePath, cachedEmployers, &errorMessage))
    {
        QMessageBox::critical(this, tr("Export"), errorMessage);
        return;
    }

    QMessageBox::information(this, tr("Export"), 
        tr("Employer list exported successfully."));
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

void MainWindow::onSortEmployersClicked()
{
    QVector<Employer> sorted = EmployerUIHelper::sortRecords(cachedEmployers);
    EmployerUIHelper::populateTable(ui->employeeTable, sorted);
    updateEmployerButtonStates();
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
