/********************************************************************************
** Form generated from reading UI file 'project.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QTabWidget *projectTabWidget;
    QWidget *projectManagementTab;
    QVBoxLayout *projectManagementLayout;
    QLabel *headerTitle;
    QHBoxLayout *topControlsLayout;
    QLineEdit *searchServices;
    QPushButton *searchprojet;
    QSpacerItem *topControlsSpacer;
    QPushButton *sortbytitle;
    QPushButton *exportexel;
    QPushButton *statistics;
    QPushButton *btnSortByName;
    QTableWidget *projectTableWidget;
    QHBoxLayout *projectButtonsLayout;
    QSpacerItem *projectButtonsSpacer;
    QPushButton *btnEditService;
    QPushButton *btnDeleteService;
    QWidget *addTab;
    QVBoxLayout *addLayout;
    QLabel *addLabel;
    QFormLayout *addFormLayout;
    QLabel *addTitleLabel;
    QLineEdit *addTitleEdit;
    QLabel *addDescriptionLabel;
    QTextEdit *addDescriptionEdit;
    QLabel *addClientIdLabel;
    QLineEdit *addClientIdEdit;
    QLabel *addServiceIdLabel;
    QLineEdit *addServiceIdEdit;
    QLabel *addCreationDateLabel;
    QDateEdit *addCreationDateEdit;
    QLabel *addModificationDateLabel;
    QDateEdit *addModificationDateEdit;
    QHBoxLayout *addButtonLayout;
    QSpacerItem *addButtonSpacer;
    QPushButton *addServiceBtn;
    QSpacerItem *addVerticalSpacer;
    QWidget *modifyTab;
    QVBoxLayout *modifyLayout;
    QLabel *modifyLabel;
    QFormLayout *modifyFormLayout;
    QLabel *modifyIdLabel;
    QLineEdit *modifyIdEdit;
    QLabel *modifyTitleLabel;
    QLineEdit *modifyTitleEdit;
    QLabel *modifyDescriptionLabel;
    QTextEdit *modifyDescriptionEdit;
    QLabel *modifyClientIdLabel;
    QLineEdit *modifyClientIdEdit;
    QLabel *modifyServiceIdLabel;
    QLineEdit *modifyServiceIdEdit;
    QLabel *modifyCreationDateLabel;
    QDateEdit *modifyCreationDateEdit;
    QLabel *modifyModificationDateLabel;
    QDateEdit *modifyModificationDateEdit;
    QHBoxLayout *modifyButtonLayout;
    QSpacerItem *modifyButtonSpacer;
    QPushButton *modifyServiceBtn;
    QSpacerItem *modifyVerticalSpacer;
    QWidget *Rollback;
    QVBoxLayout *rollbackLayout;
    QLabel *rollbackLabel;
    QListWidget *rollbackList;
    QHBoxLayout *rollbackButtonsLayout;
    QLineEdit *rollbackNewEntryEdit;
    QPushButton *rollbackAddBtn;
    QPushButton *rollbackDoBtn;
    QPushButton *rollbackClearBtn;
    QWidget *Insertion;
    QVBoxLayout *insertionLayout;
    QLabel *insertionLabel;
    QHBoxLayout *insertionTopLayout;
    QListWidget *insertionList;
    QVBoxLayout *insertionPreviewLayout;
    QFrame *insertionPreviewFrame;
    QVBoxLayout *previewFrameLayout;
    QLabel *insertionPreview;
    QHBoxLayout *videoControlsLayout;
    QPushButton *insertionPlayBtn;
    QSlider *insertionSlider;
    QHBoxLayout *insertionButtonsLayout;
    QPushButton *insertionAddBtn;
    QPushButton *insertionRemoveBtn;
    QPushButton *insertionClearBtn;
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
        projectTabWidget = new QTabWidget(centralwidget);
        projectTabWidget->setObjectName("projectTabWidget");
        projectManagementTab = new QWidget();
        projectManagementTab->setObjectName("projectManagementTab");
        projectManagementLayout = new QVBoxLayout(projectManagementTab);
        projectManagementLayout->setSpacing(10);
        projectManagementLayout->setObjectName("projectManagementLayout");
        projectManagementLayout->setContentsMargins(10, 10, 10, 10);
        headerTitle = new QLabel(projectManagementTab);
        headerTitle->setObjectName("headerTitle");
        headerTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        projectManagementLayout->addWidget(headerTitle);

        topControlsLayout = new QHBoxLayout();
        topControlsLayout->setObjectName("topControlsLayout");
        searchServices = new QLineEdit(projectManagementTab);
        searchServices->setObjectName("searchServices");
        searchServices->setMinimumSize(QSize(250, 0));
        searchServices->setClearButtonEnabled(true);

        topControlsLayout->addWidget(searchServices);

        searchprojet = new QPushButton(projectManagementTab);
        searchprojet->setObjectName("searchprojet");
        searchprojet->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ff4da6;      /* Rose vif */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 4px;             /* Rectangle avec l\303\251ger arrondi */\n"
