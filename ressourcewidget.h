#ifndef RESSOURCEWIDGET_H
#define RESSOURCEWIDGET_H

#include <QWidget>

namespace Ui {
class RessourceWidget;
}

class RessourceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RessourceWidget(QWidget *parent = nullptr);
    ~RessourceWidget();

private:
    Ui::RessourceWidget *ui;
};

#endif // RESSOURCEWIDGET_H
