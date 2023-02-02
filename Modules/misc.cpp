#include "misc.h"

namespace{
QString nVer = QCoreApplication::applicationVersion();
}

void Misc::waitForResponse(){
    QEventLoop loop;
    QAbstractSocket::connect(this, &Misc::responseReceived, &loop, &QEventLoop::quit);
    loop.exec();
}

bool Misc::updateCheck(){
    bool macos;
    int updateAvailable;
    QString aVer = QCoreApplication::applicationVersion();

    qDebug() << "Update wird abgerufen...";
    qDebug() << "Aktuell installiert ist:" << aVer;

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/EinRainerZufall/SpaeneRechner/releases/latest"));
    QNetworkReply *reply = manager->get(request);

    Misc misc;
    QObject context;
    QObject::connect(reply, &QNetworkReply::finished, &context, [reply, &misc](){
        if (reply->error()){
            qDebug() << "Fehler beim abrufen des Versionsnummer, mit Fehler:" << reply->errorString();
        }else{
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = jsonResponse.object();
            nVer = jsonObject["tag_name"].toString();
        }
        reply->deleteLater();;
        emit misc.responseReceived();
    });

    misc.waitForResponse();

    if(nVer.at(0).digitValue()){
        nVer.remove(0,1);
        qDebug() << "Neuste Version ist:" << nVer;
    }else{
        qDebug() << "Die Version: " << nVer << " hat ein ungültiges Format!";
    }

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QVersionNumber av = QVersionNumber::fromString(aVer);
    QVersionNumber nv = QVersionNumber::fromString(nVer);

    updateAvailable = QVersionNumber::compare(nv,av);

    if(updateAvailable >= 1){
        QMessageBox msg;
        QString title = QObject::tr("Update verfügbar");
        QString text = QObject::tr("Es gibt eine neue Version vom SpäneRechner!\nAktuell installiert V%0, verfügbar ist V%1.\nSoll das Update durchgeführt werden?").arg(aVer, nVer);
        if(macos) {
            msg.setInformativeText(text);
            msg.setText(title);
        }else {
            msg.setText(text);
            msg.setWindowTitle(title);
        }
        msg.setIcon(QMessageBox::Question);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::Yes);
        msg.setEscapeButton(QMessageBox::No);
        int x = msg.exec();

        switch (x) {
        case QMessageBox::Yes:
            return true;
        case QMessageBox::No:
            return false;
        }
    }

    return false;
}

void Misc::UPDATE(){
    QString type;
    QString filter;

    type = QSysInfo::productType();

    if(type.isEmpty())

    return;
}

int Misc::MSGbox(QString title, QString text, int error, int type, int buttonStyle){
    /*
     * error -> den Fehlercode der uebergeben werden soll, wenn kein Fehlercode uebergeben werden soll dann -1
     *
     * type -> welche Art von MessageBox es sein soll   - 1 = Frage
     *                                                  - 2 = Info
     *                                                  - 3 = Warnung
     *                                                  - 4 = Criticat error
     *                                                  - sonst ohne Bild
     *
     * buttonStyle  - 1 = ok Button
     *              - 2 = Ja und Nein Button
     *
     *
     * gibt den INT Wert des Button zurueck
    */

    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QMessageBox msg;
    if(macos){
        msg.setInformativeText(text);
        msg.setText(title);
    }else {
        msg.setText(text);
        msg.setWindowTitle(title);
    }

    if(error > 0){
        msg.setInformativeText(QObject::tr("Fehlercode: ") + QString::number(error));
    }

    switch(type){
    case 1:
        msg.setIcon(QMessageBox::Question);
        break;
    case 2:
        msg.setIcon(QMessageBox::Information);
        break;
    case 3:
        msg.setIcon(QMessageBox::Warning);
        break;
    case 4:
        msg.setIcon(QMessageBox::Critical);
        break;
    default:
        msg.setIcon(QMessageBox::NoIcon);
        break;
    }

    switch(buttonStyle){
    case 1:
        msg.setStandardButtons(QMessageBox::Ok);
        break;
    case 2:
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::Yes);
        msg.setEscapeButton(QMessageBox::No);
        break;
    default:
        msg.setStandardButtons(QMessageBox::Ok);
        break;
    }

    int x = msg.exec();

    return x;
}
