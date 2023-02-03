#include "Modules/thread.h"
#include "Modules/misc.h"

namespace  {
int threadIndex = 7;
bool warumWisoWeshalb = false;
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

    if(warumWisoWeshalb){
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
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(column, 2).reference().to_string()),
                                                                              QString::fromStdString(ws.title())));
    }else if(ws.cell(column, 2).data_type() != xlnt::cell_type::number){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert '%1' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(column, 2).reference().to_string()),
                                                                              QString::fromStdString(ws.cell(column, 2).to_string()),
                                                                              QString::fromStdString(ws.title())));
    }

    pitch = ws.cell(column,2).value<double>();

    return pitch;
}

double Thread::Diameter(int Dindex) {
    const std::string file = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).toStdString() + "/Daten.xlsx";
    double D;
    int column;
    std::string metrisch;
    std::string zoll1;
    std::string zoll2;
    std::string zoll3;
    std::string zollTest1;
    std::string zollTest2;
    std::string type;

    column = Dindex + 2;

    xlnt::workbook wb;
    wb.load(file);
    xlnt::worksheet ws = wb.sheet_by_index(threadIndex);

    if(ws.cell(column, 1).to_string().empty()){
        Misc::MSGbox(QObject::tr("Ungültiges Format"), QObject::tr("Eine Zelle hat einen ungültigen / nicht erlaubten Inhalt"), 4, 1,
                     QObject::tr("Die Zelle '%0' hat den Wert 'NULL' der nicht erlaubt ist."
                                 "\nDie Zelle ist im Arbeitsblatt '%2'.").arg(QString::fromStdString(ws.cell(column, 1).reference().to_string()),
                                                                              QString::fromStdString(ws.title())));
    }

    metrisch = ws.cell(column,1).value<std::string>();

    type = metrisch;
    type = type.erase(1,99);

    if(type == "M"){
        metrisch = metrisch.erase(0,1);
        D = std::stod(metrisch);
    }else if(type == "G" & (metrisch.length() > 2)){
        zoll1 = metrisch;
        zoll2 = metrisch;
        zoll3 = metrisch;

        // Test 1
        zollTest1 = metrisch;
        zollTest1 = zollTest1.erase(0,2);
        zollTest1 = zollTest1.erase(1,99);

        // Test 2
        zollTest2 = metrisch;
        zollTest2 = zollTest2.erase(0,3);
        zollTest2 = zollTest2.erase(1,99);

        if(zollTest1 == "/"){
            zoll1 = zoll1.erase(0,1);
            zoll1 = zoll1.erase(1,99);

            zoll2 = zoll2.erase(0,3);

            D = (std::stod(zoll1) / std::stod(zoll2)) * 2.54;
        }else if(zollTest2 == "/"){
            zoll1 = zoll1.erase(0,1);
            zoll1 = zoll1.erase(1,99);

            zoll2 = zoll2.erase(0,2);
            zoll2 = zoll2.erase(1,99);

            zoll3 = zoll3.erase(0,4);

            D = (std::stod(zoll1) + (std::stod(zoll2) / std::stod(zoll3))) * 2.54;
        }else{
            D = -1;
        }
    }else if(type == "G" & (metrisch.length() == 2)){
        zoll1 = metrisch;
        zoll1 = zoll1.erase(0,1);
        D = std::stod(zoll1) * 2.54;
    }else{
        D = -1;
    }

    return D;
}
