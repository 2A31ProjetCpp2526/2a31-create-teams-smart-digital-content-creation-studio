/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *authStackedWidget;
    QWidget *loginFormPage;
    QVBoxLayout *loginFormLayout;
    QLabel *loginTitle;
    QSpacerItem *loginTitleSpacer;
    QLineEdit *loginEmailLineEdit;
    QSpacerItem *loginFieldSpacer1;
    QLineEdit *loginPasswordLineEdit;
    QSpacerItem *loginFieldSpacer2;
    QCheckBox *rememberMeCheckBox;
    QSpacerItem *loginFieldSpacer3;
    QPushButton *loginButton;
    QSpacerItem *loginButtonSpacer;
    QPushButton *faceLoginButton;
    QSpacerItem *faceLoginSpacer;
    QPushButton *forgotPasswordNavButton;
    QSpacerItem *loginLinkSpacer;
    QPushButton *signUpNavButton;
    QWidget *signUpFormPage;
    QVBoxLayout *signUpFormLayout;
    QLabel *signUpTitle;
    QSpacerItem *signUpTitleSpacer;
    QLineEdit *fullNameLineEdit;
    QSpacerItem *signUpFieldSpacer1;
    QLineEdit *signUpEmailLineEdit;
    QSpacerItem *signUpFieldSpacer2;
    QLineEdit *signUpPasswordLineEdit;
    QSpacerItem *signUpFieldSpacer3;
    QLineEdit *confirmPasswordLineEdit;
    QSpacerItem *signUpFieldSpacer4;
    QCheckBox *acceptTermsCheckBox;
    QSpacerItem *signUpFieldSpacer5;
    QPushButton *signUpButton;
    QSpacerItem *signUpButtonSpacer;
    QPushButton *backToLoginFromSignUpButton;
    QWidget *forgotPasswordFormPage;
    QVBoxLayout *forgotPasswordFormLayout;
    QLabel *forgotPasswordTitle;
    QSpacerItem *forgotPasswordTitleSpacer;
    QLabel *forgotPasswordDescription;
    QSpacerItem *forgotPasswordDescSpacer;
    QLineEdit *resetEmailLineEdit;
    QSpacerItem *forgotPasswordFieldSpacer;
    QPushButton *sendResetLinkButton;
    QSpacerItem *forgotPasswordButtonSpacer;
    QPushButton *backToLoginFromForgotButton;

    void setupUi(QWidget *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName("LoginPage");
        LoginPage->resize(450, 600);
        LoginPage->setStyleSheet(QString::fromUtf8("QWidget#LoginPage {\n"
"    background-color: transparent;\n"
"    font-family: 'Poppins';\n"
"    font-weight: 300;\n"
"}"));
        verticalLayout = new QVBoxLayout(LoginPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        authStackedWidget = new QStackedWidget(LoginPage);
        authStackedWidget->setObjectName("authStackedWidget");
        loginFormPage = new QWidget();
        loginFormPage->setObjectName("loginFormPage");
        loginFormLayout = new QVBoxLayout(loginFormPage);
        loginFormLayout->setObjectName("loginFormLayout");
        loginFormLayout->setContentsMargins(48, 48, 48, 32);
        loginTitle = new QLabel(loginFormPage);
        loginTitle->setObjectName("loginTitle");
        QFont font;
        font.setFamilies({QString::fromUtf8("Poppins")});
        font.setPointSize(28);
        loginTitle->setFont(font);
        loginTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #14171a;\n"
"    font-weight: 600;\n"
"    letter-spacing: 1px;\n"
"    background-color: transparent;\n"
"    padding: 24px 0px;\n"
"    text-align: center;\n"
"}"));
        loginTitle->setAlignment(Qt::AlignCenter);

        loginFormLayout->addWidget(loginTitle);

        loginTitleSpacer = new QSpacerItem(20, 32, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(loginTitleSpacer);

        loginEmailLineEdit = new QLineEdit(loginFormPage);
        loginEmailLineEdit->setObjectName("loginEmailLineEdit");
        loginEmailLineEdit->setMinimumSize(QSize(0, 48));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Poppins")});
        font1.setPointSize(12);
        loginEmailLineEdit->setFont(font1);
        loginEmailLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));

        loginFormLayout->addWidget(loginEmailLineEdit);

        loginFieldSpacer1 = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(loginFieldSpacer1);

        loginPasswordLineEdit = new QLineEdit(loginFormPage);
        loginPasswordLineEdit->setObjectName("loginPasswordLineEdit");
        loginPasswordLineEdit->setMinimumSize(QSize(0, 48));
        loginPasswordLineEdit->setFont(font1);
        loginPasswordLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));
        loginPasswordLineEdit->setEchoMode(QLineEdit::Password);

        loginFormLayout->addWidget(loginPasswordLineEdit);

        loginFieldSpacer2 = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(loginFieldSpacer2);

        rememberMeCheckBox = new QCheckBox(loginFormPage);
        rememberMeCheckBox->setObjectName("rememberMeCheckBox");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Poppins")});
        font2.setPointSize(11);
        rememberMeCheckBox->setFont(font2);
        rememberMeCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    color: #6c757d;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QCheckBox::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    border-radius: 4px;\n"
