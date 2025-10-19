/********************************************************************************
** Form generated from reading UI file 'project.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectWidget
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QTabWidget *clientTabWidget;
    QWidget *serviceManagementTab;
    QVBoxLayout *serviceManagementLayout;
    QStackedWidget *stackedWidget;
    QWidget *main_3;
    QLineEdit *lineEdit_8;
    QLabel *label_15;
    QLineEdit *lineEdit_9;
    QLabel *label_16;
    QLineEdit *lineEdit_10;
    QLabel *label_17;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QLabel *label_18;
    QComboBox *comboBox_2;
    QPushButton *pushButton_16;
    QLabel *label_19;
    QTableWidget *tableWidget_4;
    QLabel *label_20;
    QComboBox *comboBox;
    QPushButton *exportCsvBtn;
    QPushButton *btnSortByName;
    QPushButton *btnDeleteService;
    QPushButton *btnEditService;
    QWidget *page_3;
    QWidget *voiceChatTab;
    QVBoxLayout *voiceChatLayout;
    QLabel *label_8;
    QPushButton *pushButton_7;
    QListWidget *listWidget;
    QPushButton *pushButton_5;
    QWidget *modifyTab;
    QVBoxLayout *modifyLayout;
    QLabel *label_9;
    QLabel *label_14;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QLabel *label_11;
    QLabel *label_12;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QWidget *ProjectWidget)
    {
        if (ProjectWidget->objectName().isEmpty())
            ProjectWidget->setObjectName("ProjectWidget");
        ProjectWidget->resize(1339, 784);
        centralwidget = new QWidget(ProjectWidget);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(20, 30, 1241, 881));
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(20);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(30, 20, 30, 20);
        clientTabWidget = new QTabWidget(centralwidget);
        clientTabWidget->setObjectName("clientTabWidget");
        serviceManagementTab = new QWidget();
        serviceManagementTab->setObjectName("serviceManagementTab");
        serviceManagementLayout = new QVBoxLayout(serviceManagementTab);
        serviceManagementLayout->setSpacing(15);
        serviceManagementLayout->setObjectName("serviceManagementLayout");
        serviceManagementLayout->setContentsMargins(20, 20, 20, 20);
        stackedWidget = new QStackedWidget(serviceManagementTab);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        main_3 = new QWidget();
        main_3->setObjectName("main_3");
        lineEdit_8 = new QLineEdit(main_3);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(240, 70, 641, 31));
        lineEdit_8->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;\n"
"}\n"
""));
        label_15 = new QLabel(main_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(50, 100, 311, 41));
        label_15->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        lineEdit_9 = new QLineEdit(main_3);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(240, 140, 641, 31));
        lineEdit_9->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"\n"
""));
        label_16 = new QLabel(main_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(50, 170, 311, 41));
        label_16->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        lineEdit_10 = new QLineEdit(main_3);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(240, 210, 641, 31));
        lineEdit_10->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;\n"
"}\n"
""));
        label_17 = new QLabel(main_3);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(50, 240, 311, 41));
        label_17->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        pushButton_13 = new QPushButton(main_3);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(10, 360, 111, 31));
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0077cc;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #005fa3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #004b82;\n"
"}\n"
""));
        pushButton_14 = new QPushButton(main_3);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(140, 360, 111, 31));
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0077cc;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #005fa3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #004b82;\n"
"}\n"
""));
        label_18 = new QLabel(main_3);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(370, -10, 321, 41));
        label_18->setStyleSheet(QString::fromUtf8("font: 400  18pt \"Segoe UI\";\n"
"color: black;  /* bleu */\n"
""));
        comboBox_2 = new QComboBox(main_3);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(240, 290, 641, 31));
        comboBox_2->setStyleSheet(QString::fromUtf8("border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;"));
        pushButton_16 = new QPushButton(main_3);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(290, 360, 111, 31));
        pushButton_16->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: red;       /* Button color */\n"
