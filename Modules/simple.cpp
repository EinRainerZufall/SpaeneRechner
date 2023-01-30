#include "Modules/simple.h"

namespace  {
int simpleIndex = 0;
}

QStringList Simple::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

    while (ws.cell(1, row).to_string() != "") {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

QStringList Simple::dList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList D;
    int column = 3;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

    while (ws.cell(column, 1).to_string() != "") {
        D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
        column++;
    }

    return D;
}

double Simple::Vc(int row) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

    Vc = ws.cell(2, row).value<double>();

    return Vc;
}

double Simple::fz(int column, int row) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fz;

    column = column + 3;
    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(simpleIndex);

    fz = ws.cell(column, row).value<double>();

    return fz;
}