"    border: 1px solid #dee2e6;\n"
"    background-color: #ffffff;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #007bff;\n"
"    border-color: #007bff;\n"
"}\n"
"QCheckBox::indicator:hover {\n"
"    border-color: #007bff;\n"
"}"));

        loginFormLayout->addWidget(rememberMeCheckBox);

        loginFieldSpacer3 = new QSpacerItem(20, 24, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(loginFieldSpacer3);

        loginButton = new QPushButton(loginFormPage);
        loginButton->setObjectName("loginButton");
        loginButton->setMinimumSize(QSize(0, 48));
        loginButton->setFont(font1);
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #007bff;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px 24px;\n"
"    font-weight: 500;\n"
"    letter-spacing: 0.5px;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    box-sizing: border-box;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"    transform: none;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #004085;\n"
"    transform: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/login.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        loginButton->setIcon(icon);

        loginFormLayout->addWidget(loginButton);

        loginButtonSpacer = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(loginButtonSpacer);

        faceLoginButton = new QPushButton(loginFormPage);
        faceLoginButton->setObjectName("faceLoginButton");
        faceLoginButton->setMinimumSize(QSize(0, 48));
        faceLoginButton->setFont(font1);
        faceLoginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ffffff;\n"
"    color: #007bff;\n"
"    border: 2px solid #007bff;\n"
"    border-radius: 8px;\n"
"    padding: 12px 24px;\n"
"    font-weight: 400;\n"
"    letter-spacing: 0.5px;\n"
"    font-family: 'Poppins', 'Segoe UI', Arial, sans-serif;\n"
"    box-sizing: border-box;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #f8f9fa;\n"
"    border-color: #0056b3;\n"
"    color: #0056b3;\n"
"    transform: none;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #e9ecef;\n"
"    border-color: #004085;\n"
"    color: #004085;\n"
"    transform: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/security.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        faceLoginButton->setIcon(icon1);

        loginFormLayout->addWidget(faceLoginButton);

        faceLoginSpacer = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(faceLoginSpacer);

        forgotPasswordNavButton = new QPushButton(loginFormPage);
        forgotPasswordNavButton->setObjectName("forgotPasswordNavButton");
        forgotPasswordNavButton->setFont(font2);
        forgotPasswordNavButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #007bff;\n"
"    border: none;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"    text-decoration: underline;\n"
"    text-align: center;\n"
"}\n"
"QPushButton:hover {\n"
"    color: #0056b3;\n"
"}"));
        forgotPasswordNavButton->setFlat(true);

        loginFormLayout->addWidget(forgotPasswordNavButton);

        loginLinkSpacer = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        loginFormLayout->addItem(loginLinkSpacer);

        signUpNavButton = new QPushButton(loginFormPage);
        signUpNavButton->setObjectName("signUpNavButton");
        signUpNavButton->setFont(font2);
        signUpNavButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #6c757d;\n"
"    border: none;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"    text-align: center;\n"
"}\n"
"QPushButton:hover {\n"
"    color: #007bff;\n"
"}"));
        signUpNavButton->setFlat(true);

        loginFormLayout->addWidget(signUpNavButton);

        authStackedWidget->addWidget(loginFormPage);
        signUpFormPage = new QWidget();
        signUpFormPage->setObjectName("signUpFormPage");
        signUpFormLayout = new QVBoxLayout(signUpFormPage);
        signUpFormLayout->setObjectName("signUpFormLayout");
        signUpFormLayout->setContentsMargins(48, 32, 48, 32);
        signUpTitle = new QLabel(signUpFormPage);
        signUpTitle->setObjectName("signUpTitle");
        signUpTitle->setFont(font);
        signUpTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #14171a;\n"
