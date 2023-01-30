#ifndef TURN_H
#define TURN_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Turn{
public:
    static QStringList matList();
    static double Vc(int mat, int bed, int typ);
    static int Kc(int mat);
    static double Mc(int mat);
};

#endif // TURN_H
