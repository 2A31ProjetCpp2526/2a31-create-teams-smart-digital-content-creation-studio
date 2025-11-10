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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
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
    QLabel *headerTitle;
    QHBoxLayout *topControlsLayout;
    QLineEdit *searchServices;
    QSpacerItem *topControlsSpacer;
    QPushButton *exportCsvBtn;
    QPushButton *btnSortByName;
    QTableWidget *clientsTable;
    QHBoxLayout *serviceButtonsLayout;
    QSpacerItem *serviceButtonsSpacer;
    QPushButton *btnEditService;
    QPushButton *btnDeleteService;
    QWidget *addTab;
    QVBoxLayout *addLayout;
    QLabel *addLabel;
    QFormLayout *addFormLayout;
    QLabel *addServiceIdLabel;
    QLineEdit *addServiceIdEdit;
    QLabel *addServiceNameLabel;
    QLineEdit *addNameEdit;
    QLabel *addServiceDescLabel;
    QTextEdit *addDescriptionEdit;
    QLabel *addServiceCategoryLabel;
    QComboBox *addCategoryCombo;
    QHBoxLayout *addButtonLayout;
    QSpacerItem *addButtonSpacer;
    QPushButton *addServiceBtn;
    QSpacerItem *addVerticalSpacer;
    QWidget *voiceChatTab;
    QVBoxLayout *voiceChatLayout;
    QHBoxLayout *voiceControlLayout;
    QTextEdit *addDescriptionEdit_2;
    QWidget *modifyTab;
    QVBoxLayout *modifyLayout;
    QLineEdit *searchServices_2;
    QPushButton *exportCsvBtn_2;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QTextEdit *addDescriptionEdit_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QWidget *ProjectWidget)
    {
        if (ProjectWidget->objectName().isEmpty())
            ProjectWidget->setObjectName("ProjectWidget");
        ProjectWidget->resize(1200, 800);
        centralwidget = new QWidget(ProjectWidget);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(10, 20, 1241, 665));
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
        headerTitle = new QLabel(serviceManagementTab);
        headerTitle->setObjectName("headerTitle");
        headerTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        serviceManagementLayout->addWidget(headerTitle);

        topControlsLayout = new QHBoxLayout();
        topControlsLayout->setObjectName("topControlsLayout");
        searchServices = new QLineEdit(serviceManagementTab);
        searchServices->setObjectName("searchServices");
        searchServices->setMinimumSize(QSize(250, 0));
        searchServices->setClearButtonEnabled(true);

        topControlsLayout->addWidget(searchServices);

        topControlsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topControlsLayout->addItem(topControlsSpacer);

        exportCsvBtn = new QPushButton(serviceManagementTab);
        exportCsvBtn->setObjectName("exportCsvBtn");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/export.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        exportCsvBtn->setIcon(icon);
        exportCsvBtn->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(exportCsvBtn);

        btnSortByName = new QPushButton(serviceManagementTab);
        btnSortByName->setObjectName("btnSortByName");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/sort.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSortByName->setIcon(icon1);
        btnSortByName->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(btnSortByName);


        serviceManagementLayout->addLayout(topControlsLayout);

        clientsTable = new QTableWidget(serviceManagementTab);
        if (clientsTable->columnCount() < 4)
            clientsTable->setColumnCount(4);
        QFont font;
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        clientsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        clientsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        clientsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        clientsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        clientsTable->setObjectName("clientsTable");
        clientsTable->setColumnCount(4);

        serviceManagementLayout->addWidget(clientsTable);

        serviceButtonsLayout = new QHBoxLayout();
        serviceButtonsLayout->setObjectName("serviceButtonsLayout");
        serviceButtonsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        serviceButtonsLayout->addItem(serviceButtonsSpacer);

        btnEditService = new QPushButton(serviceManagementTab);
        btnEditService->setObjectName("btnEditService");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/modify.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnEditService->setIcon(icon2);
        btnEditService->setIconSize(QSize(16, 16));

        serviceButtonsLayout->addWidget(btnEditService);

        btnDeleteService = new QPushButton(serviceManagementTab);
        btnDeleteService->setObjectName("btnDeleteService");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDeleteService->setIcon(icon3);
        btnDeleteService->setIconSize(QSize(16, 16));

        serviceButtonsLayout->addWidget(btnDeleteService);


        serviceManagementLayout->addLayout(serviceButtonsLayout);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/clients.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(serviceManagementTab, icon4, QString());
        addTab = new QWidget();
        addTab->setObjectName("addTab");
        addLayout = new QVBoxLayout(addTab);
        addLayout->setSpacing(15);
        addLayout->setObjectName("addLayout");
        addLayout->setContentsMargins(20, 20, 20, 20);
        addLabel = new QLabel(addTab);
        addLabel->setObjectName("addLabel");
        addLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        addLayout->addWidget(addLabel);

        addFormLayout = new QFormLayout();
        addFormLayout->setObjectName("addFormLayout");
        addServiceIdLabel = new QLabel(addTab);
        addServiceIdLabel->setObjectName("addServiceIdLabel");

        addFormLayout->setWidget(0, QFormLayout::LabelRole, addServiceIdLabel);

        addServiceIdEdit = new QLineEdit(addTab);
        addServiceIdEdit->setObjectName("addServiceIdEdit");
        addServiceIdEdit->setReadOnly(true);

        addFormLayout->setWidget(0, QFormLayout::FieldRole, addServiceIdEdit);

        addServiceNameLabel = new QLabel(addTab);
        addServiceNameLabel->setObjectName("addServiceNameLabel");

        addFormLayout->setWidget(1, QFormLayout::LabelRole, addServiceNameLabel);

        addNameEdit = new QLineEdit(addTab);
        addNameEdit->setObjectName("addNameEdit");

        addFormLayout->setWidget(1, QFormLayout::FieldRole, addNameEdit);

        addServiceDescLabel = new QLabel(addTab);
        addServiceDescLabel->setObjectName("addServiceDescLabel");

        addFormLayout->setWidget(2, QFormLayout::LabelRole, addServiceDescLabel);

        addDescriptionEdit = new QTextEdit(addTab);
        addDescriptionEdit->setObjectName("addDescriptionEdit");

        addFormLayout->setWidget(2, QFormLayout::FieldRole, addDescriptionEdit);

        addServiceCategoryLabel = new QLabel(addTab);
        addServiceCategoryLabel->setObjectName("addServiceCategoryLabel");

        addFormLayout->setWidget(3, QFormLayout::LabelRole, addServiceCategoryLabel);

        addCategoryCombo = new QComboBox(addTab);
        addCategoryCombo->addItem(QString());
        addCategoryCombo->addItem(QString());
        addCategoryCombo->setObjectName("addCategoryCombo");

        addFormLayout->setWidget(3, QFormLayout::FieldRole, addCategoryCombo);


        addLayout->addLayout(addFormLayout);

        addButtonLayout = new QHBoxLayout();
        addButtonLayout->setObjectName("addButtonLayout");
        addButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        addButtonLayout->addItem(addButtonSpacer);

        addServiceBtn = new QPushButton(addTab);
        addServiceBtn->setObjectName("addServiceBtn");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addServiceBtn->setIcon(icon5);

        addButtonLayout->addWidget(addServiceBtn);


        addLayout->addLayout(addButtonLayout);

        addVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        addLayout->addItem(addVerticalSpacer);

        clientTabWidget->addTab(addTab, icon5, QString());
        voiceChatTab = new QWidget();
        voiceChatTab->setObjectName("voiceChatTab");
        voiceChatLayout = new QVBoxLayout(voiceChatTab);
        voiceChatLayout->setSpacing(15);
        voiceChatLayout->setObjectName("voiceChatLayout");
        voiceChatLayout->setContentsMargins(20, 20, 20, 20);
        voiceControlLayout = new QHBoxLayout();
        voiceControlLayout->setObjectName("voiceControlLayout");
        addDescriptionEdit_2 = new QTextEdit(voiceChatTab);
        addDescriptionEdit_2->setObjectName("addDescriptionEdit_2");

        voiceControlLayout->addWidget(addDescriptionEdit_2);


        voiceChatLayout->addLayout(voiceControlLayout);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/undo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(voiceChatTab, icon6, QString());
        modifyTab = new QWidget();
        modifyTab->setObjectName("modifyTab");
        modifyLayout = new QVBoxLayout(modifyTab);
        modifyLayout->setSpacing(15);
        modifyLayout->setObjectName("modifyLayout");
        modifyLayout->setContentsMargins(20, 20, 20, 20);
        searchServices_2 = new QLineEdit(modifyTab);
        searchServices_2->setObjectName("searchServices_2");
        searchServices_2->setMinimumSize(QSize(250, 0));
        searchServices_2->setClearButtonEnabled(true);

        modifyLayout->addWidget(searchServices_2);

        exportCsvBtn_2 = new QPushButton(modifyTab);
        exportCsvBtn_2->setObjectName("exportCsvBtn_2");
        exportCsvBtn_2->setIcon(icon);
        exportCsvBtn_2->setIconSize(QSize(16, 16));

        modifyLayout->addWidget(exportCsvBtn_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        modifyLayout->addItem(verticalSpacer);

        label = new QLabel(modifyTab);
        label->setObjectName("label");

        modifyLayout->addWidget(label);

        addDescriptionEdit_3 = new QTextEdit(modifyTab);
        addDescriptionEdit_3->setObjectName("addDescriptionEdit_3");

        modifyLayout->addWidget(addDescriptionEdit_3);

        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/camera.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(modifyTab, icon7, QString());

        mainLayout->addWidget(clientTabWidget);

        menubar = new QMenuBar(ProjectWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        statusbar = new QStatusBar(ProjectWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 20, 25));

        retranslateUi(ProjectWidget);

        clientTabWidget->setCurrentIndex(3);


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
        headerTitle->setText(QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        searchServices->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Search project...", nullptr));
        exportCsvBtn->setText(QCoreApplication::translate("ProjectWidget", "Export CSV", nullptr));
        btnSortByName->setText(QCoreApplication::translate("ProjectWidget", "Sort by Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ProjectWidget", "Project ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ProjectWidget", "Titre", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ProjectWidget", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ProjectWidget", "Status", nullptr));
        btnEditService->setText(QCoreApplication::translate("ProjectWidget", "Edit", nullptr));
        btnDeleteService->setText(QCoreApplication::translate("ProjectWidget", "Delete", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(serviceManagementTab), QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        addLabel->setText(QCoreApplication::translate("ProjectWidget", "Add New Project", nullptr));
        addServiceIdLabel->setText(QCoreApplication::translate("ProjectWidget", "Project ID", nullptr));
        addServiceNameLabel->setText(QCoreApplication::translate("ProjectWidget", "Titre", nullptr));
        addServiceDescLabel->setText(QCoreApplication::translate("ProjectWidget", "Description:", nullptr));
        addServiceCategoryLabel->setText(QCoreApplication::translate("ProjectWidget", "Status", nullptr));
        addCategoryCombo->setItemText(0, QCoreApplication::translate("ProjectWidget", "Yes", nullptr));
        addCategoryCombo->setItemText(1, QCoreApplication::translate("ProjectWidget", "No", nullptr));

        addServiceBtn->setText(QCoreApplication::translate("ProjectWidget", "Add Project", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(addTab), QCoreApplication::translate("ProjectWidget", "Add", nullptr));
        addDescriptionEdit_2->setHtml(QCoreApplication::translate("ProjectWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Version 2.0 - 27 / 09 / 2025</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Mod Color</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; ma"
                        "rgin-right:0px; -qt-block-indent:0; text-indent:0px;\">Version 1.5 - 20 / 09 /2025</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">New Item</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Version 1.0 - 10 / 09 / 2025</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(voiceChatTab), QCoreApplication::translate("ProjectWidget", "RollBack", nullptr));
        searchServices_2->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Media Description...", nullptr));
        exportCsvBtn_2->setText(QCoreApplication::translate("ProjectWidget", "Chose File to upload", nullptr));
        label->setText(QCoreApplication::translate("ProjectWidget", "Preview :", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(modifyTab), QCoreApplication::translate("ProjectWidget", "Insertion of images and videos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectWidget: public Ui_ProjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
