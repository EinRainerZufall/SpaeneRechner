#ifndef SLOT_H
#define SLOT_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Slot{
public:
    static QStringList matList();
    static QStringList dList();
    static double Vc(int row);
    static double fz(int column, int row);
    static double Kc(int row);
    static double Mc(int row);
};

#endif // SLOT_H
