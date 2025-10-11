#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_login.h"
#include "ui_Profile.h"

#include "clientwidget.h"
#include "projectwidget.h"
#include "ressourcewidget.h"
#include "sponsorwidget.h"
#include "templatewidget.h"

#include "src/modules/employer/databasemanager.h"
#include "src/modules/employer/employercontroller.h"
#include "src/modules/employer/employermodel.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QGraphicsOpacityEffect>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRegularExpression>
#include <QResizeEvent>
#include <QSize>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QEasingCurve>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientsPage(nullptr)
    , resourcesPage(nullptr)
    , sponsorsPage(nullptr)
    , templatesPage(nullptr)
    , shopPage(nullptr)
    , profileWidget(nullptr)
    , profileUI(nullptr)
    , templateWidget(nullptr)
    , clientWidget(nullptr)
    , sponsorWidget(nullptr)
    , ressourceWidget(nullptr)
    , projectWidget(nullptr)
    , employerModel(nullptr)
    , employerController(nullptr)
    , loginPageWidget(nullptr)
    , authStackedWidget(nullptr)
    , loginUI(nullptr)
    , pageTransitionAnimation(nullptr)
    , animationGroup(nullptr)
    , loginFormTransitionAnimation(nullptr)
    , currentPageIndex(-1)
{
    ui->setupUi(this);

    legionPixmap = QPixmap(QStringLiteral(":/images/legion.png"));
    updateLegionLogoScaled();

    setupSidebarIcons();

    connect(ui->employerBtn, &QPushButton::clicked, this, &MainWindow::onDashboardClicked);
    connect(ui->profileBtn, &QPushButton::clicked, this, &MainWindow::onProfileClicked);
    connect(ui->projectsBtn, &QPushButton::clicked, this, &MainWindow::onProjectsClicked);
    connect(ui->clientsBtn, &QPushButton::clicked, this, &MainWindow::onClientsClicked);
    connect(ui->resourcesBtn, &QPushButton::clicked, this, &MainWindow::onResourcesClicked);
    connect(ui->sponsorsBtn, &QPushButton::clicked, this, &MainWindow::onSponsorsClicked);
    connect(ui->templatesBtn, &QPushButton::clicked, this, &MainWindow::onTemplatesClicked);
    connect(ui->shopBtn, &QPushButton::clicked, this, &MainWindow::onAboutClicked);
    connect(ui->loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    setupPages();
    setupProfileWidget();
    setupTemplateWidget();
    setupClientWidget();
    setupSponsorWidget();
    setupRessourceWidget();
    setupProjectWidget();
    setupAnimations();
    setupDashboardAnimations();

    addButtonHoverEffect(ui->employerBtn);
    addButtonHoverEffect(ui->profileBtn);
    addButtonHoverEffect(ui->projectsBtn);
    addButtonHoverEffect(ui->clientsBtn);
    addButtonHoverEffect(ui->resourcesBtn);
    addButtonHoverEffect(ui->sponsorsBtn);
    addButtonHoverEffect(ui->templatesBtn);
    addButtonHoverEffect(ui->shopBtn);
    addButtonHoverEffect(ui->loginBtn);

    employer::DatabaseManager::instance().configure(QStringLiteral("OracleQt"), QStringLiteral("system"), QStringLiteral("123456789"));
    employerModel = new employer::EmployerModel(this, employer::DatabaseManager::instance().database());
    employerController = new employer::EmployerController(
        employerModel,
        ui->employeeTable,
        ui->saveEmployeeBtn,
        ui->modifyBtn,
        ui->deleteBtn,
        ui->exportBtn,
        ui->searchInput,
        ui->searchBtn,
        ui->sortBtn,
        this);

    connect(ui->saveEmployeeBtn, &QPushButton::clicked, employerController, &employer::EmployerController::openAddDialog);
    connect(ui->employeeTable, &QTableWidget::itemSelectionChanged, employerController, &employer::EmployerController::updateSelectionState);
    connect(ui->employeeTable, &QTableWidget::itemClicked, employerController, &employer::EmployerController::handleSelectionToggle);
    connect(ui->modifyBtn, &QPushButton::clicked, employerController, &employer::EmployerController::openModifyDialog);
    connect(ui->deleteBtn, &QPushButton::clicked, employerController, &employer::EmployerController::removeSelectedEmployer);
    connect(ui->exportBtn, &QPushButton::clicked, employerController, &employer::EmployerController::exportEmployers);
    connect(ui->searchBtn, &QPushButton::clicked, employerController, &employer::EmployerController::runSearch);
    connect(ui->searchInput, &QLineEdit::returnPressed, employerController, &employer::EmployerController::runSearch);
    connect(ui->sortBtn, &QPushButton::clicked, employerController, &employer::EmployerController::runSort);

    connect(ui->cancelBtn, &QPushButton::clicked, this, [this]() {
        if (ui->employeeTable) {
            ui->employeeTable->clearSelection();
        }
        if (employerController) {
            employerController->updateSelectionState();
        }
    });

    if (!employerController->initialize())
    {
        QMessageBox::warning(this,
                             tr("Employer Module"),
                             tr("Failed to initialize the employer module. Verify the Oracle DSN 'OracleQt'."));
    }

    if (ui->modifyBtn) {
        ui->modifyBtn->setEnabled(false);
    }
    if (ui->deleteBtn) {
        ui->deleteBtn->setEnabled(false);
    }

    ui->stackedWidget->setCurrentIndex(0);
    setActiveSidebarButton(ui->employerBtn);
    currentPageIndex = 0;
}

MainWindow::~MainWindow()
{
    delete profileUI;
    delete loginUI;
    delete ui;
}

void MainWindow::setupPages()
{
    // Initialize basic page widgets if needed
    // Pages are now primarily handled through the UI file
    
    // Setup employee table
    setupEmployeeTable();
    
    // Setup login forms in the main window overlay
    setupLoginForms();
}

void MainWindow::setupLoginForms()
{
    // Create login page widget and setup its UI directly in the main authStackedWidget
    loginPageWidget = new QWidget();
    loginUI = new Ui::LoginPage();
    loginUI->setupUi(loginPageWidget);
    
    // Add the login page widget to the main window's authStackedWidget
    ui->authStackedWidget->addWidget(loginPageWidget);
    
    // Use the main window's authStackedWidget (not the nested one from login.ui)
    authStackedWidget = ui->authStackedWidget;
    
    // Set to show the login page by default
    authStackedWidget->setCurrentIndex(0);
    
    // Setup form connections
    setupLoginFormConnections();
}

void MainWindow::setupProfileWidget()
{
    // Create Profile widget and set up its UI
    profileWidget = new QWidget();
    profileUI = new Ui::Profile();
    profileUI->setupUi(profileWidget);
    
    // Replace the placeholder Profile page in the stacked widget
    QWidget* profilePlaceholder = ui->stackedWidget->widget(1); // Profile is at index 1
    if (profilePlaceholder) {
        ui->stackedWidget->removeWidget(profilePlaceholder);
        ui->stackedWidget->insertWidget(1, profileWidget);
        delete profilePlaceholder;
    }
    
    // Connect Profile form buttons to slots
    connect(profileUI->saveProfileButton, &QPushButton::clicked, this, &MainWindow::onSaveProfileClicked);
    connect(profileUI->resetProfileButton, &QPushButton::clicked, this, &MainWindow::onResetProfileClicked);
    
    // Load default profile data
    profileUI->usernameEdit->setText("John Doe");
    profileUI->emailEdit->setText("john.doe@aminetemplate.com");
}

void MainWindow::setupTemplateWidget()
{
    // Create Template widget using the TemplateWidget class
    templateWidget = new TemplateWidget();
    
    // Find which stacked widget page contains the template container
    int templatePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("templateContainer")) {
            templatePageIndex = i;
            break;
        }
    }
    
    if (templatePageIndex != -1) {
        // Replace the placeholder Template page in the stacked widget
        QWidget* templatePlaceholder = ui->stackedWidget->widget(templatePageIndex);
        if (templatePlaceholder) {
            ui->stackedWidget->removeWidget(templatePlaceholder);
            ui->stackedWidget->insertWidget(templatePageIndex, templateWidget);
            delete templatePlaceholder;
        }
    }
}