"    font-weight: 600;\n"
"    letter-spacing: 1px;\n"
"    background-color: transparent;\n"
"    padding: 24px 0px;\n"
"    text-align: center;\n"
"}"));
        signUpTitle->setAlignment(Qt::AlignCenter);

        signUpFormLayout->addWidget(signUpTitle);

        signUpTitleSpacer = new QSpacerItem(20, 24, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpTitleSpacer);

        fullNameLineEdit = new QLineEdit(signUpFormPage);
        fullNameLineEdit->setObjectName("fullNameLineEdit");
        fullNameLineEdit->setMinimumSize(QSize(0, 48));
        fullNameLineEdit->setFont(font1);
        fullNameLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));

        signUpFormLayout->addWidget(fullNameLineEdit);

        signUpFieldSpacer1 = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpFieldSpacer1);

        signUpEmailLineEdit = new QLineEdit(signUpFormPage);
        signUpEmailLineEdit->setObjectName("signUpEmailLineEdit");
        signUpEmailLineEdit->setMinimumSize(QSize(0, 48));
        signUpEmailLineEdit->setFont(font1);
        signUpEmailLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));

        signUpFormLayout->addWidget(signUpEmailLineEdit);

        signUpFieldSpacer2 = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpFieldSpacer2);

        signUpPasswordLineEdit = new QLineEdit(signUpFormPage);
        signUpPasswordLineEdit->setObjectName("signUpPasswordLineEdit");
        signUpPasswordLineEdit->setMinimumSize(QSize(0, 48));
        signUpPasswordLineEdit->setFont(font1);
        signUpPasswordLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));
        signUpPasswordLineEdit->setEchoMode(QLineEdit::Password);

        signUpFormLayout->addWidget(signUpPasswordLineEdit);

        signUpFieldSpacer3 = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpFieldSpacer3);

        confirmPasswordLineEdit = new QLineEdit(signUpFormPage);
        confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");
        confirmPasswordLineEdit->setMinimumSize(QSize(0, 48));
        confirmPasswordLineEdit->setFont(font1);
        confirmPasswordLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));
        confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

        signUpFormLayout->addWidget(confirmPasswordLineEdit);

        signUpFieldSpacer4 = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpFieldSpacer4);

        acceptTermsCheckBox = new QCheckBox(signUpFormPage);
        acceptTermsCheckBox->setObjectName("acceptTermsCheckBox");
        acceptTermsCheckBox->setFont(font2);
        acceptTermsCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    color: #6c757d;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QCheckBox::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    border-radius: 4px;\n"
"    border: 1px solid #dee2e6;\n"
"    background-color: #ffffff;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #007bff;\n"
"    border-color: #007bff;\n"
"}\n"
"QCheckBox::indicator:hover {\n"
"    border-color: #007bff;\n"
"}"));

        signUpFormLayout->addWidget(acceptTermsCheckBox);

        signUpFieldSpacer5 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpFieldSpacer5);

        signUpButton = new QPushButton(signUpFormPage);
        signUpButton->setObjectName("signUpButton");
        signUpButton->setMinimumSize(QSize(0, 48));
        signUpButton->setFont(font1);
        signUpButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #007bff;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px 24px;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #004085;\n"
"}"));

        signUpFormLayout->addWidget(signUpButton);

        signUpButtonSpacer = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        signUpFormLayout->addItem(signUpButtonSpacer);

        backToLoginFromSignUpButton = new QPushButton(signUpFormPage);
        backToLoginFromSignUpButton->setObjectName("backToLoginFromSignUpButton");
        backToLoginFromSignUpButton->setFont(font2);
        backToLoginFromSignUpButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #6c757d;\n"
"    border: none;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"    text-align: center;\n"
"}\n"
"QPushButton:hover {\n"
"    color: #007bff;\n"
"}"));
        backToLoginFromSignUpButton->setFlat(true);

        signUpFormLayout->addWidget(backToLoginFromSignUpButton);

        authStackedWidget->addWidget(signUpFormPage);
        forgotPasswordFormPage = new QWidget();
        forgotPasswordFormPage->setObjectName("forgotPasswordFormPage");
        forgotPasswordFormLayout = new QVBoxLayout(forgotPasswordFormPage);
        forgotPasswordFormLayout->setObjectName("forgotPasswordFormLayout");
        forgotPasswordFormLayout->setContentsMargins(48, 64, 48, 48);
        forgotPasswordTitle = new QLabel(forgotPasswordFormPage);
        forgotPasswordTitle->setObjectName("forgotPasswordTitle");
        forgotPasswordTitle->setFont(font);
        forgotPasswordTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #14171a;\n"
