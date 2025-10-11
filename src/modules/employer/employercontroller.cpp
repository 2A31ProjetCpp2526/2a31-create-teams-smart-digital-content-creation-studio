#include "employercontroller.h"

#include "databasemanager.h"
#include "employerform.h"

#include <QAbstractItemView>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QHeaderView>
#include <QIcon>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QTime>
#include <QPixmap>
#include <QDebug>

#include <algorithm>

using namespace employer;

namespace
{
constexpr auto kSelectSymbol = "☑";
constexpr auto kUnselectSymbol = "☐";

QString formatDate(const QDate &date)
{
    return date.isValid() ? date.toString(QStringLiteral("yyyy-MM-dd")) : QString();
}
}

EmployerController::EmployerController(EmployerModel *model,
                                       QTableWidget *table,
                                       QPushButton *addButton,
                                       QPushButton *modifyButton,
                                       QPushButton *deleteButton,
                                       QPushButton *exportButton,
                                       QLineEdit *searchInput,
                                       QPushButton *searchButton,
                                       QPushButton *sortButton,
                                       QObject *parent)
    : QObject(parent)
    , m_model(model)
    , m_table(table)
    , m_addButton(addButton)
    , m_modifyButton(modifyButton)
    , m_deleteButton(deleteButton)
    , m_exportButton(exportButton)
    , m_searchInput(searchInput)
    , m_searchButton(searchButton)
    , m_sortButton(sortButton)
{
}

bool EmployerController::initialize()
{
    if (!m_table || !m_model)
    {
        qDebug() << "[Employer][Controller] Table or model missing. Initialization failed.";
        return false;
    }

    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->horizontalHeader()->setStretchLastSection(true);

    QString errorMessage;
    if (!reloadModel(&errorMessage))
    {
        showError(tr("Load Employers"), errorMessage);
    }

    updateSelectionState();
    return true;
}

void EmployerController::openAddDialog()
{
    EmployerForm form(m_table);
    form.setMode(EmployerForm::CreateMode);

    if (form.exec() != QDialog::Accepted)
    {
        return;
    }

    QString errorMessage;
    if (!ensureConnection(&errorMessage))
    {
        showError(tr("Database"), errorMessage);
        return;
    }

    const EmployerRecord rec = form.record();
    const QString password = form.rawPassword();

    if (!insertEmployer(rec, password))
    {
        return;
    }

    if (!reloadModel(&errorMessage))
    {
        showError(tr("Load Employers"), errorMessage);
    }
    else
    {
        showInfo(tr("Employer Added"), tr("The employer has been created successfully."));
    }
}

void EmployerController::openModifyDialog()
{
    bool ok = false;
    const qint64 employerId = selectedEmployerId(&ok);
    if (!ok)
    {
        showError(tr("Update Employer"), tr("Select a single employer to modify."));
        return;
    }

    EmployerRecord existing;
    if (!m_model->fetchById(employerId, existing))
    {
        showError(tr("Update Employer"), tr("Unable to locate the selected employer record."));
        return;
    }

    EmployerForm form(m_table);
    form.setMode(EmployerForm::EditMode);
    form.setRecord(existing);

    if (form.exec() != QDialog::Accepted)
    {
        return;
    }

    const EmployerRecord updates = form.record();
    const bool passwordProvided = form.passwordProvided();
    const QString password = passwordProvided ? form.rawPassword() : existing.passwordHash;

    if (!updateEmployer(employerId, updates, password, passwordProvided))
    {
        return;
    }

    QString errorMessage;
    if (!reloadModel(&errorMessage))
    {
        showError(tr("Load Employers"), errorMessage);
    }
    else
    {
        showInfo(tr("Employer Updated"), tr("Changes saved successfully."));
    }
}

void EmployerController::removeSelectedEmployer()
{
    bool ok = false;
    const qint64 employerId = selectedEmployerId(&ok);
    if (!ok)
    {
        showError(tr("Remove Employer"), tr("Select a single employer row before deleting."));
        return;
    }

    const auto reply = QMessageBox::question(m_table, tr("Confirm Delete"),
                                             tr("Are you sure you want to delete this employer?"));
    if (reply != QMessageBox::Yes)
    {
        return;
    }

    if (!deleteEmployer(employerId))
    {
        return;
    }

    QString errorMessage;
    if (!reloadModel(&errorMessage))
    {
        showError(tr("Load Employers"), errorMessage);
    }
    else
    {
        showInfo(tr("Employer Deleted"), tr("Employer removed successfully."));
    }
}

