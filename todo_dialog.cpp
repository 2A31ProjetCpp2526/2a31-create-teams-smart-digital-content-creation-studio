#include "todo_dialog.h"
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>
#include <QListWidget>
#include <QSet>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>

TodoDialog::TodoDialog(QWidget *parent)
    : QDialog(parent), m_store("todos.json")
{
    setWindowTitle("Gestionnaire de Todo / Rappels");
    resize(680, 420);

    // two-column layout: calendar+list on left, form on right
    QHBoxLayout *root = new QHBoxLayout(this);

    QVBoxLayout *leftCol = new QVBoxLayout;
    m_calendar = new QCalendarWidget(this);
    m_calendar->setGridVisible(true);
    leftCol->addWidget(m_calendar);

    m_filterLabel = new QLabel("Tous les jours", this);
    leftCol->addWidget(m_filterLabel);

    m_list = new QListWidget(this);
    leftCol->addWidget(m_list, 1);

    root->addLayout(leftCol, 1);

    QFormLayout *form = new QFormLayout;
    m_title = new QLineEdit(this);
    m_desc = new QTextEdit(this);
    m_due = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    m_due->setCalendarPopup(true);

    form->addRow(new QLabel("Titre:"), m_title);
    form->addRow(new QLabel("Description:"), m_desc);
    form->addRow(new QLabel("Date et heure:"), m_due);

    QVBoxLayout *rightCol = new QVBoxLayout;
    rightCol->addLayout(form);

    QHBoxLayout *buttons = new QHBoxLayout;
    QPushButton *addBtn = new QPushButton("Ajouter", this);
    QPushButton *saveBtn = new QPushButton("Sauvegarder", this);
    m_deleteBtn = new QPushButton("Supprimer (sélection)", this);
    buttons->addWidget(addBtn);
    buttons->addWidget(saveBtn);
    buttons->addWidget(m_deleteBtn);


    rightCol->addLayout(buttons);

    // add an area for helpful notes or status
    QLabel *hint = new QLabel("Sélectionnez une date pour filtrer les tâches. Double-cliquez une tâche pour la copier.", this);
    rightCol->addWidget(hint);

    root->addLayout(rightCol, 1);

    connect(addBtn, &QPushButton::clicked, this, &TodoDialog::addItem);
    connect(saveBtn, &QPushButton::clicked, this, &TodoDialog::saveItems);
    connect(m_deleteBtn, &QPushButton::clicked, this, &TodoDialog::deleteSelectedTodo);
    connect(m_calendar, &QCalendarWidget::selectionChanged, this, [this]() { onCalendarDateChanged(m_calendar->selectedDate()); });
    connect(m_list, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *it){
        if (!it) return;
        QClipboard *cb = QApplication::clipboard();
        if (cb) cb->setText(it->text());
        QMessageBox::information(this, "Copié", "Tâche copiée dans le presse-papier.");
    });

    loadItems();
}

void TodoDialog::addItem()
{
    TodoItem t;
    // assign ID sequentially (simple approach)
    int maxId = 0;
    for (const TodoItem &it : std::as_const(m_items)) maxId = std::max(maxId, it.id);
    t.id = maxId + 1;
    t.title = m_title->text().trimmed();
    t.description = m_desc->toPlainText().trimmed();
    t.due = m_due->dateTime();

    if (t.title.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le titre est requis");
        return;
    }

    m_items.append(t);
    QListWidgetItem *it = new QListWidgetItem(QString("%1 — %2").arg(t.due.toString(Qt::ISODate), t.title));
    it->setData(Qt::UserRole, t.id);
    m_list->addItem(it);

    m_desc->clear();
    // leave email field as-is for convenience
}

void TodoDialog::loadItems()
{
    m_items = m_store.load();
    m_list->clear();
    // show all initially
    for (const TodoItem &t : std::as_const(m_items)) {
        QListWidgetItem *it = new QListWidgetItem(QString("%1 — %2").arg(t.due.toString(Qt::ISODate), t.title));
        it->setData(Qt::UserRole, t.id);
        m_list->addItem(it);
    }
}

void TodoDialog::onCalendarDateChanged(const QDate &d)
{
    m_filterLabel->setText(QString("Filtre: %1").arg(d.toString("yyyy-MM-dd")));
    m_list->clear();
    for (const TodoItem &t : std::as_const(m_items)) {
        if (t.due.date() == d) {
            QListWidgetItem *it = new QListWidgetItem(QString("%1 — %2").arg(t.due.toString(Qt::ISODate), t.title));
            it->setData(Qt::UserRole, t.id);
            m_list->addItem(it);
        }
    }
    // make the due editor default to the selected date at current time
    QDateTime dt = m_due->dateTime();
    dt.setDate(d);
    m_due->setDateTime(dt);
}

// exportTodosAsText removed (user requested no exports from Todo dialog)

// exportStatsAsText removed (user requested no stats export from calendar)

void TodoDialog::saveItems()
{
    bool ok = m_store.save(m_items);
    QMessageBox::information(this, ok ? "Succès" : "Erreur", ok ? "Tâches sauvegardées" : "Impossible d'enregistrer les tâches");
}

void TodoDialog::deleteSelectedTodo()
{
    QList<QListWidgetItem*> sel = m_list->selectedItems();
    if (!sel.isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmer suppression", "Supprimer les tâches sélectionnées ?", QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes) return;

        // collect ids to remove
        QSet<int> ids;
        for (QListWidgetItem *item : sel) ids.insert(item->data(Qt::UserRole).toInt());

        // remove from model
        QVector<TodoItem> newItems;
        for (const TodoItem &t : std::as_const(m_items)) {
            if (!ids.contains(t.id)) newItems.append(t);
        }
        m_items = std::move(newItems);
        saveItems();

        // refresh list for current date filter
        onCalendarDateChanged(m_calendar->selectedDate());
        return;
    }

    // nothing selected — ask to delete all for selected date
    QDate selDate = m_calendar->selectedDate();
    int countForDate = 0;
    for (const TodoItem &t : std::as_const(m_items)) if (t.due.date() == selDate) ++countForDate;
    if (countForDate == 0) {
        QMessageBox::information(this, "Suppression", "Aucune tâche pour la date sélectionnée à supprimer.");
        return;
    }

    QMessageBox::StandardButton r2 = QMessageBox::question(this, "Confirmer suppression", QString("Supprimer toutes les tâches (%1) pour %2 ?").arg(countForDate).arg(selDate.toString("yyyy-MM-dd")), QMessageBox::Yes | QMessageBox::No);
    if (r2 != QMessageBox::Yes) return;

    QVector<TodoItem> remaining;
    for (const TodoItem &t : std::as_const(m_items)) if (t.due.date() != selDate) remaining.append(t);
    m_items = std::move(remaining);
    saveItems();
    onCalendarDateChanged(m_calendar->selectedDate());
}

// sendReminder removed (mailing disabled)

// onMailResult removed
