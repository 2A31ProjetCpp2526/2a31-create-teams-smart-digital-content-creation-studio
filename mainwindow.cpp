#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "media.h"
#include "rb.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_media(new media(this))
    , m_rb(new rb(this))
{
    ui->setupUi(this);

    // Add pages to stacked widget
    ui->stackedWidget->addWidget(m_media);
    ui->stackedWidget->addWidget(m_rb);

    // Get indices
    int mediaIndex = ui->stackedWidget->indexOf(m_media);
    int rbIndex = ui->stackedWidget->indexOf(m_rb);

    // MainWindow buttons
    connect(ui->media, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(mediaIndex);
    });
    connect(ui->rb, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(rbIndex);
    });

    // 🔹 Media buttons
    connect(m_media->getCrudButton(), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(m_media->getRbButton(), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(rbIndex);
    });

    // 🔹 RB buttons
    connect(m_rb->getCrudButton(), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(m_rb->getMediaButton(), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(mediaIndex);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