void EmployerController::updateSelectionState()
{
    bool ok = false;
    selectedEmployerId(&ok);
    const bool hasSelection = ok;

    if (m_modifyButton)
    {
        m_modifyButton->setEnabled(hasSelection);
    }
    if (m_deleteButton)
    {
        m_deleteButton->setEnabled(hasSelection);
    }
}

void EmployerController::handleSelectionToggle(QTableWidgetItem *item)
{
    if (!item || item->column() != 0)
    {
        return;
    }

    for (int row = 0; row < m_table->rowCount(); ++row)
    {
        if (row == item->row())
        {
            const bool alreadySelected = item->text() == QString::fromUtf8(kSelectSymbol);
            item->setText(alreadySelected ? QString::fromUtf8(kUnselectSymbol)
                                          : QString::fromUtf8(kSelectSymbol));
            m_table->selectRow(row);
        }
        else
        {
            QTableWidgetItem *other = m_table->item(row, 0);
            if (other)
            {
                other->setText(QString::fromUtf8(kUnselectSymbol));
            }
        }
    }

    updateSelectionState();
}

void EmployerController::exportEmployers()
{
    if (!m_exportButton)
    {
        return;
    }

    const QString basePath = QCoreApplication::applicationDirPath();
    const QString filePath = QFileDialog::getSaveFileName(m_exportButton,
                                                          tr("Export Employers"),
                                                          basePath + QStringLiteral("/employers.csv"),
                                                          tr("CSV Files (*.csv)"));
    if (filePath.isEmpty())
    {
        return;
    }

    if (!exportCsv(filePath))
    {
        return;
    }

    showInfo(tr("Export"), tr("Employer list exported successfully."));
}

void EmployerController::runSearch()
{
    const QString term = m_searchInput ? m_searchInput->text().trimmed() : QString();

    if (term.isEmpty())
    {
        populateTable(m_cachedRecords, false);
        updateSelectionState();
        return;
    }

    QVector<EmployerRecord> filtered;
    filtered.reserve(m_cachedRecords.size());
    for (const auto &record : m_cachedRecords)
    {
        const QString composite = QStringLiteral("%1 %2 %3").arg(record.firstName, record.lastName, record.email);
        if (composite.contains(term, Qt::CaseInsensitive))
        {
            filtered.push_back(record);
        }
    }

    if (filtered.isEmpty())
    {
        showInfo(tr("Search"), tr("No employers matched the search term."));
    }

    populateTable(filtered, false);
    updateSelectionState();
}

void EmployerController::runSort()
{
    if (m_cachedRecords.isEmpty())
    {
        return;
    }

    QVector<EmployerRecord> sorted = m_cachedRecords;
    std::sort(sorted.begin(), sorted.end(), [](const EmployerRecord &lhs, const EmployerRecord &rhs) {
        if (lhs.lastName.compare(rhs.lastName, Qt::CaseInsensitive) == 0)
        {
            return lhs.firstName.compare(rhs.firstName, Qt::CaseInsensitive) < 0;
        }
        return lhs.lastName.compare(rhs.lastName, Qt::CaseInsensitive) < 0;
    });

    populateTable(sorted, false);
    updateSelectionState();
}

bool EmployerController::ensureConnection(QString *errorMessage)
{
    QSqlDatabase db = DatabaseManager::instance().database();
    if (!db.isValid())
    {
        if (errorMessage)
        {
            *errorMessage = tr("Database connection is not valid. Configure DSN 'OracleQt'.");
        }
        return false;
    }

    if (!db.isOpen())
    {
        if (errorMessage)
        {
            *errorMessage = tr("Unable to open database connection. Check DSN credentials.");
        }
        return false;
    }
    return true;
}

bool EmployerController::reloadModel(QString *errorMessage)
{
    if (!ensureConnection(errorMessage))
    {
        return false;
    }

    if (!m_model->refresh())
    {
        if (errorMessage)
        {
            *errorMessage = tr("Failed to load employer records: %1").arg(m_model->lastError().text());
        }
        qDebug() << "[Employer][Controller] Model refresh failed" << m_model->lastError();
        return false;
    }

    m_cachedRecords = m_model->allRecords();
    populateTable(m_cachedRecords);
    return true;
}

