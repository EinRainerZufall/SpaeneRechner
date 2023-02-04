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
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>
#include <QProcess>
#include <QSettings>

class Misc: public QObject{
    Q_OBJECT
public:
    static bool updateCheck();
    static void UPDATE();
    static int MSGbox(QString title, QString text, int type, int buttonStyle, QString error = "");
    void waitForResponseVer();
    void waitForResponseUrl();
signals:
    void responseReceivedVer();
    void responseReceivedUrl();
};

#endif // MISC_H
