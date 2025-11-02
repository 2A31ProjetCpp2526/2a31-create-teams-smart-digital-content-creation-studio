#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load Poppins font
    int fontId = QFontDatabase::addApplicationFont(":/resources/fonts/Poppins-Light.ttf");
    if (fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            QString fontFamily = fontFamilies.at(0);
            QFont font(fontFamily, 11, QFont::Light);
            font.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);
            a.setFont(font);
            qDebug() << "Poppins font loaded successfully:" << fontFamily;
        }
    } else {
        qWarning() << "Failed to load Poppins font. Using system default.";
        QFont fallbackFont("Segoe UI", 11, QFont::Light);
        fallbackFont.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);
        a.setFont(fallbackFont);
    }

    // Load and apply global stylesheet
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromLatin1(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        qDebug() << "Global stylesheet loaded successfully";
    } else {
        qWarning() << "Failed to load global stylesheet";
    }

    MainWindow w;
    w.setWindowTitle("Amine Templar");
    w.setMinimumSize(1000, 700);

    // Database connection
    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
        w.show();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
        // Optional: exit app if connection fails
        return -1;
    }

    return a.exec();
}
