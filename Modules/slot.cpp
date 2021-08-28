#include "Modules/module.h"

std::filesystem::path slotPath = std::filesystem::current_path() / "Daten.xlsx";
int slotIndex = 3;

class Slot {
public:
    static QStringList matList() {
        QStringList mat;
        int row = 2;

        xlnt::workbook wb;
        wb.load(slotPath);
        xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

        while (ws.cell(1, row).to_string() != "") {
            mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
            row++;
        }

        return mat;
    }
};
