#include "sponsorwidget.h"
#include "ui_sponsor.h"
#include <QTableWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

SponsorWidget::SponsorWidget(QWidget *parent) : QWidget(parent), ui(new Ui::SponsorWidget)
{
    ui->setupUi(this);
}

SponsorWidget::~SponsorWidget()
{
    delete ui;
}

QTableWidget* SponsorWidget::getAfficheTable() const
{
    return ui->affiche;
}

QLineEdit* SponsorWidget::getIDLineEdit() const
{
    return ui->ID;
}

QLineEdit* SponsorWidget::getNomLineEdit() const
{
    return ui->Nom;
}

QLineEdit* SponsorWidget::getEmailLineEdit() const
{
    return ui->EM;
}

QDateEdit* SponsorWidget::getDateDebutEdit() const
{
    return ui->dd;
}

QDateEdit* SponsorWidget::getDateFinEdit() const
{
    return ui->df;
}

QComboBox* SponsorWidget::getStatusComboBox() const
{
    return ui->STS;
}

QLineEdit* SponsorWidget::getSearchLineEdit() const
{
    return ui->search1;
}
