/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *main_3;
    QLabel *label_13;
    QLineEdit *lineEdit_8;
    QLabel *label_15;
    QLineEdit *lineEdit_9;
    QLabel *label_16;
    QLineEdit *lineEdit_10;
    QLabel *label_17;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QLabel *label_18;
    QPushButton *crud_2;
    QPushButton *media;
    QPushButton *rb;
    QComboBox *comboBox_2;
    QPushButton *pushButton_16;
    QLabel *label_19;
    QTableWidget *tableWidget_4;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QLabel *label_20;
    QWidget *page_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1315, 678);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 10, 1331, 701));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        main_3 = new QWidget();
        main_3->setObjectName("main_3");
        label_13 = new QLabel(main_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 0, 521, 51));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 20pt \"Segoe UI\";\n"
";\n"
"font: 900 20pt \"Segoe UI\";\n"
""));
        lineEdit_8 = new QLineEdit(main_3);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(190, 150, 641, 31));
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
        label_15->setGeometry(QRect(100, 190, 311, 41));
        label_15->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        lineEdit_9 = new QLineEdit(main_3);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(190, 240, 641, 31));
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
        label_16->setGeometry(QRect(100, 270, 311, 41));
        label_16->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        lineEdit_10 = new QLineEdit(main_3);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(190, 320, 641, 31));
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
        label_17->setGeometry(QRect(100, 350, 311, 41));
        label_17->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        pushButton_13 = new QPushButton(main_3);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(20, 440, 111, 31));
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
        pushButton_14->setGeometry(QRect(150, 440, 111, 31));
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
        pushButton_15 = new QPushButton(main_3);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(280, 440, 111, 31));
        pushButton_15->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_18->setGeometry(QRect(20, 60, 261, 41));
        label_18->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        crud_2 = new QPushButton(main_3);
        crud_2->setObjectName("crud_2");
        crud_2->setGeometry(QRect(780, 10, 141, 41));
        crud_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        media = new QPushButton(main_3);
        media->setObjectName("media");
        media->setGeometry(QRect(950, 10, 141, 41));
        media->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        rb = new QPushButton(main_3);
        rb->setObjectName("rb");
        rb->setGeometry(QRect(1120, 10, 141, 41));
        rb->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        comboBox_2 = new QComboBox(main_3);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(190, 390, 641, 31));
        comboBox_2->setStyleSheet(QString::fromUtf8("border: 2px solid #cccccc;           /* bordure grise claire */\n"
"    border-radius: 12px;                 /* coins arrondis */\n"
"    padding: 8px 12px;                   /* espacement interne */\n"
"    background: #ffffff;                 /* fond blanc */\n"
"    color: #000000;                      /* texte noir */\n"
"    selection-background-color: #90caf9; /* bleu clair pour la s\303\251lection */\n"
"    font-size: 14px;"));
        pushButton_16 = new QPushButton(main_3);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(410, 440, 111, 31));
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
        label_19->setGeometry(QRect(20, 470, 141, 51));
        label_19->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        tableWidget_4 = new QTableWidget(main_3);
        if (tableWidget_4->columnCount() < 6)
            tableWidget_4->setColumnCount(6);
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
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(190, 490, 751, 191));
        tableWidget_4->setStyleSheet(QString::fromUtf8("/* Table overall style */\n"
"QTableWidget, QTableView {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid rgba(52, 152, 219, 0.1);\n"
"    border-radius: 12px;\n"
"    gridline-color: #e1e8ed;\n"
"    font-family: \"Poppins\", sans-serif;\n"
"    font-weight: 300;\n"
"    color: #2c3e50;\n"
"    selection-background-color: #1da1f2;\n"
"    selection-color: white;\n"
"}\n"
"\n"
"/* Header */\n"
"QHeaderView::section {\n"
"    background-color: #1da1f2;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    border: none;\n"
"    font-weight: 500;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Rows */\n"
"QTableWidget::item {\n"
"    padding: 12px;\n"
"}\n"
"\n"
"/* Alternate row colors */\n"
"QTableWidget::item:!selected:alternate {\n"
"    background-color: #f7f9fa;\n"
"}\n"
"QTableWidget::item:!selected {\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* Selected row */\n"
"QTableWidget::item:selected {\n"
"    background-color: #1da1f2;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Scrollbars (optional) */"
                        "\n"
"QScrollBar:vertical {\n"
"    background-color: #f8fafe;\n"
"    width: 14px;\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                stop:0 #74b9ff, stop:1 #3498db);\n"
"    border-radius: 7px;\n"
"    min-height: 24px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                stop:0 #81c2ff, stop:1 #5dade2);\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    border: none;\n"
"    background: none;\n"
"}\n"
""));
        pushButton_17 = new QPushButton(main_3);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(980, 520, 111, 31));
        pushButton_17->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_18 = new QPushButton(main_3);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(980, 570, 111, 31));
        pushButton_18->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_19 = new QPushButton(main_3);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(810, 630, 111, 31));
        pushButton_19->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_20 = new QPushButton(main_3);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(60, 530, 121, 31));
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: green;       /* Button color */\n"
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
"    background-color: darkgreen;   /* Slightly darker on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #006400;     /* Even darker when pressed */\n"
"}\n"
""));
        pushButton_21 = new QPushButton(main_3);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(70, 580, 111, 31));
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_20 = new QLabel(main_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(90, 110, 351, 41));
        label_20->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        stackedWidget->addWidget(main_3);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1315, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "CRUD PROJECT & INPUT VALIDATION", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Title (required) :", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Description :", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Status :", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "CREATE", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "READ", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "UPDATE", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Project Management", nullptr));
        crud_2->setText(QCoreApplication::translate("MainWindow", "CRUD", nullptr));
        media->setText(QCoreApplication::translate("MainWindow", "MEDIA", nullptr));
        rb->setText(QCoreApplication::translate("MainWindow", "ROLLBACK", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "ACTIVE ", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "ARCHIVED", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "PUBLISHED", nullptr));

        pushButton_16->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Project List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Owner", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Created At	", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "VIEW", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "EDIT", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "EXPORT PDF", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "SORT", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Project ID (required, max 10 characters) :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
