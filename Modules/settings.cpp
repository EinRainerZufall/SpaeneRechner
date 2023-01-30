#include "Modules/settings.h"

namespace  {

#ifdef QT_DEBUG
const std::string settingsName = "Test.xlsx";
#else
const std::string settingsName = "Daten.xlsx";
#endif
}

/*
 * INIcheck     <- neu, pruefen ob die .ini existiert
 * create       <- neu, jetzt hier und nicht mehr in createDatabase
*/

void Settings::showDis(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int temp = true;    // 0=false(nicht anzeigen) | 1=true(anzeigen) | -1=error
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("disclaimer").toBool() == true){
            temp = 1;
    }else if(settings.value("disclaimer").toBool() == false){
            temp = 0;
    }else{
            temp = -1;
        }

    if(temp == 0){
            return;
    }else if(temp == 1){
            QMessageBox disBox;
            QString title = QObject::tr("Disclaimer");
            QString text = QObject::tr("Die Nutzung erfolgt auf eigene Gefahr des Anwenders. Der Entwickler übernimmt keinerlei Garantie oder Gewährleistung "
                                       "für die Eignung des Programms sowie für dessen vollständige Funktionsfähigkeit, insbesondere die Richtigkeit der Berechnungen. "
                                       "Der Entwickler haftet nicht für störungs- oder fehlerfreien Einsatz des Programms. Der Anwender trägt allein das Risiko. Jegliche "
                                       "Haftung des Entwicklers für Schäden, Nachteile und Anwendungen aller Art, insbesondere auch für Vermögensschäden, Datenverlust "
                                       "o.ä., die dem Anwender oder Dritten aus oder im Zusammenhang mit der Verwendung oder der Nichtanwendbarkeit der Programmes "
                                       "entstehen sollten, ist ausgeschlossen. Sind sie damit einverstanden?");
            if(OSX) {
                disBox.setInformativeText(text);
                disBox.setText(title);
            }else {
                disBox.setText(text);
                disBox.setWindowTitle(title);
            }
            disBox.setIcon(QMessageBox::Information);
            disBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            disBox.setDefaultButton(QMessageBox::Yes);
            disBox.setEscapeButton(QMessageBox::No);
            int dis = disBox.exec();

            switch (dis) {
            case QMessageBox::Yes:
                return;
            case QMessageBox::No:
                exit(0);
            }
    }else{
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für den Disclaimer in der 'config.ini' Datei gefunden werden!");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return;
};

bool Settings::readDis(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    bool temp = true;

    QSettings settings(path, QSettings::IniFormat);

    temp = settings.value("disclaimer").toBool();

    return temp;
}

