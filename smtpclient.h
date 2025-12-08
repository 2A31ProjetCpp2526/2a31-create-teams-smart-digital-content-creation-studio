#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QSslSocket>

class SmtpClient : public QObject
{
    Q_OBJECT

public:
    SmtpClient(const QString &user, const QString &pass);
    bool sendMail(const QString &to, const QString &subject, const QString &message);

private:
    QString username;
    QString password;
};

#endif
