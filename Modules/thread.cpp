#include "Modules/module.h"

namespace  {
std::filesystem::path threadPath = std::filesystem::current_path() / "Daten.xlsx";
int threadIndex = 7;
}


class Thread {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 3;

        xlnt::workbook wb;
        wb.load(threadPath);
        xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

    static double Vc(int mat, int Dindex) {
        double Vc;

        int column = Dindex + 1;

        mat = mat + 3;

        xlnt::workbook wb;
        wb.load(threadPath);
        xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

        Vc = ws.cell(column, mat).value<double>();

        return Vc;
    }

    static QStringList dList() {
        QStringList D;
        int column = 2;

        xlnt::workbook wb;
        wb.load(threadPath);
        xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

        while (ws.cell(column, 1).to_string() != "") {
            D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
            column++;
        }

        return D;
    }

    static double threadPitch(int Dindex) {
        double pitch;
        int column;

        column = Dindex + 2;

        xlnt::workbook wb;
        wb.load(threadPath);
        xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

        pitch = ws.cell(column,2).value<double>();

        return pitch;
    }

    static double Diameter(int Dindex) {
        double D;
        int column;
        std::string temp;

        column = Dindex + 2;

        xlnt::workbook wb;
        wb.load(threadPath);
        xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

        temp = ws.cell(column,1).value<std::string>();
        temp = temp.erase(0,1);
        D = std::stod(temp);

        return D;
    }
};
