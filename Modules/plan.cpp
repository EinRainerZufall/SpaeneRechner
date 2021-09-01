#include "Modules/module.h"

std::filesystem::path planPath = std::filesystem::current_path() / "Daten.xlsx";
int planIndex;
int plan90Index = 4;
int plan45Index = 5;

class Plan {
public:
    static QStringList matList(int schnForm) {
        QStringList mat;
        int row = 2;

        if(schnForm == 1) {
            planIndex = plan45Index;
        }else {
            planIndex = plan90Index;
        }

        xlnt::workbook wb;
        wb.load(planPath);
        xlnt::worksheet ws = wb.sheet_by_index(planIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

    static double Vc(int mat, int bed, int schnForm) {
        double Vc;

        mat = mat + 2;

        bed = bed + 2;

        if(schnForm == 1) {
            planIndex = plan45Index;
        }else {
            planIndex = plan90Index;
        }

        xlnt::workbook wb;
        wb.load(planPath);
        xlnt::worksheet ws = wb.sheet_by_index(planIndex);

        Vc = ws.cell(bed, mat).value<double>();

        return Vc;
    }

    static double fz(int mat, int bed, int schnForm, double D, double Ae) {
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
        wb.load(planPath);
        xlnt::worksheet ws = wb.sheet_by_index(planIndex);

        fz = ws.cell(column, mat).value<double>();

        return fz;
    }

    static int Kc(int mat, int schnForm) {
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
        wb.load(planPath);
        xlnt::worksheet ws = wb.sheet_by_index(planIndex);

        Kc = ws.cell(column, mat).value<int>();

        return Kc;
    }

    static double Mc(int mat, int schnForm) {
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
        wb.load(planPath);
        xlnt::worksheet ws = wb.sheet_by_index(planIndex);

        Mc = ws.cell(column, mat).value<double>();

        return Mc;
    }
};
