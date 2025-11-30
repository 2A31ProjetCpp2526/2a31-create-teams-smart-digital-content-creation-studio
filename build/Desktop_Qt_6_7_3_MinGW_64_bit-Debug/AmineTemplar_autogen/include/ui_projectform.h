/********************************************************************************
** Form generated from reading UI file 'projectform.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTFORM_H
#define UI_PROJECTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProjectForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *errorLabel;
    QFormLayout *formLayout;
    QLabel *titleFieldLabel;
    QLineEdit *titleLineEdit;
    QLabel *descriptionLabel;
    QTextEdit *descriptionTextEdit;
    QLabel *clientLabel;
    QLineEdit *clientLineEdit;
    QLabel *serviceLabel;
    QLineEdit *serviceLineEdit;
    QLabel *creationDateLabel;
    QDateEdit *creationDateEdit;
    QLabel *modificationDateLabel;
    QDateEdit *modificationDateEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProjectForm)
    {
        if (ProjectForm->objectName().isEmpty())
            ProjectForm->setObjectName("ProjectForm");
        ProjectForm->setMinimumSize(QSize(600, 400));
        verticalLayout = new QVBoxLayout(ProjectForm);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        titleLabel = new QLabel(ProjectForm);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        errorLabel = new QLabel(ProjectForm);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setStyleSheet(QString::fromUtf8("QLabel { color: #c82333; }"));
        errorLabel->setWordWrap(true);

        verticalLayout->addWidget(errorLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        titleFieldLabel = new QLabel(ProjectForm);
        titleFieldLabel->setObjectName("titleFieldLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, titleFieldLabel);

        titleLineEdit = new QLineEdit(ProjectForm);
        titleLineEdit->setObjectName("titleLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, titleLineEdit);

        descriptionLabel = new QLabel(ProjectForm);
        descriptionLabel->setObjectName("descriptionLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, descriptionLabel);

        descriptionTextEdit = new QTextEdit(ProjectForm);
        descriptionTextEdit->setObjectName("descriptionTextEdit");
        descriptionTextEdit->setMinimumHeight(80);

        formLayout->setWidget(1, QFormLayout::FieldRole, descriptionTextEdit);

        clientLabel = new QLabel(ProjectForm);
        clientLabel->setObjectName("clientLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, clientLabel);

        clientLineEdit = new QLineEdit(ProjectForm);
        clientLineEdit->setObjectName("clientLineEdit");
        clientLineEdit->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, clientLineEdit);

        serviceLabel = new QLabel(ProjectForm);
        serviceLabel->setObjectName("serviceLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, serviceLabel);

        serviceLineEdit = new QLineEdit(ProjectForm);
        serviceLineEdit->setObjectName("serviceLineEdit");
        serviceLineEdit->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, serviceLineEdit);

        creationDateLabel = new QLabel(ProjectForm);
        creationDateLabel->setObjectName("creationDateLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, creationDateLabel);

        creationDateEdit = new QDateEdit(ProjectForm);
        creationDateEdit->setObjectName("creationDateEdit");
        creationDateEdit->setReadOnly(true);
        creationDateEdit->setCalendarPopup(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, creationDateEdit);

        modificationDateLabel = new QLabel(ProjectForm);
        modificationDateLabel->setObjectName("modificationDateLabel");

        formLayout->setWidget(5, QFormLayout::LabelRole, modificationDateLabel);

        modificationDateEdit = new QDateEdit(ProjectForm);
        modificationDateEdit->setObjectName("modificationDateEdit");
        modificationDateEdit->setCalendarPopup(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, modificationDateEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(ProjectForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ProjectForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ProjectForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ProjectForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ProjectForm);
    } // setupUi

    void retranslateUi(QDialog *ProjectForm)
    {
        ProjectForm->setWindowTitle(QCoreApplication::translate("ProjectForm", "Project", nullptr));
        titleLabel->setText(QCoreApplication::translate("ProjectForm", "Project Details", nullptr));
        errorLabel->setText(QString());
        titleFieldLabel->setText(QCoreApplication::translate("ProjectForm", "Title *", nullptr));
        titleLineEdit->setPlaceholderText(QCoreApplication::translate("ProjectForm", "e.g. Website Redesign", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("ProjectForm", "Description *", nullptr));
        descriptionTextEdit->setPlaceholderText(QCoreApplication::translate("ProjectForm", "Enter project description", nullptr));
        clientLabel->setText(QCoreApplication::translate("ProjectForm", "Client", nullptr));
        clientLineEdit->setPlaceholderText(QCoreApplication::translate("ProjectForm", "Client ID or Name", nullptr));
        serviceLabel->setText(QCoreApplication::translate("ProjectForm", "Service", nullptr));
        serviceLineEdit->setPlaceholderText(QCoreApplication::translate("ProjectForm", "Service ID or Name", nullptr));
        creationDateLabel->setText(QCoreApplication::translate("ProjectForm", "Creation Date", nullptr));
        modificationDateLabel->setText(QCoreApplication::translate("ProjectForm", "Modification Date", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectForm: public Ui_ProjectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTFORM_H
