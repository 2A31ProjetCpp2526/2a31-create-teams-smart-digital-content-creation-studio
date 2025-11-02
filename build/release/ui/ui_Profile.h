/********************************************************************************
** Form generated from reading UI file 'Profile.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QVBoxLayout *mainLayout;
    QTabWidget *profileTabWidget;
    QWidget *infoTab;
    QVBoxLayout *infoLayout;
    QLabel *sectionTitle;
    QWidget *avatarWidget;
    QHBoxLayout *avatarLayout;
    QLabel *avatarLabel;
    QVBoxLayout *avatarButtonsLayout;
    QPushButton *changePhotoBtn;
    QPushButton *removePhotoBtn;
    QSpacerItem *avatarButtonsSpacer;
    QSpacerItem *avatarHorizontalSpacer;
    QWidget *userInfoWidget;
    QFormLayout *userInfoForm;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *roleLabel;
    QLineEdit *roleEdit;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneEdit;
    QSpacerItem *infoVerticalSpacer;
    QWidget *historyTab;
    QVBoxLayout *historyLayout;
    QLabel *sectionTitle1;
    QTableWidget *historyTable;
    QWidget *securityTab;
    QVBoxLayout *securityLayout;
    QLabel *sectionTitle2;
    QWidget *passwordWidget;
    QFormLayout *passwordForm;
    QLabel *currentPasswordLabel;
    QLineEdit *currentPasswordEdit;
    QLabel *newPasswordLabel;
    QLineEdit *newPasswordEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordEdit;
    QWidget *verificationWidget;
    QFormLayout *verificationForm;
    QLabel *verificationCodeLabel;
    QLineEdit *verificationCodeEdit;
    QWidget *securityButtonsWidget;
    QHBoxLayout *securityButtonsLayout;
    QSpacerItem *securityButtonsSpacer;
    QPushButton *changePasswordBtn;
    QSpacerItem *securityVerticalSpacer;
    QWidget *profileButtonsWidget;
    QHBoxLayout *profileButtonsLayout;
    QSpacerItem *profileButtonsSpacer;
    QPushButton *resetProfileButton;
    QPushButton *saveProfileButton;

    void setupUi(QWidget *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(800, 754);
        mainLayout = new QVBoxLayout(Profile);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(40, 40, 40, 0);
        profileTabWidget = new QTabWidget(Profile);
        profileTabWidget->setObjectName("profileTabWidget");
        infoTab = new QWidget();
        infoTab->setObjectName("infoTab");
        infoLayout = new QVBoxLayout(infoTab);
        infoLayout->setSpacing(15);
        infoLayout->setObjectName("infoLayout");
        infoLayout->setContentsMargins(20, 20, 20, 20);
        sectionTitle = new QLabel(infoTab);
        sectionTitle->setObjectName("sectionTitle");

        infoLayout->addWidget(sectionTitle);

        avatarWidget = new QWidget(infoTab);
        avatarWidget->setObjectName("avatarWidget");
        avatarLayout = new QHBoxLayout(avatarWidget);
        avatarLayout->setSpacing(24);
        avatarLayout->setObjectName("avatarLayout");
        avatarLayout->setContentsMargins(0, 0, 0, 0);
        avatarLabel = new QLabel(avatarWidget);
        avatarLabel->setObjectName("avatarLabel");
        avatarLabel->setScaledContents(true);
        avatarLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        avatarLayout->addWidget(avatarLabel);

        avatarButtonsLayout = new QVBoxLayout();
        avatarButtonsLayout->setSpacing(12);
        avatarButtonsLayout->setObjectName("avatarButtonsLayout");
        changePhotoBtn = new QPushButton(avatarWidget);
        changePhotoBtn->setObjectName("changePhotoBtn");

        avatarButtonsLayout->addWidget(changePhotoBtn);

        removePhotoBtn = new QPushButton(avatarWidget);
        removePhotoBtn->setObjectName("removePhotoBtn");

        avatarButtonsLayout->addWidget(removePhotoBtn);

        avatarButtonsSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        avatarButtonsLayout->addItem(avatarButtonsSpacer);


        avatarLayout->addLayout(avatarButtonsLayout);

        avatarHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        avatarLayout->addItem(avatarHorizontalSpacer);


        infoLayout->addWidget(avatarWidget);

        userInfoWidget = new QWidget(infoTab);
        userInfoWidget->setObjectName("userInfoWidget");
        userInfoForm = new QFormLayout(userInfoWidget);
        userInfoForm->setObjectName("userInfoForm");
        userInfoForm->setHorizontalSpacing(32);
        userInfoForm->setVerticalSpacing(24);
        userInfoForm->setContentsMargins(16, 16, 16, 16);
        usernameLabel = new QLabel(userInfoWidget);
        usernameLabel->setObjectName("usernameLabel");

        userInfoForm->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(userInfoWidget);
        usernameEdit->setObjectName("usernameEdit");

        userInfoForm->setWidget(0, QFormLayout::FieldRole, usernameEdit);

        roleLabel = new QLabel(userInfoWidget);
        roleLabel->setObjectName("roleLabel");

        userInfoForm->setWidget(1, QFormLayout::LabelRole, roleLabel);

        roleEdit = new QLineEdit(userInfoWidget);
        roleEdit->setObjectName("roleEdit");

        userInfoForm->setWidget(1, QFormLayout::FieldRole, roleEdit);

        emailLabel = new QLabel(userInfoWidget);
        emailLabel->setObjectName("emailLabel");

        userInfoForm->setWidget(2, QFormLayout::LabelRole, emailLabel);

        emailEdit = new QLineEdit(userInfoWidget);
        emailEdit->setObjectName("emailEdit");

        userInfoForm->setWidget(2, QFormLayout::FieldRole, emailEdit);

        phoneLabel = new QLabel(userInfoWidget);
        phoneLabel->setObjectName("phoneLabel");

        userInfoForm->setWidget(3, QFormLayout::LabelRole, phoneLabel);

        phoneEdit = new QLineEdit(userInfoWidget);
        phoneEdit->setObjectName("phoneEdit");

        userInfoForm->setWidget(3, QFormLayout::FieldRole, phoneEdit);


        infoLayout->addWidget(userInfoWidget);

        infoVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        infoLayout->addItem(infoVerticalSpacer);

        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/info.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        profileTabWidget->addTab(infoTab, icon, QString());
        historyTab = new QWidget();
        historyTab->setObjectName("historyTab");
        historyLayout = new QVBoxLayout(historyTab);
        historyLayout->setSpacing(15);
        historyLayout->setObjectName("historyLayout");
        historyLayout->setContentsMargins(20, 20, 20, 20);
        sectionTitle1 = new QLabel(historyTab);
        sectionTitle1->setObjectName("sectionTitle1");

        historyLayout->addWidget(sectionTitle1);

        historyTable = new QTableWidget(historyTab);
        if (historyTable->columnCount() < 3)
            historyTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        historyTable->setObjectName("historyTable");
        historyTable->setAlternatingRowColors(true);
        historyTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        historyTable->setGridStyle(Qt::PenStyle::SolidLine);
        historyTable->setColumnCount(3);
        historyTable->horizontalHeader()->setVisible(true);
        historyTable->verticalHeader()->setVisible(false);

        historyLayout->addWidget(historyTable);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/history.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        profileTabWidget->addTab(historyTab, icon1, QString());
        securityTab = new QWidget();
        securityTab->setObjectName("securityTab");
        securityLayout = new QVBoxLayout(securityTab);
        securityLayout->setSpacing(15);
        securityLayout->setObjectName("securityLayout");
        securityLayout->setContentsMargins(20, 20, 20, 20);
        sectionTitle2 = new QLabel(securityTab);
        sectionTitle2->setObjectName("sectionTitle2");

        securityLayout->addWidget(sectionTitle2);

        passwordWidget = new QWidget(securityTab);
        passwordWidget->setObjectName("passwordWidget");
        passwordForm = new QFormLayout(passwordWidget);
        passwordForm->setObjectName("passwordForm");
        passwordForm->setHorizontalSpacing(20);
        passwordForm->setVerticalSpacing(16);
        currentPasswordLabel = new QLabel(passwordWidget);
        currentPasswordLabel->setObjectName("currentPasswordLabel");

        passwordForm->setWidget(0, QFormLayout::LabelRole, currentPasswordLabel);

        currentPasswordEdit = new QLineEdit(passwordWidget);
        currentPasswordEdit->setObjectName("currentPasswordEdit");
        currentPasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordForm->setWidget(0, QFormLayout::FieldRole, currentPasswordEdit);

        newPasswordLabel = new QLabel(passwordWidget);
        newPasswordLabel->setObjectName("newPasswordLabel");

        passwordForm->setWidget(1, QFormLayout::LabelRole, newPasswordLabel);

        newPasswordEdit = new QLineEdit(passwordWidget);
        newPasswordEdit->setObjectName("newPasswordEdit");
        newPasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordForm->setWidget(1, QFormLayout::FieldRole, newPasswordEdit);

        confirmPasswordLabel = new QLabel(passwordWidget);
        confirmPasswordLabel->setObjectName("confirmPasswordLabel");

        passwordForm->setWidget(2, QFormLayout::LabelRole, confirmPasswordLabel);

        confirmPasswordEdit = new QLineEdit(passwordWidget);
        confirmPasswordEdit->setObjectName("confirmPasswordEdit");
        confirmPasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        passwordForm->setWidget(2, QFormLayout::FieldRole, confirmPasswordEdit);


        securityLayout->addWidget(passwordWidget);

        verificationWidget = new QWidget(securityTab);
        verificationWidget->setObjectName("verificationWidget");
        verificationForm = new QFormLayout(verificationWidget);
        verificationForm->setObjectName("verificationForm");
        verificationForm->setHorizontalSpacing(20);
        verificationForm->setVerticalSpacing(16);
        verificationCodeLabel = new QLabel(verificationWidget);
        verificationCodeLabel->setObjectName("verificationCodeLabel");

        verificationForm->setWidget(0, QFormLayout::LabelRole, verificationCodeLabel);

        verificationCodeEdit = new QLineEdit(verificationWidget);
        verificationCodeEdit->setObjectName("verificationCodeEdit");

        verificationForm->setWidget(0, QFormLayout::FieldRole, verificationCodeEdit);


        securityLayout->addWidget(verificationWidget);

        securityButtonsWidget = new QWidget(securityTab);
        securityButtonsWidget->setObjectName("securityButtonsWidget");
        securityButtonsLayout = new QHBoxLayout(securityButtonsWidget);
        securityButtonsLayout->setSpacing(16);
        securityButtonsLayout->setObjectName("securityButtonsLayout");
        securityButtonsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        securityButtonsLayout->addItem(securityButtonsSpacer);

        changePasswordBtn = new QPushButton(securityButtonsWidget);
        changePasswordBtn->setObjectName("changePasswordBtn");

        securityButtonsLayout->addWidget(changePasswordBtn);


        securityLayout->addWidget(securityButtonsWidget);

        securityVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        securityLayout->addItem(securityVerticalSpacer);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/security.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        profileTabWidget->addTab(securityTab, icon2, QString());

        mainLayout->addWidget(profileTabWidget);

        profileButtonsWidget = new QWidget(Profile);
        profileButtonsWidget->setObjectName("profileButtonsWidget");
        profileButtonsLayout = new QHBoxLayout(profileButtonsWidget);
        profileButtonsLayout->setSpacing(16);
        profileButtonsLayout->setObjectName("profileButtonsLayout");
        profileButtonsLayout->setContentsMargins(32, 16, 32, 24);
        profileButtonsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        profileButtonsLayout->addItem(profileButtonsSpacer);

        resetProfileButton = new QPushButton(profileButtonsWidget);
        resetProfileButton->setObjectName("resetProfileButton");

        profileButtonsLayout->addWidget(resetProfileButton);

        saveProfileButton = new QPushButton(profileButtonsWidget);
        saveProfileButton->setObjectName("saveProfileButton");

        profileButtonsLayout->addWidget(saveProfileButton);


        mainLayout->addWidget(profileButtonsWidget);


        retranslateUi(Profile);

        profileTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QWidget *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "Profile", nullptr));
        Profile->setStyleSheet(QCoreApplication::translate("Profile", "QWidget {\n"
"    background-color: #f8f9fa;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"/* Tab Widget Styling - Exact match to Employer */\n"
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
"    letter-spacing: 0.3px;\n"
"    transition: all 0.3s ease-in-out;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #ffffff;\n"
"    color: #007bff;\n"
"    border-color: #007bff;\n"
"    border-bottom: 1px solid #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:hover:!selected {\n"
"    background-color: #e9ece"
                        "f;\n"