void MainWindow::setupClientWidget()
{
    // Create Client widget using the ClientWidget class
    clientWidget = new ClientWidget();
    
    // Find which stacked widget page contains the client container
    int clientPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("clientContainer")) {
            clientPageIndex = i;
            break;
        }
    }
    
    if (clientPageIndex != -1) {
        // Replace the placeholder Client page in the stacked widget (same method as Template)
        QWidget* clientPlaceholder = ui->stackedWidget->widget(clientPageIndex);
        if (clientPlaceholder) {
            ui->stackedWidget->removeWidget(clientPlaceholder);
            ui->stackedWidget->insertWidget(clientPageIndex, clientWidget);
            delete clientPlaceholder;
        }
    }
}

void MainWindow::setupSponsorWidget()
{
    // Create Sponsor widget using the SponsorWidget class
    sponsorWidget = new SponsorWidget();
    
    // Find which stacked widget page contains the sponsor container
    int sponsorPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("sponsorContainer")) {
            sponsorPageIndex = i;
            break;
        }
    }
    
    if (sponsorPageIndex != -1) {
        // Replace the placeholder Sponsor page in the stacked widget (same method as Template)
        QWidget* sponsorPlaceholder = ui->stackedWidget->widget(sponsorPageIndex);
        if (sponsorPlaceholder) {
            ui->stackedWidget->removeWidget(sponsorPlaceholder);
            ui->stackedWidget->insertWidget(sponsorPageIndex, sponsorWidget);
            delete sponsorPlaceholder;
        }
    }
}

