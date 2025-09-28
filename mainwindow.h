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
class QLineEdit;
class QCheckBox;
class QLabel;
class QString;

namespace Ui {
class MainWindow;
class LoginPage;
class Profile;
class SignUpPage;
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
    void onProfileClicked();
    void onProjectsClicked();
    void onClientsClicked();
    void onResourcesClicked();
    void onSponsorsClicked();
    void onTemplatesClicked();
    void onShopClicked();
    void onLoginClicked();
    
    
    void onSaveEmployee();
    void onCancelAddEmployee();
    void onEmployeeTableSelectionChanged();
    void onModifyEmployeeClicked();
    void onDeleteEmployeeClicked();
    
    
    void onSaveModify();
    void onCancelModify();
    
    
    void showSignUpForm();
    void showLoginForm();
    void showForgotPasswordForm();
    void openSignUpWindow();
    
    
    void onSaveProfileClicked();
    void onResetProfileClicked();
    
    
    void validateAndLogin();
    void validateAndSignUp();
    void validateAndSendResetLink();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void setupPages();
    void setupLoginForms();
    void setupAnimations();
    void setupSidebarIcons();
    void setupCircularAvatar(QLabel* avatarLabel, const QString& initials);
    void setupProfileWidget();
    void setupEmployeeTable();
    void switchToPage(int pageIndex);
    void addButtonHoverEffect(QPushButton* button);
    void setupLoginFormConnections();
    void switchLoginFormWithAnimation(int formIndex);
    void showMainContent();
    void showLoginOverlay();
    
    
    bool isValidEmail(const QString& email);
    bool isValidPassword(const QString& password);
    void showValidationError(const QString& message);
    void setFieldError(QLineEdit* field, bool hasError);
    void addInputFieldEnhancements(QLineEdit* field);
    
    Ui::MainWindow *ui;
    
    
    QWidget *projectsPage;
    QWidget *clientsPage;
    QWidget *resourcesPage;
    QWidget *sponsorsPage;
    QWidget *templatesPage;
    QWidget *shopPage;
    
    
    QWidget *profileWidget;
    Ui::Profile *profileUI;
    
    
    QMainWindow *loginPageWidget;
    QStackedWidget *authStackedWidget;
    Ui::LoginPage *loginUI;
    
    
    QMainWindow *signUpPageWidget;
    Ui::SignUpPage *signUpUI;
    
    
    QPropertyAnimation *pageTransitionAnimation;
    QParallelAnimationGroup *animationGroup;
    QPropertyAnimation *loginFormTransitionAnimation;
    
    
    int currentPageIndex;
};

#endif 