int Settings::maxRpmFr(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int rpm = 0;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    rpm = settings.value("maxRpmFr").toInt();

    if(rpm <= 0){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine maximale Drehzahl in der Datei 'config.ini' gefunden werden!");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return rpm;
}

int Settings::maxRpmDr(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int rpm = 0;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    rpm = settings.value("maxRpmDr").toInt();

    if(rpm <= 0){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine maximale Drehzahl in der Datei 'config.ini' gefunden werden!");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return rpm;
}

double Settings::maxKw(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    double pc = 0;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    pc = settings.value("maxPcFr").toDouble();

    if(pc <= 0){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für die Spindelleistung der Fräsmaschine in der Datei 'config.ini' gefunden werden!");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return pc;
}

double Settings::maxKwDr(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    double pc = 0;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    pc = settings.value("maxPcDr").toDouble();

    if(pc <= 0){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für die Spindelleistung der Drehmaschine in der Datei 'config.ini' gefunden werden!");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return pc;
}

int Settings::condition(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int con = 3;    // 3=error
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    con = settings.value("con").toInt();

    if(con == 3){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für die standard Bedingung in der 'config.ini' Datei gefunden werden!");
            if(OSX) {
                msg.setInformativeText(text);
                msg.setText(title);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return con;
}

int Settings::cutMat(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int cutMat = 3;    // 3=error
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    cutMat = settings.value("cutMat").toInt();

    if(cutMat == 3){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für den standard Schneidstoff in der 'config.ini' Datei gefunden werden!");
            if(OSX) {
                msg.setInformativeText(text);
                msg.setText(title);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return cutMat;
}

int Settings::angleDrill(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int spiWi = 3;    // 3=error
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    spiWi = settings.value("spiWi").toInt();

    if(spiWi == 3){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für den standard Spitzenwinkel in der 'config.ini' Datei gefunden werden!");
            if(OSX) {
                msg.setInformativeText(text);
                msg.setText(title);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return spiWi;
}

int Settings::cooling(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int cooling = 3;    // 3=error
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    cooling = settings.value("cooling").toInt();

    if(cooling == 3){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für die standard Kühlung in der 'config.ini' Datei gefunden werden!");
            if(OSX) {
                msg.setInformativeText(text);
                msg.setText(title);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return cooling;
}

bool Settings::xlsxCheck(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QFile file = (path + "/Daten.xlsx");
    bool temp = false;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    if(file.exists()) {
            temp = true;
            return temp;
    }else {
            QMessageBox msg;
            QString title = QObject::tr("Fehler");
            QString text = QObject::tr("Die Datei 'Daten.xlsx' wurde nicht gefunden. Soll sie erstellt werden?");
            if(OSX) {
                msg.setInformativeText(text);
                msg.setText(title);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setDefaultButton(QMessageBox::Yes);
            msg.setEscapeButton(QMessageBox::No);
            int x = msg.exec();

            switch (x) {
            case QMessageBox::Yes:
                return temp;
            case QMessageBox::No:
                exit(0);
            }
        }

    return temp;
}

void Settings::write(int dis, int maxRpmFr, double maxKw, int con, int cutMat, int spiWi, int cooling, int maxRpmDr, double maxKwDr, int index){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    QString tempDis;

    if(dis == 0){
            tempDis = "true";
    }else{
            tempDis = "false";
        }

    QSettings settings(path, QSettings::IniFormat);
    settings.setValue("disclaimer", tempDis);
    settings.setValue("maxRpmFr", maxRpmFr);
    settings.setValue("maxPcFr", maxKw);
    settings.setValue("con", con);
    settings.setValue("cutMat", cutMat);
    settings.setValue("spiWi", spiWi);
    settings.setValue("cooling", cooling);
    settings.setValue("maxRpmDr", maxRpmDr);
    settings.setValue("maxPcDr", maxKwDr);
    settings.setValue("lastTab", index);

    settings.sync();

    if(settings.status() == QSettings().NoError){
        return;
    }else{
        return;
    }
}

bool Settings::INIcheck(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    bool temp = false;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QFile file = (path + "/config.ini");
    if(file.exists()){
            temp = true;
            return temp;
    }else{
            QMessageBox msg;
            QString title = QObject::tr("Fehler");
            QString text = QObject::tr("Die Datei 'config.ini' wurde nicht gefunden. Soll sie erstellt werden?");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setDefaultButton(QMessageBox::Yes);
            msg.setEscapeButton(QMessageBox::No);
            int x = msg.exec();

            switch (x) {
            case QMessageBox::Yes:
                return temp;
            case QMessageBox::No:
                exit(2);
            }
        }

    return temp;
}

void Settings::create(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";

    QSettings settings(path, QSettings::IniFormat);
    settings.setValue("disclaimer", true);  // ob am Anfang der Disclaimer angezeigt werden soll
    settings.setValue("maxRpmFr", 24000);   // die max Drehzahl der Fraes Spindel
    settings.setValue("maxPcFr", 2.2);      // die max leistung der Fraes Spindel
    settings.setValue("con", 1);            // die Zerspanbedingung                     (0=instabiel|1=normal|2=stabil)
    settings.setValue("cutMat", 1);         // der standard Schneidstoff von Bohrern    (0=HSS|1=VHM|2=Keramik)
    settings.setValue("spiWi", 0);          // der Spitzenwinkel von Bohrern            (0=188G|1=130G|2=140G)
    settings.setValue("cooling", 0);        // die Kuehlungsart                         (0=trocken|1=KSS|2=Oel)
    settings.setValue("maxRpmDr", 5000);    // die max Drehzahl der Dreh Spindel
    settings.setValue("maxPcDr", 2.2);      // die max leistung der Dreh Spindel
    settings.setValue("lastTab", 0);        // der letzte index vom mainTab

    settings.sync();

    if(settings.status() == QSettings().NoError){
        return;
    }else{
        return;
    }
}

int Settings::readIndex(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int index = -1;
    bool OSX;

    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QSettings settings(path, QSettings::IniFormat);
    index = settings.value("lastTab").toInt();

    if(index == -1){
            QMessageBox msg;
            QString title = QObject::tr("Kritischer Fehler");
            QString text = QObject::tr("Es konnte keine gültige Abfrage für den letzen Index in der Datei 'config.ini' gefunden werden!");
            if(OSX) {
                msg.setText(title);
                msg.setInformativeText(text);
            }else {
                msg.setText(text);
                msg.setWindowTitle(title);
            }
            msg.setIcon(QMessageBox::Critical);
            msg.setStandardButtons(QMessageBox::Close);
            msg.setDefaultButton(QMessageBox::Close);
            msg.exec();
            exit(2);
        }

    return index;
}

bool Settings::updateCheck(){
    bool OSX;
    int updateAvailable;
    QString aVer = QCoreApplication::applicationVersion();
    QString nVer = "0.4.6";

    //https://api.github.com/repos/EinRainerZufall/SpaeneRechner/releases/latest



    if(QSysInfo::productType() == "osx") {
            OSX = true;
    }else {
            OSX = false;
        }

    QVersionNumber av = QVersionNumber::fromString(aVer);
    QVersionNumber nv = QVersionNumber::fromString(nVer);

    updateAvailable = QVersionNumber::compare(nv,av);

    if(updateAvailable >= 1){
            QMessageBox msg;
            QString title = QObject::tr("Update verfügbar");
            QString text = QObject::tr("Es gibt eine neue Version vom SpäneRechner!\nAktuell installiert V%0, verfügbar ist V%1.\nSoll das Update durchgeführt werden?").arg(aVer, nVer);
            if(OSX) {
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
                return false;;
            }
        }

    return false;
}

void Settings::UPDATE(){
        return;
    }

void Settings::test(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

        QSettings settings(path + "/test.ini", QSettings::IniFormat);

        settings.setValue("test1/test2", 100);

        return;
    }
