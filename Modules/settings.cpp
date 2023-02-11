#include "Modules/settings.h"

void Settings::showDis(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    bool temp = true;    // false=nicht anzeigen | true=anzeigen
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("disclaimer").isNull()){
        qCritical() << "Es konnte 'disclaimer' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("disclaimer", true);          // ob am Anfang der Disclaimer angezeigt werden soll

        settings.sync();
    }

    temp = settings.value("disclaimer").toBool();

    if(!temp){
        return;
    }

    QMessageBox disBox;
    QString title = QObject::tr("Disclaimer");
    QString text = QObject::tr("Die Nutzung erfolgt auf eigene Gefahr des Anwenders. Der Entwickler übernimmt keinerlei Garantie oder Gewährleistung "
                               "für die Eignung des Programms sowie für dessen vollständige Funktionsfähigkeit, insbesondere die Richtigkeit der Berechnungen. "
                               "Der Entwickler haftet nicht für störungs- oder fehlerfreien Einsatz des Programms. Der Anwender trägt allein das Risiko. Jegliche "
                               "Haftung des Entwicklers für Schäden, Nachteile und Anwendungen aller Art, insbesondere auch für Vermögensschäden, Datenverlust "
                               "o.ä., die dem Anwender oder Dritten aus oder im Zusammenhang mit der Verwendung oder der Nichtanwendbarkeit der Programmes "
                               "entstehen sollten, ist ausgeschlossen. Sind sie damit einverstanden?");
    if(macos) {
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

    if(dis == QMessageBox::No){
        exit(0);
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("maxRpmFr").isNull()){
        qCritical() << "Es konnte 'maxRpmFr' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("maxRpmFr", 24000);

        settings.sync();
    }

    rpm = settings.value("maxRpmFr").toInt();

    if(rpm <= 0){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Die maximale Drehzahl in der Datei 'config.ini' hat keinen gültigen Wert!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("maxRpmDr").isNull()){
        qCritical() << "Es konnte 'maxRpmDr' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("maxRpmDr", 5000);

        settings.sync();
    }

    rpm = settings.value("maxRpmDr").toInt();

    if(rpm <= 0){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Die maximale Drehzahl in der Datei 'config.ini' hat keinen gültigen Wert!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("maxPcFr").isNull()){
        qCritical() << "Es konnte 'maxPcFr' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("maxPcFr", 2.2);
        settings.sync();
    }

    pc = settings.value("maxPcFr").toDouble();

    if(pc <= 0){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Die maximale fräs Spindelleistung in der Datei 'config.ini' hat keinen gültigen Wert!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("maxPcDr").isNull()){
        qCritical() << "Es konnte 'maxPcDr' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("maxPcDr", 2.2);

        settings.sync();
    }

    pc = settings.value("maxPcDr").toDouble();

    if(pc <= 0){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Die maximale dreh Spindelleistung in der Datei 'config.ini' hat keinen gültigen Wert!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("con").isNull()){
        qCritical() << "Es konnte 'con' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("con", 1);

        settings.sync();
    }

    con = settings.value("con").toInt();

    if((con != 0) && (con != 1) && (con != 2)){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Es konnte keine gültige Abfrage für die standard Bedingung in der 'config.ini' Datei gefunden werden!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("cutMat").isNull()){
        qCritical() << "Es konnte 'cutMat' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("cutMat", 1);

        settings.sync();
    }

    cutMat = settings.value("cutMat").toInt();

    if((cutMat != 0) && (cutMat != 1) && (cutMat != 2)){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Es konnte keine gültige Abfrage für den standard Schneidstoff in der 'config.ini' Datei gefunden werden!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("spiWi").isNull()){
        qCritical() << "Es konnte 'spiWi' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("spiWi", 0);

        settings.sync();
    }

    spiWi = settings.value("spiWi").toInt();

    if((spiWi != 0) && (spiWi != 1) && (spiWi != 2)){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Es konnte keine gültige Abfrage für den standard Spitzenwinkel in der 'config.ini' Datei gefunden werden!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("cooling").isNull()){
        qCritical() << "Es konnte 'cooling' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("cooling", 0);

        settings.sync();
    }

    cooling = settings.value("cooling").toInt();

    if((cooling != 0) && (cooling != 1) && (cooling != 2)){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Es konnte keine gültige Abfrage für die standard Kühlung in der 'config.ini' Datei gefunden werden!");
        if(macos) {
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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    if(file.exists()) {
        temp = true;
        return temp;
    }else {
        QMessageBox msg;
        QString title = QObject::tr("Fehler");
        QString text = QObject::tr("Die Datei 'Daten.xlsx' wurde nicht gefunden. Soll sie erstellt werden?");
        if(macos) {
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

void Settings::write(int dis, int maxRpmFr, double maxKw, int con, int cutMat, int spiWi, int cooling, int maxRpmDr, double maxKwDr, int index, bool update){
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
    settings.setValue("autoUpdate", update);

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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QFile file = (path + "/config.ini");
    if(file.exists()){
        temp = true;
        return temp;
    }else{
        QMessageBox msg;
        QString title = QObject::tr("Fehler");
        QString text = QObject::tr("Die Datei 'config.ini' wurde nicht gefunden. Soll sie erstellt werden?");
        if(macos) {
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
    settings.setValue("disclaimer", true);          // ob am Anfang der Disclaimer angezeigt werden soll
    settings.setValue("maxRpmFr", 24000);           // die max Drehzahl der Fraes Spindel
    settings.setValue("maxPcFr", 2.2);              // die max leistung der Fraes Spindel
    settings.setValue("con", 1);                    // die Zerspanbedingung                     (0=instabiel|1=normal|2=stabil)
    settings.setValue("cutMat", 1);                 // der standard Schneidstoff von Bohrern    (0=HSS|1=VHM|2=Keramik)
    settings.setValue("spiWi", 0);                  // der Spitzenwinkel von Bohrern            (0=188G|1=130G|2=140G)
    settings.setValue("cooling", 0);                // die Kuehlungsart                         (0=trocken|1=KSS|2=Oel)
    settings.setValue("maxRpmDr", 5000);            // die max Drehzahl der Dreh Spindel
    settings.setValue("maxPcDr", 2.2);              // die max leistung der Dreh Spindel
    settings.setValue("lastTab", 0);                // der letzte index vom mainTab
    settings.setValue("autoUpdate", true);          // ob beim Programmstart nach updates gesucht werden soll
    settings.setValue("lastCloseOnUpdate", false);  // interne variable um nach einem Update alles aufzuraeumen

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
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);
    index = settings.value("lastTab").toInt();

    if(index == -1){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Es konnte keine gültige Abfrage für den letzen Index in der Datei 'config.ini' gefunden werden!");
        if(macos) {
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

bool Settings::autoUpdate(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini";
    int out = true;
    bool macos;

    if(QSysInfo::productType() == "macos") {
        macos = true;
    }else {
        macos = false;
    }

    QSettings settings(path, QSettings::IniFormat);

    if(settings.value("autoUpdate").isNull()){
        qCritical() << "Es konnte 'autoUpdate' in der 'config.ini' nicht gefunden werden und wird neu erstellt!";
        settings.setValue("autoUpdate", true);

        settings.sync();
    }

    out = settings.value("autoUpdate").toBool();

    if(!settings.value("autoUpdate").isValid()){
        QMessageBox msg;
        QString title = QObject::tr("Kritischer Fehler");
        QString text = QObject::tr("Es konnte keine gültige Abfrage für die autoUpdate Funktion in der Datei 'config.ini' gefunden werden!");
        if(macos) {
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

    return out;
}

void Settings::deleteAll(){
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/config.ini";

    qInfo() << "Die 'config.ini' wird gelöscht!";
    QFile::remove(QString::fromStdString(file));

    return;
}

void Settings::lastCloseOnUpdate(){
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini", QSettings::IniFormat);
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/temp");

    if(!settings.value("lastCloseOnUpdate").isNull() && settings.value("lastCloseOnUpdate").isValid() && settings.value("lastCloseOnUpdate").toBool() && dir.exists()){
        qInfo() << "Der 'temp' Ordner wird nach dem Update gelöscht!";
        dir.removeRecursively();
    }

    settings.setValue("lastCloseOnUpdate", false);

    return;
}

void Settings::test(){
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    QSettings settings(path + "/test.ini", QSettings::IniFormat);

    settings.setValue("test1/test2", 100);

    return;
}
