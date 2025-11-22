#include "mainwindow.h"
#include "smtpclient.h"
#include "./ui_mainwindow.h"
#include <QCalendarWidget>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlRecord>
#include <cstdlib>
#include <ctime>
#include <QPrinter>
#include <QTextDocument>
#include <QRandomGenerator>
#include <QTextCursor>
#include <QSqlQueryModel>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCharFormat>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QColor>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QMap>
#include <QString>
#include <QList>
#include <QRectF>
#include "todo_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    //Initialisation des buttons
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addSponsor);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateSponsor);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSelectedSponsor);
    connect(ui->afficherButton, &QPushButton::clicked, this, &MainWindow::loadSponsoring);
    connect(ui->search1_2, &QPushButton::clicked, this, &MainWindow:: searchSponsorById);
    connect(ui->pdfexport, &QPushButton::clicked, this, &MainWindow::on_pdfexport_clicked);
    connect(ui->sort,&QPushButton::clicked, this, &MainWindow::on_sort_clicked);
    connect(ui->clear, &QPushButton::clicked, this, &MainWindow::clearFields);
    connect(ui->affiche, &QTableView::clicked, this, &MainWindow::onSponsorSelected);
    connect(ui->Stat, &QPushButton::clicked, this, &MainWindow::on_pushButton_stat_clicked);

    // Create a simple action in the menubar for ToDo manager
    QAction *todoAction = new QAction(tr("Tâches / Rappels"), this);
    menuBar()->addAction(todoAction);
    connect(todoAction, &QAction::triggered, this, &MainWindow::openTodoManager);

    // wire calendar button
    connect(ui->calendrier, &QPushButton::clicked, this, &MainWindow::openCalendar);


}

void MainWindow::openTodoManager()
{
    TodoDialog dlg(this);
    dlg.exec();
}

void MainWindow::openCalendar()
{
    // Open the Todo/Calendar dialog so calendar functions as a ToDo list
    TodoDialog dlg(this);
    dlg.exec();
}

// mail sending removed (Mailjet) per user request

void MainWindow::addSponsor() {
    QString idText = ui->ID->text();      // we check text before converting
    int id = idText.toInt();
    QString nom = ui->Nom->text();
    QString email = ui->EM->text();
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();
    QString status = ui->STS->currentText();

    // Vérifier le status
    if (status == "Selectionner...") {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un status valide.");
        return;
    }

    // Vérifier champs vides
    if (idText.isEmpty() || nom.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }

    // -----------------------------
    // 🔍 CONTROLES DE SAISIE
    // -----------------------------

    // ID : uniquement numérique
    QRegularExpression regexID("^[0-9]+$");
    if (!regexID.match(idText).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir uniquement des chiffres.");
        return;
    }

    // Nom : lettres + accents + espaces, minimum 4 caractères
    QRegularExpression regexNom("^[A-Za-zÀ-ÖØ-öø-ÿ ]{4,}$");
    if (!regexNom.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Erreur",
                             "Le nom doit contenir uniquement des lettres et au minimum 4 caractères.");
        return;
    }

    // Email : format valide
    QRegularExpression regexMail("^[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}$");
    if (!regexMail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un email valide.");
        return;
    }

    // Dates valides
    if (!dd.isValid() || !df.isValid()) {
        QMessageBox::warning(this, "Erreur", "Les dates ne sont pas valides.");
        return;
    }

    // Vérifier ID doublon
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

    // Insertion
    QSqlQuery query;
    query.prepare("INSERT INTO SPONSORS (ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS) "
                  "VALUES (:id, :nom, :email, :dd, :df, :status)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":dd", dd);
    query.bindValue(":df", df);
    query.bindValue(":status", status);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor ajouté avec succès.");
        loadSponsoring();
        clearFields();
    } else {
        QMessageBox::critical(this, "Erreur insertion", query.lastError().text());
    }
    SmtpClient smtp("daoudemna4@gmail.com", "aldz cikf jftf nvpj");

    QString subject = "Bienvenue parmi nos sponsors";
    QString body = "Bonjour " + nom + ",\n\n"
                                      "Merci d'avoir rejoint nos sponsors.\n"
                                      "Cordialement.";

    if(smtp.sendMail(email, subject, body)) {
        QMessageBox::information(this, "Email", "Email envoyé avec succès !");
    } else {
        QMessageBox::warning(this, "Email", "Erreur lors de l'envoi du mail.");
    }

}

