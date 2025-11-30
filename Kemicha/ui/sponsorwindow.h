#ifndef SPONSORWINDOW_H
#define SPONSORWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QModelIndex>

namespace Ui {
class SponsorForm;  // sponsorf.ui uses SponsorForm class
}

class SponsorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SponsorWindow(QWidget *parent = nullptr);
    ~SponsorWindow();

private slots:
    // CRUD Operations
    void addSponsor();
    void updateSponsor();
    void deleteSponsor();
    void loadSponsors();
    
    // Search and Sort
    void searchSponsorById();
    void sortById();
    
    // Export
    void exportPDF();
    
    // Form operations
    void clearFields();
    void onSponsorSelected(const QModelIndex &index);
    
    // Statistics and Calendar
    void showStatistics();
    void openCalendar();
    
private:
    Ui::SponsorForm *ui;
    
    // Helper methods
    QMap<QString, int> getStatusFromTable();
    void drawPieChart(const QMap<QString, int> &stats);
    bool sendWelcomeEmail(const QString &email, const QString &name);
};

#endif // SPONSORWINDOW_H
