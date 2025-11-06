#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QFile>
#include <QDebug>
#include <QDir>

// Custom message handler to write debug output to file
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QFile logFile("debug_output.log");
    static bool opened = false;
    
    if (!opened) {
        logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        opened = true;
    }
    
    QString formattedMsg;
    switch (type) {
        case QtDebugMsg:
            formattedMsg = QString("[DEBUG] %1\n").arg(msg);
            break;
        case QtWarningMsg:
          //  formattedMsg = QString("[WARNING] %1\n").arg(msg);
            break;
        case QtCriticalMsg:
            formattedMsg = QString("[CRITICAL] %1\n").arg(msg);
            break;
        case QtFatalMsg:
            formattedMsg = QString("[FATAL] %1\n").arg(msg);
            break;
        default:
            formattedMsg = QString("%1\n").arg(msg);
    }
    
    if (logFile.isOpen()) {
        logFile.write(formattedMsg.toUtf8());
        logFile.flush();
    }
    
    // Also output to console (won't show in GUI but useful for debugging)
    fprintf(stderr, "%s", formattedMsg.toLocal8Bit().constData());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Install custom message handler to capture all qDebug/qCritical output
    qInstallMessageHandler(customMessageHandler);
    
    qDebug() << "Application started - logging to debug_output.log";
    
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
    w.show();
    
    return a.exec();
}
