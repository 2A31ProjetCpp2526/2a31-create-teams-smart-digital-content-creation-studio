#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QMap<QString, int> getStatusStats();
    ~MainWindow() override = default; // Explicit default destructor

private slots:
    // Slot for adding a new appointment
    void addSponsor();
    void loadSponsoring();
    void deleteSelectedSponsor();
    void updateSponsor();
    void searchSponsorById();
    void on_pdfexport_clicked();
    void on_sort_clicked();
    void clearFields();
    void onSponsorSelected(const QModelIndex &index);
    void drawPieChart(const QMap<QString,int>& stats);
    QMap<QString,int> getStatusFromTable();
    void on_pushButton_stat_clicked();
    void openTodoManager();
    void openCalendar();
    // mail removed

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