void EmployerController::populateTable(const QVector<EmployerRecord> &records, bool updateCache)
{
    if (!m_table)
    {
        return;
    }

    if (updateCache)
    {
        m_cachedRecords = records;
    }

    m_table->setRowCount(records.size());

    for (int row = 0; row < records.size(); ++row)
    {
        const EmployerRecord &rec = records.at(row);

        auto *selectItem = new QTableWidgetItem(QString::fromUtf8(kUnselectSymbol));
        selectItem->setTextAlignment(Qt::AlignCenter);
        selectItem->setData(Qt::UserRole, rec.employerId);
        m_table->setItem(row, 0, selectItem);

        auto *avatarItem = new QTableWidgetItem();
        if (!rec.avatarPath.isEmpty())
        {
            const QPixmap pixmap(rec.avatarPath);
            if (!pixmap.isNull())
            {
                avatarItem->setIcon(QIcon(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            }
        }
        avatarItem->setToolTip(rec.avatarPath);
        m_table->setItem(row, 1, avatarItem);

        auto *idItem = new QTableWidgetItem(rec.employerId > 0 ? QString::number(rec.employerId) : QString());
        m_table->setItem(row, 2, idItem);

        auto *nameItem = new QTableWidgetItem(QStringLiteral("%1 %2").arg(rec.firstName, rec.lastName));
        m_table->setItem(row, 3, nameItem);

        auto *emailItem = new QTableWidgetItem(rec.email);
        m_table->setItem(row, 4, emailItem);

        auto *roleItem = new QTableWidgetItem(rec.role);
        m_table->setItem(row, 5, roleItem);

        auto *phoneItem = new QTableWidgetItem(rec.phone);
        m_table->setItem(row, 6, phoneItem);

        auto *dateItem = new QTableWidgetItem(formatDate(rec.startDate));
        m_table->setItem(row, 7, dateItem);

        m_table->setRowHeight(row, 90);
    }

    m_table->clearSelection();
}

bool EmployerController::insertEmployer(const EmployerRecord &record, const QString &password)
{
    QString errorMessage;
    if (!ensureConnection(&errorMessage))
    {
        showError(tr("Database"), errorMessage);
        return false;
    }

    QSqlDatabase db = DatabaseManager::instance().database();
    QSqlQuery query(db);
    query.prepare(QStringLiteral(
        "INSERT INTO EMPLOYER (FIRST_NAME, LAST_NAME, EMAIL, PHONE, ROLE, PASSWORD_HASH, START_DATE, AVATAR_PATH) "
        "VALUES (:first_name, :last_name, :email, :phone, :role, :password_hash, :start_date, :avatar_path)"));

    query.bindValue(QStringLiteral(":first_name"), record.firstName);
    query.bindValue(QStringLiteral(":last_name"), record.lastName);
    query.bindValue(QStringLiteral(":email"), record.email);
    query.bindValue(QStringLiteral(":phone"), record.phone);
    query.bindValue(QStringLiteral(":role"), record.role);
    query.bindValue(QStringLiteral(":password_hash"), hashPassword(password));
    query.bindValue(QStringLiteral(":start_date"), QDateTime(record.startDate, QTime(0, 0)));
    query.bindValue(QStringLiteral(":avatar_path"), record.avatarPath);

    if (!query.exec())
    {
        const QString driverText = query.lastError().driverText();
        qDebug() << "[Employer][Controller] Insert failure" << query.lastError();
        if (driverText.contains(QStringLiteral("ORA-00001")) || driverText.contains(QStringLiteral("unique"), Qt::CaseInsensitive))
        {
            showError(tr("Duplicate Email"), tr("An employer with this email already exists."));
        }
        else
        {
            showError(tr("Insert Employer"), query.lastError().text());
        }
        return false;
    }

    return true;
}

bool EmployerController::updateEmployer(qint64 employerId,
                                        const EmployerRecord &record,
                                        const QString &password,
                                        bool replacePassword)
{
    QString errorMessage;
    if (!ensureConnection(&errorMessage))
    {
        showError(tr("Database"), errorMessage);
        return false;
    }

    QSqlDatabase db = DatabaseManager::instance().database();
    QString sql = QStringLiteral(
        "UPDATE EMPLOYER SET FIRST_NAME = :first_name, LAST_NAME = :last_name, EMAIL = :email, "
        "PHONE = :phone, ROLE = :role, START_DATE = :start_date, AVATAR_PATH = :avatar_path");

    if (replacePassword)
    {
        sql.append(QStringLiteral(", PASSWORD_HASH = :password_hash"));
    }

    sql.append(QStringLiteral(" WHERE EMPLOYER_ID = :employer_id"));

    QSqlQuery query(db);
    query.prepare(sql);
    query.bindValue(QStringLiteral(":first_name"), record.firstName);
    query.bindValue(QStringLiteral(":last_name"), record.lastName);
    query.bindValue(QStringLiteral(":email"), record.email);
    query.bindValue(QStringLiteral(":phone"), record.phone);
    query.bindValue(QStringLiteral(":role"), record.role);
    query.bindValue(QStringLiteral(":start_date"), QDateTime(record.startDate, QTime(0, 0)));
    query.bindValue(QStringLiteral(":avatar_path"), record.avatarPath);

    if (replacePassword)
    {
        query.bindValue(QStringLiteral(":password_hash"), hashPassword(password));
    }

    query.bindValue(QStringLiteral(":employer_id"), employerId);

    if (!query.exec())
    {
        const QString driverText = query.lastError().driverText();
        qDebug() << "[Employer][Controller] Update failure" << query.lastError();
        if (driverText.contains(QStringLiteral("ORA-00001")) || driverText.contains(QStringLiteral("unique"), Qt::CaseInsensitive))
        {
            showError(tr("Duplicate Email"), tr("Another employer already uses this email."));
        }
        else
        {
            showError(tr("Update Employer"), query.lastError().text());
        }
        return false;
    }

    return true;
}

bool EmployerController::deleteEmployer(qint64 employerId)
{
    QString errorMessage;
    if (!ensureConnection(&errorMessage))
    {
        showError(tr("Database"), errorMessage);
        return false;
    }

    QSqlDatabase db = DatabaseManager::instance().database();
    QSqlQuery query(db);
    query.prepare(QStringLiteral("DELETE FROM EMPLOYER WHERE EMPLOYER_ID = :employer_id"));
    query.bindValue(QStringLiteral(":employer_id"), employerId);

    if (!query.exec())
    {
        qDebug() << "[Employer][Controller] Delete failure" << query.lastError();
        showError(tr("Delete Employer"), query.lastError().text());
        return false;
    }

    return true;
}

bool EmployerController::exportCsv(const QString &path)
{
    if (m_cachedRecords.isEmpty())
    {
        showError(tr("Export"), tr("No employer data available for export."));
        return false;
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        showError(tr("Export"), tr("Cannot open file for writing."));
        return false;
    }

    auto escape = [](const QString &value) {
        QString copy = value;
        copy.replace('"', "\"\"");
        return QStringLiteral("\"%1\"").arg(copy);
    };

    QTextStream stream(&file);
    stream << "EMPLOYER_ID,FIRST_NAME,LAST_NAME,EMAIL,PHONE,ROLE,START_DATE,AVATAR_PATH" << '\n';
    for (const auto &rec : m_cachedRecords)
    {
        stream << rec.employerId << ','
               << escape(rec.firstName) << ','
               << escape(rec.lastName) << ','
               << escape(rec.email) << ','
               << escape(rec.phone) << ','
               << escape(rec.role) << ','
               << escape(formatDate(rec.startDate)) << ','
               << escape(rec.avatarPath)
               << '\n';
    }

    return true;
}

EmployerRecord EmployerController::selectedRecord(bool *ok) const
{
    EmployerRecord record;
    bool localOk = false;
    const qint64 id = selectedEmployerId(&localOk);
    if (localOk)
    {
        for (const auto &candidate : m_cachedRecords)
        {
            if (candidate.employerId == id)
            {
                record = candidate;
                break;
            }
        }
    }

    if (ok)
    {
        *ok = localOk;
    }
    return record;
}

qint64 EmployerController::selectedEmployerId(bool *ok) const
{
    if (!m_table)
    {
        if (ok)
        {
            *ok = false;
        }
        return -1;
    }

    int row = m_table->currentRow();
    if (row < 0)
    {
        for (int r = 0; r < m_table->rowCount(); ++r)
        {
            const QTableWidgetItem *item = m_table->item(r, 0);
            if (item && item->text() == QString::fromUtf8(kSelectSymbol))
            {
                row = r;
                break;
            }
        }
    }

    if (row < 0)
    {
        if (ok)
        {
            *ok = false;
        }
        return -1;
    }

    const QTableWidgetItem *item = m_table->item(row, 0);
    qint64 id = -1;
    if (item)
    {
        id = item->data(Qt::UserRole).toLongLong();
    }

    if (ok)
    {
        *ok = id > 0;
    }
    return id;
}

QString EmployerController::hashPassword(const QString &password) const
{
    // Swap QCryptographicHash::Sha256 with a stronger algorithm if needed.
    const QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString::fromLatin1(hashed.toHex());
}

void EmployerController::showError(const QString &title, const QString &details)
{
    qDebug() << "[Employer][Controller]" << title << details;
    QMessageBox::critical(m_table, title, details);
}

void EmployerController::showInfo(const QString &title, const QString &details)
{
    QMessageBox::information(m_table, title, details);
}