"    color: #495057;\n"
"    border-bottom: 3px solid #adb5bd;\n"
"    box-shadow: 0 1px 3px rgba(0,0,0,0.08);\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"/* Avatar Styling */\n"
"QLabel#avatarLabel {\n"
"    background-color: #e9ecef;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 60px;\n"
"    min-width: 120px;\n"
"    max-width: 120px;\n"
"    min-height: 120px;\n"
"    max-height: 120px;\n"
"}\n"
"\n"
"/* Button Styling - Match Employer */\n"
"QPushButton {\n"
"    background-color: #1da1f2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px 24px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    min-height: 20px;\n"
"    letter-spacing: 0.3px;\n"
"    transition: all 0.3s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1991db;\n"
"    box-shadow: 0 4px 12px rgba(29, 161, 242, 0.3);\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"QPushBut"
                        "ton:pressed {\n"
"    background-color: #1680c7;\n"
"    transform: translateY(0px);\n"
"    box-shadow: 0 2px 6px rgba(29, 161, 242, 0.2);\n"
"}\n"
"\n"
"QPushButton#removePhotoBtn {\n"
"    background-color: #dc3545;\n"
"}\n"
"\n"
"QPushButton#removePhotoBtn:hover {\n"
"    background-color: #c82333;\n"
"    box-shadow: 0 4px 12px rgba(220, 53, 69, 0.3);\n"
"}\n"
"\n"
"QPushButton#removePhotoBtn:pressed {\n"
"    background-color: #bd2130;\n"
"}\n"
"\n"
"/* Label Styling - Match Employer with Bold and Hover Effects */\n"
"QLabel {\n"
"    color: #14171a;\n"
"    font-weight: 600;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 14px;\n"
"    letter-spacing: 0.3px;\n"
"    transition: all 0.2s ease-in-out;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: #1da1f2;\n"
"    text-decoration: underline;\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"QLabel#sectionTitle {\n"
"    font-size: 18px;\n"
"    font-weight: 700;\n"
"    color: #14171a;\n"
"    letter-spacing: 0.8px;\n"
" "
                        "   margin-bottom: 16px;\n"
