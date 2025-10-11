#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QParallelAnimationGroup>
#include <QDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QLabel;
class QString;
class TemplateWidget;
class ClientWidget;
class SponsorWidget;
class RessourceWidget;
class ProjectWidget;
namespace employer {
class EmployerController;
class EmployerModel;
}

namespace Ui {
class MainWindow;
class LoginPage;
class Profile;
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
    void onAboutClicked();
    void onLoginClicked();
    
    // Dashboard animations
    void setupDashboardAnimations();
    
    // Login form navigation slots
    void showSignUpForm();
    void showLoginForm();
    void showForgotPasswordForm();
    
    // Profile management slots
    void validateAndSendResetLink();
    void onSaveProfileClicked();
    void onResetProfileClicked();
    
    // Login/Signup validation
    void validateAndLogin();
    void validateAndSignUp();
private:
    void setupPages();
    void setupLoginForms();
    void setupProfileWidget();
    void setupTemplateWidget();
    void setupClientWidget();
    void setupSponsorWidget();
    void setupRessourceWidget();
    void setupProjectWidget();
    void setupAnimations();
    void setupSidebarIcons();
    void setupCircularAvatar(QLabel* avatarLabel, const QString& initials);
    void setupEmployeeTable();
    void switchToPage(int pageIndex);
    void addButtonHoverEffect(QPushButton* button);
    void setupLoginFormConnections();
    void switchLoginFormWithAnimation(int formIndex);
    void showMainContent();
    void showLoginOverlay();
    void setActiveSidebarButton(QPushButton* activeButton);
    
    // Validation helper methods
    bool isValidEmail(const QString& email);
    bool isValidPassword(const QString& password);
    void showValidationError(const QString& message);
    void setFieldError(QLineEdit* field, bool hasError);
    void addInputFieldEnhancements(QLineEdit* field);
    
    Ui::MainWindow *ui;
    QPixmap legionPixmap;

    // Helper to scale legion pixmap proportionally into the label
    void updateLegionLogoScaled();
    
    // Page widgets (projectsPage removed to avoid conflicts with generated UI)
    // QWidget *projectsPage;  // Commented out - using mainwindow.ui pages instead
    QWidget *clientsPage;
    QWidget *resourcesPage;
    QWidget *sponsorsPage;
    QWidget *templatesPage;
    QWidget *shopPage;
    
    // Profile widget and UI
    QWidget *profileWidget;
    Ui::Profile *profileUI;
    
    // Template widget (TemplateWidget handles its own UI)
    TemplateWidget *templateWidget;
    
    // Client, Sponsor, Ressource, Project widgets
    ClientWidget *clientWidget;
    SponsorWidget *sponsorWidget;
    RessourceWidget *ressourceWidget;
    ProjectWidget *projectWidget;
    employer::EmployerModel *employerModel;
    employer::EmployerController *employerController;
    
    // Login page widget and auth stacked widget reference
    QWidget *loginPageWidget;
    QStackedWidget *authStackedWidget;
    Ui::LoginPage *loginUI;
    
    // Animation objects
    QPropertyAnimation *pageTransitionAnimation;
    QParallelAnimationGroup *animationGroup;
    QPropertyAnimation *loginFormTransitionAnimation;
    
    // Current page tracking
    int currentPageIndex;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // MAINWINDOW_H
