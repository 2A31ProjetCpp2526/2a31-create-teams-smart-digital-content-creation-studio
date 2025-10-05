/********************************************************************************
** Form generated from reading UI file 'media.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIA_H
#define UI_MEDIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_media
{
public:
    QLabel *label_11;
    QPushButton *pushButton_5;
    QPushButton *rb;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QPushButton *media_2;
    QLabel *label_12;
    QPushButton *crud;
    QLabel *label_9;
    QPushButton *pushButton_4;

    void setupUi(QWidget *media)
    {
        if (media->objectName().isEmpty())
            media->setObjectName("media");
        media->resize(1315, 680);
        label_11 = new QLabel(media);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(110, 470, 261, 31));
        label_11->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        pushButton_5 = new QPushButton(media);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(210, 400, 111, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        rb = new QPushButton(media);
        rb->setObjectName("rb");
        rb->setGeometry(QRect(1120, 20, 141, 41));
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
        label_8 = new QLabel(media);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(90, 110, 261, 31));
        label_8->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        lineEdit_5 = new QLineEdit(media);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(230, 210, 641, 41));
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
        label_10 = new QLabel(media);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(140, 260, 351, 41));
        label_10->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        media_2 = new QPushButton(media);
        media_2->setObjectName("media_2");
        media_2->setGeometry(QRect(960, 20, 141, 41));
        media_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_12 = new QLabel(media);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(110, 560, 261, 31));
        label_12->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(30, 136, 229);   /* bleu */\n"
""));
        crud = new QPushButton(media);
        crud->setObjectName("crud");
        crud->setGeometry(QRect(800, 20, 141, 41));
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
        label_9 = new QLabel(media);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(140, 170, 351, 41));
        label_9->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"    font-weight: 500;\n"
"    color: #2980b9;        /* Deep blue */\n"
"    margin-bottom: 4px;"));
        pushButton_4 = new QPushButton(media);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(250, 310, 391, 51));
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

        retranslateUi(media);

        QMetaObject::connectSlotsByName(media);
    } // setupUi

    void retranslateUi(QWidget *media)
    {
        media->setWindowTitle(QCoreApplication::translate("media", "Form", nullptr));
        label_11->setText(QCoreApplication::translate("media", "PREVIEW : ", nullptr));
        pushButton_5->setText(QCoreApplication::translate("media", "UPLOAD", nullptr));
        rb->setText(QCoreApplication::translate("media", "ROLLBACK", nullptr));
        label_8->setText(QCoreApplication::translate("media", "ADD MEDIA", nullptr));
        label_10->setText(QCoreApplication::translate("media", "Insert an image or video : ", nullptr));
        media_2->setText(QCoreApplication::translate("media", "MEDIA", nullptr));
        label_12->setText(QCoreApplication::translate("media", "UPLOADED MEDIA : ", nullptr));
        crud->setText(QCoreApplication::translate("media", "CRUD", nullptr));
        label_9->setText(QCoreApplication::translate("media", "Media Description :", nullptr));
        pushButton_4->setText(QCoreApplication::translate("media", "CHOOSE FILE TO UPLOAD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class media: public Ui_media {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIA_H
