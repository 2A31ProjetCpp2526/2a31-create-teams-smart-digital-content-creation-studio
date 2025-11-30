#ifndef RESSOURCEWIDGET_H
#define RESSOURCEWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class RessourceWidget;
}

class RessourceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RessourceWidget(QWidget *parent = nullptr);
    ~RessourceWidget();
    
    // Public method to load resources (called from MainWindow)
    void loadRessources();

private slots:
    void onAddRessource();
    void onEditRessource();
    void onUpdateRessource(qint64 ressourceId);
    void onDeleteRessource();
    void onSearchRessource(const QString &keyword);
    void onTableCellChanged(int row, int column);
    void onExportCsv();

private:
    Ui::RessourceWidget *ui;
    QSqlQueryModel *currentModel;
    bool isEditingMode;
    
    void clearAddForm();
    void setupTableEditability();
    void refreshTable();
};

#endif // RESSOURCEWIDGET_H
