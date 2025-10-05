#include "media.h"
#include "ui_media.h"

media::media(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::media)
{
    ui->setupUi(this);
}

media::~media()
{
    delete ui;
}

QPushButton* media::getCrudButton() { return ui->crud; }
QPushButton* media::getRbButton() { return ui->rb; }
