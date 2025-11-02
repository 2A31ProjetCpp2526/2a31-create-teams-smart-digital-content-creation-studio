#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // CSV Export
    void onExportCsv();
    
    // Service management
    void onAddClient();
    void onDisplayClients();
    
    // Table selection
    void onClientTableSelectionChanged();

private:
    Ui::MainWindow *ui;
    
    // Helper methods
    void initializeUI();
    void connectSignals();
    void populateSampleData();
    void applyShadowEffects();
};

#endif // MAINWINDOW_H
