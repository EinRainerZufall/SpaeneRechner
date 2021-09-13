#include "Modules/module.h"

namespace  {
std::filesystem::path settingsPath = std::filesystem::current_path() / "Daten.xlsx";
}


class Settings {
public:
    static void showDis() {
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
            if(row == 64000) {
                QMessageBox msg;             
                if(OSX) {
                    msg.setText(QObject::tr("Kritischer Fehler"));
                    msg.setInformativeText(QObject::tr("Es konnte keine abfrage für den Disclaimer in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                }else {
                    msg.setText(QObject::tr("Es konnte keine abfrage für den Disclaimer in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                    msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
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
            if(OSX) {
                disBox.setInformativeText(QObject::tr("Die Nutzung erfolgt auf eigene Gefahr des Anwenders. Der Entwickler übernimmt keinerlei Garantie oder Gewährleistung "
                                            "für die Eignung des Programms sowie für dessen vollständige Funktionsfähigkeit, insbesondere die Richtigkeit der Berechnungen. "
                                            "Der Entwickler haftet nicht für störungs- oder fehlerfreien Einsatz des Programms. Der Anwender trägt das Risiko. Jegliche "
                                            "Haftung des Entwicklers für Schäden, Nachteile und Anwendungen aller Art, insbesondere auch für Vermögensschäden, Datenverlust "
                                            "o.ä., die dem Anwender oder Dritten aus oder im Zusammenhang mit der Verwendung oder der Nichtanwendbarkeit der Programmes "
                                            "entstehen sollten, ist ausgeschlossen. Sind sie damit einverstanden?"));
                disBox.setText(QObject::tr("Disclaimer"));
            }else {
                disBox.setText(QObject::tr("Die Nutzung erfolgt auf eigene Gefahr des Anwenders. Der Entwickler übernimmt keinerlei Garantie oder Gewährleistung "
                                            "für die Eignung des Programms sowie für dessen vollständige Funktionsfähigkeit, insbesondere die Richtigkeit der Berechnungen. "
                                            "Der Entwickler haftet nicht für störungs- oder fehlerfreien Einsatz des Programms. Der Anwender trägt das Risiko. Jegliche "
                                            "Haftung des Entwicklers für Schäden, Nachteile und Anwendungen aller Art, insbesondere auch für Vermögensschäden, Datenverlust "
                                            "o.ä., die dem Anwender oder Dritten aus oder im Zusammenhang mit der Verwendung oder der Nichtanwendbarkeit der Programmes "
                                            "entstehen sollten, ist ausgeschlossen. Sind sie damit einverstanden?"));
                disBox.setWindowTitle(QObject::tr("Disclaimer"));
            }
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

    static int maxRpmFr() {
        int rpm;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "maxRpmFr") {
            row++;
            if(row == 64000) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für den Maximale Drehzahl in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        rpm = ws.cell(2, row).value<int>();

        return rpm;
    }

    static int maxRpmDr() {
        int rpm;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "maxRpmDr") {
            row++;
            if(row == 64000) {
                QMessageBox msg;
                msg.setText(QObject::tr("Es konnte keine abfrage für den Maximale Drehzahl in der Datei 'Daten.xlsx' unter dem Einstellungs Tab gefunden werden!"));
                msg.setWindowTitle(QObject::tr("Kritischer Fehler"));
                msg.setIcon(QMessageBox::Critical);
                msg.setStandardButtons(QMessageBox::Close);
                msg.setDefaultButton(QMessageBox::Close);
                msg.exec();
                exit(2);
            }
        }

        rpm = ws.cell(2, row).value<int>();

        return rpm;
    }

    static double maxKw() {
        double pc;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "maxPc") {
            row++;
            if(row == 64000) {
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

    static double maxKwDr() {
        double pc;
        size_t index;
        int row = 2;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        while (ws.cell(1, row).to_string() != "maxPcDr") {
            row++;
            if(row == 64000) {
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

    static int condition() {
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
            if(row == 64000) {
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

    static int cutMat() {
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
            if(row == 64000) {
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

    static int angleDrill() {
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
            if(row == 64000) {
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

    static int cooling() {
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
            if(row == 64000) {
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

    static bool xlsxCheck() {
        bool temp = false;

        if(std::filesystem::exists(settingsPath)) {
            return temp;
        }else {
            QMessageBox box;
            box.setText(QObject::tr("Die Datei 'Daten.xlsx' wurde nicht gefunden soll sie erstellt werden?"));
            box.setWindowTitle(QObject::tr("Kritischer Fehler"));
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
};
