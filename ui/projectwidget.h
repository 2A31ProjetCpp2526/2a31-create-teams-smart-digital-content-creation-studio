#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "../backend/project.h"

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = nullptr);
    ~ProjectWidget();

private slots:
    // List tab slots
    void onRefreshProjectsClicked();
    
    // Add tab slots
    void onAddProjectClicked();
    void onUpdateProjectClicked(qint64 projectId);
    
    // Table button slots
    void onEditFromTableClicked();
    void onDeleteFromTableClicked();

private:
    Ui::ProjectWidget *ui;
    bool isEditingMode = false;
    qint64 currentEditingProjectId = -1;
    
    // Helper methods
    void loadAllProjects();
    void clearAddForm();
    void refreshTable();

};

#endif // PROJECTWIDGET_H
