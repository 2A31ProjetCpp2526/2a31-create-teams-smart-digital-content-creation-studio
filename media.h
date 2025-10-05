#ifndef MEDIA_H
#define MEDIA_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class media;
}

class media : public QWidget
{
    Q_OBJECT

public:
    explicit media(QWidget *parent = nullptr);
    ~media();

    QPushButton* getCrudButton();
    QPushButton* getRbButton();

private:
    Ui::media *ui;
};

#endif // MEDIA_H
