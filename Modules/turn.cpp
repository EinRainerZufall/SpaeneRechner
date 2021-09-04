#include "Modules/module.h"

namespace{
    std::filesystem::path turnPath = std::filesystem::current_path() / "Daten.xlsx";
    int turnIndex = 6;
}

class Turn {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(turnPath);
        xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

    static double Vc(int mat, int bed, int typ) {
        double Vc;
        int column = 2;

        mat = mat + 2;

        column = column + bed;

        switch (typ) {
        case 2:
            column = column + 6;
            break;
        case 1:
            column = column + 3;
            break;
        default:
            column = column + 0;
        }

        xlnt::workbook wb;
        wb.load(turnPath);
        xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

        Vc = ws.cell(column, mat).value<double>();

        return Vc;
    }

    static int Kc(int mat) {
        int Kc;

        mat = mat + 2;

        xlnt::workbook wb;
        wb.load(turnPath);
        xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

        Kc = ws.cell(11, mat).value<int>();

        return Kc;
    }

    static double Mc(int mat) {
        double Mc;

        mat = mat + 2;

        xlnt::workbook wb;
        wb.load(turnPath);
        xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

        Mc = ws.cell(12, mat).value<double>();

        return Mc;
    }
};