void MainWindow::loadSponsoring() {
    QSqlQuery query("SELECT * FROM SPONSORS"); // fetch all rows from SPONSORING

    // Clear the table first
    ui->affiche->clear();
    ui->affiche->setRowCount(0);
    ui->affiche->setColumnCount(6); // ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS

    // Set headers
    QStringList headers = {"ID", "Nom", "Email", "Date Début", "Date Fin", "Status"};
    ui->affiche->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);

        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DEBUT").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));

        row++;
    }

    // Make columns stretch to fill available space
    ui->affiche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::deleteSelectedSponsor() {
    // 1️⃣ Check if a row is selected
    int row = ui->affiche->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un sponsor à supprimer !");
        return;
    }

    // 2️⃣ Get the ID from the first column (ID_SPONS)
    QString id = ui->affiche->item(row, 0)->text();

    // 3️⃣ Ask for confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmer la suppression",
                                  "Voulez-vous vraiment supprimer ce sponsor ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    // 4️⃣ Execute DELETE query
    QSqlQuery query;
    query.prepare("DELETE FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor supprimé avec succès.");
        loadSponsoring(); // Refresh the table after deletion
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}
void MainWindow::updateSponsor()
{
    int id = ui->ID->text().toInt(); // ID cannot be changed
    QString nom = ui->Nom->text();
    QString email = ui->EM->text();
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();
    QString status = ui->STS->currentText();

    // Validate input (no empty fields, valid dates)
    if (nom.isEmpty() || email.isEmpty() || !dd.isValid() || !df.isValid() || status.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement !");
        return;
    }

    // Execute UPDATE query
    QSqlQuery query;
    query.prepare("UPDATE SPONSORS SET NOM_SPONS = :nom, EMAIL = :email, DATE_DEBUT = :dd, DATE_FIN = :df, STATUS = :status "
                  "WHERE ID_SPONS = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":dd", dd);
    query.bindValue(":df", df);
    query.bindValue(":status", status);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Sponsor mis à jour avec succès.");
        loadSponsoring(); // Refresh the table
        ui->ID->setDisabled(false); // Re-enable ID field after update
    } else {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    }
}
void MainWindow::searchSponsorById()
{
    QString searchId = ui->search1->text().trimmed(); // get text from QLineEdit

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

    // Clear table before showing search results
    ui->affiche->clear();
    ui->affiche->setRowCount(0);
    ui->affiche->setColumnCount(6);
    QStringList headers = {"ID", "Nom", "Email", "Date Début", "Date Fin", "Status"};
    ui->affiche->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DEBUT").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        row++;
    }

    ui->affiche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::on_pdfexport_clicked()
{
    // ✅ 1. Check DB connection
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "Erreur", "Base de données non connectée !");
        return;
    }

    // ✅ 2. Choose file
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty())
        return;

    // ✅ 3. Load data into model
    QSqlQueryModel model;
    model.setQuery("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS FROM SPONSORS");

    if (model.rowCount() == 0) {
        QMessageBox::information(this, "Info", "Aucune donnée trouvée dans la table SPONSORING.");
        return;
    }

    // ✅ 4. Build HTML from model
    QString html;
    html += "<html><head><style>"
            "body { font-family: Arial; margin: 20px; }"
            "table { width: 100%; border-collapse: collapse; }"
            "th, td { border: 1px solid #000; padding: 8px; text-align: center; }"
            "th { background-color: #f2f2f2; }"
            "</style></head><body>";
    html += "<h2 align='center'>Liste des Sponsors</h2><br>";
    html += "<table><tr>";

    // ✅ Table headers
    for (int col = 0; col < model.columnCount(); col++) {
        html += "<th>" + model.headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // ✅ Table data
    for (int row = 0; row < model.rowCount(); row++) {
        html += "<tr>";
        for (int col = 0; col < model.columnCount(); col++) {
            html += "<td>" + model.data(model.index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table></body></html>";

    // ✅ 5. Export to PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this, "Succès ✅", "Le fichier PDF a été généré avec succès !");
}
void MainWindow::on_sort_clicked()
{
    // ✅ Prepare SQL query (sorted by ID_SPONS ascending)
    QSqlQuery query;
    if (!query.exec("SELECT ID_SPONS, NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS FROM SPONSORS ORDER BY ID_SPONS ASC")) {
        QMessageBox::critical(this, "Erreur SQL", "Échec du tri : " + query.lastError().text());
        return;
    }

    // ✅ Clear old data from table
    ui->affiche->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->affiche->insertRow(row);
        ui->affiche->setItem(row, 0, new QTableWidgetItem(query.value("ID_SPONS").toString()));
        ui->affiche->setItem(row, 1, new QTableWidgetItem(query.value("NOM_SPONS").toString()));
        ui->affiche->setItem(row, 2, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->affiche->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DEBUT").toString()));
        ui->affiche->setItem(row, 4, new QTableWidgetItem(query.value("DATE_FIN").toString()));
        ui->affiche->setItem(row, 5, new QTableWidgetItem(query.value("STATUS").toString()));
        row++;
    }

    QMessageBox::information(this, "Tri effectué", "Les sponsors ont été triés par ID_SPONS (ordre croissant).");
}
void MainWindow::clearFields()
{
    ui->ID->clear();
    ui->Nom->clear();
    ui->EM->clear();
    ui->dd->setDate(QDate::currentDate());
    ui->df->setDate(QDate::currentDate());
    ui->STS->setCurrentIndex(-1); // deselects combo box
    ui->ID->setDisabled(false);   // re-enable ID if it was locked
}
void MainWindow::onSponsorSelected(const QModelIndex &index)
{
    // Get the model from the table inside the QTabWidget
    QAbstractItemModel *model = ui->affiche->model();
    int row = index.row();

    // Extract the sponsor ID from the first column (adjust column index if needed)
    int id = model->data(model->index(row, 0)).toInt();

    // Query the database for that sponsor
    QSqlQuery query;
    query.prepare("SELECT NOM_SPONS, EMAIL, DATE_DEBUT, DATE_FIN, STATUS "
                  "FROM SPONSORS WHERE ID_SPONS = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        ui->ID->setText(QString::number(id));
        ui->Nom->setText(query.value(0).toString());
        ui->EM->setText(query.value(1).toString());
        ui->dd->setDate(QDate::fromString(query.value(2).toString(), "yyyy-MM-dd"));
        ui->df->setDate(QDate::fromString(query.value(3).toString(), "yyyy-MM-dd"));
        ui->STS->setCurrentText(query.value(4).toString());
        ui->ID->setDisabled(true);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les données du sponsor sélectionné.");
    }
}
QMap<QString,int> MainWindow::getStatusFromTable()
{
    QMap<QString,int> stats;
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

void MainWindow::drawPieChart(const QMap<QString,int>& stats)
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

    // -----------------------------
    // 🎨 ONLY TWO COLORS
    // -----------------------------
    const QVector<QColor> palette = {
        QColor(52, 152, 219),   // Blue
        QColor(231, 76, 60)     // Red
    };

    // map to remember which status has which color
    QMap<QString, QColor> colorMap;

    int i = 0;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString key = it.key();
        int spanAngle = static_cast<int>(360.0 * it.value() / total * 16);

        // alternate color: blue, red, blue...
        QColor color = palette[i % 2];
        colorMap.insert(key, color);

        painter.setBrush(color);
        painter.setPen(Qt::black);
        painter.drawPie(rect, startAngle, spanAngle);

        startAngle += spanAngle;
        i++;
    }

    // -----------------------------
    // Display dialog with pie chart + legend
    // -----------------------------
    QDialog dlg(this);
    dlg.setWindowTitle("Statistiques - Camembert");
    QVBoxLayout *lay = new QVBoxLayout(&dlg);

    QLabel *lbl = new QLabel(&dlg);
    lbl->setPixmap(pix);

    QWidget *legendWidget = new QWidget(&dlg);
    QVBoxLayout *legendLayout = new QVBoxLayout(legendWidget);
    legendLayout->setContentsMargins(6,6,6,6);
    legendLayout->setSpacing(8);

    int idx = 0;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString name = it.key();
        int count = it.value();
        double pct = total > 0 ? (100.0 * count / total) : 0.0;

        QLabel *row = new QLabel(legendWidget);
        row->setText(QString("%1 — %2 (%3%)")
                         .arg(name).arg(count).arg(QString::number(pct, 'f', 1)));
        row->setMargin(4);

        QLabel *swatch = new QLabel(legendWidget);
        swatch->setFixedSize(18,18);
        swatch->setStyleSheet(
            QString("background-color: %1; border: 1px solid #000;")
                .arg(colorMap.value(name).name())
            );

        QHBoxLayout *h = new QHBoxLayout;
        h->addWidget(swatch);
        h->addWidget(row);
        h->addStretch();
        legendLayout->addLayout(h);

        idx++;
    }

    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(lbl);
    container->addWidget(legendWidget);
    lay->addLayout(container);

    dlg.exec();
}

void MainWindow::on_pushButton_stat_clicked()
{
    QMap<QString,int> stats = getStatusFromTable();
    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible.");
        return;
    }

    // Show pie chart
    drawPieChart(stats);

    // Build textual summary
    int total = 0; for (auto v : stats) total += v;
    QString summary;
    summary += QString("Total sponsors: %1\n\n").arg(total);
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        double pct = (total>0) ? (100.0 * it.value() / total) : 0.0;
        summary += QString("%1: %2 (%3%)\n").arg(it.key()).arg(QString::number(it.value())).arg(QString::number(pct, 'f', 1));
    }

    // Show text and offer export
    QMessageBox::information(this, "Statistiques (texte)", summary);
    QString out = QFileDialog::getSaveFileName(this, "Enregistrer statistiques", QDir::homePath(), "Fichiers texte (*.txt)");
    if (!out.isEmpty()) {
        QFile f(out);
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream ts(&f);
            ts << "Statistiques Sponsors\n" << "====================\n\n" << summary;
            f.close();
            QMessageBox::information(this, "Export", "Statistiques sauvegardées en texte.");
        } else {
            QMessageBox::warning(this, "Export", "Impossible d'ouvrir le fichier pour écriture.");
        }
    }
}
