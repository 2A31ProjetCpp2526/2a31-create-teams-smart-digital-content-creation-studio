#ifndef TODO_DIALOG_H
#define TODO_DIALOG_H

#include <QDialog>
#include <QVector>
#include "todo.h"
#include <QClipboard>

class QListWidget;
class QLineEdit;
class QTextEdit;
class QDateTimeEdit;
class QCalendarWidget;
class QPushButton;
class QLabel;

class TodoDialog : public QDialog {
    Q_OBJECT
public:
    explicit TodoDialog(QWidget *parent = nullptr);

private slots:
    void addItem();
    void saveItems();
    void loadItems();
    // mail removed — no sendReminder
    void deleteSelectedTodo();
    void onCalendarDateChanged(const QDate &d);
    // onMailResult removed (mail integration removed)

private:
    QVector<TodoItem> m_items;
    TodoStore m_store;

    // UI
    QListWidget *m_list;
    QLineEdit *m_title;
    QTextEdit *m_desc;
    // email field removed (mail disabled)
    QDateTimeEdit *m_due;
    QCalendarWidget *m_calendar;
    // export button removed per user request
    QPushButton *m_deleteBtn;
    // m_mail removed — Mailjet integration removed
    QLabel *m_filterLabel;
};

#endif // TODO_DIALOG_H