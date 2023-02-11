#include "Modules/thread.h"
#include "Modules/misc.h"

namespace  {
int threadIndex = 7;
}

QStringList Thread::matList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList mat;
    int row = 3;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

    while (!ws.cell(1, row).to_string().empty()) {
        mat.append(QString::fromStdString(ws.cell(1, row).to_string()));
        row++;
    }

    return mat;
}

double Thread::Vc(int mat, int column) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double Vc;

    column = column + 2;

    mat = mat + 3;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

    static bool warumWisoWeshalb = false;
    if(warumWisoWeshalb){
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
    }
    warumWisoWeshalb = true;

    Vc = ws.cell(column, mat).value<double>();

    return Vc;
}

QStringList Thread::dList() {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    QStringList D;
    int column = 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

    while (!ws.cell(column, 1).to_string().empty()) {
        D.append(QString::fromStdString(ws.cell(column, 1).to_string()));
        column++;
    }

    return D;
}

double Thread::threadPitch(int Dindex) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double pitch;
    int column;

    column = Dindex + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

    if(ws.cell(column, 2).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, 2).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }else if(ws.cell(column, 2).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, 2).reference().to_string()),
                          QString::fromStdString(ws.cell(column, 2).to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    pitch = ws.cell(column,2).value<double>();

    return pitch;
}

double Thread::Diameter(int Dindex) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double D;
    int column;
    QString rawRead;

    column = Dindex + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

    if(ws.cell(column, 1).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.\nDer Feler ist in der '%3' Funktion aufgetreten.")
                     .arg(QString::fromStdString(ws.cell(column, 1).reference().to_string()),
                          QString::fromStdString(ws.title()),
                          __FUNCTION__));
    }

    rawRead = QString::fromStdString(ws.cell(column,1).value<std::string>());

    if(rawRead.at(0) == 'M'){
        // Normales Gewinde
        D = rawRead.remove(0, 1).toDouble();
    }else if(rawRead.at(0) == 'G' && (rawRead.length() == 2)){
        // Zoelliges ganz zahliges Gewinde
        D = rawRead.remove(0, 1).toDouble() * 2.54;
    }else if(rawRead.at(0) == 'G' && (rawRead.length() > 2)){
        if(rawRead.at(2) == '/'){
            // Zoelliges Gewinde das kleiner als 1 Zoll ist (1/4, 1/8)
            D = (QString(rawRead.at(1)).toDouble() / QString(rawRead.at(3)).toDouble()) * 2.54;
            D = round(D * 1000) / 1000;
        }else if(rawRead.at(2) == ' ' && rawRead.at(4) == '/'){
            // Zoelliges Gewinde das groesser als 1 Zoll ist(1 1/2, 1 3/8)
            D = (QString(rawRead.at(1)).toDouble() + (QString(rawRead.at(3)).toDouble() / QString(rawRead.at(5)).toDouble())) * 2.54;
            D = round(D * 1000) / 1000;
        }else{
            qWarning() << "Es ist kein gültiger Type für das Gewinde in Zelle" << ws.cell(column, 1).reference().to_string() << "im Arbeitsblatt" << ws.title() << "angegeben";
            D = -1;
        }
    }else{
        qWarning() << "Es ist kein gültiger Type für das Gewinde in Zelle" << ws.cell(column, 1).reference().to_string() << "im Arbeitsblatt" << ws.title() << "angegeben";
        D = -1;
    }

    return D;
}
