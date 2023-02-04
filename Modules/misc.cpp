#include "misc.h"

namespace{
QString nVer = QCoreApplication::applicationVersion();
QString downloadUrl = "";
}

void Misc::waitForResponseVer(){
    QEventLoop loop;
    QAbstractSocket::connect(this, &Misc::responseReceivedVer, &loop, &QEventLoop::quit);
    loop.exec();
}

void Misc::waitForResponseUrl(){
    QEventLoop loop;
    QAbstractSocket::connect(this, &Misc::responseReceivedUrl, &loop, &QEventLoop::quit);
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
    request.setRawHeader("User-Agent", "application/vnd.github+json");
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
        emit misc.responseReceivedVer();
    });

    misc.waitForResponseVer();

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
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp");
    QString type = QSysInfo::productType();
    QString filter;
    QString DateiName;

    qDebug() << "Update wird gestartet";

    if(type == "windows"){
        filter = "windows-x64-installer";
        DateiName = "installer.exe";
        qDebug() << "Update wird für" << QSysInfo::prettyProductName() << "ausgeführt!";

    }else if(type == "macos"){
        //filter = "windows-installer";
        //DateiName = "installer.exe";
        qDebug() << "Update wird für" << QSysInfo::prettyProductName() << "ausgeführt!";
        qDebug() << "Das automatische Update wird im moment nur unter Windows unterstützt!";
        return;

    }else if(type == ""){
        //filter = "windows-installer";
        //DateiName = "installer.exe";
        qDebug() << "Update wird für" << QSysInfo::prettyProductName() << "ausgeführt!";
        qDebug() << "Das automatische Update wird im moment nur unter Windows unterstützt!";
        return;

    }else{
        qDebug() << "Bestimmung des Systems Fehlgeschlagen";
        qDebug() << "Der Systemname ist:" << QSysInfo::productType();
        return;
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/EinRainerZufall/SpaeneRechner/releases/latest"));
    request.setRawHeader("User-Agent", "application/vnd.github+json");
    QNetworkReply *reply = manager->get(request);

    Misc misc;
    QObject context;
    connect(reply, &QNetworkReply::finished, &context, [reply, &misc, filter]() {
        if (reply->error()){
            qDebug() << "Fehler beim abrufen der Download url, mit Fehler:" << reply->errorString();
        }else{
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonArray assets = jsonResponse.object()["assets"].toArray();
            for (const auto &asset : assets) {
                downloadUrl = asset.toObject()["browser_download_url"].toString();
                if(downloadUrl.contains(filter)) {
                    qDebug() << "Download url:" << downloadUrl;
                }
            }
        }
        emit misc.responseReceivedUrl();
    });

    misc.waitForResponseUrl();

    if(downloadUrl.isEmpty()){
        qDebug() << "Es ist ein Fehler beim Abrufen der url aufgetreten!";
        return;
    }

    if(dir.exists()){
        qDebug() << "Der 'temp' Ordner ist vorhanden und wird gelöscht!";
        dir.removeRecursively();
    }
    dir.mkdir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp");

    reply = manager->get(QNetworkRequest(QUrl(downloadUrl)));
    QEventLoop download;
    connect(reply, &QNetworkReply::finished, &download, &QEventLoop::quit);
    qDebug() << "Download der Datei gestartet...";
    download.exec();
    if(reply->error()){
        qDebug() << "Download der Datei fehlgeschlagen!";
        qDebug() << reply->errorString();
    }else{
        QFile file(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp/"+DateiName);
        file.open(QIODevice::WriteOnly);
        file.write(reply->readAll());
        file.close();
        reply->deleteLater();
    }

    qDebug() << "Download der Datei erfolgreich!";

    if(type == "windows"){
        QSettings settings(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini", QSettings::IniFormat);

        QFile autoUpdater(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp/"+"autoUpdater.bat");
        if(autoUpdater.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&autoUpdater);
            stream << "@echo off\ntaskkill /im SpaeneRechner.exe\nstart " << QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp/"+DateiName;
            autoUpdater.close();
            qDebug() << "Auto Update script für" << QSysInfo::prettyProductName() << "erstellt!";
        }

        qDebug() << "Automatische installation gestartet!";
        QProcess autoStart;
        settings.setValue("lastCloseOnUpdate", true);
        autoStart.start("cmd.exe", QStringList() << "/c" << QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp/"+"autoUpdater.bat");
        autoStart.waitForFinished();
    }
    return;
}

int Misc::MSGbox(QString title, QString text, int type, int buttonStyle, QString error){
    /*
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
     * error -> den genauen Fehler der uebergeben werden soll
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

    if(!error.isEmpty()){
        msg.setDetailedText(error);
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
