#include "Modules/module.h"

//std::string name = "Daten.xlsx";
std::string name = "Test.xlsx";
std::filesystem::path createPath = std::filesystem::current_path() / name;

class createDatabase {
public:
    static void createSimple() {
        int column = 1;
        int row = 1;

        std::string array[11][11] = {
            {"Material",                "Vc",       "1.0",      "2.0",      "3.0",      "4.0",      "5.0",      "6.0",      "8.0",      "10.0",     "12.0"},
            {"Aluminium Knetlegierung", "500.0",    "0.01",     "0.02",     "0.025",    "0.05",     "0.05",     "0.05",     "0.064",    "0.08",     "0.1"},
            {"Guss-Aluminium > 6% Si",  "200.0",    "0.01",     "0.01",     "0.01",     "0.015",    "0.015",    "0.025",    "0.03",     "0.038",    "0.05"},
            {"Weichkunststoff",         "600.0",    "0.025",    "0.03",     "0.035",    "0.045",    "0.065",    "0.09",     "0.1",      "0.2",      "0.3"},
            {"Hartkunststoff",          "550.0",    "0.015",    "0.02",     "0.025",    "0.05",     "0.06",     "0.08",     "0.089",    "0.1",      "0.15"},
            {"Holz hart",               "450.0",    "0.02",     "0.025",    "0.03",     "0.055",    "0.065",    "0.085",    "0.095",    "0.095",    "0.155"},
            {"Holz weich",              "500.0",    "0.025",    "0.03",     "0.035",    "0.06",     "0.07",     "0.09",     "0.1",      "0.11",     "0.16"},
            {"MDF",                     "450.0",    "0.05",     "0.07",     "0.1",      "0.15",     "0.2",      "0.3",      "0.4",      "0.5",      "0.6"},
            {"Messing, Bronze, Kupfer", "360.0",    "0.015",    "0.02",     "0.025",    "0.025",    "0.03",     "0.05",     "0.056",    "0.065",    "0.08"},
            {"Stahl",                   "90.0",     "0.01",     "0.01",     "0.012",    "0.025",    "0.03",     "0.038",    "0.045",    "0.05",     "0.08"},
            {"Testmaterial 10",         "100.0",    "1.0",      "2.0",      "3.0",      "4.0",      "5.0",      "6.0",      "7.0",      "8.0",      "9.0"}
        };

        xlnt::workbook wb;
        xlnt::worksheet ws = wb.active_sheet();

        //create table
        while (row <= 11) {
            while (column <= 11) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Simple");

        wb.save(name);

        return;
    }

    static void createDynamic() {
        int column = 1;
        int row = 1;

        std::string array[9][18] = {
            {"Material",                     "Vc min","Vc typ","Vc max","fz min (D10)","fz typ (D10)","fz max (D10)","fz min (D20)","fz typ (D20)","fz max (D20)","ae min (D10)","ae typ (D10)","ae max (D10)","ae min (D20)","ae typ (D20)","ae max (D20)","Kc",      "Mc"},
            {"Stahl gehaertet 48 - 55 HRC",  "90.0",  "165.0", "240.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.25",        "0.25",        "0.25",        "0.4",         "0.4",         "0.4",         "1410.0",  "0.39"},
            {"Stahl gehaertet 55 - 67 HRC",  "75.0",  "97.5",  "120.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.2",         "0.2",         "0.2",         "0.35",        "0.35",        "0.35",        "2300.0",  "0.26"},
            {"EN - GJS > 180 HB",            "300.0", "333.0", "360.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.25",        "0.25",        "0.25",        "0.4",         "0.4",         "0.4",         "1132.0",  "0.44"},
            {"Cu - Legierung",               "90.0",  "115.0", "140.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.2",         "0.2",         "0.2",         "0.35",        "0.35",        "0.35",        "710.0",   "0.215"},
            {"Al - Legierung",               "300.0", "400.0", "500.0", "0.1",         "0.175",       "0.25",        "0.2",         "0.3",         "0.4",         "0.1",         "0.2",         "0.3",         "0.2",         "0.3",         "0.4",         "813.0",   "0.23"},
            {"Stahl Rm 850 - 1100",          "280.0", "320.0", "360.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.25",        "0.25",        "0.25",        "0.4",         "0.4",         "0.4",         "1922.0",  "0.12"},
            {"Stahl Rm 1100 - 1400",         "210.0", "240.0", "270.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.25",        "0.25",        "0.25",        "0.4",         "0.4",         "0.4",         "2350.0",  "0.26"},
            {"Titanlegierung",               "90.0",  "180.0", "270.0", "0.09",        "0.11",        "0.13",        "0.13",        "0.155",       "0.18",        "0.2",         "0.225",       "0.25",        "0.35",        "0.375",       "0.4",         "1450.0",  "0.23"}
        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(1);

        //create table
        while (row <= 9) {
            while (column <= 18) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Dynamic");

        wb.save(name);

        return;
    }

    static void createDrill() {
        int column = 1;
        int row = 1;

        std::string array[11][11] = {};

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(2);

        //create table
        while (row <= 11) {
            while (column <= 11) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Drill");

        wb.save(name);

        return;
    }

    static void createSlot() {
        int column = 1;
        int row = 1;

        std::string array[11][11] = {};

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(3);

        //create table
        while (row <= 11) {
            while (column <= 11) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Slot");

        wb.save(name);

        return;
    }

    static void createPlan90() {
        int column = 1;
        int row = 1;

        std::string array[11][11] = {};

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(4);

        //create table
        while (row <= 11) {
            while (column <= 11) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Plan90");

        wb.save(name);

        return;
    }

    static void createPlan45() {
        int column = 1;
        int row = 1;

        std::string array[11][11] = {};

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(5);

        //create table
        while (row <= 11) {
            while (column <= 11) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Plan45");

        wb.save(name);

        return;
    }

    static void createSettings() {
        int column = 1;
        int row = 1;

        std::string array[8][3] = {
            {"Name",            "Wert",     "Hilfe"},
            {"Warnung",         "Ja",       "Ob beim Programm start der Disclaimer angezeigt werden soll (Ja|Nein)"},
            {"max RPM",         "24000",    "Die maximale Drehzal der Machine"},
            {"max Leistung",    "2.2",      "Die maximale Spindelleistung der Maschine (in kW)"},
            {"Bedingungen",     "normal",   "die Bedingungen der Bearbeitung (auspanung, Werkzeuglaenge und Stabilitaet der Maschine) (instabil|normal|stabil)"},
            {"Schneidstoff",    "VHM",      "Der standart Schneidstoff für Werkzeuge (HSS|VHM|Keramik)"},
            {"Spitzenwinkel",   "118",      "Der standart Spitzenwinkel fuer Bohrer (118|130|140)"},
            {"Kuehlung",        "Trocken",  "Die standart Kuehlung der Werkzeuge (Trocken|KSS|Oel)"}

        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(wb.sheet_count());

        //create table
        while (row <= 8) {
            while (column <= 3) {
                ws.cell(column, row).value(array[row-1][column-1]);
                column++;
            }
            column = 1;
            row++;
        }

        ws.title("Einstellungen");

        wb.save(name);

        return;
    }
};
