#ifndef SPONSORWIDGET_H
#define SPONSORWIDGET_H

#include <QWidget>

namespace Ui { class SponsorWidget; }

class QTableWidget;
class QLineEdit;
class QDateEdit;
class QComboBox;

class SponsorWidget : public QWidget {
    Q_OBJECT
public:
    explicit SponsorWidget(QWidget *parent = nullptr);
    ~SponsorWidget();

    // Public getters for UI widgets
    QTableWidget* getAfficheTable() const;
    QLineEdit* getIDLineEdit() const;
    QLineEdit* getNomLineEdit() const;
    QLineEdit* getEmailLineEdit() const;
    QDateEdit* getDateDebutEdit() const;
    QDateEdit* getDateFinEdit() const;
    QComboBox* getStatusComboBox() const;
    QLineEdit* getSearchLineEdit() const;

private:
    Ui::SponsorWidget *ui;
};

#endif // SPONSORWIDGET_H