"    padding: 6px 14px;              /* Taille normale */\n"
"    font-weight: 600;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    letter-spacing: 0.3px;\n"
"    transition: all 0.2s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ff1f8f;      /* Rose plus fonc\303\251 */\n"
"    box-shadow: 0 4px 14px rgba(255, 77, 166, 0.5);\n"
"    transform: translateY(-2px);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #e60073;      /* Rose profond */\n"
"    transform: translateY(0px);\n"
"    box-shadow: 0 2px 6px rgba(255, 77, 166, 0.3);\n"
"}\n"
""));
        searchprojet->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(searchprojet);

        topControlsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topControlsLayout->addItem(topControlsSpacer);

        sortbytitle = new QPushButton(projectManagementTab);
        sortbytitle->setObjectName("sortbytitle");
        sortbytitle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ff8c00;      /* Orange */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 4px;             /* Rectangle l\303\251ger */\n"
"    padding: 6px 14px;              /* Taille normale */\n"
"    font-weight: 600;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    letter-spacing: 0.3px;\n"
"    transition: all 0.2s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #e67e00;      /* Orange plus fonc\303\251 au hover */\n"
"    box-shadow: 0 4px 14px rgba(255, 140, 0, 0.45);\n"
"    transform: translateY(-2px);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #cc6f00;      /* Orange profond */\n"
"    transform: translateY(0px);\n"
"    box-shadow: 0 2px 6px rgba(255, 140, 0, 0.3);\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/sort.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        sortbytitle->setIcon(icon);
        sortbytitle->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(sortbytitle);

        exportexel = new QPushButton(projectManagementTab);
        exportexel->setObjectName("exportexel");
        exportexel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f1c40f;      /* Jaune vif / gold */\n"
"    color: black;                   /* Meilleure lisibilit\303\251 sur jaune */\n"
"    border: none;\n"
"    border-radius: 4px;             /* Rectangle l\303\251ger */\n"
"    padding: 6px 14px;              /* Taille normale */\n"
"    font-weight: 600;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    letter-spacing: 0.3px;\n"
"    transition: all 0.2s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d4ac0d;      /* Jaune fonc\303\251 au hover */\n"
"    box-shadow: 0 4px 14px rgba(241, 196, 15, 0.45);\n"
"    transform: translateY(-2px);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #b7950b;      /* Jaune profond */\n"
"    transform: translateY(0px);\n"
"    box-shadow: 0 2px 6px rgba(241, 196, 15, 0.3);\n"
"}\n"
""));
        exportexel->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(exportexel);

        statistics = new QPushButton(projectManagementTab);
        statistics->setObjectName("statistics");
        statistics->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ff4da6;      /* Rose vif */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 4px;             /* Rectangle avec l\303\251ger arrondi */\n"
