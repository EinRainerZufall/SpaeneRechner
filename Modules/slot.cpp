#include "Modules/slot.h"

namespace  {
int slotIndex = 3;
}

QStringList Slot::matList() {
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

QStringList Slot::dList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList D;
    int column = 5;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    while (ws.cell(column, 1).to_string() != "") {
        D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
        column++;
    }

    return D;
}

double Slot::Vc(int row) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    Vc = ws.cell(4, row).value<double>();

    return Vc;
}

double Slot::fz(int column, int row) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fz;

    column = column + 5;
    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    fz = ws.cell(column, row).value<double>();

    return fz;
}

double Slot::Kc(int row){
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Kc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    Kc = ws.cell(2, row).value<double>();

    return Kc;
}

double Slot::Mc(int row){
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Mc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    Mc = ws.cell(3, row).value<double>();

    return Mc;
}
