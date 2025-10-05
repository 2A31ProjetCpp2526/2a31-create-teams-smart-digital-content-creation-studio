#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "media.h"
#include "rb.h"

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

private:
    Ui::MainWindow *ui;
    media *m_media;
    rb *m_rb;
};

#endif // MAINWINDOW_H
