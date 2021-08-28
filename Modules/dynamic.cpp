#include "Modules/module.h"

std::filesystem::path dynamicPath = std::filesystem::current_path() / "Daten.xlsx";
int dynamicIndex = 1;

class Dynamic {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(dynamicPath);
        xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }

};
