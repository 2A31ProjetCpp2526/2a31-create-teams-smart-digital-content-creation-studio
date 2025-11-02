#include "sponsorwidget.h"
#include "ui_sponsor.h"

SponsorWidget::SponsorWidget(QWidget *parent) : QWidget(parent), ui(new Ui::SponsorWidget)
{
    ui->setupUi(this);
}

SponsorWidget::~SponsorWidget()
{
    delete ui;
}
