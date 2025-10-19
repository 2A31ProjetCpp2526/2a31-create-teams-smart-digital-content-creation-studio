#include "ressourcewidget.h"
#include "ui_ressource.h"

RessourceWidget::RessourceWidget(QWidget *parent) : QWidget(parent), ui(new Ui::RessourceWidget)
{
    ui->setupUi(this);
}

RessourceWidget::~RessourceWidget()
{
    delete ui;
}
