#ifndef PROJECTINSERTION_H
#define PROJECTINSERTION_H

#include <QString>
#include <QStringList>

class ProjectInsertion
{
public:
    ProjectInsertion();
    ~ProjectInsertion();

    // Load media list from file
    QStringList loadMediaListFromFile();

    // Save media list to file
    void saveMediaListToFile(const QStringList &mediaPaths);

    // Get the file path where media list is stored
    QString getMediaListFilePath() const;

    // Get file path for a specific project (optional, for project-specific storage)
    QString getMediaListFilePathForProject(qint64 projectId) const;

private:
    QString mediaListFilePath;

    // Initialize file path in app data location
    void initializeFilePath();
};

#endif // PROJECTINSERTION_H
