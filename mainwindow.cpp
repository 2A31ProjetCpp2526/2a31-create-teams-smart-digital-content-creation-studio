#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_login.h"
#include "ui_Profile.h"
#include "ui_signup.h"
#include <QGraphicsOpacityEffect>
#include <QEasingCurve>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRegularExpression>
#include <QMessageBox>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentPageIndex(0)
    , profileWidget(nullptr)
    , profileUI(nullptr)
    , signUpPageWidget(nullptr)
    , signUpUI(nullptr)
{
    ui->setupUi(this);
    
    
    ui->loginBtn->setIcon(QIcon(":/resources/icons/login.svg"));
    ui->loginBtn->setIconSize(QSize(20, 20));
    ui->loginBtn->setStyleSheet(
        "QPushButton { "
        "    text-align: left; "
        "    padding: 12px 24px; "
        "    border: none; "
        "    background-color: transparent; "
        "    color: #6c757d; "
        "    font-weight: 300; "
        "    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif; "
        "    letter-spacing: 0.5px; "
        "    border-radius: 6px; "
        "} "
        "QPushButton:hover { "
        "    background-color: #e9ecef; "
        "    color: #495057; "
        "    transform: translateX(5px); "
        "    transition: all 0.3s ease; "
        "} "
        "QPushButton:pressed { "
        "    background-color: #dee2e6; "
        "}"
    );
    
    
    
    setupPages();
    setupProfileWidget();
    setupAnimations();
    setupSidebarIcons();
    
    
    
    connect(ui->employerBtn, &QPushButton::clicked, this, &MainWindow::onDashboardClicked);
    connect(ui->profileBtn, &QPushButton::clicked, this, &MainWindow::onProfileClicked);
    connect(ui->projectsBtn, &QPushButton::clicked, this, &MainWindow::onProjectsClicked);
    connect(ui->clientsBtn, &QPushButton::clicked, this, &MainWindow::onClientsClicked);
    connect(ui->resourcesBtn, &QPushButton::clicked, this, &MainWindow::onResourcesClicked);
    connect(ui->sponsorsBtn, &QPushButton::clicked, this, &MainWindow::onSponsorsClicked);
    connect(ui->templatesBtn, &QPushButton::clicked, this, &MainWindow::onTemplatesClicked);
    connect(ui->shopBtn, &QPushButton::clicked, this, &MainWindow::onShopClicked);
    connect(ui->loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    
    
    connect(ui->backToMainButton, &QPushButton::clicked, this, &MainWindow::showMainContent);
    
    
    connect(ui->saveEmployeeBtn, &QPushButton::clicked, this, &MainWindow::onSaveEmployee);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &MainWindow::onCancelAddEmployee);
    
    
    connect(ui->saveModifyBtn, &QPushButton::clicked, this, &MainWindow::onSaveModify);
    connect(ui->cancelModifyBtn, &QPushButton::clicked, this, &MainWindow::onCancelModify);
    
    
    connect(ui->employeeTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onEmployeeTableSelectionChanged);
    connect(ui->employeeTable, &QTableWidget::itemClicked, this, [this](QTableWidgetItem* item) {
        
        if (item && item->column() == 0) {
            bool isSelected = item->text() == "☑";
            item->setText(isSelected ? "☐" : "☑");
            
            
            bool hasAnySelection = false;
            for (int row = 0; row < ui->employeeTable->rowCount(); ++row) {
                QTableWidgetItem* checkItem = ui->employeeTable->item(row, 0);
                if (checkItem && checkItem->text() == "☑") {
                    hasAnySelection = true;
                    break;
                }
            }
            ui->modifyBtn->setEnabled(hasAnySelection);
            ui->deleteBtn->setEnabled(hasAnySelection);
        }
    });
    connect(ui->modifyBtn, &QPushButton::clicked, this, &MainWindow::onModifyEmployeeClicked);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteEmployeeClicked);
    
    
    
    
    addButtonHoverEffect(ui->employerBtn);
    addButtonHoverEffect(ui->profileBtn);
    addButtonHoverEffect(ui->projectsBtn);
    addButtonHoverEffect(ui->clientsBtn);
    addButtonHoverEffect(ui->resourcesBtn);
    addButtonHoverEffect(ui->sponsorsBtn);
    addButtonHoverEffect(ui->templatesBtn);
    addButtonHoverEffect(ui->shopBtn);
    addButtonHoverEffect(ui->loginBtn);
    
    
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete profileUI;
    delete loginUI;
    delete signUpUI;
    if (signUpPageWidget) {
        signUpPageWidget->close();
        delete signUpPageWidget;
    }
    delete ui;
}

