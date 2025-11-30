#include "sponsorwindow.h"
#include "ui_sponsorf.h"
#include "../smtpclient.h"
#include "../todo_dialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QHeaderView>
#include <QRegularExpression>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>

SponsorWindow::SponsorWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SponsorForm)
{
    ui->setupUi(this);
    
    setWindowTitle("Gestion des Sponsors");
    
    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &SponsorWindow::addSponsor);
    connect(ui->updateButton, &QPushButton::clicked, this, &SponsorWindow::updateSponsor);
    connect(ui->deleteButton, &QPushButton::clicked, this, &SponsorWindow::deleteSponsor);
    connect(ui->afficherButton, &QPushButton::clicked, this, &SponsorWindow::loadSponsors);
    connect(ui->search1_2, &QPushButton::clicked, this, &SponsorWindow::searchSponsorById);
    connect(ui->pdfexport, &QPushButton::clicked, this, &SponsorWindow::exportPDF);
    connect(ui->sort, &QPushButton::clicked, this, &SponsorWindow::sortById);
    connect(ui->clear, &QPushButton::clicked, this, &SponsorWindow::clearFields);
    connect(ui->affiche, &QTableWidget::clicked, this, &SponsorWindow::onSponsorSelected);
    connect(ui->Stat, &QPushButton::clicked, this, &SponsorWindow::showStatistics);
    connect(ui->calendrier, &QPushButton::clicked, this, &SponsorWindow::openCalendar);
    
    // Initialize date fields with current date
    ui->dd->setDate(QDate::currentDate());
    ui->df->setDate(QDate::currentDate().addMonths(12));
    
    // Load sponsors on startup
    loadSponsors();
}

SponsorWindow::~SponsorWindow()
{
    delete ui;
}

void SponsorWindow::addSponsor()
{
    QString idText = ui->ID->text().trimmed();
    int id = idText.toInt();
    QString nom = ui->Nom->text().trimmed();
    QString email = ui->EM->text().trimmed();
    QDate dateDebut = ui->dd->date();
    QDate dateFin = ui->df->date();
    QString status = ui->STS->currentText();
    
    // Validate status selection
    if (status == "Selectionner...") {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un status valide.");
        return;
    }
    
    // Validate empty fields
    if (idText.isEmpty() || nom.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }
    
    // Validate ID: only numbers
    QRegularExpression regexID("^[0-9]+$");
    if (!regexID.match(idText).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir uniquement des chiffres.");
        return;
    }
    
    // Validate Name: letters + accents + spaces, minimum 4 characters
    QRegularExpression regexNom("^[A-Za-zÀ-ÖØ-öø-ÿ ]{4,}$");
    if (!regexNom.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Erreur", 
            "Le nom doit contenir uniquement des lettres et au minimum 4 caractères.");
        return;
    }
    
    // Validate Email format
    QRegularExpression regexMail("^[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}$");
    if (!regexMail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un email valide.");
        return;
    }
    
    // Validate dates
    if (!dateDebut.isValid() || !dateFin.isValid()) {
        QMessageBox::warning(this, "Erreur", "Les dates ne sont pas valides.");
        return;
    }
    
    // Check for duplicate ID
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM SPONSORS WHERE ID_SPONS = :id");
    checkQuery.bindValue(":id", id);
    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Erreur", checkQuery.lastError().text());
        return;
    }
    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "Cet ID existe déjà !");
        return;
    }
    
    // Insert into database
    QSqlQuery query;
    query.prepare("INSERT INTO SPONSORS (ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS) "
                  "VALUES (:id, :nom, :email, :dd, :df, :status)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":dd", dateDebut);
    query.bindValue(":df", dateFin);
    query.bindValue(":status", status);
    
    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor ajouté avec succès.");
        
        // Send welcome email
        if (sendWelcomeEmail(email, nom)) {
            QMessageBox::information(this, "Email", "Email de bienvenue envoyé avec succès !");
        } else {
            QMessageBox::warning(this, "Email", "Erreur lors de l'envoi du mail de bienvenue.");
        }
        
        loadSponsors();
        clearFields();
    } else {
        QMessageBox::critical(this, "Erreur insertion", query.lastError().text());
    }
}

