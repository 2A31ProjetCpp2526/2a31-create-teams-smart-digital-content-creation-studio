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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
