#ifndef SPONSORWIDGET_H
#define SPONSORWIDGET_H

#include <QWidget>

namespace Ui {
class SponsorWidget;
}

class SponsorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SponsorWidget(QWidget *parent = nullptr);
    ~SponsorWidget();

private:
    Ui::SponsorWidget *ui;
};

#endif // SPONSORWIDGET_H