void SponsorWindow::updateSponsor()
{
    int id = ui->ID->text().toInt();
    QString nom = ui->Nom->text().trimmed();
    QString email = ui->EM->text().trimmed();
    QDate dateDebut = ui->dd->date();
    QDate dateFin = ui->df->date();
    QString status = ui->STS->currentText();
    
    // Validate input
    if (nom.isEmpty() || email.isEmpty() || !dateDebut.isValid() || !dateFin.isValid() || status.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement !");
        return;
    }
    
    if (status == "Selectionner...") {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un status valide.");
        return;
    }
    
    // Execute UPDATE query
    QSqlQuery query;
    query.prepare("UPDATE SPONSORS SET NOM_SPONS = :nom, EMAIL = :email, DATE_DEBUT = :dd, "
                  "DATE_FIN = :df, STATUS = :status WHERE ID_SPONS = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":dd", dateDebut);
    query.bindValue(":df", dateFin);
    query.bindValue(":status", status);
    
    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor mis à jour avec succès.");
        loadSponsors();
        ui->ID->setEnabled(true);
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}

void SponsorWindow::deleteSponsor()
{
    int row = ui->affiche->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un sponsor à supprimer !");
        return;
    }
    
    QString id = ui->affiche->item(row, 0)->text();
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer la suppression",
                                  "Voulez-vous vraiment supprimer ce sponsor ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;
    
    QSqlQuery query;
    query.prepare("DELETE FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);
    
    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor supprimé avec succès.");
        loadSponsors();
        clearFields();
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}

void SponsorWindow::loadSponsors()
{
    QSqlQuery query("SELECT * FROM SPONSORS");
    
    ui->affiche->clear();
    ui->affiche->setRowCount(0);
    ui->affiche->setColumnCount(6);
    
    QStringList headers = {"ID", "Nom", "Date Début", "Date Fin", "Email", "Status"};
    ui->affiche->setHorizontalHeaderLabels(headers);
    
    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("DATE_DEBUT").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        
        row++;
    }
    
    ui->affiche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void SponsorWindow::searchSponsorById()
{
    QString searchId = ui->search1->text().trimmed();
    
    if (searchId.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à rechercher !");
        return;
    }
    
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", searchId);
    
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        return;
    }
    
    ui->affiche->clear();
    ui->affiche->setRowCount(0);
    ui->affiche->setColumnCount(6);
    QStringList headers = {"ID", "Nom", "Date Début", "Date Fin", "Email", "Status"};
    ui->affiche->setHorizontalHeaderLabels(headers);
    
    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("DATE_DEBUT").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        row++;
    }
    
    ui->affiche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void SponsorWindow::sortById()
{
    QSqlQuery query;
    if (!query.exec("SELECT ID_SPONS, NOM_SPONS, DATE_DEBUT, DATE_FIN, EMAIL, STATUS FROM SPONSORS ORDER BY ID_SPONS ASC")) {
        QMessageBox::critical(this, "Erreur SQL", "Échec du tri : " + query.lastError().text());
        return;
    }
    
    ui->affiche->setRowCount(0);
    
    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("DATE_DEBUT").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        row++;
    }
    
    QMessageBox::information(this, "Tri effectué", "Les sponsors ont été triés par ID (ordre croissant).");
}

void SponsorWindow::exportPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", 
                                                     QDir::homePath() + "/sponsors.pdf", 
                                                     "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty())
        return;
    
    QSqlQueryModel model;
    model.setQuery("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS FROM SPONSORS");
    
    if (model.rowCount() == 0) {
        QMessageBox::information(this, "Info", "Aucune donnée trouvée dans la table SPONSORS.");
        return;
    }
    
    QString html;
    html += "<html><head><style>"
            "body { font-family: Arial; margin: 20px; }"
            "table { width: 100%; border-collapse: collapse; }"
            "th, td { border: 1px solid #000; padding: 8px; text-align: center; }"
            "th { background-color: #f2f2f2; }"
            "</style></head><body>";
    html += "<h2 align='center'>Liste des Sponsors</h2><br>";
    html += "<table><tr>";
    
    QStringList headers = {"ID", "Nom", "Email", "Date Début", "Date Fin", "Status"};
    for (const QString &header : headers) {
        html += "<th>" + header + "</th>";
    }
    html += "</tr>";
    
    for (int row = 0; row < model.rowCount(); row++) {
        html += "<tr>";
        for (int col = 0; col < model.columnCount(); col++) {
            html += "<td>" + model.data(model.index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }
    
    html += "</table></body></html>";
    
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    
    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);
    
    QMessageBox::information(this, "Succès", "Fichier PDF exporté avec succès !");
}

void SponsorWindow::clearFields()
{
    ui->ID->clear();
    ui->Nom->clear();
    ui->EM->clear();
    ui->dd->setDate(QDate::currentDate());
    ui->df->setDate(QDate::currentDate().addMonths(12));
    ui->STS->setCurrentIndex(0);
    ui->ID->setEnabled(true);
}

void SponsorWindow::onSponsorSelected(const QModelIndex &index)
{
    int row = index.row();
    
    QAbstractItemModel *model = ui->affiche->model();
    int id = model->data(model->index(row, 0)).toInt();
    
    QSqlQuery query;
    query.prepare("SELECT NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        ui->ID->setText(QString::number(id));
        ui->Nom->setText(query.value(0).toString());
        ui->EM->setText(query.value(1).toString());
        ui->dd->setDate(QDate::fromString(query.value(2).toString(), "yyyy-MM-dd"));
        ui->df->setDate(QDate::fromString(query.value(3).toString(), "yyyy-MM-dd"));
        ui->STS->setCurrentText(query.value(4).toString());
        ui->ID->setEnabled(false);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les données du sponsor sélectionné.");
    }
}

