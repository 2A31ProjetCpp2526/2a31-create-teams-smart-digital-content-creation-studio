/********************************************************************************
** Form generated from reading UI file 'sponsorf.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPONSORF_H
#define UI_SPONSORF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
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

class Ui_SponsorForm
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QTableWidget *affiche;
    QLineEdit *search1;
    QPushButton *search1_2;
    QPushButton *pdfexport;
    QPushButton *deleteButton;
    QLabel *label;
    QPushButton *sort;
    QPushButton *afficherButton;
    QWidget *tab;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *ID;
    QLabel *label_5;
    QLabel *label_9;
    QPushButton *addButton;
    QLineEdit *Nom;
    QLineEdit *EM;
    QDateEdit *dd;
    QDateEdit *df;
    QComboBox *STS;
    QPushButton *updateButton;
    QPushButton *clear;
    QWidget *tab_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *calendrier;
    QPushButton *Stat;
    QMenuBar *menubar;
    QMenu *menuG_SPONSORING;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SponsorForm)
    {
        if (SponsorForm->objectName().isEmpty())
            SponsorForm->setObjectName("SponsorForm");
        SponsorForm->resize(1718, 832);
        SponsorForm->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(SponsorForm);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(130, 50, 1441, 671));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"    background: white;             /* white background */\n"
"    color: black;                  /* black text */\n"
"    padding: 8px 20px;\n"
"    border: 1px solid #ccc;        /* light gray border */\n"
"    border-radius: 5px;           /* rounded rectangle */\n"
"    margin: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #f0f0f0;           /* light gray when active */\n"
"    font-weight: bold;\n"
"    border: 1px solid #999; \n"
"border-bottom: 3px solid #2c3e50;       /* darker border for selected */\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #e6e6e6;           /* hover effect */\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 10px;\n"
"    margin-top: 5px;\n"
"    background: white;\n"
"}\n"
""));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        affiche = new QTableWidget(tab_2);
        if (affiche->columnCount() < 6)
            affiche->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        affiche->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        affiche->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        affiche->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        affiche->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        affiche->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        affiche->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        affiche->setObjectName("affiche");
        affiche->setGeometry(QRect(40, 130, 1211, 391));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(affiche->sizePolicy().hasHeightForWidth());
        affiche->setSizePolicy(sizePolicy);
        affiche->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
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
        affiche->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        affiche->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        affiche->setAutoScroll(true);
        search1 = new QLineEdit(tab_2);
        search1->setObjectName("search1");
        search1->setGeometry(QRect(40, 60, 361, 41));
        search1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        search1->setInputMask(QString::fromUtf8(""));
        search1_2 = new QPushButton(tab_2);
        search1_2->setObjectName("search1_2");
        search1_2->setGeometry(QRect(440, 60, 141, 41));
        search1_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pdfexport = new QPushButton(tab_2);
        pdfexport->setObjectName("pdfexport");
        pdfexport->setGeometry(QRect(1190, 50, 211, 41));
        pdfexport->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        deleteButton = new QPushButton(tab_2);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(1270, 550, 151, 41));
        deleteButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 381, 31));
        label->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Simplified Arabic\";\n"
