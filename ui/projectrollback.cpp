#include "projectrollback.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

ProjectRollback::ProjectRollback()
{
    initializeFilePath();
}

ProjectRollback::~ProjectRollback()
{
}

void ProjectRollback::initializeFilePath()
{
    // Save rollback_history.txt to the project root / current working directory
    QString dataPath = QDir::currentPath();
    if (!QDir(dataPath).exists()) {
        QDir().mkpath(dataPath);
    }
    rollbackHistoryFilePath = QDir(dataPath).filePath("rollback_history.txt");
    qDebug() << "ProjectRollback::initializeFilePath() - Rollback history file path:" << rollbackHistoryFilePath;
}

QStringList ProjectRollback::loadRollbackHistoryFromFile()
{
    QStringList result;
    QFile file(rollbackHistoryFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ProjectRollback::loadRollbackHistoryFromFile() - File does not exist yet:" << rollbackHistoryFilePath;
        return result;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            result.append(line);
        }
    }

    file.close();
    qDebug() << "ProjectRollback::loadRollbackHistoryFromFile() - Loaded" << result.count() << "history entries";
    return result;
}

void ProjectRollback::saveRollbackHistoryToFile(const QStringList &history)
{
    QFile file(rollbackHistoryFilePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "ProjectRollback::saveRollbackHistoryToFile() - Failed to open file for writing:" << rollbackHistoryFilePath;
        return;
    }

    QTextStream out(&file);
    for (const QString &entry : history) {
        out << entry << "\n";
    }

    file.close();
    qDebug() << "ProjectRollback::saveRollbackHistoryToFile() - Saved" << history.count() << "history entries";

    // Remove file if history is empty
    if (history.isEmpty()) {
        if (QFile::exists(rollbackHistoryFilePath)) {
            QFile::remove(rollbackHistoryFilePath);
            qDebug() << "ProjectRollback::saveRollbackHistoryToFile() - Removed empty file:" << rollbackHistoryFilePath;
        }
    }
}

void ProjectRollback::addAction(const QString &action, const QString &undoSql, const QStringList &currentHistory)
{
    // Build JSON entry { timestamp, action, undoSql }
    QJsonObject entry;
    entry["timestamp"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    entry["action"] = action;
    entry["undoSql"] = undoSql;

    QJsonDocument doc(entry);
    QString jsonLine = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));

    QStringList updatedHistory = currentHistory;
    updatedHistory.append(jsonLine);
    saveRollbackHistoryToFile(updatedHistory);
    qDebug() << "ProjectRollback::addAction() - Added action:" << action << "undoSql:" << undoSql;
}

QString ProjectRollback::rollbackLastAction(QStringList &history)
{
    if (history.isEmpty()) {
        qDebug() << "ProjectRollback::rollbackLastAction() - History is empty";
        return QString();
    }

    QString lastLine = history.takeLast();

    // Try to parse JSON. If parsing fails, treat the line as legacy plain text and simply return it
    QString actionText;
    QString undoSql;
    QJsonParseError perr;
    QJsonDocument doc = QJsonDocument::fromJson(lastLine.toUtf8(), &perr);

    if (perr.error == QJsonParseError::NoError && doc.isObject()) {
        QJsonObject obj = doc.object();
        actionText = obj.value("action").toString();
        undoSql = obj.value("undoSql").toString();
    } else {
        // legacy format
        actionText = lastLine;
        undoSql.clear();
    }

    // If we have an undo SQL, attempt to execute it
    if (!undoSql.isEmpty()) {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen()) {
            QSqlQuery q(db);
            qDebug() << "ProjectRollback::rollbackLastAction() - Executing undo SQL:" << undoSql;
            if (!q.exec(undoSql)) {
                qDebug() << "ProjectRollback::rollbackLastAction() - ERROR executing undo SQL:" << q.lastError().text();
                // rollback failed; do not remove the history entry so the user can retry
                // re-add the last line back to history (we removed it earlier)
                history.append(lastLine);
                return QString();
            }
        } else {
            qDebug() << "ProjectRollback::rollbackLastAction() - Database not open, cannot execute undo SQL";
            history.append(lastLine);
            return QString();
        }
    } else {
        qDebug() << "ProjectRollback::rollbackLastAction() - legacy action, no undo SQL to execute. Removing entry only.";
    }

    // Persist modified history (we already removed lastLine from history variable)
    saveRollbackHistoryToFile(history);
    qDebug() << "ProjectRollback::rollbackLastAction() - Rolled back action:" << actionText;
    return actionText;
}

QString ProjectRollback::getRollbackHistoryFilePath() const
{
    return rollbackHistoryFilePath;
}

QString ProjectRollback::getRollbackHistoryFilePathForProject(qint64 projectId) const
{
    // Return project-specific rollback file if needed
    QString dataPath = QDir::currentPath();
    return QDir(dataPath).filePath(QString("rollback_history_project_%1.txt").arg(projectId));
}
