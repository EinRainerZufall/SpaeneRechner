#include "Modules/turn.h"
#include "Modules/misc.h"

namespace  {
int turnIndex = 6;
}

QStringList Turn::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

    while (ws.cell(1, row).to_string() != "") {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

double Turn::Vc(int mat, int bed, int typ) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;
    int column = 2;

    mat = mat + 2;

    column = column + bed;

    switch (typ) {
    case 2:
        column = column + 6;
        break;
    case 1:
        column = column + 3;
        break;
    default:
        column = column + 0;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

    if(ws.cell(column, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(column, mat).reference().to_string()),
                                                                              QString::fromStdString(ws.title())));
    }else if(ws.cell(column, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(column, mat).reference().to_string()),
                                                                              QString::fromStdString(ws.cell(column, mat).to_string()),
                                                                              QString::fromStdString(ws.title())));
    }

    Vc = ws.cell(column, mat).value<double>();

    return Vc;
}

int Turn::Kc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    int Kc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

    if(ws.cell(11, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(11, mat).reference().to_string()),
                                                                              QString::fromStdString(ws.title())));
    }else if(ws.cell(11, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(11, mat).reference().to_string()),
                                                                              QString::fromStdString(ws.cell(11, mat).to_string()),
                                                                              QString::fromStdString(ws.title())));
    }

    Kc = ws.cell(11, mat).value<int>();

    return Kc;
}

double Turn::Mc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Mc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(turnIndex);

    if(ws.cell(12, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(12, mat).reference().to_string()),
                                                                              QString::fromStdString(ws.title())));
    }else if(ws.cell(12, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(12, mat).reference().to_string()),
                                                                              QString::fromStdString(ws.cell(12, mat).to_string()),
                                                                              QString::fromStdString(ws.title())));
    }

    Mc = ws.cell(12, mat).value<double>();

    return Mc;
}
