#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_projects.h"
#include "./ui_editor.h"
#include "./ui_library.h"
#include "./ui_settings.h"
#include "./ui_login.h"
#include <QGraphicsOpacityEffect>
#include <QEasingCurve>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentPageIndex(0)
{
    ui->setupUi(this);
    
    setupPages();
    setupAnimations();
    
    // Connect sidebar buttons
    connect(ui->dashboardBtn, &QPushButton::clicked, this, &MainWindow::onDashboardClicked);
    connect(ui->projectsBtn, &QPushButton::clicked, this, &MainWindow::onProjectsClicked);
    connect(ui->editorBtn, &QPushButton::clicked, this, &MainWindow::onEditorClicked);
    connect(ui->libraryBtn, &QPushButton::clicked, this, &MainWindow::onLibraryClicked);
    connect(ui->settingsBtn, &QPushButton::clicked, this, &MainWindow::onSettingsClicked);
    connect(ui->loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    
    // Add hover effects to buttons
    addButtonHoverEffect(ui->dashboardBtn);
    addButtonHoverEffect(ui->projectsBtn);
    addButtonHoverEffect(ui->editorBtn);
    addButtonHoverEffect(ui->libraryBtn);
    addButtonHoverEffect(ui->settingsBtn);
    addButtonHoverEffect(ui->loginBtn);
    
    // Set initial page
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPages()
{
    // Create page widgets
    projectsPage = new QWidget();
    editorPage = new QWidget();
    libraryPage = new QWidget();
    settingsPage = new QWidget();
    loginPage = new QWidget();
    
    // Setup UI for each page
    Ui::ProjectsPage projectsUI;
    Ui::EditorPage editorUI;
    Ui::LibraryPage libraryUI;
    Ui::SettingsPage settingsUI;
    Ui::LoginPage loginUI;
    
    projectsUI.setupUi(projectsPage);
    editorUI.setupUi(editorPage);
    libraryUI.setupUi(libraryPage);
    settingsUI.setupUi(settingsPage);
    loginUI.setupUi(loginPage);
    
    // Add pages to stacked widget
    ui->stackedWidget->addWidget(projectsPage);     // Index 1
    ui->stackedWidget->addWidget(editorPage);       // Index 2
    ui->stackedWidget->addWidget(libraryPage);      // Index 3
    ui->stackedWidget->addWidget(settingsPage);     // Index 4
    ui->stackedWidget->addWidget(loginPage);        // Index 5
}

void MainWindow::setupAnimations()
{
    pageTransitionAnimation = new QPropertyAnimation(this);
    pageTransitionAnimation->setDuration(250);
    pageTransitionAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    animationGroup = new QParallelAnimationGroup(this);
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
    switchToPage(0);
}

void MainWindow::onProjectsClicked()
{
    switchToPage(1);
}

void MainWindow::onEditorClicked()
{
    switchToPage(2);
}

void MainWindow::onLibraryClicked()
{
    switchToPage(3);
}

void MainWindow::onSettingsClicked()
{
    switchToPage(4);
}

void MainWindow::onLoginClicked()
{
    switchToPage(5);
}
