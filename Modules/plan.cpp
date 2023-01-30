#include "Modules/plan.h"

namespace{
int planIndex;
int plan90Index = 4;
int plan45Index = 5;
}

QStringList Plan::matList(int schnForm) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    if(schnForm == 1) {
        planIndex = plan45Index;
    }else {
        planIndex = plan90Index;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(planIndex);

    while (ws.cell(1, row).to_string() != "") {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

double Plan::Vc(int mat, int bed, int schnForm) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;

    mat = mat + 2;

    bed = bed + 2;

    if(schnForm == 1) {
        planIndex = plan45Index;
    }else {
        planIndex = plan90Index;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(planIndex);

    Vc = ws.cell(bed, mat).value<double>();

    return Vc;
}

double Plan::fz(int mat, int bed, int schnForm, double D, double Ae) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fz;
    int column = 5;

    mat = mat + 2;

    if(schnForm == 1) {
        planIndex = plan45Index;
    }else {
        planIndex = plan90Index;
    }

    if(bed == 2) {
        column = column + 2;
    }else if(bed == 1) {
        column = column + 1;
    }else {
        column = column + 0;
    }

    if(Ae > (D / 2)) {
        column = column + 3;
    }else {
        column = column + 0;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(planIndex);

    fz = ws.cell(column, mat).value<double>();

    return fz;
}

int Plan::Kc(int mat, int schnForm) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    int Kc;
    int column;

    mat = mat + 2;

    if(schnForm == 1) {
        planIndex = plan45Index;
        column = 11;
    }else {
        planIndex = plan90Index;
        column = 11;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(planIndex);

    Kc = ws.cell(column, mat).value<int>();

    return Kc;
}

double Plan::Mc(int mat, int schnForm) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Mc;
    int column;

    mat = mat + 2;

    if(schnForm == 1) {
        planIndex = plan45Index;
        column = 12;
    }else {
        planIndex = plan90Index;
        column = 12;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(planIndex);

    Mc = ws.cell(column, mat).value<double>();

    return Mc;
}

