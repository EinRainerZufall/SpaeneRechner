#include "Modules/module.h"

std::filesystem::path settingsPath = std::filesystem::current_path() / "Daten.xlsx";

class Settings {
public:
    static void showDis() {
        QString temp;
        size_t index;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        temp = QString::fromStdString(ws.cell("B2").to_string());

        if(temp == "Nein") {
            return;
        } else {
            QMessageBox disBox;
            disBox.setText(QObject::tr("Die Nutzung erfolgt auf eigene Gefahr des Anwenders. Der Entwickler übernimmt keinerlei Garantie oder Gewährleistung "
                                        "für die Eignung des Programms sowie für dessen vollständige Funktionsfähigkeit, insbesondere die Richtigkeit der Berechnungen. "
                                        "Der Entwickler haftet nicht für störungs- oder fehlerfreien Einsatz des Programms. Der Anwender trägt das Risiko. Jegliche "
                                        "Haftung des Entwicklers für Schäden, Nachteile und Anwendungen aller Art, insbesondere auch für Vermögensschäden, Datenverlust "
                                        "o.ä., die dem Anwender oder Dritten aus oder im Zusammenhang mit der Verwendung oder der Nichtanwendbarkeit der Programmes "
                                        "entstehen sollten, ist ausgeschlossen. Sind sie damit einverstanden?"));
            disBox.setWindowTitle(QObject::tr("Disclaimer"));
            disBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
            disBox.setDefaultButton(QMessageBox::Ok);
            disBox.setEscapeButton(QMessageBox::No);
            int dis = disBox.exec();

            switch (dis) {
            case QMessageBox::Ok:
                return;
            case QMessageBox::No:
                exit(0);
            }
        }
        return;
    }

    static int maxRpm() {
        int rpm;
        size_t index;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        rpm = ws.cell("B3").value<int>();

        return rpm;
    }

    static double maxKw() {
        double pc;
        size_t index;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        pc = ws.cell("B4").value<double>();

        return pc;
    }

    static int condition() {
        std::string temp;
        int con;
        size_t index;

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        temp = ws.cell("B5").to_string();

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

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        temp = ws.cell("B6").to_string();

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

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        temp = ws.cell("B7").to_string();

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

        xlnt::workbook wb;
        wb.load(settingsPath);
        index = (wb.sheet_count() - 1);
        xlnt::worksheet ws = wb.sheet_by_index(index);

        temp = ws.cell("B8").to_string();

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
