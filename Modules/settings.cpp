#include "Modules/module.h"

namespace  {
const std::filesystem::path settingsPath = std::filesystem::current_path() / "Daten.xlsx";
int maxRow = 50;

#ifdef QT_DEBUG
const std::string settingsName = "Test.xlsx";
#else
const std::string settingsName = "Daten.xlsx";
#endif
}
/*
 * xlsxCheck    <- muss noch neu werden
 * write        <- muss noch neu werden
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
                                       "Der Entwickler haftet nicht für störungs- oder fehlerfreien Einsatz des Programms. Der Anwender trägt das Risiko. Jegliche "
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für den Disclaimer in der 'config.ini' Datei gefunden werden!");
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für die Spindelleistung der Fräsmaschine in der Datei 'config.ini' gefunden werden!");
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für die Spindelleistung der Drehmaschine in der Datei 'config.ini' gefunden werden!");
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für die standart Bedingung in der 'config.ini' Datei gefunden werden!");
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für den standart Schneidstoff in der 'config.ini' Datei gefunden werden!");
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für den standart Spitzenwinkel in der 'config.ini' Datei gefunden werden!");
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
            QString text = QObject::tr("Es konnte keine gültige abfrage für die standart Kühlung in der 'config.ini' Datei gefunden werden!");
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
        bool temp = false;

        if(std::filesystem::exists(settingsPath)) {
            return temp;
        }else {
            QMessageBox box;
            box.setText(QObject::tr("Die Datei 'Daten.xlsx' wurde nicht gefunden soll sie erstellt werden?"));
            box.setWindowTitle(QObject::tr("Fehler"));
            box.setIcon(QMessageBox::Critical);
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setDefaultButton(QMessageBox::Yes);
            box.setEscapeButton(QMessageBox::No);
            int x = box.exec();

            switch (x) {
            case QMessageBox::Yes:
                temp = true;
                return temp;
            case QMessageBox::No:
                exit(0);
            }
        }

        return temp;
    }

    static void write(bool dis, int FrN, double FrPc, int bed, int cutMat, int BoWinkel, int cooling, int TurN, double TurPc){
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        //dis
        while (ws.cell(1, row).to_string() != "disclaimer") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        if(dis) {
            ws.cell(2, row).value("Nein");
        }else {
            ws.cell(2, row).value("Ja");
        }

        //FrN
        row = 2;
        while (ws.cell(1, row).to_string() != "maxRpmFr") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        ws.cell(2, row).value(FrN);

        //FrPc
        row = 2;
        while (ws.cell(1, row).to_string() != "maxPc") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        ws.cell(2, row).value(FrPc);

        //bed
        row = 2;
        while (ws.cell(1, row).to_string() != "bed") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        if(bed == 2) {
            ws.cell(2, row).value("stabil");
        }else if(bed == 1) {
            ws.cell(2, row).value("normal");
        }else {
            ws.cell(2, row).value("instabil");
        }

        //cutMat
        row = 2;
        while (ws.cell(1, row).to_string() != "schn") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        if(cutMat == 2) {
            ws.cell(2, row).value("Keramik");
        }else if(cutMat == 1) {
            ws.cell(2, row).value("VHM");
        }else {
            ws.cell(2, row).value("HSS");
        }

        //BoWinkel
        row = 2;
        while (ws.cell(1, row).to_string() != "spiWi") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        ws.cell(2, row).value(BoWinkel);

        //cooling
        row = 2;
        while (ws.cell(1, row).to_string() != "cooling") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        if(cooling == 2) {
            ws.cell(2, row).value("Oel");
        }else if(cooling == 1) {
            ws.cell(2, row).value("KSS");
        }else {
            ws.cell(2, row).value("Trocken");
        }

        //TurN
        row = 2;
        while (ws.cell(1, row).to_string() != "maxRpmDr") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        ws.cell(2, row).value(TurN);

        //TurPc
        row = 2;
        while (ws.cell(1, row).to_string() != "maxPcDr") {
            row++;
            if(row == maxRow) {
                exit(2);
            }
        }
        ws.cell(2, row).value(TurPc);

        wb.save(settingsName);

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
            return temp;
        }else{
            QMessageBox msg;
            QString title = QObject::tr("Fehler");
            QString text = QObject::tr("Die Datei 'config.ini' wurde nicht gefunden soll sie erstellt werden?");
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
                temp = true;
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
                            "maxPcDr=2.2\n";    // die max leistung der Dreh Spindel

        if (!dir.exists(path)){
            dir.mkpath(path);
        }

        file.open(QIODevice::WriteOnly);

        file.write(data);

        return;
    }

    static void test(){
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        xlnt::path test = xlnt::path(path.toStdString() + "/" + settingsName);

        xlnt::workbook wb;
        wb.abs_path(path.toStdString());
        wb.empty();

        wb.save(test);

        return;
    }
};
