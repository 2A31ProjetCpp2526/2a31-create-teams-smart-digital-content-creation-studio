#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = nullptr);
    ~ProjectWidget();

signals:
    void addProjectRequested(QString pid, QString titre, QString desc, QString status);
    void editProjectRequested(QString pid, QString titre, QString desc, QString status);
    void deleteProjectRequested(QString pid);

private slots:
    void onAddProjClicked();
    void onEditProjClicked();
    void onDeleteProjClicked();
    void onViewProjClicked();   // ✅ Add this line

private:
    Ui::ProjectWidget *ui;
};

#endif // PROJECTWIDGET_H
