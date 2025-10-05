#ifndef RB_H
#define RB_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class rb;
}

class rb : public QWidget
{
    Q_OBJECT

public:
    explicit rb(QWidget *parent = nullptr);
    ~rb();

    QPushButton* getCrudButton();
    QPushButton* getMediaButton();
    QPushButton* getRbButton();  // optional

private:
    Ui::rb *ui;
};

#endif // RB_H
