#include "Modules/module.h"

namespace {
    //const std::string name = "Daten.xlsx";
    const std::string name = "Test.xlsx";
    const std::filesystem::path createPath = std::filesystem::current_path() / name;
}


class createDatabase {
public:
    static void createSimple() {
        int column = 2;
        int row = 1;
        int color = 191;

        const std::string mat[1][11] = {{"Material", "Aluminium Knetlegierung", "Guss-Aluminium > 6% Si", "Weichkunststoff", "Hartkunststoff",
                                   "Holz hart", "Holz weich", "MDF", "Messing, Bronze, Kupfer", "Stahl", "Testmaterial 10"}};
        const double numbers[11][10] = {
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

        const std::string header[1][18] = {{"Material","Vc min","Vc typ","Vc max","fz min (D10)","fz typ (D10)","fz max (D10)","fz min (D20)","fz typ (D20)",
                                      "fz max (D20)","ae min (D10)","ae typ (D10)","ae max (D10)","ae min (D20)","ae typ (D20)","ae max (D20)","Kc","Mc",}};
        const std::string mat[1][8] = {{"Stahl gehaertet 48 - 55 HRC", "Stahl gehaertet 55 - 67 HRC", "EN - GJS > 180 HB", "Cu - Legierung",
                                  "Al - Legierung", "Stahl Rm 850 - 1100", "Stahl Rm 1100 - 1400", "Titanlegierung"}};
        const double numbers[8][17] = {
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

        const std::string header[1][14] = {{"Material","Vc min HSS","Vc typ HSS","Vc max HSS","Vc min VHM","Vc typ VHM","Vc max VHM","f in mm/U (D2)",
                                      "f in mm/U (D5)","f in mm/U (D8)","f in mm/U (D12)","f in mm/U (D16)","Kc","Mc"}};
        const std::string mat[1][28] = {{"Gusseisen mit Kugelgrafit <= 250 HB","Gusseisen mit Kugelgrafit > 250 HB","Gusseisen mit Lamellengrafit <= 200 HB","Nichtrostenderstahl, austenitisch Rm <= 680",
                                   "Nichtrostenderstahl, austenitisch Rm > 680","Nichtrostenderstahl, mertensitisch Rm > 500","CuZn - Legierung (Messing) Langspanend","Al - Gusslegierung",
                                   "CuSn - Legierung (Bronze) Kurzspanend","Al - Knetlegierung","Al - Legierung, Kurzspanend","CuSn - Legierung (Bronze) Langspanend","CuZn - Legierung (Messing) Kurzspanend",
                                   "Duroplast","Thermoplast","Automatenstahl Rm <= 570","Automatenstahl Rm > 570","Baustahl Rm <= 500","Baustahl Rm > 500","Einsatzstahl, unlegiert Rm <= 550",
                                   "Einsatzstahl, legiert Rm <= 750","Einsatzstahl, legiert Rm > 750","Verguetungsstahl, legiert Rm <= 750","Verguetungsstahl, legiert Rm > 750",
                                   "Verguetungsstahl, unlegiert Rm <= 650","Verguetungsstahl, unlegiert Rm > 650","Werkzeugstahl Rm <= 750","Werkzeugstahl Rm > 750"}};
        const double numbers[28][13] = {
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
        int row = 2;
        int color = 191;

        const std::string header[1][12] = {{"Material","Vc min","Vc typ","Vc max","fz (bei ae 0,1 * D) min","fz (bei ae 0,1 * D) typ","fz (bei ae 0,1 * D) max",
                                      "fz (bei ae 0,5 bis 1) * D min","fz (bei ae 0,5 bis 1) * D typ","fz (bei ae 0,5 bis 1) * D max","Kc","Mc"}};
        const std::string mat[1][32] = {{"Gusseisen mit Kugelgrafit <= 250 HB","Gusseisen mit Kugelgrafit > 250 HB","Gusseisen mit Lamellengrafit <= 200 HB","Gusseisen mit Lamellengrafit > 200 HB",
                                   "Temperguss <= 230 HB","Temperguss > 230 HB","Nichtrostenderstahl, austenitisch Rm <= 680","Nichtrostenderstahl, austenitisch Rm > 680",
                                   "Nichtrostenderstahl, ferritisch Rm <= 700","Nichtrostenderstahl, mertensitisch Rm > 500","Al - Gusslegierung <= 75 HB","Al - Gusslegierung > 75 HB",
                                   "Al - Knetlegierung Rm <= 300","Al - Legierung, Ausgehärtet Rm > 300","CuZn - Legierung (Bronze) Rm <= 700","CuZn - Legierung (Messing) Rm <= 600",
                                   "Faserverstärkte Kunststoffe","Thermoplast, Duroplast","Automatenstahl Rm <= 570","Automatenstahl Rm > 570","Baustahl Rm <= 500","Baustahl Rm > 500",
                                   "Einsatzstahl Rm <= 570","Einsatzstahl Rm > 570","Stahlguss Rm <= 700","Stahlguss Rm > 700","Verguetungsstahl, legiert Rm <= 750","Verguetungsstahl, legiert Rm > 750",
                                   "Verguetungsstahl, unlegiert Rm <= 650","Verguetungsstahl, unlegiert Rm > 650","Werkzeugstahl Rm <= 750","Werkzeugstahl Rm > 750"}};
        const double numbers[32][11] = {
            {200, 220, 240, 0.14, 0.23, 0.32, 0.08, 0.13, 0.18, 1005, 0.25},
            {110, 130, 150, 0.14, 0.23, 0.32, 0.08, 0.13, 0.18, 1132, 0.44},
            {220, 240, 260, 0.14, 0.23, 0.32, 0.08, 0.13, 0.18, 950,  0.21},
            {120, 140, 160, 0.14, 0.23, 0.32, 0.08, 0.13, 0.18, 1470, 0.26},
            {120, 140, 160, 0.14, 0.23, 0.32, 0.08, 0.13, 0.18, 1313, 0.2},
            {100, 120, 140, 0.14, 0.23, 0.32, 0.08, 0.13, 0.18, 1313, 0.2},
            {180, 200, 220, 0.17, 0.22, 0.28, 0.1,  0.13, 0.16, 1820, 0.26},
            {160, 180, 200, 0.17, 0.21, 0.25, 0.09, 0.12, 0.14, 1820, 0.26},
            {190, 210, 230, 0.17, 0.22, 0.28, 0.1,  0.13, 0.16, 2350, 0.21},
            {150, 170, 190, 0.17, 0.19, 0.21, 0.09, 0.11, 0.12, 1820, 0.26},
            {200, 350, 500, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 830,  0.23},
            {180, 300, 420, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 544,  0.24},
            {600, 700, 800, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 830,  0.23},
            {400, 500, 600, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 780,  0.23},
            {300, 400, 500, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 780,  0.18},
            {500, 600, 700, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 640,  0.25},
            {200, 350, 500, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1,    0.1},
            {400, 500, 600, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1,    0.1},
            {160, 200, 240, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1200, 0.18},
            {160, 200, 240, 0.17, 0.25, 0.31, 0.1,  0.14, 0.18, 1200, 0.18},
            {200, 230, 260, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1780, 0.17},
            {160, 200, 240, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 2260, 0.3},
            {200, 235, 270, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1820, 0.22},
            {140, 165, 190, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 2290, 0.17},
            {190, 210, 230, 0.11, 0.15, 0.19, 0.08, 0.1,  0.12, 1313, 0.2},
            {130, 150, 170, 0.11, 0.15, 0.19, 0.08, 0.1,  0.12, 1313, 0.2},
            {140, 165, 190, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 2500, 0.26},
            {140, 165, 190, 0.14, 0.21, 0.28, 0.08, 0.12, 0.16, 2220, 0.26},
            {150, 175, 200, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1516, 0.27},
            {140, 165, 190, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 2130 ,0.18},
            {140, 165, 190, 0.17, 0.24, 0.31, 0.1,  0.14, 0.18, 1410, 0.39},
            {75,  100, 125, 0.14, 0.19, 0.24, 0.08, 0.11, 0.14, 1820, 0.26}
        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(4);

        //create table
        while (column <= 12) {
            ws.cell(column, 1).value(header[0][column-1]);
            ws.cell(column, 1).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
            ws.cell(column, 1).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            column++;
        }

        while (row <= 33) {
            ws.cell(1, row).value(mat[0][row-2]);
            ws.cell(1, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            row++;
        }

        column = 2;
        row = 2;
        while (row <= 33) {
            while (column <= 12) {
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
        while (row <= 33) {
            while (column <= 12) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            column = 1;
            row = row + 2;
        }

        ws.title("Plan90");

        column = 5;
        while (column <= 10) {
            ws.column_properties(column).width = 24;
            column++;
        }
        ws.column_properties(1).width = 45;
        ws.column_properties(2).width = 10;
        ws.column_properties(3).width = 10;
        ws.column_properties(4).width = 10;
        ws.column_properties(11).width = 10;
        ws.column_properties(12).width = 10;

        wb.save(name);

        return;
    }

    static void createPlan45() {
        int column = 1;
        int row = 1;
        int color = 191;

        const std::string header[1][12] = {{"Material","Vc min","Vc typ","Vc max","fz (bei ae 0,1 * D) min","fz (bei ae 0,1 * D) typ","fz (bei ae 0,1 * D) max",
                                      "fz (bei ae 0,5 bis 1) * D min","fz (bei ae 0,5 bis 1) * D typ","fz (bei ae 0,5 bis 1) * D max","Kc","Mc"}};
        const std::string mat[1][32] = {{"Gusseisen mit Kugelgrafit <= 250 HB","Gusseisen mit Kugelgrafit > 250 HB","Gusseisen mit Lamellengrafit <= 200 HB","Gusseisen mit Lamellengrafit > 200 HB",
                                   "Temperguss <= 230 HB","Temperguss > 230 HB","Nichtrostenderstahl, austenitisch Rm <= 680","Nichtrostenderstahl, austenitisch Rm > 680",
                                   "Nichtrostenderstahl, ferritisch Rm <= 700","Nichtrostenderstahl, mertensitisch Rm > 500","Al - Gusslegierung <= 75 HB","Al - Gusslegierung > 75 HB",
                                   "Al - Knetlegierung Rm <= 300","Al - Legierung, Ausgehärtet Rm > 300","CuZn - Legierung (Bronze) Rm <= 700","CuZn - Legierung (Messing) Rm <= 600",
                                   "Faserverstärkte Kunststoffe","Thermoplast, Duroplast","Automatenstahl Rm <= 570","Automatenstahl Rm > 570","Baustahl Rm <= 500","Baustahl Rm > 500",
                                   "Einsatzstahl Rm <= 570","Einsatzstahl Rm > 570","Stahlguss Rm <= 700","Stahlguss Rm > 700","Verguetungsstahl, legiert Rm <= 750",
                                   "Verguetungsstahl, legiert Rm > 750","Verguetungsstahl, unlegiert Rm <= 650","Verguetungsstahl, unlegiert Rm > 650","Werkzeugstahl Rm <= 750","Werkzeugstahl Rm > 750"}};
        const double numbers[32][11] = {
            {190, 210, 230, 0.18, 0.23, 0.28, 0.18, 0.21, 0.24, 1005, 0.25},
            {200, 215, 230, 0.25, 0.29, 0.33, 0.25, 0.29, 0.33, 1132, 0.44},
            {220, 235, 250, 0.25, 0.29, 0.33, 0.25, 0.29, 0.33, 950,  0.21},
            {115, 130, 145, 0.18, 0.23, 0.28, 0.18, 0.21, 0.24, 1470, 0.26},
            {190, 205, 220, 0.25, 0.29, 0.33, 0.18, 0.21, 0.24, 1313, 0.2},
            {170, 190, 210, 0.18, 0.23, 0.28, 0.18, 0.21, 0.24, 1313, 0.2},
            {190, 210, 230, 0.32, 0.34, 0.36, 0.16, 0.19, 0.22, 1820, 0.26},
            {150, 170, 190, 0.32, 0.34, 0.36, 0.16, 0.19, 0.22, 1820, 0.26},
            {200, 220, 240, 0.32, 0.34, 0.36, 0.16, 0.19, 0.22, 2350, 0.21},
            {130, 145, 160, 0.32, 0.34, 0.36, 0.16, 0.19, 0.22, 1820, 0.26},
            {250, 350, 500, 0.38, 0.42, 0.46, 0.2,  0.23, 0.26, 830,  0.23},
            {230, 300, 370, 0.38, 0.42, 0.46, 0.2,  0.23, 0.26, 544,  0.24},
            {600, 725, 850, 0.38, 0.42, 0.46, 0.2,  0.23, 0.26, 830,  0.23},
            {400, 500, 600, 0.38, 0.42, 0.38, 0.2,  0.23, 0.26, 780,  0.23},
            {300, 350, 400, 0.38, 0.42, 0.46, 0.2,  0.23, 0.26, 780,  0.18},
            {500, 550, 600, 0.38, 0.42, 0.46, 0.2,  0.23, 0.26, 640,  0.25},
            {250, 350, 500, 0.38, 0.42, 0.46, 02,   0.23, 0.26, 1,    0.1},
            {400, 500, 600, 0.38, 0.42, 0.46, 0.2,  0.23, 0.26, 1,    0.1},
            {230, 250, 270, 0.32, 0.34, 0.36, 0.18, 0.21, 0.24, 1200, 0.18},
            {220, 240, 270, 0.27, 0.3,  0.33, 0.16, 0.19, 0.22, 1200, 0.18},
            {250, 275, 300, 0.32, 0.34, 0.36, 0.18, 0.21, 0.24, 1780, 0.17},
            {220, 235, 250, 0.32, 0.34, 0.36, 0.18, 0.21, 0.24, 2260, 0.3},
            {200, 230, 260, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 1820, 0.22},
            {150, 175, 200, 0.32, 0.34, 0.36, 0.16, 0.19, 0.22, 2290, 0.17},
            {190, 210, 230, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 1313, 0.2},
            {140, 160, 180, 0.32, 0.34, 0.36, 0.16, 0.19, 0.22, 1313, 0.2},
            {190, 220, 250, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 2500, 0.26},
            {150, 175, 200, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 2220, 0.26},
            {200, 230, 260, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 1516, 0.27},
            {150, 175, 200, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 2130, 0.18},
            {120, 135, 150, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 1410, 0.39},
            {95,  105, 115, 0.32, 0.34, 0.36, 0.17, 0.2,  0.23, 1820, 0.26}
        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(5);

        //create table
        while (column <= 12) {
            ws.cell(column, 1).value(header[0][column-1]);
            ws.cell(column, 1).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
            ws.cell(column, 1).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            column++;
        }

        while (row <= 33) {
            ws.cell(1, row).value(mat[0][row-2]);
            ws.cell(1, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            row++;
        }

        column = 2;
        row = 2;
        while (row <= 33) {
            while (column <= 12) {
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
        while (row <= 33) {
            while (column <= 12) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            column = 1;
            row = row + 2;
        }

        ws.title("Plan45");
        while (column <= 10) {
            ws.column_properties(column).width = 24;
            column++;
        }
        ws.column_properties(1).width = 45;
        ws.column_properties(2).width = 10;
        ws.column_properties(3).width = 10;
        ws.column_properties(4).width = 10;
        ws.column_properties(11).width = 10;
        ws.column_properties(12).width = 10;

        wb.save(name);

        return;
    }

    static void createTurn() {
        int column = 1;
        int row = 1;
        int color = 191;

        std::string header[1][12] = {{"Material","Plan Vc min","Plan Vc typ","Plan Vc max","Laengs Vc min SR","Laengs Vc typ SR","Laengs Vc max SR",
                                      "Laengs Vc min SL","Laengs Vc typ SL","Laengs Vc max SL","Kc","Mc"}};
        const std::string mat[1][32] = {{"Gusseisen mit Kugelgrafit <= 250 HB","Gusseisen mit Kugelgrafit > 250 HB","Gusseisen mit Lamellengrafit <= 200 HB","Gusseisen mit Lamellengrafit > 200 HB",
                                   "Temperguss <= 230 HB","Temperguss > 230 HB","Nichtrostenderstahl, austenitisch Rm <= 680","Nichtrostenderstahl, austenitisch Rm > 680",
                                   "Nichtrostenderstahl, ferritisch Rm <= 700","Nichtrostenderstahl, mertensitisch Rm > 500","Al - Gusslegierung <= 75 HB","Al - Gusslegierung > 75 HB",
                                   "Al - Knetlegierung Rm <= 300","Al - Legierung, Ausgehärtet Rm > 300","CuZn - Legierung (Bronze) Rm <= 700","CuZn - Legierung (Messing) Rm <= 600",
                                   "Faserverstärkte Kunststoffe","Thermoplast, Duroplast","Automatenstahl Rm <= 570","Automatenstahl Rm > 570","Baustahl Rm <= 500","Baustahl Rm > 500",
                                   "Einsatzstahl Rm <= 570","Einsatzstahl Rm > 570","Stahlguss Rm <= 700","Stahlguss Rm > 700","Verguetungsstahl, legiert Rm <= 750","Verguetungsstahl, legiert Rm > 750",
                                   "Verguetungsstahl, unlegiert Rm <= 650","Verguetungsstahl, unlegiert Rm > 650","Werkzeugstahl Rm <= 750","Werkzeugstahl Rm > 750"}};
        double numbers[32][11] = {
            {210, 270, 330, 160, 210, 260, 250, 320, 410, 1005, 0.25},
            {160, 200, 250, 140, 170, 210, 180, 230, 300, 1132, 0.44},
            {300, 370, 440, 230, 280, 330, 380, 450, 520, 950,  0.21},
            {195, 250, 305, 140, 190, 240, 230, 300, 370, 1470, 0.26},
            {190, 235, 280, 140, 170, 200, 240, 300, 370, 1313, 0.2},
            {150, 190, 230, 100, 130, 160, 200, 260, 330, 1313, 0.2},
            {140, 170, 200, 90,  110, 130, 200, 230, 260, 1820, 0.26},
            {100, 120, 140, 70,  90,  110, 130, 150, 170, 1820, 0.26},
            {180, 215, 240, 160, 180, 200, 230, 250, 270, 2350, 0.21},
            {130, 160, 190, 110, 130, 150, 150, 190, 230, 1820, 0.26},
            {310, 400, 490, 300, 360, 420, 450, 550, 650, 830,  0.23},
            {290, 330, 420, 200, 270, 340, 300, 400, 500, 544,  0.24},
            {350, 450, 560, 380, 450, 520, 600, 700, 800, 830,  0.23},
            {200, 320, 440, 240, 300, 360, 400, 500, 600, 780,  0.23},
            {200, 230, 260, 130, 150, 170, 280, 310, 340, 780,  0.18},
            {320, 355, 390, 250, 270, 300, 400, 440, 480, 640,  0.25},
            {230, 320, 410, 190, 220, 310, 340, 420, 500, 1,    0.1},
            {340, 430, 520, 270, 360, 450, 400, 500, 600, 1,    0.1},
            {180, 250, 320, 130, 200, 270, 240, 300, 360, 1200, 0.18},
            {130, 200, 270, 100, 160, 220, 200, 250, 360, 1200, 0.18},
            {210, 280, 350, 150, 220, 300, 280, 340, 400, 1780, 0.17},
            {160, 230, 300, 100, 170, 240, 220, 290, 350, 2260, 0.3},
            {200, 270, 320, 150, 210, 260, 250, 320, 360, 1820, 0.22},
            {160, 220, 270, 110, 160, 210, 200, 270, 340, 2290, 0.17},
            {140, 180, 220, 105, 155, 180, 160, 200, 240, 1313, 0.2},
            {100, 135, 170, 80,  110, 140, 130, 160, 190, 1313, 0.2},
            {100, 160, 220, 90,  130, 180, 125, 185, 245, 2500, 0.26},
            {80,  130, 180, 70,  110, 160, 100, 150, 200, 2220, 0.26},
            {180, 250, 320, 120, 190, 240, 220, 300, 380, 1516, 0.27},
            {110, 200, 280, 110, 150, 200, 190, 250, 310, 2130, 0.18},
            {95,  145, 195, 85,  125, 170, 115, 165, 215, 1410, 0.39},
            {60,  110, 160, 40,  80,  120, 100, 140, 180, 1820, 0.26}
        };
        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(6);

        //create table
        while (column <= 12) {
            ws.cell(column, 1).value(header[0][column-1]);
            ws.cell(column, 1).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
            ws.cell(column, 1).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            column++;
        }

        while (row <= 33) {
            ws.cell(1, row).value(mat[0][row-2]);
            ws.cell(1, row).alignment(xlnt::alignment().horizontal(xlnt::horizontal_alignment::center));
            row++;
        }

        column = 2;
        row = 2;
        while (row <= 33) {
            while (column <= 12) {
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
        while (row <= 33) {
            while (column <= 12) {
                ws.cell(column, row).fill(xlnt::fill::solid(xlnt::rgb_color(color, color, color)));
                column++;
            }
            column = 1;
            row = row + 2;
        }

        ws.title("Drehen");
        column = 2;
        while (column <= 10) {
            ws.column_properties(column).width = 15;
            column++;
        }
        ws.column_properties(1).width = 45;
        ws.column_properties(11).width = 10;
        ws.column_properties(12).width = 10;

        wb.save(name);

        return;
    }

    static void createSettings() {
        int column = 1;
        int row = 1;
        int color = 191;

        const std::string array[9][3] = {
            {"Name",            "Wert",     "Hilfe"},
            {"disclaimer",      "Ja",       "Ob beim Programm start der Disclaimer angezeigt werden soll (Ja|Nein)"},
            {"maxRpmFr",        "77",       "Die maximale Drehzal der Fraesmachine"},
            {"maxPc",           "77",       "Die maximale Spindelleistung der Maschine (in kW)"},
            {"bed",             "normal",   "die Bedingungen der Bearbeitung (auspanung, Werkzeuglaenge und Stabilitaet der Maschine) (instabil|normal|stabil)"},
            {"schn",            "VHM",      "Der standart Schneidstoff für Werkzeuge (HSS|VHM|Keramik)"},
            {"spiWi",           "77",       "Der standart Spitzenwinkel fuer Bohrer (118|130|140)"},
            {"cooling",         "Trocken",  "Die standart Kuehlung der Werkzeuge (Trocken|KSS|Oel)"},
            {"maxRpmDr",        "77",       "Die maximale Drehzal der Drehmachine"}

        };

        xlnt::workbook wb;
        wb.load(createPath);
        xlnt::worksheet ws = wb.create_sheet(wb.sheet_count());

        //create table
        while (row <= 9) {
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
        while (row <= 9) {
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
        ws.cell(2, 9).value(5000);

        ws.title("Einstellungen");

        ws.column_properties(1).width = 25;
        ws.column_properties(2).width = 8;
        ws.column_properties(3).width = 100;

        wb.save(name);

        return;
    }
};
