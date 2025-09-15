#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QParallelAnimationGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class ProjectsPage;
class EditorPage;
class LibraryPage;
class SettingsPage;
class LoginPage;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDashboardClicked();
    void onProjectsClicked();
    void onEditorClicked();
    void onLibraryClicked();
    void onSettingsClicked();
    void onLoginClicked();

private:
    void setupPages();
    void setupAnimations();
    void switchToPage(int pageIndex);
    void addButtonHoverEffect(QPushButton* button);
    
    Ui::MainWindow *ui;
    
    // Page widgets
    QWidget *projectsPage;
    QWidget *editorPage;
    QWidget *libraryPage;
    QWidget *settingsPage;
    QWidget *loginPage;
    
    // Animation objects
    QPropertyAnimation *pageTransitionAnimation;
    QParallelAnimationGroup *animationGroup;
    
    // Current page tracking
    int currentPageIndex;
};

#endif // MAINWINDOW_H
