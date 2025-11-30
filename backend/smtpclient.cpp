#include "smtpclient.h"
#include <QDebug>

SmtpClient::SmtpClient(const QString &user, const QString &pass)
    : username(user), password(pass) {}

bool SmtpClient::sendMail(const QString &to, const QString &subject, const QString &message)
{
    QSslSocket socket;
    socket.connectToHostEncrypted("smtp.gmail.com", 465);

    if (!socket.waitForConnected(5000)) {
        qDebug() << "Connection failed!";
        return false;
    }

    auto read = [&](QString code){
        socket.waitForReadyRead(5000);
        QByteArray resp = socket.readAll();
        qDebug() << "SERVER:" << resp;   // <--- DEBUG HERE
        return resp.startsWith(code.toUtf8());
    };

    auto write = [&](QString cmd){
        qDebug() << "CLIENT:" << cmd;    // <--- DEBUG
        socket.write(cmd.toUtf8() + "\r\n");
        socket.waitForBytesWritten(5000);
    };

    // ---- SMTP SEQUENCE ----
    if (!read("220")) return false;

    write("EHLO localhost");
    if (!read("250")) return false;

    write("AUTH LOGIN");
    if (!read("334")) return false;

    write(username.toUtf8().toBase64());
    if (!read("334")) return false;

    write(password.toUtf8().toBase64());
    if (!read("235")) return false;

    // MAIL FROM
    write("MAIL FROM:<" + username + ">");
    if (!read("250")) return false;

    // RCPT TO
    write("RCPT TO:<" + to + ">");
    if (!read("250")) return false;

    // DATA
    write("DATA");
    if (!read("354")) return false;

    // FULL HEADERS
    QString data =
        "From: <" + username + ">\r\n"
                               "To: <" + to + ">\r\n"
               "Subject: " + subject + "\r\n"
                    "\r\n" +
        message +
        "\r\n.";

    write(data);
    if (!read("250")) return false;

    write("QUIT");
    read("221");

    return true;
}
