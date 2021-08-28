#include "Modules/module.h"

std::filesystem::path plan90Path = std::filesystem::current_path() / "Daten.xlsx";
int plan90Index = 4;

class Plan90 {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(plan90Path);
        xlnt::worksheet ws = wb.sheet_by_index(plan90Index);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

};
