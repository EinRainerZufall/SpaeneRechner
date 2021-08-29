#include "Modules/module.h"

std::filesystem::path dynamicPath = std::filesystem::current_path() / "Daten.xlsx";
int dynamicIndex = 1;

class Dynamic {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

    static double Vc(int mat, int bed) {
        double Vc;
        int column = bed + 2;

        mat = mat + 2;

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        Vc = std::stod(ws.cell(column, mat).to_string());

        return Vc;
    }

    static double fz(int mat, int bed, double D) {
        double fz;
        int column = 5;

        mat = mat + 2;

        column = column + bed;

        if(D > 15) {
            column = column + 3;
        }

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        fz = std::stod(ws.cell(column, mat).to_string());

        return fz;
    }

    static double ae(int mat, int bed, double D) {
        double ae;
        int column = 11;

        mat = mat + 2;

        column = column + bed;

        if(D > 15) {
            column = column + 3;
        }

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        ae = std::stod(ws.cell(column, mat).to_string());

        return ae;
    }

    static int Kc(int mat) {
        int Kc;

        mat = mat + 2;

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        Kc = std::stoi(ws.cell(17, mat).to_string());

        return Kc;
    }

    static double Mc(int mat) {
        double Mc;

        mat = mat + 2;

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        Mc = std::stod(ws.cell(18, mat).to_string());

        return Mc;
    }
};
