/********************************************************************************
** Form generated from reading UI file 'employerform.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYERFORM_H
#define UI_EMPLOYERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EmployerForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *errorLabel;
    QHBoxLayout *mainLayout;
    QVBoxLayout *formLayout_main;
    QLabel *label_info;
    QFormLayout *formLayout;
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *roleLabel;
    QComboBox *roleComboBox;
    QLabel *startDateLabel;
    QDateEdit *startDateEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *avatarLabel;
    QHBoxLayout *avatarLayout;
    QLineEdit *avatarLineEdit;
    QPushButton *browseAvatarButton;
    QLabel *avatarPreviewLabel;
    QVBoxLayout *avatarLayout_2;
    QLabel *resourceLabel;
    QListWidget *resourceListWidget;
    QHBoxLayout *resourceButtonLayout;
    QPushButton *addResourceButton;
    QPushButton *removeResourceButton;
    QLabel *projectLabel;
    QListWidget *projectListWidget;
    QHBoxLayout *projectButtonLayout;
    QPushButton *addProjectButton;
    QPushButton *removeProjectButton;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *EmployerForm)
    {
        if (EmployerForm->objectName().isEmpty())
            EmployerForm->setObjectName("EmployerForm");
        EmployerForm->resize(980, 700);
        EmployerForm->setMinimumSize(QSize(900, 680));
        verticalLayout = new QVBoxLayout(EmployerForm);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        titleLabel = new QLabel(EmployerForm);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(titleLabel);

        errorLabel = new QLabel(EmployerForm);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setStyleSheet(QString::fromUtf8("QLabel { color: #c82333; }"));
        errorLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        errorLabel->setWordWrap(true);

        verticalLayout->addWidget(errorLabel);

        mainLayout = new QHBoxLayout();
        mainLayout->setObjectName("mainLayout");
        formLayout_main = new QVBoxLayout();
        formLayout_main->setObjectName("formLayout_main");
        label_info = new QLabel(EmployerForm);
        label_info->setObjectName("label_info");

        formLayout_main->addWidget(label_info);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        firstNameLabel = new QLabel(EmployerForm);
        firstNameLabel->setObjectName("firstNameLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, firstNameLabel);

        firstNameLineEdit = new QLineEdit(EmployerForm);
        firstNameLineEdit->setObjectName("firstNameLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, firstNameLineEdit);

        lastNameLabel = new QLabel(EmployerForm);
        lastNameLabel->setObjectName("lastNameLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, lastNameLabel);

        lastNameLineEdit = new QLineEdit(EmployerForm);
        lastNameLineEdit->setObjectName("lastNameLineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, lastNameLineEdit);

        emailLabel = new QLabel(EmployerForm);
        emailLabel->setObjectName("emailLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, emailLabel);

        emailLineEdit = new QLineEdit(EmployerForm);
        emailLineEdit->setObjectName("emailLineEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, emailLineEdit);

        phoneLabel = new QLabel(EmployerForm);
        phoneLabel->setObjectName("phoneLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, phoneLabel);

        phoneLineEdit = new QLineEdit(EmployerForm);
        phoneLineEdit->setObjectName("phoneLineEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, phoneLineEdit);

        roleLabel = new QLabel(EmployerForm);
        roleLabel->setObjectName("roleLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, roleLabel);

        roleComboBox = new QComboBox(EmployerForm);
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->setObjectName("roleComboBox");

        formLayout->setWidget(4, QFormLayout::FieldRole, roleComboBox);

        startDateLabel = new QLabel(EmployerForm);
        startDateLabel->setObjectName("startDateLabel");

        formLayout->setWidget(5, QFormLayout::LabelRole, startDateLabel);

        startDateEdit = new QDateEdit(EmployerForm);
        startDateEdit->setObjectName("startDateEdit");
        startDateEdit->setCalendarPopup(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, startDateEdit);

        passwordLabel = new QLabel(EmployerForm);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(6, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(EmployerForm);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(6, QFormLayout::FieldRole, passwordLineEdit);

        avatarLabel = new QLabel(EmployerForm);
        avatarLabel->setObjectName("avatarLabel");

        formLayout->setWidget(7, QFormLayout::LabelRole, avatarLabel);

        avatarLayout = new QHBoxLayout();
        avatarLayout->setObjectName("avatarLayout");
        avatarLineEdit = new QLineEdit(EmployerForm);
        avatarLineEdit->setObjectName("avatarLineEdit");
        avatarLineEdit->setReadOnly(true);

        avatarLayout->addWidget(avatarLineEdit);

        browseAvatarButton = new QPushButton(EmployerForm);
        browseAvatarButton->setObjectName("browseAvatarButton");

        avatarLayout->addWidget(browseAvatarButton);


        formLayout->setLayout(7, QFormLayout::FieldRole, avatarLayout);

        avatarPreviewLabel = new QLabel(EmployerForm);
        avatarPreviewLabel->setObjectName("avatarPreviewLabel");
        avatarPreviewLabel->setMinimumSize(QSize(180, 180));
        avatarPreviewLabel->setMaximumSize(QSize(180, 180));
        avatarPreviewLabel->setStyleSheet(QString::fromUtf8("QLabel { border: 2px solid #ccc; border-radius: 0px; background-color: #f5f5f5; }"));
        avatarPreviewLabel->setFrameShape(QFrame::Shape::StyledPanel);
        avatarPreviewLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(8, QFormLayout::FieldRole, avatarPreviewLabel);


        formLayout_main->addLayout(formLayout);


        mainLayout->addLayout(formLayout_main);

        avatarLayout_2 = new QVBoxLayout();
        avatarLayout_2->setObjectName("avatarLayout_2");
        resourceLabel = new QLabel(EmployerForm);
        resourceLabel->setObjectName("resourceLabel");

        avatarLayout_2->addWidget(resourceLabel);

        resourceListWidget = new QListWidget(EmployerForm);
        resourceListWidget->setObjectName("resourceListWidget");
        resourceListWidget->setMinimumSize(QSize(220, 90));

        avatarLayout_2->addWidget(resourceListWidget);

        resourceButtonLayout = new QHBoxLayout();
        resourceButtonLayout->setObjectName("resourceButtonLayout");
        addResourceButton = new QPushButton(EmployerForm);
        addResourceButton->setObjectName("addResourceButton");

        resourceButtonLayout->addWidget(addResourceButton);

        removeResourceButton = new QPushButton(EmployerForm);
        removeResourceButton->setObjectName("removeResourceButton");

        resourceButtonLayout->addWidget(removeResourceButton);


        avatarLayout_2->addLayout(resourceButtonLayout);

        projectLabel = new QLabel(EmployerForm);
        projectLabel->setObjectName("projectLabel");

        avatarLayout_2->addWidget(projectLabel);

        projectListWidget = new QListWidget(EmployerForm);
        projectListWidget->setObjectName("projectListWidget");
        projectListWidget->setMinimumSize(QSize(220, 90));

        avatarLayout_2->addWidget(projectListWidget);

        projectButtonLayout = new QHBoxLayout();
        projectButtonLayout->setObjectName("projectButtonLayout");
        addProjectButton = new QPushButton(EmployerForm);
        addProjectButton->setObjectName("addProjectButton");

        projectButtonLayout->addWidget(addProjectButton);

        removeProjectButton = new QPushButton(EmployerForm);
        removeProjectButton->setObjectName("removeProjectButton");

        projectButtonLayout->addWidget(removeProjectButton);


        avatarLayout_2->addLayout(projectButtonLayout);


        mainLayout->addLayout(avatarLayout_2);


        verticalLayout->addLayout(mainLayout);

        buttonBox = new QDialogButtonBox(EmployerForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(EmployerForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, EmployerForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, EmployerForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EmployerForm);
    } // setupUi

    void retranslateUi(QDialog *EmployerForm)
    {
        EmployerForm->setWindowTitle(QCoreApplication::translate("EmployerForm", "Employer", nullptr));
        titleLabel->setText(QCoreApplication::translate("EmployerForm", "Employer Details", nullptr));
        errorLabel->setText(QString());
        label_info->setText(QCoreApplication::translate("EmployerForm", "Personal Information", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("EmployerForm", "First Name *", nullptr));
        firstNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerForm", "e.g. Alex", nullptr));
        lastNameLabel->setText(QCoreApplication::translate("EmployerForm", "Last Name *", nullptr));
        lastNameLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerForm", "e.g. Morgan", nullptr));
        emailLabel->setText(QCoreApplication::translate("EmployerForm", "Email *", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerForm", "name@example.com", nullptr));
        phoneLabel->setText(QCoreApplication::translate("EmployerForm", "Phone", nullptr));
        phoneLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerForm", "Optional", nullptr));
        roleLabel->setText(QCoreApplication::translate("EmployerForm", "Role *", nullptr));
        roleComboBox->setItemText(0, QCoreApplication::translate("EmployerForm", "Select role", nullptr));
        roleComboBox->setItemText(1, QCoreApplication::translate("EmployerForm", "Administrator", nullptr));
        roleComboBox->setItemText(2, QCoreApplication::translate("EmployerForm", "HR Manager", nullptr));
        roleComboBox->setItemText(3, QCoreApplication::translate("EmployerForm", "Project Lead", nullptr));
        roleComboBox->setItemText(4, QCoreApplication::translate("EmployerForm", "Recruiter", nullptr));
        roleComboBox->setItemText(5, QCoreApplication::translate("EmployerForm", "Finance", nullptr));

        startDateLabel->setText(QCoreApplication::translate("EmployerForm", "Start Date *", nullptr));
        passwordLabel->setText(QCoreApplication::translate("EmployerForm", "Password *", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerForm", "Minimum 8 characters", nullptr));
        avatarLabel->setText(QCoreApplication::translate("EmployerForm", "Avatar", nullptr));
        avatarLineEdit->setPlaceholderText(QCoreApplication::translate("EmployerForm", "Optional image path", nullptr));
        browseAvatarButton->setText(QCoreApplication::translate("EmployerForm", "Browse...", nullptr));
        avatarPreviewLabel->setText(QCoreApplication::translate("EmployerForm", "No preview", nullptr));
        resourceLabel->setText(QCoreApplication::translate("EmployerForm", "Assigned Resources", nullptr));
        addResourceButton->setText(QCoreApplication::translate("EmployerForm", "Add Resource", nullptr));
        removeResourceButton->setText(QCoreApplication::translate("EmployerForm", "Remove", nullptr));
        projectLabel->setText(QCoreApplication::translate("EmployerForm", "Assigned Projects", nullptr));
        addProjectButton->setText(QCoreApplication::translate("EmployerForm", "Add Project", nullptr));
        removeProjectButton->setText(QCoreApplication::translate("EmployerForm", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmployerForm: public Ui_EmployerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYERFORM_H
