#include "Modules/plan.h"
#include "Modules/misc.h"

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

    if(ws.cell(bed, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(bed, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(bed, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(bed, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(bed, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

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

    Mc = ws.cell(column, mat).value<double>();

    return Mc;
}