void MainWindow::setupRessourceWidget()
{
    // Create Ressource widget using the RessourceWidget class
    ressourceWidget = new RessourceWidget();
    
    // Find which stacked widget page contains the ressource container
    int ressourcePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("ressourceContainer")) {
            ressourcePageIndex = i;
            break;
        }
    }
    
    if (ressourcePageIndex != -1) {
        // Replace the placeholder Ressource page in the stacked widget (same method as Template)
        QWidget* ressourcePlaceholder = ui->stackedWidget->widget(ressourcePageIndex);
        if (ressourcePlaceholder) {
            ui->stackedWidget->removeWidget(ressourcePlaceholder);
            ui->stackedWidget->insertWidget(ressourcePageIndex, ressourceWidget);
            delete ressourcePlaceholder;
        }
    }
}

void MainWindow::setupProjectWidget()
{
    // Create Project widget using the ProjectWidget class
    projectWidget = new ProjectWidget();
    
    // Find which stacked widget page contains the project container
    int projectPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* page = ui->stackedWidget->widget(i);
        if (page && page->findChild<QWidget*>("projectContainer")) {
            projectPageIndex = i;
            break;
        }
    }
    
    if (projectPageIndex != -1) {
        // Replace the placeholder Project page in the stacked widget (same method as Template)
        QWidget* projectPlaceholder = ui->stackedWidget->widget(projectPageIndex);
        if (projectPlaceholder) {
            ui->stackedWidget->removeWidget(projectPlaceholder);
            ui->stackedWidget->insertWidget(projectPageIndex, projectWidget);
            delete projectPlaceholder;
        }
    }
}

void MainWindow::setupAnimations()
{
    pageTransitionAnimation = new QPropertyAnimation(this);
    pageTransitionAnimation->setDuration(250);
    pageTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    animationGroup = new QParallelAnimationGroup(this);
    
    // Create login form transition animation
    loginFormTransitionAnimation = new QPropertyAnimation(this);
    loginFormTransitionAnimation->setDuration(300);
    loginFormTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void MainWindow::updateLegionLogoScaled()
{
    if (legionPixmap.isNull() || !ui->legionLogo) return;

    // Determine available width inside the legionLogo label accounting for padding/margins
    int maxW = ui->legionLogo->maximumWidth();
    int maxH = ui->legionLogo->maximumHeight();

    // If maximums are large, instead use current label width (so it scales with layout)
    if (maxW <= 0 || maxW > 1000) maxW = ui->legionLogo->width();
    if (maxH <= 0 || maxH > 1000) maxH = ui->legionLogo->height();

    QSize targetSize = legionPixmap.size();
    targetSize.scale(maxW, maxH, Qt::KeepAspectRatio);

    QPixmap scaled = legionPixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->legionLogo->setPixmap(scaled);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    // Update legion logo scaling on window resize to maintain aspect ratio and prevent distortion
    if (!legionPixmap.isNull()) {
        updateLegionLogoScaled();
    }
}

void MainWindow::switchToPage(int pageIndex)
{
    if (pageIndex == currentPageIndex) return;
    
    currentPageIndex = pageIndex;
    
    // Simple fade transition
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
    ui->stackedWidget->setGraphicsEffect(effect);
    
    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(125);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.3);
    
    QPropertyAnimation *fadeIn = new QPropertyAnimation(effect, "opacity");
    fadeIn->setDuration(125);
    fadeIn->setStartValue(0.3);
    fadeIn->setEndValue(1.0);
    
    connect(fadeOut, &QPropertyAnimation::finished, [this, pageIndex, fadeIn]() {
        ui->stackedWidget->setCurrentIndex(pageIndex);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    });
    
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::addButtonHoverEffect(QPushButton* button)
{
    // Basic hover effect - more complex animations can be added later
    button->setCursor(Qt::PointingHandCursor);
}

void MainWindow::onDashboardClicked()
{
    setActiveSidebarButton(ui->employerBtn);
    switchToPage(0); // Dashboard is at index 0
}

void MainWindow::onProfileClicked()
{
    setActiveSidebarButton(ui->profileBtn);
    switchToPage(1); // Profile is at index 1
}

void MainWindow::onProjectsClicked()
{
    setActiveSidebarButton(ui->projectsBtn);
    // Find which stacked widget page contains the project widget
    int projectPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == projectWidget) {
            projectPageIndex = i;
            break;
        }
    }
    
    if (projectPageIndex != -1) {
        switchToPage(projectPageIndex); // Switch to the project page
    }
}

