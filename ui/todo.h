#ifndef TODO_H
#define TODO_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QJsonObject>

struct TodoItem {
    int id;
    QString title;
    QString description;
    QDateTime due;
    // notifyEmail removed (mailing disabled)

    QJsonObject toJson() const;
    static TodoItem fromJson(const QJsonObject &o);
};

class TodoStore {
public:
    explicit TodoStore(const QString &path);

    QVector<TodoItem> load();
    bool save(const QVector<TodoItem> &items);

    // Helper: write a listing of the given directory into a text file
    static bool exportDirectoryListing(const QString &dirPath, const QString &outputTextFile);

private:
    QString m_path;
};

#endif // TODO_H