"    padding: 6px 14px;              /* Taille normale */\n"
"    font-weight: 600;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    letter-spacing: 0.3px;\n"
"    transition: all 0.2s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ff1f8f;      /* Rose plus fonc\303\251 */\n"
"    box-shadow: 0 4px 14px rgba(255, 77, 166, 0.5);\n"
"    transform: translateY(-2px);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #e60073;      /* Rose profond */\n"
"    transform: translateY(0px);\n"
"    box-shadow: 0 2px 6px rgba(255, 77, 166, 0.3);\n"
"}\n"
""));
        statistics->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(statistics);

        btnSortByName = new QPushButton(projectManagementTab);
        btnSortByName->setObjectName("btnSortByName");
        btnSortByName->setIcon(icon);
        btnSortByName->setIconSize(QSize(16, 16));

        topControlsLayout->addWidget(btnSortByName);


        projectManagementLayout->addLayout(topControlsLayout);

        projectTableWidget = new QTableWidget(projectManagementTab);
        if (projectTableWidget->columnCount() < 8)
            projectTableWidget->setColumnCount(8);
        QFont font;
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        projectTableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        projectTableWidget->setObjectName("projectTableWidget");
        projectTableWidget->setColumnCount(8);

        projectManagementLayout->addWidget(projectTableWidget);

        projectButtonsLayout = new QHBoxLayout();
        projectButtonsLayout->setObjectName("projectButtonsLayout");
        projectButtonsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        projectButtonsLayout->addItem(projectButtonsSpacer);

        btnEditService = new QPushButton(projectManagementTab);
        btnEditService->setObjectName("btnEditService");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/modify.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnEditService->setIcon(icon1);
        btnEditService->setIconSize(QSize(16, 16));

        projectButtonsLayout->addWidget(btnEditService);

        btnDeleteService = new QPushButton(projectManagementTab);
        btnDeleteService->setObjectName("btnDeleteService");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDeleteService->setIcon(icon2);
        btnDeleteService->setIconSize(QSize(16, 16));

        projectButtonsLayout->addWidget(btnDeleteService);


        projectManagementLayout->addLayout(projectButtonsLayout);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/clients.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        projectTabWidget->addTab(projectManagementTab, icon3, QString());
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
        addTitleLabel = new QLabel(addTab);
        addTitleLabel->setObjectName("addTitleLabel");

        addFormLayout->setWidget(0, QFormLayout::LabelRole, addTitleLabel);

        addTitleEdit = new QLineEdit(addTab);
        addTitleEdit->setObjectName("addTitleEdit");

        addFormLayout->setWidget(0, QFormLayout::FieldRole, addTitleEdit);

        addDescriptionLabel = new QLabel(addTab);
        addDescriptionLabel->setObjectName("addDescriptionLabel");

        addFormLayout->setWidget(1, QFormLayout::LabelRole, addDescriptionLabel);

        addDescriptionEdit = new QTextEdit(addTab);
        addDescriptionEdit->setObjectName("addDescriptionEdit");

        addFormLayout->setWidget(1, QFormLayout::FieldRole, addDescriptionEdit);

        addClientIdLabel = new QLabel(addTab);
        addClientIdLabel->setObjectName("addClientIdLabel");

        addFormLayout->setWidget(2, QFormLayout::LabelRole, addClientIdLabel);

        addClientIdEdit = new QLineEdit(addTab);
        addClientIdEdit->setObjectName("addClientIdEdit");

        addFormLayout->setWidget(2, QFormLayout::FieldRole, addClientIdEdit);

        addServiceIdLabel = new QLabel(addTab);
        addServiceIdLabel->setObjectName("addServiceIdLabel");

        addFormLayout->setWidget(3, QFormLayout::LabelRole, addServiceIdLabel);

        addServiceIdEdit = new QLineEdit(addTab);
        addServiceIdEdit->setObjectName("addServiceIdEdit");

        addFormLayout->setWidget(3, QFormLayout::FieldRole, addServiceIdEdit);

        addCreationDateLabel = new QLabel(addTab);
        addCreationDateLabel->setObjectName("addCreationDateLabel");

        addFormLayout->setWidget(4, QFormLayout::LabelRole, addCreationDateLabel);

        addCreationDateEdit = new QDateEdit(addTab);
        addCreationDateEdit->setObjectName("addCreationDateEdit");
        addCreationDateEdit->setDate(QDate(2024, 11, 8));

        addFormLayout->setWidget(4, QFormLayout::FieldRole, addCreationDateEdit);

        addModificationDateLabel = new QLabel(addTab);
        addModificationDateLabel->setObjectName("addModificationDateLabel");

        addFormLayout->setWidget(5, QFormLayout::LabelRole, addModificationDateLabel);

        addModificationDateEdit = new QDateEdit(addTab);
        addModificationDateEdit->setObjectName("addModificationDateEdit");
        addModificationDateEdit->setDate(QDate(2024, 11, 8));

        addFormLayout->setWidget(5, QFormLayout::FieldRole, addModificationDateEdit);


        addLayout->addLayout(addFormLayout);

        addButtonLayout = new QHBoxLayout();
        addButtonLayout->setObjectName("addButtonLayout");
        addButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        addButtonLayout->addItem(addButtonSpacer);

        addServiceBtn = new QPushButton(addTab);
        addServiceBtn->setObjectName("addServiceBtn");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addServiceBtn->setIcon(icon4);

        addButtonLayout->addWidget(addServiceBtn);


        addLayout->addLayout(addButtonLayout);

        addVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        addLayout->addItem(addVerticalSpacer);

        projectTabWidget->addTab(addTab, icon4, QString());
        modifyTab = new QWidget();
        modifyTab->setObjectName("modifyTab");
        modifyLayout = new QVBoxLayout(modifyTab);
        modifyLayout->setSpacing(15);
        modifyLayout->setObjectName("modifyLayout");
        modifyLayout->setContentsMargins(20, 20, 20, 20);
        modifyLabel = new QLabel(modifyTab);
        modifyLabel->setObjectName("modifyLabel");
        modifyLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        modifyLayout->addWidget(modifyLabel);

        modifyFormLayout = new QFormLayout();
        modifyFormLayout->setObjectName("modifyFormLayout");
        modifyIdLabel = new QLabel(modifyTab);
        modifyIdLabel->setObjectName("modifyIdLabel");

        modifyFormLayout->setWidget(0, QFormLayout::LabelRole, modifyIdLabel);

        modifyIdEdit = new QLineEdit(modifyTab);
        modifyIdEdit->setObjectName("modifyIdEdit");

        modifyFormLayout->setWidget(0, QFormLayout::FieldRole, modifyIdEdit);

        modifyTitleLabel = new QLabel(modifyTab);
        modifyTitleLabel->setObjectName("modifyTitleLabel");

        modifyFormLayout->setWidget(1, QFormLayout::LabelRole, modifyTitleLabel);

        modifyTitleEdit = new QLineEdit(modifyTab);
        modifyTitleEdit->setObjectName("modifyTitleEdit");

        modifyFormLayout->setWidget(1, QFormLayout::FieldRole, modifyTitleEdit);

        modifyDescriptionLabel = new QLabel(modifyTab);
        modifyDescriptionLabel->setObjectName("modifyDescriptionLabel");

        modifyFormLayout->setWidget(2, QFormLayout::LabelRole, modifyDescriptionLabel);

        modifyDescriptionEdit = new QTextEdit(modifyTab);
        modifyDescriptionEdit->setObjectName("modifyDescriptionEdit");

        modifyFormLayout->setWidget(2, QFormLayout::FieldRole, modifyDescriptionEdit);

        modifyClientIdLabel = new QLabel(modifyTab);
        modifyClientIdLabel->setObjectName("modifyClientIdLabel");

        modifyFormLayout->setWidget(3, QFormLayout::LabelRole, modifyClientIdLabel);

        modifyClientIdEdit = new QLineEdit(modifyTab);
        modifyClientIdEdit->setObjectName("modifyClientIdEdit");

        modifyFormLayout->setWidget(3, QFormLayout::FieldRole, modifyClientIdEdit);

        modifyServiceIdLabel = new QLabel(modifyTab);
        modifyServiceIdLabel->setObjectName("modifyServiceIdLabel");

        modifyFormLayout->setWidget(4, QFormLayout::LabelRole, modifyServiceIdLabel);

        modifyServiceIdEdit = new QLineEdit(modifyTab);
        modifyServiceIdEdit->setObjectName("modifyServiceIdEdit");

        modifyFormLayout->setWidget(4, QFormLayout::FieldRole, modifyServiceIdEdit);

        modifyCreationDateLabel = new QLabel(modifyTab);
        modifyCreationDateLabel->setObjectName("modifyCreationDateLabel");

        modifyFormLayout->setWidget(5, QFormLayout::LabelRole, modifyCreationDateLabel);

        modifyCreationDateEdit = new QDateEdit(modifyTab);
        modifyCreationDateEdit->setObjectName("modifyCreationDateEdit");
        modifyCreationDateEdit->setReadOnly(true);
        modifyCreationDateEdit->setDate(QDate(2024, 11, 8));

        modifyFormLayout->setWidget(5, QFormLayout::FieldRole, modifyCreationDateEdit);

        modifyModificationDateLabel = new QLabel(modifyTab);
        modifyModificationDateLabel->setObjectName("modifyModificationDateLabel");

        modifyFormLayout->setWidget(6, QFormLayout::LabelRole, modifyModificationDateLabel);

        modifyModificationDateEdit = new QDateEdit(modifyTab);
        modifyModificationDateEdit->setObjectName("modifyModificationDateEdit");
        modifyModificationDateEdit->setDate(QDate(2024, 11, 8));

        modifyFormLayout->setWidget(6, QFormLayout::FieldRole, modifyModificationDateEdit);


        modifyLayout->addLayout(modifyFormLayout);

        modifyButtonLayout = new QHBoxLayout();
        modifyButtonLayout->setObjectName("modifyButtonLayout");
        modifyButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        modifyButtonLayout->addItem(modifyButtonSpacer);

        modifyServiceBtn = new QPushButton(modifyTab);
        modifyServiceBtn->setObjectName("modifyServiceBtn");
        modifyServiceBtn->setIcon(icon1);

        modifyButtonLayout->addWidget(modifyServiceBtn);


        modifyLayout->addLayout(modifyButtonLayout);

        modifyVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        modifyLayout->addItem(modifyVerticalSpacer);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/calendar.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        projectTabWidget->addTab(modifyTab, icon5, QString());
        Rollback = new QWidget();
        Rollback->setObjectName("Rollback");
        rollbackLayout = new QVBoxLayout(Rollback);
        rollbackLayout->setSpacing(10);
        rollbackLayout->setObjectName("rollbackLayout");
        rollbackLabel = new QLabel(Rollback);
        rollbackLabel->setObjectName("rollbackLabel");
        rollbackLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        rollbackLayout->addWidget(rollbackLabel);

        rollbackList = new QListWidget(Rollback);
        rollbackList->setObjectName("rollbackList");
        rollbackList->setAlternatingRowColors(true);

        rollbackLayout->addWidget(rollbackList);

        rollbackButtonsLayout = new QHBoxLayout();
        rollbackButtonsLayout->setObjectName("rollbackButtonsLayout");
        rollbackNewEntryEdit = new QLineEdit(Rollback);
        rollbackNewEntryEdit->setObjectName("rollbackNewEntryEdit");

        rollbackButtonsLayout->addWidget(rollbackNewEntryEdit);

        rollbackAddBtn = new QPushButton(Rollback);
        rollbackAddBtn->setObjectName("rollbackAddBtn");

        rollbackButtonsLayout->addWidget(rollbackAddBtn);

        rollbackDoBtn = new QPushButton(Rollback);
        rollbackDoBtn->setObjectName("rollbackDoBtn");

        rollbackButtonsLayout->addWidget(rollbackDoBtn);

        rollbackClearBtn = new QPushButton(Rollback);
        rollbackClearBtn->setObjectName("rollbackClearBtn");

        rollbackButtonsLayout->addWidget(rollbackClearBtn);


        rollbackLayout->addLayout(rollbackButtonsLayout);

        projectTabWidget->addTab(Rollback, QString());
        Insertion = new QWidget();
        Insertion->setObjectName("Insertion");
        insertionLayout = new QVBoxLayout(Insertion);
        insertionLayout->setSpacing(10);
        insertionLayout->setObjectName("insertionLayout");
        insertionLabel = new QLabel(Insertion);
        insertionLabel->setObjectName("insertionLabel");
        insertionLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        insertionLayout->addWidget(insertionLabel);

        insertionTopLayout = new QHBoxLayout();
        insertionTopLayout->setObjectName("insertionTopLayout");
        insertionList = new QListWidget(Insertion);
        insertionList->setObjectName("insertionList");
        insertionList->setMinimumSize(QSize(240, 0));
        insertionList->setMaximumSize(QSize(360, 16777215));
        insertionList->setAlternatingRowColors(true);

        insertionTopLayout->addWidget(insertionList);

        insertionPreviewLayout = new QVBoxLayout();
        insertionPreviewLayout->setSpacing(8);
        insertionPreviewLayout->setObjectName("insertionPreviewLayout");
        insertionPreviewFrame = new QFrame(Insertion);
        insertionPreviewFrame->setObjectName("insertionPreviewFrame");
        insertionPreviewFrame->setMinimumSize(QSize(500, 360));
        insertionPreviewFrame->setFrameShape(QFrame::Shape::StyledPanel);
        insertionPreviewFrame->setFrameShadow(QFrame::Shadow::Raised);
        previewFrameLayout = new QVBoxLayout(insertionPreviewFrame);
        previewFrameLayout->setObjectName("previewFrameLayout");
        insertionPreview = new QLabel(insertionPreviewFrame);
        insertionPreview->setObjectName("insertionPreview");
        insertionPreview->setEnabled(true);
        insertionPreview->setMinimumSize(QSize(500, 360));
        insertionPreview->setScaledContents(false);
        insertionPreview->setAlignment(Qt::AlignmentFlag::AlignCenter);
        insertionPreview->setWordWrap(false);

        previewFrameLayout->addWidget(insertionPreview);


        insertionPreviewLayout->addWidget(insertionPreviewFrame);

        videoControlsLayout = new QHBoxLayout();
        videoControlsLayout->setObjectName("videoControlsLayout");
        insertionPlayBtn = new QPushButton(Insertion);
        insertionPlayBtn->setObjectName("insertionPlayBtn");

        videoControlsLayout->addWidget(insertionPlayBtn);

        insertionSlider = new QSlider(Insertion);
        insertionSlider->setObjectName("insertionSlider");
        insertionSlider->setOrientation(Qt::Orientation::Horizontal);

        videoControlsLayout->addWidget(insertionSlider);


        insertionPreviewLayout->addLayout(videoControlsLayout);


        insertionTopLayout->addLayout(insertionPreviewLayout);


        insertionLayout->addLayout(insertionTopLayout);

        insertionButtonsLayout = new QHBoxLayout();
        insertionButtonsLayout->setObjectName("insertionButtonsLayout");
        insertionAddBtn = new QPushButton(Insertion);
        insertionAddBtn->setObjectName("insertionAddBtn");

        insertionButtonsLayout->addWidget(insertionAddBtn);

        insertionRemoveBtn = new QPushButton(Insertion);
        insertionRemoveBtn->setObjectName("insertionRemoveBtn");

        insertionButtonsLayout->addWidget(insertionRemoveBtn);

        insertionClearBtn = new QPushButton(Insertion);
        insertionClearBtn->setObjectName("insertionClearBtn");

        insertionButtonsLayout->addWidget(insertionClearBtn);


        insertionLayout->addLayout(insertionButtonsLayout);

        projectTabWidget->addTab(Insertion, QString());

        mainLayout->addWidget(projectTabWidget);

        menubar = new QMenuBar(ProjectWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        statusbar = new QStatusBar(ProjectWidget);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 20, 25));

        retranslateUi(ProjectWidget);

        projectTabWidget->setCurrentIndex(0);


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
"    font-weight: 700;\n"
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
"    border-radius: 6px;\n"
"   "
                        " color: #000000;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #e9ecef;\n"