QMap<QString, int> SponsorWindow::getStatusFromTable()
{
    QMap<QString, int> stats;
    int rows = ui->affiche->rowCount();
    int statusCol = 5; // index of STATUS column
    
    for (int i = 0; i < rows; ++i) {
        QTableWidgetItem *item = ui->affiche->item(i, statusCol);
        if (!item) continue;
        QString status = item->text();
        stats[status] += 1;
    }
    return stats;
}

void SponsorWindow::drawPieChart(const QMap<QString, int> &stats)
{
    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible.");
        return;
    }
    
    const int size = 360;
    QPixmap pix(size, size);
    pix.fill(Qt::transparent);
    
    QPainter painter(&pix);
    painter.setRenderHint(QPainter::Antialiasing);
    QRectF rect(0, 0, size, size);
    
    int total = 0;
    for (auto v : stats) total += v;
    
    int startAngle = 0;
    
    const QVector<QColor> palette = {
        QColor(52, 152, 219),   // Blue
        QColor(231, 76, 60),    // Red
        QColor(46, 204, 113),   // Green
        QColor(155, 89, 182),   // Purple
        QColor(241, 196, 15)    // Yellow
    };
    
    QMap<QString, QColor> colorMap;
    
    int i = 0;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString key = it.key();
        int spanAngle = static_cast<int>(360.0 * it.value() / total * 16);
        
        QColor color = palette[i % palette.size()];
        colorMap.insert(key, color);
        
        painter.setBrush(color);
        painter.setPen(Qt::black);
        painter.drawPie(rect, startAngle, spanAngle);
        
        startAngle += spanAngle;
        i++;
    }
    
    QDialog dlg(this);
    dlg.setWindowTitle("Statistiques - Camembert");
    dlg.setMinimumSize(500, 400);
    QVBoxLayout *lay = new QVBoxLayout(&dlg);
    
    QLabel *lbl = new QLabel(&dlg);
    lbl->setPixmap(pix);
    lbl->setAlignment(Qt::AlignCenter);
    
    QWidget *legendWidget = new QWidget(&dlg);
    QVBoxLayout *legendLayout = new QVBoxLayout(legendWidget);
    legendLayout->setContentsMargins(6, 6, 6, 6);
    legendLayout->setSpacing(8);
    
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString name = it.key();
        int count = it.value();
        double pct = total > 0 ? (100.0 * count / total) : 0.0;
        
        QHBoxLayout *rowLayout = new QHBoxLayout;
        
        QLabel *swatch = new QLabel(legendWidget);
        swatch->setFixedSize(18, 18);
        swatch->setStyleSheet(QString("background-color: %1; border: 1px solid #000;")
                                  .arg(colorMap.value(name).name()));
        
        QLabel *textLabel = new QLabel(QString("%1 — %2 (%3%)")
                                           .arg(name).arg(count).arg(QString::number(pct, 'f', 1)), legendWidget);
        
        rowLayout->addWidget(swatch);
        rowLayout->addWidget(textLabel);
        rowLayout->addStretch();
        legendLayout->addLayout(rowLayout);
    }
    
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(lbl);
    container->addWidget(legendWidget);
    lay->addLayout(container);
    
    dlg.exec();
}

void SponsorWindow::showStatistics()
{
    loadSponsors();
    
    QMap<QString, int> stats = getStatusFromTable();
    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible.");
        return;
    }
    
    drawPieChart(stats);
    
    int total = 0;
    for (auto v : stats) total += v;
    
    QString summary;
    summary += QString("Total sponsors: %1\n\n").arg(total);
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        double pct = (total > 0) ? (100.0 * it.value() / total) : 0.0;
        summary += QString("%1: %2 (%3%)\n")
                       .arg(it.key())
                       .arg(QString::number(it.value()))
                       .arg(QString::number(pct, 'f', 1));
    }
    
    QMessageBox::information(this, "Statistiques (texte)", summary);
}

void SponsorWindow::openCalendar()
{
    TodoDialog dlg(this);
    dlg.exec();
}

bool SponsorWindow::sendWelcomeEmail(const QString &email, const QString &name)
{
    SmtpClient smtp("daoudemna4@gmail.com", "aldz cikf jftf nvpj");
    
    QString subject = "Bienvenue parmi nos sponsors";
    QString body = "Bonjour " + name + ",\n\n"
                   "Merci d'avoir rejoint notre programme de sponsors.\n"
                   "Nous sommes ravis de vous compter parmi nos partenaires.\n\n"
                   "Cordialement,\n"
                   "L'équipe AmineTemplar";
    
    return smtp.sendMail(email, subject, body);
}