void MainWindow::onClientsClicked()
{
    setActiveSidebarButton(ui->clientsBtn);
    // Find which stacked widget page contains the client widget
    int clientPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == clientWidget) {
            clientPageIndex = i;
            break;
        }
    }
    
    if (clientPageIndex != -1) {
        switchToPage(clientPageIndex); // Switch to the client page
    }
}

void MainWindow::onResourcesClicked()
{
    setActiveSidebarButton(ui->resourcesBtn);
    // Find which stacked widget page contains the ressource widget
    int ressourcePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == ressourceWidget) {
            ressourcePageIndex = i;
            break;
        }
    }
    
    if (ressourcePageIndex != -1) {
        switchToPage(ressourcePageIndex); // Switch to the ressource page
    }
}

void MainWindow::onSponsorsClicked()
{
    setActiveSidebarButton(ui->sponsorsBtn);
    // Find which stacked widget page contains the sponsor widget
    int sponsorPageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == sponsorWidget) {
            sponsorPageIndex = i;
            break;
        }
    }
    
    if (sponsorPageIndex != -1) {
        switchToPage(sponsorPageIndex); // Switch to the sponsor page
    }
}

void MainWindow::onTemplatesClicked()
{
    setActiveSidebarButton(ui->templatesBtn);
    // Find which stacked widget page contains the template widget
    int templatePageIndex = -1;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == templateWidget) {
            templatePageIndex = i;
            break;
        }
    }
    
    if (templatePageIndex != -1) {
        switchToPage(templatePageIndex); // Switch to the template page (index 7)
    }
}

void MainWindow::onAboutClicked()
{
    setActiveSidebarButton(ui->shopBtn);
    // About page is at index 9 in the stackedWidget
    switchToPage(9);
}

void MainWindow::onLoginClicked()
{
    // Switch to login overlay instead of a page
    ui->mainStackedWidget->setCurrentIndex(1); // Show loginOverlayPage
    ui->authStackedWidget->setCurrentIndex(0); // Show login form
}

void MainWindow::showMainContent()
{
    // Switch back to normal content
    ui->mainStackedWidget->setCurrentIndex(0); // Show normalContentPage
}

void MainWindow::showLoginOverlay()
{
    // Switch to login overlay
    ui->mainStackedWidget->setCurrentIndex(1); // Show loginOverlayPage
    if (authStackedWidget) {
        authStackedWidget->setCurrentIndex(0); // Show login form
    }
}

void MainWindow::setupLoginFormConnections()
{
    if (!authStackedWidget || !loginPageWidget) return;
    
    // Find and connect Sign Up navigation button on login form
    QPushButton* signUpNavButton = loginPageWidget->findChild<QPushButton*>("signUpNavButton");
    if (signUpNavButton) {
        connect(signUpNavButton, &QPushButton::clicked, this, &MainWindow::showSignUpForm);
        addButtonHoverEffect(signUpNavButton);
    }
    
    // Find and connect Forgot Password navigation button on login form
    QPushButton* forgotPasswordNavButton = loginPageWidget->findChild<QPushButton*>("forgotPasswordNavButton");
    if (forgotPasswordNavButton) {
        connect(forgotPasswordNavButton, &QPushButton::clicked, this, &MainWindow::showForgotPasswordForm);
        addButtonHoverEffect(forgotPasswordNavButton);
    }
    
    // Find and connect back to login buttons
    QPushButton* backToLoginFromSignUpButton = loginPageWidget->findChild<QPushButton*>("backToLoginFromSignUpButton");
    if (backToLoginFromSignUpButton) {
        connect(backToLoginFromSignUpButton, &QPushButton::clicked, this, &MainWindow::showLoginForm);
        addButtonHoverEffect(backToLoginFromSignUpButton);
    }
    
    QPushButton* backToLoginFromForgotButton = loginPageWidget->findChild<QPushButton*>("backToLoginFromForgotButton");
    if (backToLoginFromForgotButton) {
        connect(backToLoginFromForgotButton, &QPushButton::clicked, this, &MainWindow::showLoginForm);
        addButtonHoverEffect(backToLoginFromForgotButton);
    }
    
    // Connect form submission buttons to validation functions
    QPushButton* loginButton = loginPageWidget->findChild<QPushButton*>("loginButton");
    if (loginButton) {
        connect(loginButton, &QPushButton::clicked, this, &MainWindow::validateAndLogin);
        addButtonHoverEffect(loginButton);
    }
    
    QPushButton* signUpButton = loginPageWidget->findChild<QPushButton*>("signUpButton");
    if (signUpButton) {
        connect(signUpButton, &QPushButton::clicked, this, &MainWindow::validateAndSignUp);
        addButtonHoverEffect(signUpButton);
    }
    
    QPushButton* sendResetLinkButton = loginPageWidget->findChild<QPushButton*>("sendResetLinkButton");
    if (sendResetLinkButton) {
        connect(sendResetLinkButton, &QPushButton::clicked, this, &MainWindow::validateAndSendResetLink);
        addButtonHoverEffect(sendResetLinkButton);
    }
    
    // Connect Face Login button
    QPushButton* faceLoginButton = loginPageWidget->findChild<QPushButton*>("faceLoginButton");
    if (faceLoginButton) {
        connect(faceLoginButton, &QPushButton::clicked, this, [this]() {
            QMessageBox::information(this, "Face Login", "Face login coming soon!\n\nThis feature will use advanced facial recognition technology for secure authentication.");
        });
        addButtonHoverEffect(faceLoginButton);
    }
    
    // Enhance input fields with better focus effects
    QLineEdit* loginEmailField = loginPageWidget->findChild<QLineEdit*>("loginEmailLineEdit");
    QLineEdit* loginPasswordField = loginPageWidget->findChild<QLineEdit*>("loginPasswordLineEdit");
    QLineEdit* fullNameField = loginPageWidget->findChild<QLineEdit*>("fullNameLineEdit");
    QLineEdit* signUpEmailField = loginPageWidget->findChild<QLineEdit*>("signUpEmailLineEdit");
    QLineEdit* signUpPasswordField = loginPageWidget->findChild<QLineEdit*>("signUpPasswordLineEdit");
    QLineEdit* confirmPasswordField = loginPageWidget->findChild<QLineEdit*>("confirmPasswordLineEdit");
    QLineEdit* resetEmailField = loginPageWidget->findChild<QLineEdit*>("resetEmailLineEdit");
    
    if (loginEmailField) addInputFieldEnhancements(loginEmailField);
    if (loginPasswordField) addInputFieldEnhancements(loginPasswordField);
    if (fullNameField) addInputFieldEnhancements(fullNameField);
    if (signUpEmailField) addInputFieldEnhancements(signUpEmailField);
    if (signUpPasswordField) addInputFieldEnhancements(signUpPasswordField);
    if (confirmPasswordField) addInputFieldEnhancements(confirmPasswordField);
    if (resetEmailField) addInputFieldEnhancements(resetEmailField);
}