"    color: white;                /* Text color */\n"
"    border-radius: 8px;          /* Rounded corners */\n"
"    padding: 8px 15px;           /* Internal spacing */\n"
"    font-weight: bold;            /* Bold text */\n"
"    font-family: \"Poppins\", sans-serif;\n"
"    border: none;                /* Remove default border */\n"
"    min-width: 80px;             /* Optional minimum width */\n"
"    cursor: pointer;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: darkred;   /* Slightly darker on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #a30000;   /* Even darker when pressed */\n"
"}\n"
""));
        label_19 = new QLabel(main_3);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(0, 400, 141, 51));
        label_19->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        tableWidget_4 = new QTableWidget(main_3);
        if (tableWidget_4->columnCount() < 7)
            tableWidget_4->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(420, 420, 741, 221));
        tableWidget_4->setStyleSheet(QString::fromUtf8(""));
        label_20 = new QLabel(main_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(50, 30, 351, 41));
        label_20->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        comboBox = new QComboBox(main_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(260, 450, 141, 31));
        exportCsvBtn = new QPushButton(main_3);
        exportCsvBtn->setObjectName("exportCsvBtn");
        exportCsvBtn->setGeometry(QRect(90, 450, 141, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/export.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        exportCsvBtn->setIcon(icon);
        exportCsvBtn->setIconSize(QSize(16, 16));
        btnSortByName = new QPushButton(main_3);
        btnSortByName->setObjectName("btnSortByName");
        btnSortByName->setGeometry(QRect(90, 500, 141, 31));
        btnSortByName->setStyleSheet(QString::fromUtf8("   background-color: gray;  "));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/sort.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSortByName->setIcon(icon1);
        btnSortByName->setIconSize(QSize(16, 16));
        btnDeleteService = new QPushButton(main_3);
        btnDeleteService->setObjectName("btnDeleteService");
        btnDeleteService->setGeometry(QRect(90, 550, 141, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDeleteService->setIcon(icon2);
        btnDeleteService->setIconSize(QSize(16, 16));
        btnEditService = new QPushButton(main_3);
        btnEditService->setObjectName("btnEditService");
        btnEditService->setGeometry(QRect(90, 600, 141, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/modify.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnEditService->setIcon(icon3);
        btnEditService->setIconSize(QSize(16, 16));
        stackedWidget->addWidget(main_3);
        tableWidget_4->raise();
        lineEdit_8->raise();
        label_15->raise();
        lineEdit_9->raise();
        label_16->raise();
        lineEdit_10->raise();
        label_17->raise();
        pushButton_13->raise();
        pushButton_14->raise();
        label_18->raise();
        comboBox_2->raise();
        pushButton_16->raise();
        label_19->raise();
        label_20->raise();
        comboBox->raise();
        exportCsvBtn->raise();
        btnSortByName->raise();
        btnDeleteService->raise();
        btnEditService->raise();
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);

        serviceManagementLayout->addWidget(stackedWidget);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/clients.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(serviceManagementTab, icon4, QString());
        voiceChatTab = new QWidget();
        voiceChatTab->setObjectName("voiceChatTab");
        voiceChatLayout = new QVBoxLayout(voiceChatTab);
        voiceChatLayout->setSpacing(15);
        voiceChatLayout->setObjectName("voiceChatLayout");
        voiceChatLayout->setContentsMargins(20, 20, 20, 20);
        label_8 = new QLabel(voiceChatTab);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));

        voiceChatLayout->addWidget(label_8);

        pushButton_7 = new QPushButton(voiceChatTab);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(128, 128, 128);   /* Gray background */\n"
"    color: white;                           /* Text color */\n"
"    font-family: \"Poppins\", sans-serif;\n"
"    font-weight: 500;\n"
"    font-size: 14px;\n"
"    border-radius: 8px;                     /* Rounded corners */\n"
"    padding: 10px 20px;                     /* Internal spacing */\n"
"    border: 2px solid rgb(128, 128, 128);  /* Border same as background */\n"
"    min-width: 120px;                       /* Minimum width */\n"
"    cursor: pointer;\n"
"    transition: all 0.3s;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(80, 80, 80);      /* Even darker on press */\n"
"    border-color: rgb(80, 80, 80);\n"
"}"));

        voiceChatLayout->addWidget(pushButton_7);

        listWidget = new QListWidget(voiceChatTab);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");

        voiceChatLayout->addWidget(listWidget);

        pushButton_5 = new QPushButton(voiceChatTab);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: gray;        /* Button color */\n"
"    color: white;                  /* Text color */\n"
"    border-radius: 8px;            /* Rounded corners */\n"
"    padding: 8px 15px;             /* Internal spacing */\n"
"    font-weight: bold;              /* Bold text */\n"
"    font-family: \"Poppins\", sans-serif;\n"
"    border: none;                  /* Remove default border */\n"
"    min-width: 80px;               /* Optional minimum width */\n"
"    cursor: pointer;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #555555;     /* Slightly darker on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #333333;     /* Even darker when pressed */\n"
"}\n"
""));

        voiceChatLayout->addWidget(pushButton_5);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/undo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(voiceChatTab, icon5, QString());
        modifyTab = new QWidget();
        modifyTab->setObjectName("modifyTab");
        modifyLayout = new QVBoxLayout(modifyTab);
        modifyLayout->setSpacing(15);
        modifyLayout->setObjectName("modifyLayout");
        modifyLayout->setContentsMargins(20, 20, 20, 20);
        label_9 = new QLabel(modifyTab);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));

        modifyLayout->addWidget(label_9);

        label_14 = new QLabel(modifyTab);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));

        modifyLayout->addWidget(label_14);

        lineEdit_5 = new QLineEdit(modifyTab);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;\n"
