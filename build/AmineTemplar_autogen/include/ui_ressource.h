/********************************************************************************
** Form generated from reading UI file 'ressource.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESSOURCE_H
#define UI_RESSOURCE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
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

class Ui_RessourceWidget
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
    QLabel *addServicePriceLabel;
    QLineEdit *addPriceEdit;
    QLabel *addServiceDateLabel;
    QDateTimeEdit *addDateEdit;
    QHBoxLayout *addButtonLayout;
    QSpacerItem *addButtonSpacer;
    QPushButton *addServiceBtn;
    QSpacerItem *addVerticalSpacer;
    QWidget *voiceChatTab;
    QVBoxLayout *voiceChatLayout;
    QHBoxLayout *voiceControlLayout;
    QWidget *modifyTab;
    QVBoxLayout *modifyLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QWidget *RessourceWidget)
    {
        if (RessourceWidget->objectName().isEmpty())
            RessourceWidget->setObjectName("RessourceWidget");
        RessourceWidget->resize(1200, 800);
        centralwidget = new QWidget(RessourceWidget);
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
        if (clientsTable->columnCount() < 9)
            clientsTable->setColumnCount(9);
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
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        clientsTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        clientsTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        clientsTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        clientsTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        clientsTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        clientsTable->setObjectName("clientsTable");
        clientsTable->setColumnCount(9);

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
        addCategoryCombo->addItem(QString());
        addCategoryCombo->addItem(QString());
        addCategoryCombo->setObjectName("addCategoryCombo");

        addFormLayout->setWidget(3, QFormLayout::FieldRole, addCategoryCombo);

        addServicePriceLabel = new QLabel(addTab);
        addServicePriceLabel->setObjectName("addServicePriceLabel");

        addFormLayout->setWidget(4, QFormLayout::LabelRole, addServicePriceLabel);

        addPriceEdit = new QLineEdit(addTab);
        addPriceEdit->setObjectName("addPriceEdit");

        addFormLayout->setWidget(4, QFormLayout::FieldRole, addPriceEdit);

        addServiceDateLabel = new QLabel(addTab);
        addServiceDateLabel->setObjectName("addServiceDateLabel");

        addFormLayout->setWidget(5, QFormLayout::LabelRole, addServiceDateLabel);

        addDateEdit = new QDateTimeEdit(addTab);
        addDateEdit->setObjectName("addDateEdit");

        addFormLayout->setWidget(5, QFormLayout::FieldRole, addDateEdit);


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

        voiceChatLayout->addLayout(voiceControlLayout);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/qrcode.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(voiceChatTab, icon6, QString());
        modifyTab = new QWidget();
        modifyTab->setObjectName("modifyTab");
        modifyLayout = new QVBoxLayout(modifyTab);
        modifyLayout->setSpacing(15);
        modifyLayout->setObjectName("modifyLayout");
        modifyLayout->setContentsMargins(20, 20, 20, 20);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/upload.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clientTabWidget->addTab(modifyTab, icon7, QString());

        mainLayout->addWidget(clientTabWidget);

        menubar = new QMenuBar(RessourceWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        statusbar = new QStatusBar(RessourceWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 20, 25));

        retranslateUi(RessourceWidget);

        clientTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RessourceWidget);
    } // setupUi

    void retranslateUi(QWidget *RessourceWidget)
    {
        RessourceWidget->setStyleSheet(QCoreApplication::translate("RessourceWidget", "QMainWindow {\n"
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
        headerTitle->setText(QCoreApplication::translate("RessourceWidget", "Resources Management", nullptr));
        searchServices->setPlaceholderText(QCoreApplication::translate("RessourceWidget", "Search resources...", nullptr));
        exportCsvBtn->setText(QCoreApplication::translate("RessourceWidget", "Export CSV", nullptr));
        btnSortByName->setText(QCoreApplication::translate("RessourceWidget", "Sort by Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RessourceWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RessourceWidget", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RessourceWidget", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RessourceWidget", "Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = clientsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("RessourceWidget", "Enterprise", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = clientsTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("RessourceWidget", "Format", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = clientsTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("RessourceWidget", "Owner", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = clientsTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("RessourceWidget", "Upload Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = clientsTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("RessourceWidget", "Tags", nullptr));
        btnEditService->setText(QCoreApplication::translate("RessourceWidget", "Edit", nullptr));
        btnDeleteService->setText(QCoreApplication::translate("RessourceWidget", "Delete", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(serviceManagementTab), QCoreApplication::translate("RessourceWidget", "Resources Management", nullptr));
        addLabel->setText(QCoreApplication::translate("RessourceWidget", "Add New Resources", nullptr));
        addServiceIdLabel->setText(QCoreApplication::translate("RessourceWidget", "Title", nullptr));
        addServiceIdEdit->setPlaceholderText(QCoreApplication::translate("RessourceWidget", "Enter resource title...", nullptr));
        addServiceNameLabel->setText(QCoreApplication::translate("RessourceWidget", "Path", nullptr));
        addServiceDescLabel->setText(QCoreApplication::translate("RessourceWidget", "Owner", nullptr));
        addServiceCategoryLabel->setText(QCoreApplication::translate("RessourceWidget", "Format", nullptr));
        addCategoryCombo->setItemText(0, QCoreApplication::translate("RessourceWidget", "MP4", nullptr));
        addCategoryCombo->setItemText(1, QCoreApplication::translate("RessourceWidget", "MP3", nullptr));
        addCategoryCombo->setItemText(2, QCoreApplication::translate("RessourceWidget", "JPG", nullptr));
        addCategoryCombo->setItemText(3, QCoreApplication::translate("RessourceWidget", "PNG", nullptr));

        addServicePriceLabel->setText(QCoreApplication::translate("RessourceWidget", "Access", nullptr));
        addServiceDateLabel->setText(QCoreApplication::translate("RessourceWidget", "Upload Date", nullptr));
        addDateEdit->setDisplayFormat(QCoreApplication::translate("RessourceWidget", "yyyy-MM-dd HH:mm", nullptr));
        addServiceBtn->setText(QCoreApplication::translate("RessourceWidget", "Add", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(addTab), QCoreApplication::translate("RessourceWidget", "Add", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(voiceChatTab), QCoreApplication::translate("RessourceWidget", "QR Code", nullptr));
        clientTabWidget->setTabText(clientTabWidget->indexOf(modifyTab), QCoreApplication::translate("RessourceWidget", "Insertion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RessourceWidget: public Ui_RessourceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESSOURCE_H
