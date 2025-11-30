#include "todo.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>

QJsonObject TodoItem::toJson() const
{
    QJsonObject obj;
    obj["id"] = id;
    obj["title"] = title;
    obj["description"] = description;
    obj["due"] = due.toString(Qt::ISODate);
    // notifyEmail removed - no email stored
    return obj;
}

TodoItem TodoItem::fromJson(const QJsonObject &o)
{
    TodoItem t;
    t.id = o.value("id").toInt();
    t.title = o.value("title").toString();
    t.description = o.value("description").toString();
    t.due = QDateTime::fromString(o.value("due").toString(), Qt::ISODate);
    // notifyEmail removed - nothing to load
    return t;
}

TodoStore::TodoStore(const QString &path): m_path(path) {}

QVector<TodoItem> TodoStore::load()
{
    QVector<TodoItem> v;
    QFile f(m_path);
    if (!f.open(QIODevice::ReadOnly)) return v;
    QByteArray data = f.readAll();
    f.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return v;

    QJsonArray arr = doc.array();
    for (const QJsonValue &val : arr) {
        if (val.isObject()) v.append(TodoItem::fromJson(val.toObject()));
    }
    return v;
}

bool TodoStore::save(const QVector<TodoItem> &items)
{
    QJsonArray arr;
    for (const TodoItem &t : items) arr.append(t.toJson());

    QJsonDocument doc(arr);
    QFile f(m_path);
    if (!f.open(QIODevice::WriteOnly)) return false;
    f.write(doc.toJson(QJsonDocument::Indented));
    f.close();
    return true;
}

bool TodoStore::exportDirectoryListing(const QString &dirPath, const QString &outputTextFile)
{
    QDir d(dirPath);
    if (!d.exists()) return false;
    QFile out(outputTextFile);
    if (!out.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream ts(&out);
    ts << "Directory listing for: " << dirPath << "\n";
    ts << "------------------------------------\n";

    auto entries = d.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::DirsFirst);
    for (const QFileInfo &fi : entries) {
        ts << (fi.isDir() ? "[DIR]  " : "[FILE] ") << fi.fileName() << "\n";
    }

    out.close();
    return true;
}