"}\n"
""));

        modifyLayout->addWidget(lineEdit_5);

        label_10 = new QLabel(modifyTab);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));

        modifyLayout->addWidget(label_10);

        pushButton_4 = new QPushButton(modifyTab);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(128, 128, 128);   /* Gray background */\n"
"    color: white;                           /* Text color */\n"
"    font-family: \"Poppins\", sans-serif;\n"
"    font-weight: 500;\n"
"    font-size: 14px;\n"
"    border-radius: 8px;                     /* Rounded corners */\n"
"    padding: 10px 20px;                     /* Internal spacing */\n"
"    border: 2px solid rgb(128, 128, 128);  /* Border same as background */\n"
"    min-width: 120px;                       /* Minimum width */\n"
"    cursor: pointer;\n"
"    transition: all 0.3s;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(80, 80, 80);      /* Even darker on press */\n"
"    border-color: rgb(80, 80, 80);\n"
"}"));

        modifyLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(modifyTab);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0077cc;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #005fa3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #004b82;\n"
"}\n"
""));

        modifyLayout->addWidget(pushButton_6);

        label_11 = new QLabel(modifyTab);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));

        modifyLayout->addWidget(label_11);

        label_12 = new QLabel(modifyTab);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));

        modifyLayout->addWidget(label_12);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/camera.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(modifyTab, icon6, QString());

        mainLayout->addWidget(clientTabWidget);

        menubar = new QMenuBar(ProjectWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        statusbar = new QStatusBar(ProjectWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 20, 25));

        retranslateUi(ProjectWidget);

        clientTabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProjectWidget);
    } // setupUi

    void retranslateUi(QWidget *ProjectWidget)
    {
        ProjectWidget->setStyleSheet(QCoreApplication::translate("ProjectWidget", "QMainWindow {\n"
"    background-color: #f8f9fa;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #e1e8ed;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    margin-top: 4px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    alignment: left;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #f8f9fa;\n"
"    border: 1px solid #dee2e6;\n"
"    border-bottom: none;\n"
"    border-radius: 6px 6px 0 0;\n"
"    padding: 12px 20px;\n"
"    margin-right: 2px;\n"
"    font-weight: 700; /* make tab text bold */\n"
"    color: #495057;\n"
"    font-size: 14px;\n"
"    min-width: 100px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #ffffff;\n"
"    color: #007bff;\n"
"    border-color: #007bff;\n"
"    border-bottom: 1px solid #ffffff;\n"
"}\n"
"\n"
"QTableWidget {\n"
"    gridline-color: #e9ecef;\n"
"    background-color: #ffffff;\n"
"    alternate-background-color: #f8f9fa;\n"
"    border: 1px solid #dee2e6;\n"
"    bo"
                        "rder-radius: 6px;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #e9ecef;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #e3f2fd;\n"
"    color: #1976d2;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #f1f3f4;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    border-bottom: 2px solid #007bff;\n"
"    font-weight: 600;\n"
"    color: #495057;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #007bff;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 6px;\n"
"    font-weight: 600;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Service Management Button Colors */\n"
"QPushButton#exportCsvBtn {\n"
"    background-color: #28a745;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#exportCsvBtn:hover {\n"
"    background-color: #218838;\n"
"}\n"
"\n"
"QPushButton#btnSortByName {\n"
"    background-color: #17a2b8;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#btnSortByName:hover {\n"
""
                        "    background-color: #138496;\n"
"}\n"
"\n"
"QPushButton#btnEditService {\n"
"    /* Modified to match reference: yellow/golden modify button */\n"
"    background-color: #f5b400;\n"
"    color: white;\n"
"    font-weight: 600;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"}\n"
"\n"
"QPushButton#btnEditService:hover {\n"
"    background-color: #e0a800;\n"
"}\n"
"\n"
"QPushButton#btnEditService:disabled {\n"
"    background-color: #6c757d;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnDeleteService {\n"
"    background-color: #e53935;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 10px 20px;\n"
"}\n"
"\n"
"QPushButton#btnDeleteService:hover {\n"
"    background-color: #c62828;\n"
"}\n"
"\n"
"QPushButton#btnDeleteService:disabled {\n"
"    background-color: #6c757d;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* updateClientBtn removed from UI (Modify button removed from Clients tab) */\n"
"\n"
"QLineEdit, QTextEdit, QComboBox {\n"
"    padding: 8px 12px;\n"
"    border: 2"
                        "px solid #d0d7dd;\n"
"    border-radius: 12px;\n"
"    background-color: #ffffff;\n"
"    color: #000000;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 2px solid #4da3ff;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #007bff;\n"
"    outline: none;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #000000;\n"
"    font-size: 14px;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QLabel#headerTitle {\n"
"    font-size: 24px;\n"
"    font-weight: 700;\n"
"    color: #000000;\n"
"    padding: 20px 0;\n"
"}\n"
"QLabel#headerTitle:hover {\n"
"    color: #1e88ff; /* light blue text on hover */\n"
"}\n"
"", nullptr));
        label_15->setText(QCoreApplication::translate("ProjectWidget", "Title (required) :", nullptr));
        label_16->setText(QCoreApplication::translate("ProjectWidget", "Description :", nullptr));
        label_17->setText(QCoreApplication::translate("ProjectWidget", "Status :", nullptr));
        pushButton_13->setText(QCoreApplication::translate("ProjectWidget", "CREATE", nullptr));
        pushButton_14->setText(QCoreApplication::translate("ProjectWidget", "VIEW", nullptr));
        label_18->setText(QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("ProjectWidget", "ACTIVE ", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("ProjectWidget", "ARCHIVED", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("ProjectWidget", "PUBLISHED", nullptr));

        pushButton_16->setText(QCoreApplication::translate("ProjectWidget", "DELETE", nullptr));
        label_19->setText(QCoreApplication::translate("ProjectWidget", "Project List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ProjectWidget", "Check", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ProjectWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ProjectWidget", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ProjectWidget", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ProjectWidget", "Owner", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ProjectWidget", "Created At	", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_4->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ProjectWidget", "Actions", nullptr));
        label_20->setText(QCoreApplication::translate("ProjectWidget", "Project ID (required, max 10 characters) :", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ProjectWidget", "CSV", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ProjectWidget", "EXCEL", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ProjectWidget", "PDF", nullptr));

        exportCsvBtn->setText(QCoreApplication::translate("ProjectWidget", "Export", nullptr));
        btnSortByName->setText(QCoreApplication::translate("ProjectWidget", "Sort by Name", nullptr));
        btnDeleteService->setText(QCoreApplication::translate("ProjectWidget", "Delete", nullptr));
        btnEditService->setText(QCoreApplication::translate("ProjectWidget", "Edit", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(serviceManagementTab), QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        label_8->setText(QCoreApplication::translate("ProjectWidget", "Rollback (Version History)", nullptr));
        pushButton_7->setText(QCoreApplication::translate("ProjectWidget", "TELECHARGER HISTORIQUE", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ProjectWidget", "Version 2.0 - 27/09/2025\n"
"", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ProjectWidget", "Mod color", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ProjectWidget", "Version 1.5 - 20/09/2025\n"
"", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("ProjectWidget", "New Item", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("ProjectWidget", "Version 1.0 - 10/09/2025\n"
"", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        pushButton_5->setText(QCoreApplication::translate("ProjectWidget", "RESTORE", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(voiceChatTab), QCoreApplication::translate("ProjectWidget", "RollBack", nullptr));
        label_9->setText(QCoreApplication::translate("ProjectWidget", "ADD MEDIA", nullptr));
        label_14->setText(QCoreApplication::translate("ProjectWidget", "Media Description :", nullptr));
        label_10->setText(QCoreApplication::translate("ProjectWidget", "Insert an image or video : ", nullptr));
        pushButton_4->setText(QCoreApplication::translate("ProjectWidget", "CHOOSE FILE TO UPLOAD", nullptr));
        pushButton_6->setText(QCoreApplication::translate("ProjectWidget", "UPLOAD", nullptr));
        label_11->setText(QCoreApplication::translate("ProjectWidget", "PREVIEW : ", nullptr));
        label_12->setText(QCoreApplication::translate("ProjectWidget", "UPLOADED MEDIA : ", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(modifyTab), QCoreApplication::translate("ProjectWidget", "Insertion of images and videos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectWidget: public Ui_ProjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
