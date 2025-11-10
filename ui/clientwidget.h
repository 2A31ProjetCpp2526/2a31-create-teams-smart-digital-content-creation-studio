#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void loadClients();
    void onAddClient();
    void onEditClient();
    void onUpdateClient(qint64 clientId);
    void onDeleteClient();
    void onSearchClient(const QString &keyword);
    void onExportCsv();
    void onSortByName();

private:
    Ui::ClientWidget *ui;
    void clearAddForm();
};

#endif // CLIENTWIDGET_H
