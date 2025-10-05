/********************************************************************************
** Form generated from reading UI file 'rb.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RB_H
#define UI_RB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rb
{
public:
    QLabel *label_2;
    QPushButton *rb_2;
    QLabel *label_8;
    QPushButton *media;
    QPushButton *pushButton_5;
    QPushButton *crud;
    QListWidget *listWidget;

    void setupUi(QWidget *rb)
    {
        if (rb->objectName().isEmpty())
            rb->setObjectName("rb");
        rb->resize(1314, 679);
        label_2 = new QLabel(rb);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 240, 471, 71));
        label_2->setStyleSheet(QString::fromUtf8("font:700 14pt \"Segoe UI\";"));
        rb_2 = new QPushButton(rb);
        rb_2->setObjectName("rb_2");
        rb_2->setGeometry(QRect(1110, 30, 141, 41));
        rb_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_8 = new QLabel(rb);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(80, 120, 361, 31));
        label_8->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        media = new QPushButton(rb);
        media->setObjectName("media");
        media->setGeometry(QRect(950, 30, 141, 41));
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
        pushButton_5 = new QPushButton(rb);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1080, 520, 151, 31));
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
        crud = new QPushButton(rb);
        crud->setObjectName("crud");
        crud->setGeometry(QRect(790, 30, 141, 41));
        crud->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        listWidget = new QListWidget(rb);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(90, 190, 1111, 301));

        retranslateUi(rb);

        QMetaObject::connectSlotsByName(rb);
    } // setupUi

    void retranslateUi(QWidget *rb)
    {
        rb->setWindowTitle(QCoreApplication::translate("rb", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("rb", "Installer des Photos et des Videos  :", nullptr));
        rb_2->setText(QCoreApplication::translate("rb", "ROLLBACK", nullptr));
        label_8->setText(QCoreApplication::translate("rb", "Rollback (Version History)", nullptr));
        media->setText(QCoreApplication::translate("rb", "MEDIA", nullptr));
        pushButton_5->setText(QCoreApplication::translate("rb", "RESTORE", nullptr));
        crud->setText(QCoreApplication::translate("rb", "CRUD", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("rb", "Version 2.0 - 27/09/2025\n"
"", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("rb", "Mod color", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("rb", "Version 1.5 - 20/09/2025\n"
"", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("rb", "New Item", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("rb", "Version 1.0 - 10/09/2025\n"
"", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class rb: public Ui_rb {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RB_H
