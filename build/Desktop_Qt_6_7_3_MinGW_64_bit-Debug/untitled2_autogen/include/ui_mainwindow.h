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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_6;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QLabel *label_8;
    QPushButton *pushButton_6;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *tab;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *label_9;
    QPushButton *pushButton_7;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QDateEdit *dateEdit;
    QDateEdit *dateEdit_2;
    QPushButton *pushButton_5;
    QWidget *tab_3;
    QMenuBar *menubar;
    QMenu *menuG_SPONSORING;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1354, 728);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: 000000;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, -10, 1451, 71));
        label_6->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #004080;  /* bleu uni */\n"
"    font: 700 28pt \"Calibri\"; /* taille plus petite, gras */\n"
"    background: transparent;\n"
"    padding: 8px 15px; /* r\303\251duire un peu le padding */\n"
"    letter-spacing: 1px; /* espacement un peu plus normal */\n"
"    border: none;\n"
"    border-bottom: 2px solid #004080; /* ligne en bas assortie au texte */\n"
"    text-shadow: 1px 1px 2px rgba(0,0,0,0.15); /* ombre plus subtile */\n"
"    qproperty-alignment: 'AlignCenter'; /* centrer le texte */\n"
"}\n"
""));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(30, 70, 1251, 681));
        tabWidget->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0);\n"
"font: 14pt \"Segoe UI\";"));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidget = new QTableWidget(tab_2);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 100, 641, 471));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #f2f2f2;   /* gris tr\303\250s clair, proche du blanc */\n"
"    gridline-color: #bdc3c7;     /* couleur des lignes */\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #000000;              /* texte en noir */\n"
"    selection-background-color: #3498db; /* fond bleu quand s\303\251lectionn\303\251 */\n"
"    selection-color: #ffffff;    /* texte blanc quand s\303\251lectionn\303\251 */\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    background-color: #f2f2f2; /* gris clair pour chaque cellule */\n"
"    color: #000000;            /* texte noir dans les cellules */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #2c3e50;   /* fond des en-t\303\252tes */\n"
"    color: #ffffff;              /* texte blanc dans les titres */\n"
"    font-weight: bold;\n"
"    padding: 6px;\n"
"    border: none;\n"
"}\n"
"\n"
""));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        tableWidget->setAutoScroll(true);
        lineEdit_3 = new QLineEdit(tab_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(30, 60, 341, 31));
        lineEdit_3->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #3498db;   /* bleu d\303\250s le d\303\251part */\n"
"    border-radius: 8px;\n"
"    padding: 6px;\n"
"    background-color: #ecf0f1;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #1d6fa5;   /* bleu plus fonc\303\251 quand focus */\n"
"    background-color: #ffffff;\n"
"}\n"
""));
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(390, 50, 141, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2a75b3; /* bleu fonc\303\251 de base */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #28a745; /* vert au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1e3f66; /* bleu encore plus fonc\303\251 au clic */\n"
"}\n"
""));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(890, 330, 181, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28a745; /* vert normal */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #218838; /* vert fonc\303\251 quand souris dessus */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #004080; /* bleu fonc\303\251 quand on clique */\n"
"}\n"
""));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(40, 0, 411, 61));
        label_8->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Verdana\"; color: rgb(0, 0, 0)"));
        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(880, 420, 201, 61));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db; /* bleu normal */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5dade2; /* bleu clair au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #21618c; /* bleu fonc\303\251 au clic */\n"
