#include "Modules/dynamic.h"

namespace  {
int dynamicIndex = 1;
}


QStringList Dynamic::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    while (ws.cell(1, row).to_string() != "") {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

double Dynamic::Vc(int mat, int bed) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;
    int column = bed + 2;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    Vc = ws.cell(column, mat).value<double>();

    return Vc;
}

double Dynamic::fz(int mat, int bed, double D) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fz;
    int column = 5;

    mat = mat + 2;

    column = column + bed;

    if(D > 15) {
        column = column + 3;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    fz = ws.cell(column, mat).value<double>();

    return fz;
}

double Dynamic::ae(int mat, int bed, double D) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double ae;
    int column = 11;

    mat = mat + 2;

    column = column + bed;

    if(D > 15) {
        column = column + 3;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    ae = ws.cell(column, mat).value<double>();

    return ae;
}

int Dynamic::Kc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    int Kc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    Kc = ws.cell(17, mat).value<int>();

    return Kc;
}

double Dynamic::Mc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Mc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    Mc = ws.cell(18, mat).value<double>();

    return Mc;
}
