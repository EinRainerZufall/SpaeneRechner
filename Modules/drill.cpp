#include "Modules/module.h"

std::filesystem::path drillPath = std::filesystem::current_path() / "Daten.xlsx";
int drillIndex = 2;

class Drill {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(drillPath);
        xlnt::worksheet ws = wb.sheet_by_index(drillIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

};
