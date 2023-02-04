#include "Modules/slot.h"
#include "Modules/misc.h"

namespace  {
int slotIndex = 3;
}

QStringList Slot::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    while (!ws.cell(1, row).to_string().empty()) {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

QStringList Slot::dList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList D;
    int column = 5;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    while (!ws.cell(column, 1).to_string().empty()) {
        if(ws.cell(column, 1).data_type() != xlnt::cell_type::number){
            Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                         QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                     "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                         .arg(QString::fromStdString(ws.cell(column, 1).reference().to_string()),
                              QString::fromStdString(ws.cell(column, 1).to_string()),
                              QString::fromStdString(ws.title()),
                              __FUNCTION__));
            exit(2);
        }else{
            D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
            column++;
        }
    }

    return D;
}

double Slot::Vc(int row) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    if(ws.cell(4, row).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(4, row).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(4, row).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(4, row).reference().to_string()),
                          QString::fromStdString(ws.cell(4, row).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Vc = ws.cell(4, row).value<double>();

    return Vc;
}

double Slot::fz(int column, int row) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fz;

    column = column + 5;
    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    if(ws.cell(column, row).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, row).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(column, row).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, row).reference().to_string()),
                          QString::fromStdString(ws.cell(column, row).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    fz = ws.cell(column, row).value<double>();

    return fz;
}

double Slot::Kc(int row){
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Kc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    if(ws.cell(2, row).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(2, row).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(2, row).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(2, row).reference().to_string()),
                          QString::fromStdString(ws.cell(2, row).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Kc = ws.cell(2, row).value<double>();

    return Kc;
}

double Slot::Mc(int row){
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Mc;

    row = row + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(slotIndex);

    if(ws.cell(3, row).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(3, row).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(3, row).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(3, row).reference().to_string()),
                          QString::fromStdString(ws.cell(3, row).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Mc = ws.cell(3, row).value<double>();

    return Mc;
}