"    padding: 16px 0px 16px 0px;\n"
"    border-bottom: 1px solid #e1e8ed;\n"
"}\n"
"\n"
"QLabel#sectionTitle:hover {\n"
"    color: #1da1f2;\n"
"    text-decoration: underline;\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"/* Input Field Styling */\n"
"QLineEdit {\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"    color: #495057;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    font-weight: 400;\n"
"    transition: all 0.2s ease-in-out;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1da1f2;\n"
"    outline: none;\n"
"    box-shadow: 0 0 0 3px rgba(29, 161, 242, 0.1);\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}\n"
"\n"
"/* Table Styling */\n"
"QTableWidget {\n"
"    border: 1px solid #e1e8ed;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    gridline-color: #f1f3f4;\n"
"    font-family: 'Poppins', '"
                        "Segoe UI', Arial, sans-serif;\n"
"    selection-background-color: rgba(29, 161, 242, 0.1);\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #f8f9fa;\n"
"    border: none;\n"
"    border-bottom: 2px solid #e1e8ed;\n"
"    padding: 12px 16px;\n"
"    font-weight: 700;\n"
"    color: #495057;\n"
"    letter-spacing: 0.3px;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 8px 16px;\n"
"    border-bottom: 1px solid #f1f3f4;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: rgba(29, 161, 242, 0.1);\n"
"    color: #1da1f2;\n"
"}", nullptr));
        sectionTitle->setText(QCoreApplication::translate("Profile", "User Profile Information", nullptr));
        avatarLabel->setText(QCoreApplication::translate("Profile", "Avatar", nullptr));
        changePhotoBtn->setText(QCoreApplication::translate("Profile", "Change Photo", nullptr));
        removePhotoBtn->setText(QCoreApplication::translate("Profile", "Remove Photo", nullptr));
        userInfoWidget->setStyleSheet(QCoreApplication::translate("Profile", "QWidget#userInfoWidget {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e1e8ed;\n"
"    border-radius: 10px;\n"
"    padding: 16px;\n"
"    margin: 8px 0;\n"
"}", nullptr));
        usernameLabel->setStyleSheet(QCoreApplication::translate("Profile", "QLabel {\n"
"    font-weight: 700;\n"
"    font-size: 15px;\n"
"    color: #2c3e50;\n"
"    padding: 8px 0;\n"
"    min-width: 120px;\n"
"}", nullptr));
        usernameLabel->setText(QCoreApplication::translate("Profile", "Username:", nullptr));
        usernameEdit->setStyleSheet(QCoreApplication::translate("Profile", "QLineEdit {\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1da1f2;\n"
"    background-color: #ffffff;\n"
"    box-shadow: 0 0 0 3px rgba(29, 161, 242, 0.1);\n"
"}", nullptr));
        roleLabel->setStyleSheet(QCoreApplication::translate("Profile", "QLabel {\n"
"    font-weight: 700;\n"
"    font-size: 15px;\n"
"    color: #2c3e50;\n"
"    padding: 8px 0;\n"
"    min-width: 120px;\n"
"}", nullptr));
        roleLabel->setText(QCoreApplication::translate("Profile", "Role:", nullptr));
        roleEdit->setStyleSheet(QCoreApplication::translate("Profile", "QLineEdit {\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1da1f2;\n"
"    background-color: #ffffff;\n"
"    box-shadow: 0 0 0 3px rgba(29, 161, 242, 0.1);\n"
"}", nullptr));
        emailLabel->setStyleSheet(QCoreApplication::translate("Profile", "QLabel {\n"
"    font-weight: 700;\n"
"    font-size: 15px;\n"
"    color: #2c3e50;\n"
"    padding: 8px 0;\n"
"    min-width: 120px;\n"
"}", nullptr));
        emailLabel->setText(QCoreApplication::translate("Profile", "Email:", nullptr));
        emailEdit->setStyleSheet(QCoreApplication::translate("Profile", "QLineEdit {\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1da1f2;\n"
"    background-color: #ffffff;\n"
"    box-shadow: 0 0 0 3px rgba(29, 161, 242, 0.1);\n"
"}", nullptr));
        phoneLabel->setStyleSheet(QCoreApplication::translate("Profile", "QLabel {\n"
"    font-weight: 700;\n"
"    font-size: 15px;\n"
"    color: #2c3e50;\n"
"    padding: 8px 0;\n"
"    min-width: 120px;\n"
"}", nullptr));
        phoneLabel->setText(QCoreApplication::translate("Profile", "Phone Number:", nullptr));
        phoneEdit->setStyleSheet(QCoreApplication::translate("Profile", "QLineEdit {\n"
"    padding: 12px 16px;\n"
"    font-size: 14px;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #f8f9fa;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #1da1f2;\n"
"    background-color: #ffffff;\n"
"    box-shadow: 0 0 0 3px rgba(29, 161, 242, 0.1);\n"
"}", nullptr));
        profileTabWidget->setTabText(profileTabWidget->indexOf(infoTab), QCoreApplication::translate("Profile", "Info", nullptr));
        sectionTitle1->setText(QCoreApplication::translate("Profile", "Activity History", nullptr));
        QTableWidgetItem *___qtablewidgetitem = historyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Profile", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = historyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Profile", "Activity", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = historyTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Profile", "Details", nullptr));
        profileTabWidget->setTabText(profileTabWidget->indexOf(historyTab), QCoreApplication::translate("Profile", "History", nullptr));
        sectionTitle2->setText(QCoreApplication::translate("Profile", "Security Settings", nullptr));
        currentPasswordLabel->setText(QCoreApplication::translate("Profile", "Current Password:", nullptr));
        newPasswordLabel->setText(QCoreApplication::translate("Profile", "New Password:", nullptr));
        confirmPasswordLabel->setText(QCoreApplication::translate("Profile", "Confirm Password:", nullptr));
        verificationCodeLabel->setText(QCoreApplication::translate("Profile", "Verification Code:", nullptr));
        verificationCodeEdit->setPlaceholderText(QCoreApplication::translate("Profile", "Enter verification code", nullptr));
        changePasswordBtn->setText(QCoreApplication::translate("Profile", "Change Password", nullptr));
        profileTabWidget->setTabText(profileTabWidget->indexOf(securityTab), QCoreApplication::translate("Profile", "Security", nullptr));
        resetProfileButton->setStyleSheet(QCoreApplication::translate("Profile", "QPushButton {\n"
"    background-color: #6c757d;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5a6268;\n"
"    box-shadow: 0 4px 12px rgba(108, 117, 125, 0.3);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #545b62;\n"
"}", nullptr));
        resetProfileButton->setText(QCoreApplication::translate("Profile", "Reset", nullptr));
        saveProfileButton->setText(QCoreApplication::translate("Profile", "Save Changes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
