#include "Modules/module.h"

namespace  {
std::filesystem::path simplePath = std::filesystem::current_path() / "Daten.xlsx";
int simpleIndex = 0;
}


class Simple {
public:
    static QString test() {
        QString temp;

        xlnt::workbook wb;
        wb.load(simplePath);

        temp = QString::number(wb.sheet_count() - 1);

        return temp;
    }

    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(simplePath);
        xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

    static QStringList dList() {
        QStringList D;
        int column = 3;

        xlnt::workbook wb;
        wb.load(simplePath);
        xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

        while (ws.cell(column, 1).to_string() != "") {
            D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
            column++;
        }

        return D;
    }

    static double Vc(int row) {
        double Vc;

        row = row + 2;

        xlnt::workbook wb;
        wb.load(simplePath);
        xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

        Vc = ws.cell(2, row).value<double>();

        return Vc;
    }

    static double fz(int column, int row) {
        double fz;

        column = column + 3;
        row = row + 2;

        xlnt::workbook wb;
        wb.load(simplePath);
        xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

        fz = ws.cell(column, row).value<double>();

        return fz;
    }
};
