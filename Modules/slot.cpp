#include "Modules/module.h"

namespace  {
int slotIndex = 3;
}


class Slot {
public:
    static QStringList matList() {
        const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(file);
        xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

    static QStringList dList() {
        const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
        QStringList D;
        int column = 3;

        xlnt::workbook wb;
        wb.load(file);
        xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

        while (ws.cell(column, 1).to_string() != "") {
            D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
            column++;
        }

        return D;
    }

    static double Vc(int row) {
        const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
        double Vc;

        row = row + 2;

        xlnt::workbook wb;
        wb.load(file);
        xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

        Vc = ws.cell(2, row).value<double>();

        return Vc;
    }

    static double fz(int column, int row) {
        const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
        double fz;

        column = column + 3;
        row = row + 2;

        xlnt::workbook wb;
        wb.load(file);
        xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

        fz = ws.cell(column, row).value<double>();

        return fz;
    }
};