void MainWindow::switchLoginFormWithAnimation(int formIndex)
{
    if (!loginUI || !loginPageWidget) return;
    
    // Get the nested authStackedWidget from the login.ui
    QStackedWidget* loginStackedWidget = loginPageWidget->findChild<QStackedWidget*>("authStackedWidget");
    if (!loginStackedWidget) return;
    
    // Get current and target widgets
    QWidget* currentWidget = loginStackedWidget->currentWidget();
    QWidget* targetWidget = loginStackedWidget->widget(formIndex);
    
    if (currentWidget == targetWidget) return;
    
    // Create fade out animation for current widget
    QGraphicsOpacityEffect* currentEffect = new QGraphicsOpacityEffect(currentWidget);
    currentWidget->setGraphicsEffect(currentEffect);
    
    QPropertyAnimation* fadeOut = new QPropertyAnimation(currentEffect, "opacity");
    fadeOut->setDuration(150);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->setEasingCurve(QEasingCurve::OutCubic);
    
    // Create fade in animation for target widget
    QGraphicsOpacityEffect* targetEffect = new QGraphicsOpacityEffect(targetWidget);
    targetWidget->setGraphicsEffect(targetEffect);
    
    QPropertyAnimation* fadeIn = new QPropertyAnimation(targetEffect, "opacity");
    fadeIn->setDuration(150);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::InCubic);
    
    // Connect fade out finished to start fade in
    connect(fadeOut, &QPropertyAnimation::finished, [=]() {
        loginStackedWidget->setCurrentIndex(formIndex);
        fadeIn->start();
        // Clean up fade out effect
        currentWidget->setGraphicsEffect(nullptr);
        fadeOut->deleteLater();
    });
    
    // Connect fade in finished to clean up
    connect(fadeIn, &QPropertyAnimation::finished, [=]() {
        targetWidget->setGraphicsEffect(nullptr);
        fadeIn->deleteLater();
    });
    
    // Start the fade out animation
    fadeOut->start();
}

void MainWindow::showLoginForm()
{
    switchLoginFormWithAnimation(0); // Login form page
}

void MainWindow::showSignUpForm()
{
    switchLoginFormWithAnimation(1); // Sign up form page
}

void MainWindow::showForgotPasswordForm()
{
    switchLoginFormWithAnimation(2); // Forgot password form page
}

