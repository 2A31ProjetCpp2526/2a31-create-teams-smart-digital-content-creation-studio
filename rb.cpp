#include "rb.h"
#include "ui_rb.h"

rb::rb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rb)
{
    ui->setupUi(this);
}

rb::~rb()
{
    delete ui;
}

// Buttons
QPushButton* rb::getCrudButton() { return ui->crud; }      // back to MainWindow
QPushButton* rb::getMediaButton() { return ui->media; }    // goes to Media
