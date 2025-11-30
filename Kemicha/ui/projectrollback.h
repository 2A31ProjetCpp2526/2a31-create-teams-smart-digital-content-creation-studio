#ifndef PROJECTROLLBACK_H
#define PROJECTROLLBACK_H

#include <QString>
#include <QStringList>

class ProjectRollback
{
public:
    ProjectRollback();
    ~ProjectRollback();

    // Load rollback history from file
    QStringList loadRollbackHistoryFromFile();

    // Save rollback history to file
    void saveRollbackHistoryToFile(const QStringList &history);

    // Add action to history. `undoSql` is the SQL string to execute when rolling back this action.
    void addAction(const QString &action, const QString &undoSql, const QStringList &currentHistory);

    // Get last action, execute its undo SQL and remove it from history. Returns the human-readable action text on success, empty string on failure.
    QString rollbackLastAction(QStringList &history);

    // Get the file path where rollback history is stored
    QString getRollbackHistoryFilePath() const;

    // Get file path for a specific project (optional)
    QString getRollbackHistoryFilePathForProject(qint64 projectId) const;

private:
    QString rollbackHistoryFilePath;

    // Initialize file path in app data location
    void initializeFilePath();
};

#endif // PROJECTROLLBACK_H