"}\n"
""));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(890, 170, 131, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #e67e22; /* orange normal */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d35400; /* orange fonc\303\251 quand souris dessus */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #ff0000; /* rouge pur quand on clique */\n"
"}\n"
""));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(890, 250, 131, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #e74c3c; /* rouge normal */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #c0392b; /* rouge fonc\303\251 quand souris dessus */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #27ae60; /* vert quand on clique */\n"
"}\n"
""));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(470, 270, 131, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: #ffffff;  /* texte noir */"));
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 280, 121, 21));
        label_4->setStyleSheet(QString::fromUtf8("color: #ffffff;  /* texte noir */"));
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(470, 190, 151, 31));
        label_3->setStyleSheet(QString::fromUtf8("color: #ffffff;  /* texte noir */"));
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 200, 141, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: #ffffff  /* texte noir */\n"
""));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 190, 171, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #3498db;   /* bleu d\303\250s le d\303\251part */\n"
"    border-radius: 8px;\n"
"    padding: 6px;\n"
"    background-color: #ecf0f1;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #1d6fa5;   /* bleu plus fonc\303\251 quand focus */\n"
"    background-color: #ffffff;\n"
"}\n"
""));
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(470, 350, 111, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Verdana\"; color: #ffffff;  /* texte noir */"));
        checkBox = new QCheckBox(tab);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(610, 350, 141, 25));
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    spacing: 8px;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"/* Case vide */\n"
"QCheckBox::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    border-radius: 4px;\n"
"    border: 2px solid #3498db;\n"
"    background: #ffffff;\n"
"}\n"
"\n"
"/* Survol */\n"
"QCheckBox::indicator:hover {\n"
"    border: 2px solid #2980b9;\n"
"}\n"
"\n"
"/* Case coch\303\251e (affiche le \342\234\224 par d\303\251faut de Qt) */\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #3498db;\n"
"}\n"
""));
        checkBox_2 = new QCheckBox(tab);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(760, 350, 171, 25));
        checkBox_2->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    spacing: 8px;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"/* Style de la case (vide) */\n"
"QCheckBox::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    border-radius: 4px; /* arrondi */\n"
"    border: 2px solid #3498db; /* contour bleu */\n"
"    background: #ffffff;\n"
"}\n"
"\n"
"/* Quand on passe la souris dessus */\n"
"QCheckBox::indicator:hover {\n"
"    border: 2px solid #2980b9; \n"
"}\n"
"\n"
"/* Quand elle est coch\303\251e */\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #3498db;  /* fond bleu */\n"
"    image: url(:/icons/check.png); /* \342\234\205 ic\303\264ne check */\n"
"}\n"
""));
        label_9 = new QLabel(tab);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 350, 201, 21));
        label_9->setStyleSheet(QString::fromUtf8("color: #ffffff;  /* texte noir */"));
        pushButton_7 = new QPushButton(tab);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(20, 500, 131, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #0fff67; /* orange normal */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d35400; /* orange fonc\303\251 quand souris dessus */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #ff0000; /* rouge pur quand on clique */\n"
"}\n"
""));
        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(660, 190, 171, 41));
        lineEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #3498db;   /* bleu d\303\250s le d\303\251part */\n"
"    border-radius: 8px;\n"
"    padding: 6px;\n"
"    background-color: #ecf0f1;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #1d6fa5;   /* bleu plus fonc\303\251 quand focus */\n"
"    background-color: #ffffff;\n"
"}\n"
""));
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(660, 260, 171, 41));
        lineEdit_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #3498db;   /* bleu d\303\250s le d\303\251part */\n"
"    border-radius: 8px;\n"
"    padding: 6px;\n"
"    background-color: #ecf0f1;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #1d6fa5;   /* bleu plus fonc\303\251 quand focus */\n"
"    background-color: #ffffff;\n"
"}\n"
""));
        dateEdit = new QDateEdit(tab);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(200, 280, 194, 29));
        dateEdit_2 = new QDateEdit(tab);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(200, 350, 194, 29));
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(170, 500, 131, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #e74c3c; /* rouge normal */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #c0392b; /* rouge fonc\303\251 quand souris dessus */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #27ae60; /* vert quand on clique */\n"
"}\n"
""));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1354, 25));
        menuG_SPONSORING = new QMenu(menubar);
        menuG_SPONSORING->setObjectName("menuG_SPONSORING");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuG_SPONSORING->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Gestion Sponsoring", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom ", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Date-D", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Date-F", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "E-Mail", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "search Sponsor", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Modify ", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Delete ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Display", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Date-D\303\251but", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Nom-Sponsor", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ID-SPONSOR", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "ID_Spons", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", " Status :", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "active ", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "non active ", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Date-Fin", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "Nom_Spons", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Add", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        menuG_SPONSORING->setTitle(QCoreApplication::translate("MainWindow", "G SPONSORING", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