void MainWindow::setupPages()
{
    
    
    
    
    setupEmployeeTable();
    
    
    setupLoginForms();
}

void MainWindow::setupLoginForms()
{
    
    loginPageWidget = new QMainWindow();
    loginUI = new Ui::LoginPage();
    loginUI->setupUi(static_cast<QMainWindow*>(loginPageWidget));
    
    
    loginPageWidget->setWindowFlags(Qt::Window);
    loginPageWidget->setWindowState(Qt::WindowMaximized);
    
    
    loginPageWidget->installEventFilter(this);
    
    
    authStackedWidget = ui->authStackedWidget;
    
    
    setupLoginFormConnections();
}

void MainWindow::setupProfileWidget()
{
    
    profileWidget = new QWidget();
    profileUI = new Ui::Profile();
    profileUI->setupUi(profileWidget);
    
    
    QWidget* profilePlaceholder = ui->stackedWidget->widget(1); 
    if (profilePlaceholder) {
        ui->stackedWidget->removeWidget(profilePlaceholder);
        ui->stackedWidget->insertWidget(1, profileWidget);
        delete profilePlaceholder;
    }
    
    
    connect(profileUI->saveProfileButton, &QPushButton::clicked, this, &MainWindow::onSaveProfileClicked);
    connect(profileUI->resetProfileButton, &QPushButton::clicked, this, &MainWindow::onResetProfileClicked);
    
    
    profileUI->usernameEdit->setText("John Doe");
    profileUI->emailEdit->setText("john.doe@aminetemplate.com");
}