void MainWindow::addInputFieldEnhancements(QLineEdit* field)
{
    if (!field) return;
    
    // Simply enhance the existing styles with better focus effects
    field->setStyleSheet(R"(
        QLineEdit {
            padding: 12px 16px;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            background-color: #ffffff;
            color: #495057;
            font-weight: 300;
            letter-spacing: 0.5px;
            transition: all 0.3s ease;
        }
        QLineEdit:focus {
            border: 2px solid #007bff;
            background-color: #f8f9fa;
            outline: none;
        }
        QLineEdit:hover {
            border-color: #adb5bd;
            background-color: #f8f9fa;
        }
    )");
}

// Validation helper methods
bool MainWindow::isValidEmail(const QString& email)
{
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

bool MainWindow::isValidPassword(const QString& password)
{
    // Password must be at least 8 characters and contain at least one number or special character
    if (password.length() < 8) return false;
    
    QRegularExpression hasNumberOrSpecial(R"([0-9!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?])");
    return hasNumberOrSpecial.match(password).hasMatch();
}

void MainWindow::showValidationError(const QString& message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Validation Error");
    msgBox.setText(message);
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #ffffff;
            color: #343a40;
            font-family: 'Poppins';
            font-size: 12px;
        }
        QMessageBox QPushButton {
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: 300;
            min-width: 60px;
        }
        QMessageBox QPushButton:hover {
            background-color: #0056b3;
        }
    )");
    msgBox.exec();
}

void MainWindow::setFieldError(QLineEdit* field, bool hasError)
{
    if (!field) return;
    
    if (hasError) {
        field->setStyleSheet(R"(
            QLineEdit {
                padding: 12px 16px;
                border: 2px solid #dc3545;
                border-radius: 8px;
                background-color: #fff5f5;
                color: #495057;
                font-weight: 300;
                letter-spacing: 0.5px;
            }
            QLineEdit:focus {
                border-color: #dc3545;
                outline: none;
            }
        )");
    } else {
        field->setStyleSheet(R"(
            QLineEdit {
                padding: 12px 16px;
                border: 1px solid #dee2e6;
                border-radius: 8px;
                background-color: #ffffff;
                color: #495057;
                font-weight: 300;
                letter-spacing: 0.5px;
            }
            QLineEdit:focus {
                border-color: #007bff;
                outline: none;
            }
            QLineEdit:hover {
                border-color: #adb5bd;
            }
        )");
    }
}

