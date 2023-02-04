#include "Modules/drill.h"
#include "Modules/misc.h"

namespace  {
int drillIndex = 2;
}


QStringList Drill::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(drillIndex);

    while (ws.cell(1, row).to_string() != "") {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

double Drill::Vc(int mat, int bed, int schn) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;
    int column = 2;

    mat = mat + 2;

    switch (bed) {
    case 2:
        column = column + 2;
        break;
    case 1:
        column = column + 1;
        break;
    default: //0
        column = column + 0;
        break;
    }

    switch (schn) {
    case 1:
        column = column + 3;
        break;
    default:
        column = column + 0;
        break;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(drillIndex);

    if(ws.cell(column, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(column, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(column, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Vc = ws.cell(column, mat).value<double>();

    return Vc;
}

double Drill::fu(int mat, double D) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fu;
    int column;

    mat = mat +2;

    if(D >= 16) {
        column = 12;
    }else if(D >= 12) {
        column = 11;
    }else if(D >= 8) {
        column = 10;
    }else if(D >= 5) {
        column = 9;
    }else { //D >= 2
        column = 8;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(drillIndex);

    if(ws.cell(column, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(column, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(column, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    fu = ws.cell(column, mat).value<double>();

    return fu;
}

int Drill::Kc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    int Kc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(drillIndex);

    if(ws.cell(13, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(13, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(13, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(13, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(13, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Kc = ws.cell(13, mat).value<int>();

    return Kc;
}

double Drill::Mc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Kc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(drillIndex);

    if(ws.cell(14, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(14, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(14, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(14, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(14, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Kc = ws.cell(14, mat).value<double>();

    return Kc;
}
