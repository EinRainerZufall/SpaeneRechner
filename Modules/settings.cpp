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
 * showDis      <- muss noch neu werden
 * maxKw        <- muss noch neu werden
 * maxKwDr      <- muss noch neu werden
 * condition    <- muss noch neu werden
 * cutMat       <- muss noch neu werden
 * angleDrill   <- muss noch neu werden
 * angleDrill   <- muss noch neu werden
 * xlsxCheck    <- muss noch neu werden
 * write        <- muss noch neu werden
 * INIcheck     <- neu, pruefen ob die .ini existiert
 * create       <- neu jetzt hier und nicht mehr in createDatabase
*/

class Settings {
public:
    static void showDis(){
        QString temp;
        size_t index;
        int row = 2;
        int OSX;

        if(QSysInfo::productType() == "osx") {
            OSX = 1;
        }else {
            OSX = 0;
        }        


        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "disclaimer") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;             
                QString title = QObject::tr("Kritischer Fehler");
                QString text = QObject::tr("Es konnte keine abfrage für den Disclaimer in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!");
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
        }

        temp = QString::fromStdString(ws.cell(2, row).to_string());

        if(temp == "Nein") {
            return;
        } else {
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
        double pc;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "maxPc") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für die Spindelleistung der Fraesmaschine in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        pc = ws.cell(2, row).value<double>();

        return pc;
    }

    static double maxKwDr(){
        double pc;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "maxPcDr") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für die Spindelleistung der Drehmaschine in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        pc = ws.cell(2, row).value<double>();

        return pc;
    }

    static int condition(){
        std::string temp;
        int con;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "bed") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für die standart Bedingung in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        temp = ws.cell(2, row).to_string();

        if(temp == "stabil" or temp == "stable") {
            con = 2;
        }else if(temp == "normal") {
            con = 1;
        }else {
            con = 0; //instabil
        }

        return con;
    }

    static int cutMat(){
        std::string temp;
        int mat;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "schn") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für den standart Schneidstoff in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        temp = ws.cell(2, row).to_string();

        if(temp == "Keramik") {
            mat = 2;
        } else if(temp == "VHM") {
            mat = 1;
        } else {
            mat = 0; //HSS
        }

        return mat;
    }

    static int angleDrill(){
        std::string temp;
        int angle;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "spiWi") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für den standart Spitzenwinkel an Bohrern in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        temp = ws.cell(2, row).to_string();

        if(temp == "140") {
            angle = 2;
        } else if(temp == "130") {
            angle = 1;
        } else {
            angle = 0;
        }

        return angle;
    }

    static int cooling(){
        std::string temp;
        int cool;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "cooling") {
            row++;
            if(row == maxRow) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für die standart Kuehlung in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        temp = ws.cell(2, row).to_string();

        if(temp == "Oel") {
            cool = 2;
        } else if(temp == "KSS") {
            cool = 1;
        } else {
            cool = 0; //Trocken
        }

        return cool;
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
                            "maxPc=2.2\n"       // die max leistung der Fraes Spindel
                            "bed=1\n"           // die Zerspanbedingung                     (0=instabiel|1=normal|2=stabil)
                            "schn=1\n"          // der standard Schneidstoff von Bohrern    (0=HSS|1=VHM|2=Keramik)
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

        return;
    }
};
