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
    QLineEdit *pid;
    QLabel *label_15;
    QLineEdit *titre;
    QLabel *label_16;
    QLineEdit *desc;
    QLabel *label_17;
    QPushButton *viewproj;
    QLabel *label_18;
    QComboBox *status;
    QLabel *label_19;
    QTableWidget *twp;
    QLabel *label_20;
    QComboBox *comboBox;
    QPushButton *exportCsvBtn;
    QPushButton *btnSortByName;
    QPushButton *deleteproj;
    QPushButton *edit;
    QPushButton *addproj;
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
    QPushButton *addServiceBtn;

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
        pid = new QLineEdit(main_3);
        pid->setObjectName("pid");
        pid->setGeometry(QRect(200, 60, 641, 31));
        pid->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_15->setGeometry(QRect(50, 100, 121, 41));
        label_15->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        titre = new QLineEdit(main_3);
        titre->setObjectName("titre");
        titre->setGeometry(QRect(200, 120, 641, 31));
        titre->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_16->setGeometry(QRect(50, 160, 91, 41));
        label_16->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        desc = new QLineEdit(main_3);
        desc->setObjectName("desc");
        desc->setGeometry(QRect(200, 180, 641, 31));
        desc->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_17->setGeometry(QRect(50, 220, 61, 41));
        label_17->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        viewproj = new QPushButton(main_3);
        viewproj->setObjectName("viewproj");
        viewproj->setGeometry(QRect(170, 290, 111, 31));
        viewproj->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        status = new QComboBox(main_3);
        status->addItem(QString());
        status->addItem(QString());
        status->addItem(QString());
        status->setObjectName("status");
        status->setGeometry(QRect(200, 240, 641, 31));
        status->setStyleSheet(QString::fromUtf8("border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;"));
        label_19 = new QLabel(main_3);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 320, 161, 51));
        label_19->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        twp = new QTableWidget(main_3);
        if (twp->columnCount() < 5)
            twp->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twp->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twp->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twp->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twp->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twp->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        twp->setObjectName("twp");
        twp->setGeometry(QRect(390, 330, 741, 221));
        twp->setStyleSheet(QString::fromUtf8(""));
        label_20 = new QLabel(main_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(50, 50, 101, 41));
        label_20->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        comboBox = new QComboBox(main_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(220, 400, 141, 31));
        exportCsvBtn = new QPushButton(main_3);
        exportCsvBtn->setObjectName("exportCsvBtn");
        exportCsvBtn->setGeometry(QRect(50, 400, 151, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/export.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        exportCsvBtn->setIcon(icon);
        exportCsvBtn->setIconSize(QSize(16, 16));
        btnSortByName = new QPushButton(main_3);
        btnSortByName->setObjectName("btnSortByName");
        btnSortByName->setGeometry(QRect(50, 470, 151, 31));
        btnSortByName->setStyleSheet(QString::fromUtf8("   background-color: gray;  "));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/sort.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSortByName->setIcon(icon1);
        btnSortByName->setIconSize(QSize(16, 16));
        deleteproj = new QPushButton(main_3);
        deleteproj->setObjectName("deleteproj");
        deleteproj->setGeometry(QRect(310, 290, 121, 31));
        deleteproj->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 0, 0);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        deleteproj->setIcon(icon2);
        deleteproj->setIconSize(QSize(16, 16));
        edit = new QPushButton(main_3);
        edit->setObjectName("edit");
        edit->setGeometry(QRect(460, 290, 121, 31));
        edit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(181, 161, 50);\n"
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/modify.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        edit->setIcon(icon3);
        edit->setIconSize(QSize(16, 16));
        addproj = new QPushButton(main_3);
        addproj->setObjectName("addproj");
        addproj->setGeometry(QRect(30, 289, 111, 31));
        addproj->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addproj->setIcon(icon4);
        stackedWidget->addWidget(main_3);
        twp->raise();
        pid->raise();
        label_15->raise();
        titre->raise();
        label_16->raise();
        desc->raise();
        label_17->raise();
        viewproj->raise();
        label_18->raise();
        status->raise();
        label_19->raise();
        label_20->raise();
        comboBox->raise();
        exportCsvBtn->raise();
        btnSortByName->raise();
        deleteproj->raise();
        edit->raise();
        addproj->raise();
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);

        serviceManagementLayout->addWidget(stackedWidget);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/clients.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(serviceManagementTab, icon5, QString());
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

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/undo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(voiceChatTab, icon6, QString());
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

        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/camera.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(modifyTab, icon7, QString());

        mainLayout->addWidget(clientTabWidget);

        menubar = new QMenuBar(ProjectWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1339, 26));
        statusbar = new QStatusBar(ProjectWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 20, 25));
        addServiceBtn = new QPushButton(ProjectWidget);
        addServiceBtn->setObjectName("addServiceBtn");
        addServiceBtn->setGeometry(QRect(450, 750, 89, 40));
        addServiceBtn->setIcon(icon4);

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
        label_15->setText(QCoreApplication::translate("ProjectWidget", "Title :", nullptr));
        label_16->setText(QCoreApplication::translate("ProjectWidget", "Description :", nullptr));
        label_17->setText(QCoreApplication::translate("ProjectWidget", "Status :", nullptr));
        viewproj->setText(QCoreApplication::translate("ProjectWidget", "VIEW", nullptr));
        label_18->setText(QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        status->setItemText(0, QCoreApplication::translate("ProjectWidget", "ACTIVE ", nullptr));
        status->setItemText(1, QCoreApplication::translate("ProjectWidget", "ARCHIVED", nullptr));
        status->setItemText(2, QCoreApplication::translate("ProjectWidget", "PUBLISHED", nullptr));

        label_19->setText(QCoreApplication::translate("ProjectWidget", "Project List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twp->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ProjectWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twp->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ProjectWidget", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twp->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ProjectWidget", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twp->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ProjectWidget", "Owner", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = twp->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ProjectWidget", "Created At	", nullptr));
        label_20->setText(QCoreApplication::translate("ProjectWidget", "Project ID  :", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ProjectWidget", "CSV", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ProjectWidget", "EXCEL", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ProjectWidget", "PDF", nullptr));

        exportCsvBtn->setText(QCoreApplication::translate("ProjectWidget", "Export", nullptr));
        btnSortByName->setText(QCoreApplication::translate("ProjectWidget", "Sort by Name", nullptr));
        deleteproj->setText(QCoreApplication::translate("ProjectWidget", "DELETE", nullptr));
        edit->setText(QCoreApplication::translate("ProjectWidget", "EDIT", nullptr));
        addproj->setText(QCoreApplication::translate("ProjectWidget", "ADD", nullptr));
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
        addServiceBtn->setText(QCoreApplication::translate("ProjectWidget", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectWidget: public Ui_ProjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