// Form validation methods
void MainWindow::validateAndLogin()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("loginEmailLineEdit");
    QLineEdit* passwordField = loginPageWidget->findChild<QLineEdit*>("loginPasswordLineEdit");
    
    if (!emailField || !passwordField) return;
    
    QString email = emailField->text().trimmed();
    QString password = passwordField->text();
    
    bool hasErrors = false;
    
    // Validate email
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        showValidationError("Please enter your email or username.");
        hasErrors = true;
    } else if (!isValidEmail(email) && !email.contains(QRegularExpression("^[a-zA-Z0-9_]+$"))) {
        setFieldError(emailField, true);
        showValidationError("Please enter a valid email address or username.");
        hasErrors = true;
    } else {
        setFieldError(emailField, false);
    }
    
    // Validate password
    if (password.isEmpty()) {
        setFieldError(passwordField, true);
        if (!hasErrors) showValidationError("Please enter your password.");
        hasErrors = true;
    } else {
        setFieldError(passwordField, false);
    }
    
    if (!hasErrors) {
        // Successfully validated - redirect to main content
        showMainContent();
        // Switch to Employer (Dashboard) page by default
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::validateAndSignUp()
{
    QLineEdit* nameField = loginPageWidget->findChild<QLineEdit*>("fullNameLineEdit");
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("signUpEmailLineEdit");
    QLineEdit* passwordField = loginPageWidget->findChild<QLineEdit*>("signUpPasswordLineEdit");
    QLineEdit* confirmPasswordField = loginPageWidget->findChild<QLineEdit*>("confirmPasswordLineEdit");
    QCheckBox* termsCheckBox = loginPageWidget->findChild<QCheckBox*>("acceptTermsCheckBox");
    
    if (!nameField || !emailField || !passwordField || !confirmPasswordField || !termsCheckBox) return;
    
    QString name = nameField->text().trimmed();
    QString email = emailField->text().trimmed();
    QString password = passwordField->text();
    QString confirmPassword = confirmPasswordField->text();
    
    bool hasErrors = false;
    QString errorMessage;
    
    // Validate full name
    if (name.isEmpty()) {
        setFieldError(nameField, true);
        errorMessage = "Please enter your full name.";
        hasErrors = true;
    } else if (name.length() < 2) {
        setFieldError(nameField, true);
        errorMessage = "Full name must be at least 2 characters long.";
        hasErrors = true;
    } else {
        setFieldError(nameField, false);
    }
    
    // Validate email
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please enter your email address.";
        hasErrors = true;
    } else if (!isValidEmail(email)) {
        setFieldError(emailField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please enter a valid email address.";
        hasErrors = true;
    } else {
        setFieldError(emailField, false);
    }
    
    // Validate password
    if (password.isEmpty()) {
        setFieldError(passwordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please enter a password.";
        hasErrors = true;
    } else if (!isValidPassword(password)) {
        setFieldError(passwordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Password must be at least 8 characters long and contain at least one number or special character.";
        hasErrors = true;
    } else {
        setFieldError(passwordField, false);
    }
    
    // Validate confirm password
    if (confirmPassword.isEmpty()) {
        setFieldError(confirmPasswordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Please confirm your password.";
        hasErrors = true;
    } else if (password != confirmPassword) {
        setFieldError(confirmPasswordField, true);
        if (errorMessage.isEmpty()) errorMessage = "Passwords do not match.";
        hasErrors = true;
    } else {
        setFieldError(confirmPasswordField, false);
    }
    
    // Validate terms acceptance
    if (!termsCheckBox->isChecked()) {
        if (errorMessage.isEmpty()) errorMessage = "Please accept the terms and conditions.";
        hasErrors = true;
    }
    
    if (hasErrors) {
        showValidationError(errorMessage);
    } else {
        // TODO: Implement actual sign up logic here
        showValidationError("Sign up functionality not implemented yet.\nThis would create a new user account.");
    }
}

void MainWindow::validateAndSendResetLink()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("resetEmailLineEdit");
    
    if (!emailField) return;
    
    QString email = emailField->text().trimmed();
    
    // Validate email
    if (email.isEmpty()) {
        setFieldError(emailField, true);
        showValidationError("Please enter your email address or username.");
    } else if (!isValidEmail(email) && !email.contains(QRegularExpression("^[a-zA-Z0-9_]+$"))) {
        setFieldError(emailField, true);
        showValidationError("Please enter a valid email address or username.");
    } else {
        setFieldError(emailField, false);
        // Show success message and return to login form
        QMessageBox::information(this, "Password Reset", "If an account with this email exists, a password reset link has been sent.\n\nPlease check your email and follow the instructions to reset your password.");
        showLoginForm(); // Return to login form
    }
}

void MainWindow::setupSidebarIcons()
{
    // Set up icons for each sidebar button using SVG resources
    if (ui->employerBtn) {
        ui->employerBtn->setIcon(QIcon(":/resources/icons/employer.svg"));
        ui->employerBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->profileBtn) {
        ui->profileBtn->setIcon(QIcon(":/resources/icons/profile.svg"));
        ui->profileBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->projectsBtn) {
        ui->projectsBtn->setIcon(QIcon(":/resources/icons/projects.svg"));
        ui->projectsBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->clientsBtn) {
        ui->clientsBtn->setIcon(QIcon(":/resources/icons/clients.svg"));
        ui->clientsBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->resourcesBtn) {
        ui->resourcesBtn->setIcon(QIcon(":/resources/icons/library.svg"));
        ui->resourcesBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->sponsorsBtn) {
        ui->sponsorsBtn->setIcon(QIcon(":/resources/icons/star.svg"));
        ui->sponsorsBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->templatesBtn) {
        ui->templatesBtn->setIcon(QIcon(":/resources/icons/display.svg"));
        ui->templatesBtn->setIconSize(QSize(20, 20));
    }
    
    if (ui->shopBtn) {
        ui->shopBtn->setIcon(QIcon(":/resources/icons/shop.svg"));
        ui->shopBtn->setIconSize(QSize(20, 20));
    }
}

void MainWindow::setActiveSidebarButton(QPushButton* activeButton)
{
    // List of all sidebar buttons
    QList<QPushButton*> sidebarButtons = {
        ui->employerBtn,
        ui->profileBtn,
        ui->projectsBtn,
        ui->clientsBtn,
        ui->resourcesBtn,
        ui->sponsorsBtn,
        ui->templatesBtn,
        ui->shopBtn
    };
    
    // Reset all buttons to inactive state
    for (QPushButton* btn : sidebarButtons) {
        if (btn) {
            btn->setChecked(false);
            btn->setProperty("active", false);
            // Force style refresh
            btn->style()->unpolish(btn);
            btn->style()->polish(btn);
            btn->update();
        }
    }
    
    // Set the active button
    if (activeButton) {
        activeButton->setChecked(true);
        activeButton->setProperty("active", true);
        // Force style refresh for active button
        activeButton->style()->unpolish(activeButton);
        activeButton->style()->polish(activeButton);
        activeButton->update();
    }
}

void MainWindow::setupCircularAvatar(QLabel* avatarLabel, const QString& initials)
{
    if (!avatarLabel) return;
    
    // Set circular avatar styling
    avatarLabel->setStyleSheet(
        "QLabel { "
        "    background-color: #007bff; "
        "    color: white; "
        "    border-radius: 20px; "
        "    font-size: 14px; "
        "    font-weight: 500; "
        "    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif; "
        "    text-align: center; "
        "}"
    );
    
    avatarLabel->setText(initials);
    avatarLabel->setAlignment(Qt::AlignCenter);
    
    // Ensure it's always circular
    avatarLabel->setMinimumSize(40, 40);
    avatarLabel->setMaximumSize(40, 40);
    avatarLabel->setScaledContents(true);
}

// Profile management slot implementations
void MainWindow::onSaveProfileClicked()
{
    // Validate profile information
    QString fullName = profileUI->usernameEdit->text().trimmed();
    QString email = profileUI->emailEdit->text().trimmed();
    QString password = profileUI->currentPasswordEdit->text();
    
    // Basic validation
    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Full name is required.");
        profileUI->usernameEdit->setFocus();
        return;
    }
    
    if (email.isEmpty() || !isValidEmail(email)) {
        QMessageBox::warning(this, "Validation Error", "Please enter a valid email address.");
        profileUI->emailEdit->setFocus();
        return;
    }
    
    // Here you would typically save to database or settings
    // For now, just show a success message
    QMessageBox::information(this, "Profile Saved", "Your profile information has been saved successfully!");
}

void MainWindow::onResetProfileClicked()
{
    // Reset profile form to default values
    profileUI->usernameEdit->setText("John Doe");
    profileUI->emailEdit->setText("john.doe@aminetemplate.com");
    profileUI->currentPasswordEdit->clear();
    
    QMessageBox::information(this, "Profile Reset", "Profile information has been reset to default values.");
}

void MainWindow::setupEmployeeTable()
{
    // Set specific column widths for better layout with more space since Actions column removed
    ui->employeeTable->setColumnWidth(0, 90);  // Select column
    ui->employeeTable->setColumnWidth(1, 100); // Avatar column
    ui->employeeTable->setColumnWidth(2, 90);  // ID column  
    ui->employeeTable->setColumnWidth(3, 220); // Name column (more space)
    ui->employeeTable->setColumnWidth(4, 280); // Email column (more space)
    ui->employeeTable->setColumnWidth(5, 150); // Role column (more space)
    ui->employeeTable->setColumnWidth(6, 180); // Phone column (more space)
    ui->employeeTable->setColumnWidth(7, 150); // Start Date column
    
    // Ensure the table rows have the proper height
    ui->employeeTable->verticalHeader()->setDefaultSectionSize(90);
    ui->employeeTable->verticalHeader()->setMinimumSectionSize(90);
    
    // Enable better selection behavior
    ui->employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // Center align headers
    for (int i = 0; i < ui->employeeTable->columnCount(); ++i) {
        QTableWidgetItem* headerItem = ui->employeeTable->horizontalHeaderItem(i);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindow::setupDashboardAnimations()
{
    // Fade in the dashboard title and statistics container
    if (ui->dashboardTabTitle) {
        QPropertyAnimation* titleFade = new QPropertyAnimation(ui->dashboardTabTitle, "windowOpacity");
        titleFade->setDuration(800);
        titleFade->setStartValue(0.0);
        titleFade->setEndValue(1.0);
        titleFade->setEasingCurve(QEasingCurve::InOutCubic);
        titleFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if (ui->statisticsCardsContainer) {
        QPropertyAnimation* statsFade = new QPropertyAnimation(ui->statisticsCardsContainer, "windowOpacity");
        statsFade->setDuration(1000);
        statsFade->setStartValue(0.0);
        statsFade->setEndValue(1.0);
        statsFade->setEasingCurve(QEasingCurve::OutCubic);
        statsFade->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // Slide and fade-in the three main statistic cards that exist in the UI
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QList<QWidget*> statWidgets;
    if (ui->totalEmployeesCard) statWidgets.append(ui->totalEmployeesCard);
    if (ui->activeProjectsCard) statWidgets.append(ui->activeProjectsCard);
    if (ui->performanceCard) statWidgets.append(ui->performanceCard);

    for (int i = 0; i < statWidgets.size(); ++i) {
        QWidget* w = statWidgets[i];
        QRect finalGeom = w->geometry();

        QPropertyAnimation* slide = new QPropertyAnimation(w, "geometry");
        slide->setDuration(900 + i * 150);
        slide->setStartValue(QRect(finalGeom.x(), finalGeom.y() + 30, finalGeom.width(), finalGeom.height()));
        slide->setEndValue(finalGeom);
        slide->setEasingCurve(QEasingCurve::OutCubic);

        QPropertyAnimation* fade = new QPropertyAnimation(w, "windowOpacity");
        fade->setDuration(900 + i * 150);
        fade->setStartValue(0.0);
        fade->setEndValue(1.0);
        fade->setEasingCurve(QEasingCurve::InOutCubic);

        group->addAnimation(slide);
        group->addAnimation(fade);
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}


