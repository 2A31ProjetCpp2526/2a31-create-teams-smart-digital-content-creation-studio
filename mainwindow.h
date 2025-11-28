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
#include <QSize>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include "backend/employer.h"
#include "backend/project.h"
#include "backend/faceapi.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QLabel;
class QString;
class TemplateWidget;
class ClientWidget;
class SponsorWidget;
class SponsorWindow;
class RessourceWidget;
class ProjectWidget;
class Employer;
class OpenAIChatbot;
#if 0
class FaceRecognitionLogin;
#endif
class FaceRecognitionWidget;
class QTimer;

namespace Ui {
class MainWindow;
class LoginPage;
class Profile;
class EmployerForm;
class ProjectForm;
}
QT_END_NAMESPACE

// =============================================================================
// EmployerForm - Dialog for adding/editing employers
// =============================================================================
class EmployerForm : public QDialog
{
    Q_OBJECT

public:
    enum Mode
    {
        CreateMode,
        EditMode
    };

    explicit EmployerForm(QWidget *parent = nullptr);
    ~EmployerForm() override;

    void setMode(Mode mode);
    void setRecord(const Employer &record);
    Employer record() const;

    bool passwordProvided() const;
    QString rawPassword() const;

    void setErrorMessage(const QString &message);

protected:
    void accept() override;

private slots:
    void browseAvatar();
    void updateAvatarPreview(const QString &path);
    void clearErrorMessage();
    void onAddResourceClicked();
    void onRemoveResourceClicked();
    void onAddProjectClicked();
    void onRemoveProjectClicked();

private:
    bool validate(QString *message) const;
    void loadEmployerResources(qint64 employerId);
    void loadEmployerProjects(qint64 employerId);
    void refreshResourceList();
    void refreshProjectList();

    Mode m_mode { CreateMode };
    qint64 m_employerId { -1 };
    QVector<qint64> m_selectedResourceIds;
    QVector<qint64> m_selectedProjectIds;
    Ui::EmployerForm *ui;

    // Getters for resource and project data
public:
    QVector<qint64> selectedResourceIds() const { return m_selectedResourceIds; }
    void setSelectedResourceIds(const QVector<qint64>& ids) { m_selectedResourceIds = ids; }
    
    QVector<qint64> selectedProjectIds() const { return m_selectedProjectIds; }
    void setSelectedProjectIds(const QVector<qint64>& ids) { m_selectedProjectIds = ids; }
};

// =============================================================================
// ProjectForm - Dialog for adding/editing projects
// =============================================================================
class ProjectForm : public QDialog
{
    Q_OBJECT

public:
    enum Mode
    {
        CreateMode,
        EditMode
    };

    explicit ProjectForm(QWidget *parent = nullptr);
    ~ProjectForm() override;

    void setMode(Mode mode);
    void setRecord(const Project &record);
    Project record() const;

    void setErrorMessage(const QString &message);

protected:
    void accept() override;

private slots:
    void clearErrorMessage();

private:
    bool validate(QString *message) const;

    Mode m_mode { CreateMode };
    qint64 m_projectId { -1 };
    Ui::ProjectForm *ui;
};

// =============================================================================
// ResourceSelectionDialog - Dialog for selecting resources for employer
// =============================================================================
class ResourceSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResourceSelectionDialog(QWidget *parent = nullptr);
    ~ResourceSelectionDialog() override;

    // Set resources that are already assigned
    void setAssignedResources(const QVector<qint64>& resourceIds);
    
    // Get selected resource IDs
    QVector<qint64> selectedResourceIds() const;

private:
    void setupUi();
    void loadAllResources();
    
    QListWidget *resourceListWidget;
    QVector<qint64> m_assignedResourceIds;
};

// =============================================================================
// ProjectSelectionDialog - Dialog for selecting projects for employer
// =============================================================================
class ProjectSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectSelectionDialog(QWidget *parent = nullptr);
    ~ProjectSelectionDialog() override;

    // Set projects that are already assigned
    void setAssignedProjects(const QVector<qint64>& projectIds);
    
    // Get selected project IDs
    QVector<qint64> selectedProjectIds() const;

private:
    void setupUi();
    void loadAllProjects();
    
    QListWidget *projectListWidget;
    QVector<qint64> m_assignedProjectIds;
};

// =============================================================================
// EmployerUIHelper - Static UI utility methods
// =============================================================================
class EmployerUIHelper
{
public:
    // Table population
    static void populateTable(QTableWidget* table, const QVector<Employer>& records);
    
