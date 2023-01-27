#include "Modules/module.h"

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

class Settings {
public:
    static void showDis(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int temp = true;    // 0=false(nicht anzeigen) | 1=true(anzeigen) | 2=error
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(10,99) == "disclaimer"){
                if(lineOut.remove("disclaimer=") == "true"){
                    temp = 1;
                    break;
                }else if(lineOut == "false"){
                    temp = 0;
                    break;
                }else{
                    temp = 2;
                    // hier die Fehlermeldung einpflegen
                    break;
                }
            }
            line = in.readLine();
            lineOut = line;
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
    }

    static bool readDis(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        bool temp = true;

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(10,99) == "disclaimer"){
                if(lineOut.remove("disclaimer=") == "true"){
                    temp = true;
                    break;
                }else if(lineOut == "false"){
                    temp = false;
                    break;
                }else{
                    exit(2);
                    break;
                }
            }
            line = in.readLine();
            lineOut = line;
        }

        return temp;
    }

    static int maxRpmFr(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int rpm = 0;
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(8,99) == "maxRpmFr"){
                rpm = (lineOut.remove("maxRpmFr=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

        if(rpm == 0){
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

    static int maxRpmDr(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int rpm = 0;
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(8,99) == "maxRpmDr"){
                rpm = (lineOut.remove("maxRpmDr=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

        if(rpm == 0){
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

    static double maxKw(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        double pc = 0;
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(7,99) == "maxPcFr"){
                pc = (lineOut.remove("maxPcFr=")).toDouble();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

        if(pc == 0){
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

    static double maxKwDr(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        double pc = 0;
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(7,99) == "maxPcDr"){
                pc = (lineOut.remove("maxPcDr=")).toDouble();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

        if(pc == 0){
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

    static int condition(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int con = 3;    // 3=error
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(3,99) == "con"){
                con = (lineOut.remove("con=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

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

    static int cutMat(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int cutMat = 3;    // 3=error
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(6,99) == "cutMat"){
                cutMat = (lineOut.remove("cutMat=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

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

    static int angleDrill(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int spiWi = 3;    // 3=error
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(5,99) == "spiWi"){
                spiWi = (lineOut.remove("spiWi=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

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

    static int cooling(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int cooling = 3;    // 3=error
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(7,99) == "cooling"){
                cooling = (lineOut.remove("cooling=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

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

    static bool xlsxCheck(){
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

    static void write(int dis, int maxRpmFr, double maxKw, int con, int cutMat, int spiWi, int cooling, int maxRpmDr, double maxKwDr, int index){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        const QDir dir;
        QString tempDis;
        QString line;

        if(dis == 0){
            tempDis = "true";
        }else{
            tempDis = "false";
        }

        if (!dir.exists(path)){
            dir.mkpath(path);
        }

        file.open(QIODevice::WriteOnly);

        line = "disclaimer=" + tempDis + "\n";
        file.write(line.toUtf8());
        line = "maxRpmFr=" + QString::number(maxRpmFr) + "\n";
        file.write(line.toUtf8());
        line = "maxPcFr=" + QString::number(maxKw) + "\n";
        file.write(line.toUtf8());
        line = "con=" + QString::number(con) + "\n";
        file.write(line.toUtf8());
        line = "cutMat=" + QString::number(cutMat) + "\n";
        file.write(line.toUtf8());
        line = "spiWi=" + QString::number(spiWi) + "\n";
        file.write(line.toUtf8());
        line = "cooling=" + QString::number(cooling) + "\n";
        file.write(line.toUtf8());
        line = "maxRpmDr=" + QString::number(maxRpmDr) + "\n";
        file.write(line.toUtf8());
        line = "maxPcDr=" + QString::number(maxKwDr) + "\n";
        file.write(line.toUtf8());
        line = "lastTab=" + QString::number(index) + "\n";
        file.write(line.toUtf8());

        file.close();

        return;
    }

    static bool INIcheck(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        bool temp = false;
        int OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = 1;
        }else {
            OSX = 0;
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
                temp = false;
                return temp;
            case QMessageBox::No:
                exit(2);
            }
        }

        return temp;
    }

    static void create(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        const QDir dir;
        const char data[] = "disclaimer=true\n" // ob am Anfang der Disclaimer angezeigt werden soll
                            "maxRpmFr=24000\n"  // die max Drehzahl der Fraes Spindel
                            "maxPcFr=2.2\n"     // die max leistung der Fraes Spindel
                            "con=1\n"           // die Zerspanbedingung                     (0=instabiel|1=normal|2=stabil)
                            "cutMat=1\n"        // der standard Schneidstoff von Bohrern    (0=HSS|1=VHM|2=Keramik)
                            "spiWi=0\n"         // der Spitzenwinkel von Bohrern            (0=188G|1=130G|2=140G)
                            "cooling=0\n"       // die Kuehlungsart                         (0=trocken|1=KSS|2=Oel)
                            "maxRpmDr=5000\n"   // die max Drehzahl der Dreh Spindel
                            "maxPcDr=2.2\n"     // die max leistung der Dreh Spindel
                            "lastTab=0\n";      // der letzte index vom mainTab

        if (!dir.exists(path)){
            dir.mkpath(path);
        }

        file.open(QIODevice::WriteOnly);

        file.write(data);

        return;
    }

    static int readIndex(){
        const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QFile file = (path + "/config.ini");
        int index = -1;
        bool OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = true;
        }else {
            OSX = false;
        }

        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);
        QString line = in.readLine();
        QString lineOut = line;
        while(!line.isNull()){
            if(line.remove(7,99) == "lastTab"){
                index = (lineOut.remove("lastTab=")).toInt();
                break;
            }
            line = in.readLine();
            lineOut = line;
        }

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

    static void test(){
        //const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);// + "/";
        const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";

        xlnt::workbook wb;

        wb.empty();

        wb.save(file);
        return;
    }
};