"color: #000000"));
        sort = new QPushButton(tab_2);
        sort->setObjectName("sort");
        sort->setGeometry(QRect(1020, 50, 161, 41));
        sort->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        afficherButton = new QPushButton(tab_2);
        afficherButton->setObjectName("afficherButton");
        afficherButton->setGeometry(QRect(1100, 550, 151, 41));
        afficherButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(470, 270, 131, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: #000000  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 280, 121, 21));
        label_4->setStyleSheet(QString::fromUtf8("color: #000000  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(470, 190, 151, 31));
        label_3->setStyleSheet(QString::fromUtf8("color: #000000  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 200, 141, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: #000000  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        ID = new QLineEdit(tab);
        ID->setObjectName("ID");
        ID->setGeometry(QRect(200, 190, 171, 41));
        ID->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_5->setStyleSheet(QString::fromUtf8("color: #000000  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        label_9 = new QLabel(tab);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 350, 201, 21));
        label_9->setStyleSheet(QString::fromUtf8("color: #000000  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        addButton = new QPushButton(tab);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(50, 410, 101, 51));
        addButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7DDE92; /* vert pastel cool */\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #6CCB82; /* hover vert */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5BB56F; /* vert press\303\251 */\n"
"}\n"
""));
        Nom = new QLineEdit(tab);
        Nom->setObjectName("Nom");
        Nom->setGeometry(QRect(660, 190, 271, 41));
        Nom->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        EM = new QLineEdit(tab);
        EM->setObjectName("EM");
        EM->setGeometry(QRect(660, 260, 271, 41));
        EM->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        dd = new QDateEdit(tab);
        dd->setObjectName("dd");
        dd->setGeometry(QRect(200, 280, 194, 29));
        dd->setStyleSheet(QString::fromUtf8("color: #FFFF;  /* texte noir */"));
        df = new QDateEdit(tab);
        df->setObjectName("df");
        df->setGeometry(QRect(200, 350, 194, 29));
        df->setStyleSheet(QString::fromUtf8("color: #FFFF;  /* texte noir */"));
        STS = new QComboBox(tab);
        STS->addItem(QString());
        STS->addItem(QString());
        STS->addItem(QString());
        STS->setObjectName("STS");
        STS->setGeometry(QRect(660, 350, 271, 41));
        STS->setStyleSheet(QString::fromUtf8("color: #FFFF  /* texte noir */;\n"
"\n"
"font: 12pt \"MS Serif\";\n"
""));
        updateButton = new QPushButton(tab);
        updateButton->setObjectName("updateButton");
        updateButton->setGeometry(QRect(310, 410, 121, 51));
        updateButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #aee1f9;   /* bleu clair pastel */\n"
"    color: #1b4f72;              /* bleu fonc\303\251 lisible */\n"
"    border-radius: 12px;\n"
"    padding: 10px 22px;\n"
"    font-weight: bold;\n"
"    border: 2px solid #87cdee;   /* contour l\303\251ger */\n"
"}\n"
"\n"
"/* Hover \342\200\223 plus vif */\n"
"QPushButton:hover {\n"
"    background-color: #87cdee;   /* bleu un peu plus fonc\303\251 */\n"
"    border-color: #5ab3d6;\n"
"}\n"
"\n"
"/* Pressed \342\200\223 effet enfonc\303\251 */\n"
"QPushButton:pressed {\n"
"    background-color: #74c0e3;   /* bleu plus soutenu */\n"
"    border-color: #4c9fcf;\n"
"}\n"
"\n"
"/* Optionnel : effet de transition */\n"
"QPushButton {\n"
"    transition: 0.25s;\n"
"}\n"
""));
        clear = new QPushButton(tab);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(180, 410, 111, 51));
        clear->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #55efc4; /* vert menthe clair */\n"
"    color: #2d3436;  /* texte fonc\303\251 pour contraste */\n"
"    border-radius: 10px;\n"
"    padding: 8px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2ecc71; /* vert plus appuy\303\251 */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #27ae60; /* vert profond */\n"
"}\n"
""));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        horizontalLayoutWidget = new QWidget(tab_3);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(420, 10, 541, 581));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        calendrier = new QPushButton(horizontalLayoutWidget);
        calendrier->setObjectName("calendrier");
        calendrier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        horizontalLayout->addWidget(calendrier);

        Stat = new QPushButton(horizontalLayoutWidget);
        Stat->setObjectName("Stat");
        Stat->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        horizontalLayout->addWidget(Stat);

        tabWidget->addTab(tab_3, QString());
        SponsorForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SponsorForm);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1718, 25));
        menuG_SPONSORING = new QMenu(menubar);
        menuG_SPONSORING->setObjectName("menuG_SPONSORING");
        SponsorForm->setMenuBar(menubar);
        statusbar = new QStatusBar(SponsorForm);
        statusbar->setObjectName("statusbar");
        SponsorForm->setStatusBar(statusbar);

        menubar->addAction(menuG_SPONSORING->menuAction());

        retranslateUi(SponsorForm);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SponsorForm);
    } // setupUi

    void retranslateUi(QMainWindow *SponsorForm)
    {
        SponsorForm->setWindowTitle(QCoreApplication::translate("SponsorForm", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = affiche->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SponsorForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = affiche->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SponsorForm", "Nom ", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = affiche->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SponsorForm", "Date-D", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = affiche->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SponsorForm", "Date-F", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = affiche->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SponsorForm", "E-Mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = affiche->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SponsorForm", "Status", nullptr));
        search1->setText(QString());
        search1->setPlaceholderText(QCoreApplication::translate("SponsorForm", "Entrer ID a recherch\303\251", nullptr));
        search1_2->setText(QCoreApplication::translate("SponsorForm", "\360\237\224\215Search", nullptr));
        pdfexport->setText(QCoreApplication::translate("SponsorForm", "\360\237\223\245Exporter PDF", nullptr));
        deleteButton->setText(QCoreApplication::translate("SponsorForm", "\360\237\227\221Delete ", nullptr));
        label->setText(QCoreApplication::translate("SponsorForm", "Gestion Sposoring Management", nullptr));
        sort->setText(QCoreApplication::translate("SponsorForm", "\360\237\224\204Sort by ID", nullptr));
        afficherButton->setText(QCoreApplication::translate("SponsorForm", "Afficher", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SponsorForm", "\360\237\214\220Display", nullptr));
        label_7->setText(QCoreApplication::translate("SponsorForm", "Email", nullptr));
        label_4->setText(QCoreApplication::translate("SponsorForm", "Date-D\303\251but", nullptr));
        label_3->setText(QCoreApplication::translate("SponsorForm", "Nom-Sponsor", nullptr));
        label_2->setText(QCoreApplication::translate("SponsorForm", "ID-SPONSOR", nullptr));
        ID->setText(QString());
        ID->setPlaceholderText(QCoreApplication::translate("SponsorForm", "Entrez L'ID", nullptr));
        label_5->setText(QCoreApplication::translate("SponsorForm", " Status :", nullptr));
        label_9->setText(QCoreApplication::translate("SponsorForm", "Date-Fin", nullptr));
        addButton->setText(QCoreApplication::translate("SponsorForm", "\342\236\225 Add", nullptr));
        Nom->setText(QString());
        Nom->setPlaceholderText(QCoreApplication::translate("SponsorForm", "Entrez le Nom de Sponsor...", nullptr));
        EM->setText(QString());
        EM->setPlaceholderText(QCoreApplication::translate("SponsorForm", "Entrez l'Email", nullptr));
        STS->setItemText(0, QCoreApplication::translate("SponsorForm", "Selectionner...", nullptr));
        STS->setItemText(1, QCoreApplication::translate("SponsorForm", "Active", nullptr));
        STS->setItemText(2, QCoreApplication::translate("SponsorForm", "Non Active", nullptr));

        STS->setPlaceholderText(QString());
        updateButton->setText(QCoreApplication::translate("SponsorForm", "\342\234\250Modify ", nullptr));
        clear->setText(QCoreApplication::translate("SponsorForm", "\342\234\250Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SponsorForm", "\342\236\225Add", nullptr));
        calendrier->setText(QCoreApplication::translate("SponsorForm", "\360\237\223\205Calendrier", nullptr));
        Stat->setText(QCoreApplication::translate("SponsorForm", "\360\237\223\212Stat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("SponsorForm", "\360\237\223\212Gestion", nullptr));
        menuG_SPONSORING->setTitle(QCoreApplication::translate("SponsorForm", "G SPONSORING", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SponsorForm: public Ui_SponsorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPONSORF_H
