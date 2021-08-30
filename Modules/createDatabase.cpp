#include "Modules/module.h"

std::string name = "Daten.xlsx";
//std::string name = "Test.xlsx";
std::filesystem::path createPath = std::filesystem::current_path() / name;

class createDatabase {
public:
    static void createSimple() {
        int column = 2;
        int row = 1;
        int color = 191;

        std::string mat[1][11] = {{"Material", "Aluminium Knetlegierung", "Guss-Aluminium > 6% Si", "Weichkunststoff", "Hartkunststoff",
                                   "Holz hart", "Holz weich", "MDF", "Messing, Bronze, Kupfer", "Stahl", "Testmaterial 10"}};
        double numbers[11][10] = {
            {77,       1.0,      2.0,      3.0,      4.0,      5.0,      6.0,      8.0,      10.0,     12.0},
            {500,      0.01,     0.02,     0.025,    0.05,     0.05,     0.05,     0.064,    0.08,     0.1},
            {200,      0.01,     0.01,     0.01,     0.015,    0.015,    0.025,    0.03,     0.038,    0.05},
            {600,      0.025,    0.03,     0.035,    0.045,    0.065,    0.09,     0.1,      0.2,      0.3},
            {550,      0.015,    0.02,     0.025,    0.05,     0.06,     0.08,     0.089,    0.1,      0.15},
            {450,      0.02,     0.025,    0.03,     0.055,    0.065,    0.085,    0.095,    0.095,    0.155},
            {500,      0.025,    0.03,     0.035,    0.06,     0.07,     0.09,     0.1,      0.11,     0.16},
            {450,      0.05,     0.07,     0.1,      0.15,     0.2,      0.3,      0.4,      0.5,      0.6},
            {360,      0.015,    0.02,     0.025,    0.025,    0.03,     0.05,     0.056,    0.065,    0.08},
            {90,       0.01,     0.01,     0.012,    0.025,    0.03,     0.038,    0.045,    0.05,     0.08},
            {100,      1.0,      2.0,      3.0,      4.0,      5.0,      6.0,      7.0,      8.0,      9.0}
        };

        xlnt::workbook wb;
        xlnt::worksheet ws = wb.active_sheet();

        //create table
        while (row <= 11) {
            ws.cell(1, row).value(mat[0][row-1]);
            ws.cell(1, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            row++;
        }

        row = 1;
        while (column <= 11) {
            while (row <= 11) {
                ws.cell(column, row).value(numbers[row-1][column-2]);
                ws.cell(column, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
                row++;
            }
            ws.column_properties(column).width = 10;
            row = 1;
            column++;
        }

        ws.cell("B1").value("Vc");
        ws.title("Simple");

        ws.column_properties(1).width = 23.55;

        row = 1;
        column = 1;
        while (row <= 11) {
            while (column <= 11) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            column = 1;
            row = row +2;
            color = 242;
        }

        wb.save(name);

        return;
    }

    static void createDynamic() {
        int column = 1;
        int row = 2;
        int color = 191;

        std::string header[1][18] = {{"Material","Vc min","Vc typ","Vc max","fz min (D10)","fz typ (D10)","fz max (D10)","fz min (D20)","fz typ (D20)",
                                      "fz max (D20)","ae min (D10)","ae typ (D10)","ae max (D10)","ae min (D20)","ae typ (D20)","ae max (D20)","Kc","Mc",}};
        std::string mat[1][8] = {{"Stahl gehaertet 48 - 55 HRC", "Stahl gehaertet 55 - 67 HRC", "EN - GJS > 180 HB", "Cu - Legierung",
                                  "Al - Legierung", "Stahl Rm 850 - 1100", "Stahl Rm 1100 - 1400", "Titanlegierung"}};
        double numbers[8][17] = {
            {90,  165, 240, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.25, 0.25,  0.25, 0.4,  0.4,   0.4,  1410, 0.39},
            {75,  97,  120, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.2,  0.2,   0.2,  0.35, 0.35,  0.35, 2300, 0.26},
            {300, 333, 360, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.25, 0.25,  0.25, 0.4,  0.4,   0.4,  1132, 0.44},
            {90,  115, 140, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.2,  0.2,   0.2,  0.35, 0.35,  0.35, 710,  0.215},
            {300, 400, 500, 0.1,  0.175, 0.25, 0.2,  0.3,   0.4,  0.1,  0.2,   0.3,  0.2,  0.3,   0.4,  813,  0.23},
            {280, 320, 360, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.25, 0.25,  0.25, 0.4,  0.4,   0.4,  1922, 0.12},
            {210, 240, 270, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.25, 0.25,  0.25, 0.4,  0.4,   0.4,  2350, 0.26},
            {90,  180, 270, 0.09, 0.11,  0.13, 0.13, 0.155, 0.18, 0.2,  0.225, 0.25, 0.35, 0.375, 0.4,  1450, 0.23}
        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(1);

        //create table
        while (column <= 18) {
            ws.cell(column, 1).value(header[0][column-1]);
            ws.cell(column, 1).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
            ws.cell(column, 1).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            column++;
        }

        while (row <= 9) {
            ws.cell(1, row).value(mat[0][row-2]);
            ws.cell(1, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            row++;
        }

        column = 2;
        row = 2;
        while (row <= 9) {
            while (column <= 18) {
                ws.cell(column, row).value(numbers[row-2][column-2]);
                ws.cell(column, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
                column++;
            }
            column = 2;
            row++;
        }

        column = 1;
        row = 3;
        color = 242;
        while (row <= 9) {
            while (column <= 18) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            column = 1;
            row = row + 2;
        }

        ws.column_properties(1).width = 35;
        ws.column_properties(2).width = 10;
        ws.column_properties(3).width = 10;
        ws.column_properties(4).width = 10;
        ws.column_properties(17).width = 10;
        ws.column_properties(18).width = 10;
        column = 5;
        while (column <= 16) {
            ws.column_properties(column).width = 13;
            column++;
        }

        ws.title("Dynamic");
        wb.save(name);

        return;
    }

    static void createDrill() {
        int column = 1;
        int row = 2;
        int color = 191;

        std::string header[1][14] = {{"Material","Vc min HSS","Vc typ HSS","Vc max HSS","Vc min VHM","Vc typ VHM","Vc max VHM","f in mm/U (D2)",
                                      "f in mm/U (D5)","f in mm/U (D8)","f in mm/U (D12)","f in mm/U (D16)","Kc","Mc"}};
        std::string mat[1][28] = {{"Gusseisen mit Kugelgrafit <= 250 HB","Gusseisen mit Kugelgrafit > 250 HB","Gusseisen mit Lamellengrafit <= 200 HB","Nichtrostenderstahl, austenitisch Rm <= 680",
                                   "Nichtrostenderstahl, austenitisch Rm > 680","Nichtrostenderstahl, mertensitisch Rm > 500","CuZn - Legierung (Messing) Langspanend","Al - Gusslegierung",
                                   "CuSn - Legierung (Bronze) Kurzspanend","Al - Knetlegierung","Al - Legierung, Kurzspanend","CuSn - Legierung (Bronze) Langspanend","CuZn - Legierung (Messing) Kurzspanend",
                                   "Duroplast","Thermoplast","Automatenstahl Rm <= 570","Automatenstahl Rm > 570","Baustahl Rm <= 500","Baustahl Rm > 500","Einsatzstahl, unlegiert Rm <= 550",
                                   "Einsatzstahl, legiert Rm <= 750","Einsatzstahl, legiert Rm > 750","Verguetungsstahl, legiert Rm <= 750","Verguetungsstahl, legiert Rm > 750",
                                   "Verguetungsstahl, unlegiert Rm <= 650","Verguetungsstahl, unlegiert Rm > 650","Werkzeugstahl Rm <= 750","Werkzeugstahl Rm > 750"}};
        double numbers[28][13] = {
            {31, 37,  44,  70,  85,  100, 0.05, 0.13, 0.22, 0.27, 0.32, 1005, 0.25},
            {23, 25,  28,  70,  85,  100, 0.04, 0.11, 0.17, 0.22, 0.27, 1132, 0.44},
            {25, 31,  38,  80,  105, 130, 0.05, 0.13, 0.22, 0.27, 0.32, 1020, 0.25},
            {13, 19,  25,  30,  40,  50,  0.02, 0.05, 0.09, 0.13, 0.15, 2350, 0.21},
            {10, 15,  19,  25,  35,  45,  0.02, 0.05, 0.09, 0.13, 0.15, 2350, 0.21},
            {8,  10,  13,  25,  30,  35,  0.02, 0.05, 0.09, 0.13, 0.15, 1820, 0.26},
            {44, 56,  75,  120, 170, 230, 0.05, 0.16, 0.22, 0.27, 0.28, 780,  0.18},
            {38, 50,  63,  120, 170, 130, 0.03, 0.09, 0.15, 0.22, 0.27, 830,  0.23},
            {31, 50,  63,  120, 170, 230, 0.05, 0.09, 0.13, 0.22, 0.27, 640,  0.25},
            {50, 87,  125, 180, 240, 300, 0.05, 0.15, 0.19, 0.24, 0.32, 830,  0.23},
            {38, 56,  75,  120, 170, 230, 0.05, 0.15, 0.19, 0.24, 0.32, 780,  0.23},
            {19, 29,  44,  90,  135, 180, 0.05, 0.09, 0.15, 0.22, 0.27, 640,  0.25},
            {75, 100, 125, 120, 170, 230, 0.09, 0.19, 0.27, 0.28, 0.32, 780,  0.18},
            {10, 15,  20,  0,   0,   0,   0.05, 0.08, 0.14, 0.2,  0.25, 1,    0.1},
            {20, 30,  40,  0,   0,   0,   0.5,  0.08, 0.14, 0.2,  0.25, 1,    0.1},
            {31, 37,  44,  70,  85,  100, 0.05, 0.13, 0.22, 0.27, 0.32, 1200, 0.18},
            {25, 31,  38,  60,  75,  85,  0.03, 0.08, 0.11, 0.17, 0.22, 1200, 0.18},
            {38, 50,  63,  70,  85,  100, 0.05, 0.13, 0.22, 0.27, 0.32, 1780, 0.17},
            {31, 37,  44,  70,  85,	 100, 0.05, 0.13, 0.22, 0.27, 0.32, 2110, 0.17},
            {31, 37,  44,  70,  85,  100, 0.03, 0.08, 0.11, 0.17, 0.22, 1820, 0.22},
            {19, 22,  25,  60,  75,  80,  0.02, 0.05, 0.09, 0.13, 0.15, 2100, 0.26},
            {10, 12,  15,  50,  65,  80,  0.02, 0.05, 0.09, 0.13, 0.15, 2290, 0.17},
            {19, 21,  28,  60,  75,  85,  0.02, 0.05, 0.09, 0.13, 0.15, 2220, 0.26},
            {10, 12,  15,  50,  65,  80,  0.02, 0.05, 0.09, 0.13, 0.15, 2500, 0.26},
            {31, 37,  44,  70,  85,  100, 0.03, 0.08, 0.11, 0.17, 0.22, 1516, 0.27},
            {25, 27,  31,  60,  75,  80,  0.02, 0.06, 0.1,  0.15, 0.19, 2130, 0.18},
            {13, 16,  19,  60,  75,  85,  0.02, 0.05, 0.09, 0.13, 0.15, 1820, 0.26},
            {10, 12,  15,  40,  55,  70,  0.02, 0.05, 0.09, 0.13, 0.15, 2300, 0.21}

        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(2);

        //create table
        while (column <= 14) {
            ws.cell(column, 1).value(header[0][column-1]);
            ws.cell(column, 1).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
            ws.cell(column, 1).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            column++;
        }

        while (row <= 29) {
            ws.cell(1, row).value(mat[0][row-2]);
            ws.cell(1, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            row++;
        }

        column = 2;
        row = 2;
        while (row <= 29) {
            while (column <= 14) {
                ws.cell(column, row).value(numbers[row-2][column-2]);
                ws.cell(column, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
                column++;
            }
            column = 2;
            row++;
        }


        column = 1;
        row = 3;
        color = 242;
        while (row <= 29) {
            while (column <= 14) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            column = 1;
            row = row + 2;
        }

        column = 2;
        while (column <= 12) {
            ws.column_properties(column).width = 15;
            column++;
        }
        ws.column_properties(1).width = 45;
        ws.column_properties(13).width = 10;
        ws.column_properties(14).width = 10;

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

        ws.title("Plan45");

        wb.save(name);

        return;
    }

    static void createSettings() {
        int column = 1;
        int row = 1;
        int color = 191;

        std::string array[8][3] = {
            {"Name",            "Wert",     "Hilfe"},
            {"Warnung",         "Ja",       "Ob beim Programm start der Disclaimer angezeigt werden soll (Ja|Nein)"},
            {"max RPM",         "77",    "Die maximale Drehzal der Machine"},
            {"max Leistung",    "77",      "Die maximale Spindelleistung der Maschine (in kW)"},
            {"Bedingungen",     "normal",   "die Bedingungen der Bearbeitung (auspanung, Werkzeuglaenge und Stabilitaet der Maschine) (instabil|normal|stabil)"},
            {"Schneidstoff",    "VHM",      "Der standart Schneidstoff für Werkzeuge (HSS|VHM|Keramik)"},
            {"Spitzenwinkel",   "77",      "Der standart Spitzenwinkel fuer Bohrer (118|130|140)"},
            {"Kuehlung",        "Trocken",  "Die standart Kuehlung der Werkzeuge (Trocken|KSS|Oel)"}

        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(wb.sheet_count());

        //create table
        while (row <= 8) {
            while (column <= 3) {
                ws.cell(column, row).value(array[row-1][column-1]);
                ws.cell(column, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
                ws.column_properties(column).width = 10;
                column++;
            }
            column = 1;
            row++;
        }

        column = 1;
        row = 1;
        while (row <= 8) {
            while (column <= 3) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            row = row + 2;
            color = 242;
            column = 1;
        }

        ws.cell(2, 3).value(24000);
        ws.cell(2, 4).value(2.2);
        ws.cell(2, 7).value(118);

        ws.title("Einstellungen");

        ws.column_properties(1).width = 25;
        ws.column_properties(2).width = 8;
        ws.column_properties(3).width = 100;

        wb.save(name);

        return;
    }
};