"    font-weight: 600;\n"
"    letter-spacing: 1px;\n"
"    background-color: transparent;\n"
"    padding: 24px 0px;\n"
"    text-align: center;\n"
"}"));
        forgotPasswordTitle->setAlignment(Qt::AlignCenter);

        forgotPasswordFormLayout->addWidget(forgotPasswordTitle);

        forgotPasswordTitleSpacer = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        forgotPasswordFormLayout->addItem(forgotPasswordTitleSpacer);

        forgotPasswordDescription = new QLabel(forgotPasswordFormPage);
        forgotPasswordDescription->setObjectName("forgotPasswordDescription");
        forgotPasswordDescription->setFont(font1);
        forgotPasswordDescription->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #6c757d;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}"));
        forgotPasswordDescription->setAlignment(Qt::AlignCenter);
        forgotPasswordDescription->setWordWrap(true);

        forgotPasswordFormLayout->addWidget(forgotPasswordDescription);

        forgotPasswordDescSpacer = new QSpacerItem(20, 32, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        forgotPasswordFormLayout->addItem(forgotPasswordDescSpacer);

        resetEmailLineEdit = new QLineEdit(forgotPasswordFormPage);
        resetEmailLineEdit->setObjectName("resetEmailLineEdit");
        resetEmailLineEdit->setMinimumSize(QSize(0, 48));
        resetEmailLineEdit->setFont(font1);
        resetEmailLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 12px 16px;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: #ffffff;\n"
"    color: #495057;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #007bff;\n"
"    outline: none;\n"
"}\n"
"QLineEdit:hover {\n"
"    border-color: #adb5bd;\n"
"}"));

        forgotPasswordFormLayout->addWidget(resetEmailLineEdit);

        forgotPasswordFieldSpacer = new QSpacerItem(20, 24, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        forgotPasswordFormLayout->addItem(forgotPasswordFieldSpacer);

        sendResetLinkButton = new QPushButton(forgotPasswordFormPage);
        sendResetLinkButton->setObjectName("sendResetLinkButton");
        sendResetLinkButton->setMinimumSize(QSize(0, 48));
        sendResetLinkButton->setFont(font1);
        sendResetLinkButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #007bff;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px 24px;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #004085;\n"
"}"));

        forgotPasswordFormLayout->addWidget(sendResetLinkButton);

        forgotPasswordButtonSpacer = new QSpacerItem(20, 32, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        forgotPasswordFormLayout->addItem(forgotPasswordButtonSpacer);

        backToLoginFromForgotButton = new QPushButton(forgotPasswordFormPage);
        backToLoginFromForgotButton->setObjectName("backToLoginFromForgotButton");
        backToLoginFromForgotButton->setFont(font2);
        backToLoginFromForgotButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #6c757d;\n"
"    border: none;\n"
"    font-weight: 300;\n"
"    letter-spacing: 0.5px;\n"
"    text-align: center;\n"
"}\n"
"QPushButton:hover {\n"
"    color: #007bff;\n"
"}"));
        backToLoginFromForgotButton->setFlat(true);

        forgotPasswordFormLayout->addWidget(backToLoginFromForgotButton);

        authStackedWidget->addWidget(forgotPasswordFormPage);

        verticalLayout->addWidget(authStackedWidget);


        retranslateUi(LoginPage);

        authStackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QWidget *LoginPage)
    {
        LoginPage->setWindowTitle(QCoreApplication::translate("LoginPage", "Login", nullptr));
        loginTitle->setText(QCoreApplication::translate("LoginPage", "Sign In", nullptr));
        loginEmailLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Email or Username", nullptr));
        loginPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Password", nullptr));
        rememberMeCheckBox->setText(QCoreApplication::translate("LoginPage", "Remember me", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginPage", "Sign In", nullptr));
        faceLoginButton->setText(QCoreApplication::translate("LoginPage", "Login with Face", nullptr));
        forgotPasswordNavButton->setText(QCoreApplication::translate("LoginPage", "Forgot password?", nullptr));
        signUpNavButton->setText(QCoreApplication::translate("LoginPage", "Don't have an account? Sign up", nullptr));
        signUpTitle->setText(QCoreApplication::translate("LoginPage", "Create Account", nullptr));
        fullNameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Full Name", nullptr));
        signUpEmailLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Email", nullptr));
        signUpPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Password", nullptr));
        confirmPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Confirm Password", nullptr));
        acceptTermsCheckBox->setText(QCoreApplication::translate("LoginPage", "I accept the terms & conditions", nullptr));
        signUpButton->setText(QCoreApplication::translate("LoginPage", "Create Account", nullptr));
        backToLoginFromSignUpButton->setText(QCoreApplication::translate("LoginPage", "Already have an account? Sign in", nullptr));
        forgotPasswordTitle->setText(QCoreApplication::translate("LoginPage", "Reset Password", nullptr));
        forgotPasswordDescription->setText(QCoreApplication::translate("LoginPage", "Enter your email address and we'll send you a link to reset your password.", nullptr));
        resetEmailLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Email or Username", nullptr));
        sendResetLinkButton->setText(QCoreApplication::translate("LoginPage", "Send Reset Link", nullptr));
        backToLoginFromForgotButton->setText(QCoreApplication::translate("LoginPage", "Remember your password? Sign in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