    // Selection helpers
    static qint64 getSelectedEmployerId(QTableWidget* table, bool* ok);
    static Employer getSelectedRecord(QTableWidget* table, const QVector<Employer>& cache, bool* ok);
    static void handleSelectionToggle(QTableWidget* table, QTableWidgetItem* item);
    static void updateButtonStates(QPushButton* modifyBtn, QPushButton* deleteBtn, QTableWidget* table);
    
    // Search and sort
    static QVector<Employer> searchRecords(const QVector<Employer>& records, const QString& query);
    static QVector<Employer> sortRecords(const QVector<Employer>& records);
    
    // Export helpers (CSV export removed - use PDF exporters instead from backend)

private:
    EmployerUIHelper() = delete; // Static class - no instances
};

// =============================================================================
// MainWindow - Main Application Window
// =============================================================================
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
    void onLoginBackClicked();
    
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
    
    // Employer management slots
    void onAddEmployerClicked();
    void onModifyEmployerClicked();
    void onDeleteEmployerClicked();
    void onExportEmployersClicked();
    void onSearchEmployersClicked();
    void onSearchInputChanged(const QString &text);
    void onSortEmployersClicked();
    void onStatisticsClicked();
    void onEmployeeTableSelectionChanged();
    void onEmployeeTableItemClicked(QTableWidgetItem *item);
    void onCancelSelectionClicked();
    
private:
    void setupPages();
    void setupLoginForms();
    void setupProfileWidget();
    void setupTemplateWidget();
    void setupClientWidget();
    void setupSponsorWidget();
    void setupRessourceWidget();
    void setupProjectWidget();
    void setupFaceRecognitionWidget();
    void setupAnimations();
    void setupSidebarIcons();
    void setupCircularAvatar(QLabel* avatarLabel, const QString& initials);
    void setupEmployeeTable();
    void switchToPage(int pageIndex);
    
    // User session helper
    void updateUserSessionDisplay();
    void addButtonHoverEffect(QPushButton* button);
    bool eventFilter(QObject *watched, QEvent *event) override;
    void setupLoginFormConnections();
    void switchLoginFormWithAnimation(int formIndex);
    void showMainContent();
    void showLoginOverlay();
    void setActiveSidebarButton(QPushButton* activeButton);
    
    // Validation helper methods
    bool isValidEmail(const QString& email);
    bool isValidPassword(const QString& password);
    void showValidationError(const QString& message);
    void showStyledValidationError(const QString& title, const QString& message);
    void setFieldError(QLineEdit* field, bool hasError);
    void addInputFieldEnhancements(QLineEdit* field);
    
    // Employer helper methods
    void loadEmployers();
    void updateEmployerButtonStates();
    
    // Chatbot slots
    void onChatbotSendClicked();
    void onChatbotClearClicked();
    void onChatbotHistoryClicked();
    void onChatbotResponseReceived(const QString &response);
    void onChatbotErrorOccurred(const QString &errorMessage);
    void onChatbotProcessingStatusChanged(bool isBusy);
    
    // Face Recognition AI slots (Local Offline)
    void onFaceLoginClicked();
    void onFaceEnrollmentClicked();
    void onFaceRecognitionStatusChanged(const QString &status);
    void onFaceDetected(const QImage &faceImage);
    void onFaceNotDetected();
    void onFaceProcessingError(const QString &error);
    void onFaceRecognitionCompleted(const FaceApi::CloudResult &result);
    
    Ui::MainWindow *ui;
    QPixmap legionPixmap;

    // Debounce timer for live search (search-as-you-type)
    QTimer *m_searchDebounceTimer = nullptr;

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
    SponsorWindow *sponsorWindow;
    RessourceWidget *ressourceWidget;
    ProjectWidget *projectWidget;
    QVector<Employer> cachedEmployers;
    
    // Chatbot
    OpenAIChatbot *chatbot;
    // Face recognition API client
    FaceApi::Client *faceApiClient;
    // Face recognition widget (Real-time camera)
    FaceRecognitionWidget *faceRecognitionWidget;
    
    // Login page widget and auth stacked widget reference
    QWidget *loginPageWidget;
    QStackedWidget *authStackedWidget;
    Ui::LoginPage *loginUI;
    
    // Current connected user
    int currentConnectedEmployeeId = -1;
    QString currentConnectedUserRole = "";
    QString currentConnectedUserName = "";
    
    // Animation objects
    QPropertyAnimation *pageTransitionAnimation;
    QParallelAnimationGroup *animationGroup;
    QPropertyAnimation *loginFormTransitionAnimation;
    
    // Access control helper
    bool checkAdminAccess(const QString &actionName);
    
    // Current page tracking
    int currentPageIndex;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // MAINWINDOW_H
