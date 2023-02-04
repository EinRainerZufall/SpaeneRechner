#include "Modules/dynamic.h"
#include "Modules/misc.h"

namespace  {
int dynamicIndex = 1;
}


QStringList Dynamic::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    while (!ws.cell(1, row).to_string().empty()) {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

double Dynamic::Vc(int mat, int bed) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;
    int column = bed + 2;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

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

double Dynamic::fz(int mat, int bed, double D) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double fz;
    int column = 5;

    mat = mat + 2;

    column = column + bed;

    if(D > 15) {
        column = column + 3;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

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

double Dynamic::ae(int mat, int bed, double D) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double ae;
    int column = 11;

    mat = mat + 2;

    column = column + bed;

    if(D > 15) {
        column = column + 3;
    }

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

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

    ae = ws.cell(column, mat).value<double>();

    return ae;
}

int Dynamic::Kc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    int Kc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    if(ws.cell(17, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(17, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(17, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(17, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(17, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Kc = ws.cell(17, mat).value<int>();

    return Kc;
}

double Dynamic::Mc(int mat) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Mc;

    mat = mat + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(dynamicIndex);

    if(ws.cell(18, mat).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(18, mat).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(18, mat).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(18, mat).reference().to_string()),
                          QString::fromStdString(ws.cell(18, mat).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    Mc = ws.cell(18, mat).value<double>();

    return Mc;
}
