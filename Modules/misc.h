#ifndef MISC_H
#define MISC_H

#include <QCoreApplication>
#include <QMessageBox>
#include <QSysInfo>
#include <QVersionNumber>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class Misc: public QObject{
    Q_OBJECT
public:
    static bool updateCheck();
    static void UPDATE();
    static int MSGbox(QString title, QString text, int error, int type, int buttonStyle);
    void waitForResponse();
signals:
    void responseReceived();
};

#endif // MISC_H
