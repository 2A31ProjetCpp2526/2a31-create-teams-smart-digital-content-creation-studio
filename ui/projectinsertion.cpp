#include "projectinsertion.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

ProjectInsertion::ProjectInsertion()
{
    initializeFilePath();
}

ProjectInsertion::~ProjectInsertion()
{
}

void ProjectInsertion::initializeFilePath()
{
    // Save media_paths.txt to the project root / current working directory
    QString dataPath = QDir::currentPath();
    if (!QDir(dataPath).exists()) {
        QDir().mkpath(dataPath);
    }
    mediaListFilePath = QDir(dataPath).filePath("media_paths.txt");
    qDebug() << "ProjectInsertion::initializeFilePath() - Media list file path:" << mediaListFilePath;
}

QStringList ProjectInsertion::loadMediaListFromFile()
{
    QStringList result;
    QFile file(mediaListFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ProjectInsertion::loadMediaListFromFile() - File does not exist yet:" << mediaListFilePath;
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
    qDebug() << "ProjectInsertion::loadMediaListFromFile() - Loaded" << result.count() << "media paths";
    return result;
}

void ProjectInsertion::saveMediaListToFile(const QStringList &mediaPaths)
{
    QFile file(mediaListFilePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "ProjectInsertion::saveMediaListToFile() - Failed to open file for writing:" << mediaListFilePath;
        return;
    }

    QTextStream out(&file);
    for (const QString &path : mediaPaths) {
        out << path << "\n";
    }

    file.close();
    qDebug() << "ProjectInsertion::saveMediaListToFile() - Saved" << mediaPaths.count() << "media paths";

    // If saved list is empty then delete the file to keep project root clean
    if (mediaPaths.isEmpty()) {
        if (QFile::exists(mediaListFilePath)) {
            QFile::remove(mediaListFilePath);
            qDebug() << "ProjectInsertion::saveMediaListToFile() - Removed empty file:" << mediaListFilePath;
        }
    }
}

QString ProjectInsertion::getMediaListFilePath() const
{
    return mediaListFilePath;
}

QString ProjectInsertion::getMediaListFilePathForProject(qint64 projectId) const
{
    // Return project-specific media file if needed
    QString dataPath = QDir::currentPath();
    return QDir(dataPath).filePath(QString("media_paths_project_%1.txt").arg(projectId));
}