void MainWindow::setupAnimations()
{
    pageTransitionAnimation = new QPropertyAnimation(this);
    pageTransitionAnimation->setDuration(250);
    pageTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    animationGroup = new QParallelAnimationGroup(this);
    
    
    loginFormTransitionAnimation = new QPropertyAnimation(this);
    loginFormTransitionAnimation->setDuration(300);
    loginFormTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void MainWindow::switchToPage(int pageIndex)
{
    if (pageIndex == currentPageIndex) return;
    
    currentPageIndex = pageIndex;
    
    
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
    
    button->setCursor(Qt::PointingHandCursor);
}

void MainWindow::onDashboardClicked()
{
    switchToPage(0); 
}

void MainWindow::onProfileClicked()
{
    switchToPage(1); 
}

void MainWindow::onProjectsClicked()
{
    switchToPage(2); 
}

void MainWindow::onClientsClicked()
{
    switchToPage(3); 
}

void MainWindow::onResourcesClicked()
{
    switchToPage(4); 
}

void MainWindow::onSponsorsClicked()
{
    switchToPage(5); 
}

void MainWindow::onTemplatesClicked()
{
    switchToPage(6); 
}

void MainWindow::onShopClicked()
{
    switchToPage(7); 
}

void MainWindow::onLoginClicked()
{
    
    if (loginPageWidget) {
        loginPageWidget->show();
        loginPageWidget->raise();
        loginPageWidget->activateWindow();
    }
}

void MainWindow::showMainContent()
{
    
    if (loginPageWidget) {
        loginPageWidget->hide();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == loginPageWidget && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            loginPageWidget->hide();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::showLoginOverlay()
{
    
    ui->mainStackedWidget->setCurrentIndex(1); 
    if (authStackedWidget) {
        authStackedWidget->setCurrentIndex(0); 
    }
}


void MainWindow::onSaveEmployee()
{
    
    QString firstName = ui->firstNameEdit->text().trimmed();
    QString lastName = ui->lastNameEdit->text().trimmed();
    QString email = ui->emailEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();
    QString role = ui->roleComboBox->currentText();
    QString department = ui->departmentComboBox->currentText();
    QString salary = ui->salaryEdit->text().trimmed();
    QDate startDate = ui->startDateEdit->date();
    
    
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty()) {
        
        return;
    }
    
    
    if (!isValidEmail(email)) {
        setFieldError(ui->emailEdit, true);
        return;
    }
    
    
    setFieldError(ui->firstNameEdit, false);
    setFieldError(ui->lastNameEdit, false);
    setFieldError(ui->emailEdit, false);
    
    
    
    onCancelAddEmployee();
    
    
}

void MainWindow::onCancelAddEmployee()
{
    
    ui->firstNameEdit->clear();
    ui->lastNameEdit->clear();
    ui->emailEdit->clear();
    ui->phoneEdit->clear();
    ui->roleComboBox->setCurrentIndex(0);
    ui->departmentComboBox->setCurrentIndex(0);
    ui->salaryEdit->clear();
    ui->startDateEdit->setDate(QDate::currentDate());
    
    
    setFieldError(ui->firstNameEdit, false);
    setFieldError(ui->lastNameEdit, false);
    setFieldError(ui->emailEdit, false);
    setFieldError(ui->phoneEdit, false);
    setFieldError(ui->salaryEdit, false);
}

void MainWindow::setupLoginFormConnections()
{
    if (!loginPageWidget) return;
    
    
    QPushButton* signUpButton = loginPageWidget->findChild<QPushButton*>("signUpButton");
    if (signUpButton) {
        connect(signUpButton, &QPushButton::clicked, this, &MainWindow::openSignUpWindow);
        addButtonHoverEffect(signUpButton);
    }
    
    
    QPushButton* signUpNavButton = loginPageWidget->findChild<QPushButton*>("signUpNavButton");
    if (signUpNavButton) {
        connect(signUpNavButton, &QPushButton::clicked, this, &MainWindow::showSignUpForm);
        addButtonHoverEffect(signUpNavButton);
    }
    
    
    QPushButton* forgotPasswordNavButton = loginPageWidget->findChild<QPushButton*>("forgotPasswordNavButton");
    if (forgotPasswordNavButton) {
        connect(forgotPasswordNavButton, &QPushButton::clicked, this, &MainWindow::showForgotPasswordForm);
        addButtonHoverEffect(forgotPasswordNavButton);
    }
    
    
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
    
    
    QPushButton* loginButton = loginPageWidget->findChild<QPushButton*>("loginButton");
    if (loginButton) {
        connect(loginButton, &QPushButton::clicked, this, &MainWindow::validateAndLogin);
        addButtonHoverEffect(loginButton);
    }
    
    QPushButton* sendResetLinkButton = loginPageWidget->findChild<QPushButton*>("sendResetLinkButton");
    if (sendResetLinkButton) {
        connect(sendResetLinkButton, &QPushButton::clicked, this, &MainWindow::validateAndSendResetLink);
        addButtonHoverEffect(sendResetLinkButton);
    }
    
    
    QPushButton* faceLoginButton = loginPageWidget->findChild<QPushButton*>("faceLoginButton");
    if (faceLoginButton) {
        connect(faceLoginButton, &QPushButton::clicked, this, [this]() {
            QMessageBox::information(this, "Face Login", "Face login coming soon!\n\nThis feature will use advanced facial recognition technology for secure authentication.");
        });
        addButtonHoverEffect(faceLoginButton);
    }
    
    
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
    
    
    QStackedWidget* loginStackedWidget = loginPageWidget->findChild<QStackedWidget*>("authStackedWidget");
    if (!loginStackedWidget) return;
    
    
    QWidget* currentWidget = loginStackedWidget->currentWidget();
    QWidget* targetWidget = loginStackedWidget->widget(formIndex);
    
    if (currentWidget == targetWidget) return;
    
    
    QGraphicsOpacityEffect* currentEffect = new QGraphicsOpacityEffect(currentWidget);
    currentWidget->setGraphicsEffect(currentEffect);
    
    QPropertyAnimation* fadeOut = new QPropertyAnimation(currentEffect, "opacity");
    fadeOut->setDuration(150);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->setEasingCurve(QEasingCurve::OutCubic);
    
    
    QGraphicsOpacityEffect* targetEffect = new QGraphicsOpacityEffect(targetWidget);
    targetWidget->setGraphicsEffect(targetEffect);
    
    QPropertyAnimation* fadeIn = new QPropertyAnimation(targetEffect, "opacity");
    fadeIn->setDuration(150);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::InCubic);
    
    
    connect(fadeOut, &QPropertyAnimation::finished, [=]() {
        loginStackedWidget->setCurrentIndex(formIndex);
        fadeIn->start();
        
        currentWidget->setGraphicsEffect(nullptr);
        fadeOut->deleteLater();
    });
    
    
    connect(fadeIn, &QPropertyAnimation::finished, [=]() {
        targetWidget->setGraphicsEffect(nullptr);
        fadeIn->deleteLater();
    });
    
    
    fadeOut->start();
}

void MainWindow::showLoginForm()
{
    switchLoginFormWithAnimation(0); 
}

void MainWindow::showSignUpForm()
{
    switchLoginFormWithAnimation(1); 
}

void MainWindow::showForgotPasswordForm()
{
    switchLoginFormWithAnimation(2); 
}

void MainWindow::openSignUpWindow()
{
    
    if (!signUpPageWidget) {
        signUpPageWidget = new QMainWindow(this);
        signUpUI = new Ui::SignUpPage;
        signUpUI->setupUi(signUpPageWidget);
        
        
        signUpPageWidget->setWindowTitle("Sign Up - Amine Templar");
        signUpPageWidget->setMinimumSize(1000, 700);
        signUpPageWidget->setAttribute(Qt::WA_DeleteOnClose, false);
        
        
        QPushButton* backToLoginButton = signUpPageWidget->findChild<QPushButton*>("backToLoginButton");
        if (backToLoginButton) {
            connect(backToLoginButton, &QPushButton::clicked, [this]() {
                signUpPageWidget->hide();
                this->show();
            });
            addButtonHoverEffect(backToLoginButton);
        }
        
        
        QPushButton* createAccountButton = signUpPageWidget->findChild<QPushButton*>("createAccountButton");
        if (createAccountButton) {
            connect(createAccountButton, &QPushButton::clicked, this, &MainWindow::validateAndSignUp);
            addButtonHoverEffect(createAccountButton);
        }
    }
    
    
    signUpPageWidget->show();
    signUpPageWidget->raise();
    signUpPageWidget->activateWindow();
}

void MainWindow::addInputFieldEnhancements(QLineEdit* field)
{
    if (!field) return;
    
    
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


bool MainWindow::isValidEmail(const QString& email)
{
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

bool MainWindow::isValidPassword(const QString& password)
{
    
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


void MainWindow::validateAndLogin()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("loginEmailLineEdit");
    QLineEdit* passwordField = loginPageWidget->findChild<QLineEdit*>("loginPasswordLineEdit");
    
    if (!emailField || !passwordField) return;
    
    QString email = emailField->text().trimmed();
    QString password = passwordField->text();
    
    bool hasErrors = false;
    

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
    

    if (password.isEmpty()) {
        setFieldError(passwordField, true);
        if (!hasErrors) showValidationError("Please enter your password.");
        hasErrors = true;
    } else {
        setFieldError(passwordField, false);
    }
    
    if (!hasErrors) {

        showMainContent();

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
    

    if (!termsCheckBox->isChecked()) {
        if (errorMessage.isEmpty()) errorMessage = "Please accept the terms and conditions.";
        hasErrors = true;
    }
    
    if (hasErrors) {
        showValidationError(errorMessage);
    } else {

        showValidationError("Sign up functionality not implemented yet.\nThis would create a new user account.");
    }
}

void MainWindow::validateAndSendResetLink()
{
    QLineEdit* emailField = loginPageWidget->findChild<QLineEdit*>("resetEmailLineEdit");
    
    if (!emailField) return;
    
    QString email = emailField->text().trimmed();
    

    if (email.isEmpty()) {
        setFieldError(emailField, true);
        showValidationError("Please enter your email address or username.");
    } else if (!isValidEmail(email) && !email.contains(QRegularExpression("^[a-zA-Z0-9_]+$"))) {
        setFieldError(emailField, true);
        showValidationError("Please enter a valid email address or username.");
    } else {
        setFieldError(emailField, false);

        QMessageBox::information(this, "Password Reset", "If an account with this email exists, a password reset link has been sent.\n\nPlease check your email and follow the instructions to reset your password.");
        showLoginForm();     }
}

void MainWindow::setupSidebarIcons()
{

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

void MainWindow::setupCircularAvatar(QLabel* avatarLabel, const QString& initials)
{
    if (!avatarLabel) return;
    

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
    

    avatarLabel->setMinimumSize(40, 40);
    avatarLabel->setMaximumSize(40, 40);
    avatarLabel->setScaledContents(true);
}


void MainWindow::onSaveProfileClicked()
{

    QString fullName = profileUI->usernameEdit->text().trimmed();
    QString email = profileUI->emailEdit->text().trimmed();
    QString password = profileUI->currentPasswordEdit->text();
    

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
    


    QMessageBox::information(this, "Profile Saved", "Your profile information has been saved successfully!");
}

void MainWindow::onResetProfileClicked()
{

    profileUI->usernameEdit->setText("John Doe");
    profileUI->emailEdit->setText("john.doe@aminetemplate.com");
    profileUI->currentPasswordEdit->clear();
    
    QMessageBox::information(this, "Profile Reset", "Profile information has been reset to default values.");
}

void MainWindow::onEmployeeTableSelectionChanged()
{

    bool hasSelection = false;
    for (int row = 0; row < ui->employeeTable->rowCount(); ++row) {
        QTableWidgetItem* checkItem = ui->employeeTable->item(row, 0);
        if (checkItem && checkItem->text() == "☑") {
            hasSelection = true;
            break;
        }
    }
    

    ui->modifyBtn->setEnabled(hasSelection);
    ui->deleteBtn->setEnabled(hasSelection);
}

void MainWindow::onModifyEmployeeClicked()
{

    int selectedRow = -1;
    for (int row = 0; row < ui->employeeTable->rowCount(); ++row) {
        QTableWidgetItem* checkItem = ui->employeeTable->item(row, 0);
        if (checkItem && checkItem->text() == "☑") {
            selectedRow = row;
            break;
        }
    }
    
    if (selectedRow < 0) {
        return;     }
    

    QTableWidgetItem* idItem = ui->employeeTable->item(selectedRow, 2);     QTableWidgetItem* nameItem = ui->employeeTable->item(selectedRow, 3);     QTableWidgetItem* emailItem = ui->employeeTable->item(selectedRow, 4);     QTableWidgetItem* phoneItem = ui->employeeTable->item(selectedRow, 6);     
    if (!idItem || !nameItem) {
        return;
    }
    

    QString fullName = nameItem->text();
    QStringList nameParts = fullName.split(" ", Qt::SkipEmptyParts);
    QString firstName = nameParts.isEmpty() ? "" : nameParts[0];
    QString lastName = nameParts.size() > 1 ? nameParts.mid(1).join(" ") : "";
    

    ui->modifyFirstNameEdit->setText(firstName);
    ui->modifyLastNameEdit->setText(lastName);
    ui->modifyEmailEdit->setText(emailItem ? emailItem->text() : "");
    ui->modifyPhoneEdit->setText(phoneItem ? phoneItem->text() : "");
    

    ui->employerTabWidget->setCurrentIndex(2);
}

void MainWindow::onDeleteEmployeeClicked()
{

    int selectedRow = -1;
    for (int row = 0; row < ui->employeeTable->rowCount(); ++row) {
        QTableWidgetItem* checkItem = ui->employeeTable->item(row, 0);
        if (checkItem && checkItem->text() == "☑") {
            selectedRow = row;
            break;
        }
    }
    
    if (selectedRow < 0) {
        return;     }
    

    QTableWidgetItem* nameItem = ui->employeeTable->item(selectedRow, 3);     
    if (!nameItem) {
        return;
    }
    

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Employee", 
                                       QString("Are you sure you want to delete employee: %1?").arg(nameItem->text()),
                                       QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {

        ui->employeeTable->removeRow(selectedRow);
        QMessageBox::information(this, "Employee Deleted", 
                               QString("Employee %1 has been deleted successfully.").arg(nameItem->text()));
    }
}

void MainWindow::onSaveModify()
{

    QString firstName = ui->modifyFirstNameEdit->text().trimmed();
    QString lastName = ui->modifyLastNameEdit->text().trimmed();
    QString email = ui->modifyEmailEdit->text().trimmed();
    QString phone = ui->modifyPhoneEdit->text().trimmed();
    

    if (firstName.isEmpty() || lastName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter both first and last name.");
        return;
    }
    
    if (!email.isEmpty() && !isValidEmail(email)) {
        QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
        return;
    }
    

    int selectedRow = -1;
    for (int row = 0; row < ui->employeeTable->rowCount(); ++row) {
        QTableWidgetItem* checkItem = ui->employeeTable->item(row, 0);
        if (checkItem && checkItem->text() == "☑") {
            selectedRow = row;
            break;
        }
    }
    
    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Selection", "No employee selected for modification.");
        return;
    }
    

    QString fullName = firstName + " " + lastName;
    ui->employeeTable->item(selectedRow, 3)->setText(fullName);     if (ui->employeeTable->item(selectedRow, 4)) {
        ui->employeeTable->item(selectedRow, 4)->setText(email);     }
    if (ui->employeeTable->item(selectedRow, 6)) {
        ui->employeeTable->item(selectedRow, 6)->setText(phone);     }
    

    ui->modifyFirstNameEdit->clear();
    ui->modifyLastNameEdit->clear();
    ui->modifyEmailEdit->clear();
    ui->modifyPhoneEdit->clear();
    

    ui->employerTabWidget->setCurrentIndex(0);
    

    QMessageBox::information(this, "Employee Updated", 
                           QString("Employee %1 has been updated successfully.").arg(fullName));
}

void MainWindow::onCancelModify()
{

    ui->modifyFirstNameEdit->clear();
    ui->modifyLastNameEdit->clear();
    ui->modifyEmailEdit->clear();
    ui->modifyPhoneEdit->clear();
    

    ui->employerTabWidget->setCurrentIndex(0);
}

void MainWindow::setupEmployeeTable()
{

    ui->employeeTable->setColumnWidth(0, 90);      ui->employeeTable->setColumnWidth(1, 100);     ui->employeeTable->setColumnWidth(2, 90);      ui->employeeTable->setColumnWidth(3, 220);     ui->employeeTable->setColumnWidth(4, 280);     ui->employeeTable->setColumnWidth(5, 150);     ui->employeeTable->setColumnWidth(6, 180);     

    ui->employeeTable->verticalHeader()->setDefaultSectionSize(90);
    ui->employeeTable->verticalHeader()->setMinimumSectionSize(90);
    

    ui->employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    

    for (int i = 0; i < ui->employeeTable->columnCount(); ++i) {
        QTableWidgetItem* headerItem = ui->employeeTable->horizontalHeaderItem(i);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignCenter);
        }
    }
}