"    color: #000000;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #e3f2fd;\n"
"    color: #000000;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #f1f3f4;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    border-bottom: 2px solid #007bff;\n"
"    font-weight: 600;\n"
"    color: #000000;\n"
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
"    background-color"
                        ": #138496;\n"
"}\n"
"\n"
"QPushButton#btnEditService {\n"
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
"QLineEdit, QTextEdit, QComboBox {\n"
"    padding: 8px 12px;\n"
"    border: 2px solid #d0d7dd;\n"
"    border-radius: 12px;\n"
"    background-color: #ffffff;\n"
"    color: #000000;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border:"
                        " 2px solid #4da3ff;\n"
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
"\n"
"QLabel#headerTitle:hover {\n"
"    color: #1e88ff;\n"
"}\n"
"", nullptr));
        headerTitle->setText(QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        searchServices->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Search project...", nullptr));
        searchprojet->setText(QCoreApplication::translate("ProjectWidget", "Search", nullptr));
        sortbytitle->setText(QCoreApplication::translate("ProjectWidget", "Sort by Title", nullptr));
        exportexel->setText(QCoreApplication::translate("ProjectWidget", "Export as Exel", nullptr));
        statistics->setText(QCoreApplication::translate("ProjectWidget", "Statictics", nullptr));
        btnSortByName->setText(QCoreApplication::translate("ProjectWidget", "Refresh", nullptr));
        QTableWidgetItem *___qtablewidgetitem = projectTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ProjectWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = projectTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ProjectWidget", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = projectTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ProjectWidget", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = projectTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ProjectWidget", "Client ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = projectTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ProjectWidget", "Service ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = projectTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ProjectWidget", "Creation Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = projectTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ProjectWidget", "Modification Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = projectTableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ProjectWidget", "Owner ID", nullptr));
        btnEditService->setText(QCoreApplication::translate("ProjectWidget", "Edit", nullptr));
        btnDeleteService->setText(QCoreApplication::translate("ProjectWidget", "Delete", nullptr));
        projectTabWidget->setTabText(projectTabWidget->indexOf(projectManagementTab), QCoreApplication::translate("ProjectWidget", "Project Management", nullptr));
        addLabel->setText(QCoreApplication::translate("ProjectWidget", "Add New Project", nullptr));
        addTitleLabel->setText(QCoreApplication::translate("ProjectWidget", "Title", nullptr));
        addTitleEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter project title", nullptr));
        addDescriptionLabel->setText(QCoreApplication::translate("ProjectWidget", "Description", nullptr));
        addDescriptionEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter project description", nullptr));
        addClientIdLabel->setText(QCoreApplication::translate("ProjectWidget", "Client ID", nullptr));
        addClientIdEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter client ID (optional)", nullptr));
        addServiceIdLabel->setText(QCoreApplication::translate("ProjectWidget", "Service ID", nullptr));
        addServiceIdEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter service ID (optional)", nullptr));
        addCreationDateLabel->setText(QCoreApplication::translate("ProjectWidget", "Creation Date", nullptr));
        addModificationDateLabel->setText(QCoreApplication::translate("ProjectWidget", "Modification Date", nullptr));
        addServiceBtn->setText(QCoreApplication::translate("ProjectWidget", "Add", nullptr));
        projectTabWidget->setTabText(projectTabWidget->indexOf(addTab), QCoreApplication::translate("ProjectWidget", "Add", nullptr));
        modifyLabel->setText(QCoreApplication::translate("ProjectWidget", "Modify Project", nullptr));
        modifyIdLabel->setText(QCoreApplication::translate("ProjectWidget", "Project ID", nullptr));
        modifyIdEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter project ID", nullptr));
        modifyTitleLabel->setText(QCoreApplication::translate("ProjectWidget", "Title", nullptr));
        modifyTitleEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter project title", nullptr));
        modifyDescriptionLabel->setText(QCoreApplication::translate("ProjectWidget", "Description", nullptr));
        modifyDescriptionEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter project description", nullptr));
        modifyClientIdLabel->setText(QCoreApplication::translate("ProjectWidget", "Client ID", nullptr));
        modifyClientIdEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter client ID (optional)", nullptr));
        modifyServiceIdLabel->setText(QCoreApplication::translate("ProjectWidget", "Service ID", nullptr));
        modifyServiceIdEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter service ID (optional)", nullptr));
        modifyCreationDateLabel->setText(QCoreApplication::translate("ProjectWidget", "Creation Date", nullptr));
        modifyModificationDateLabel->setText(QCoreApplication::translate("ProjectWidget", "Modification Date", nullptr));
        modifyServiceBtn->setText(QCoreApplication::translate("ProjectWidget", "Update", nullptr));
        projectTabWidget->setTabText(projectTabWidget->indexOf(modifyTab), QCoreApplication::translate("ProjectWidget", "Modify", nullptr));
        rollbackLabel->setText(QCoreApplication::translate("ProjectWidget", "Rollback / History", nullptr));
        rollbackNewEntryEdit->setPlaceholderText(QCoreApplication::translate("ProjectWidget", "Enter a history action to store", nullptr));
        rollbackAddBtn->setText(QCoreApplication::translate("ProjectWidget", "Add", nullptr));
        rollbackDoBtn->setText(QCoreApplication::translate("ProjectWidget", "Rollback Last", nullptr));
        rollbackClearBtn->setText(QCoreApplication::translate("ProjectWidget", "Clear", nullptr));
        projectTabWidget->setTabText(projectTabWidget->indexOf(Rollback), QCoreApplication::translate("ProjectWidget", "Rollback", nullptr));
        insertionLabel->setText(QCoreApplication::translate("ProjectWidget", "Media Insertion (images & videos)", nullptr));
        insertionPreview->setText(QCoreApplication::translate("ProjectWidget", "Preview", nullptr));
        insertionPlayBtn->setText(QCoreApplication::translate("ProjectWidget", "Play", nullptr));
        insertionAddBtn->setText(QCoreApplication::translate("ProjectWidget", "Import Media...", nullptr));
        insertionRemoveBtn->setText(QCoreApplication::translate("ProjectWidget", "Remove Selected", nullptr));
        insertionClearBtn->setText(QCoreApplication::translate("ProjectWidget", "Clear All", nullptr));
        projectTabWidget->setTabText(projectTabWidget->indexOf(Insertion), QCoreApplication::translate("ProjectWidget", "Insertion of Images and Videos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectWidget: public Ui_ProjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
