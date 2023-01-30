#ifndef DRILL_H
#define DRILL_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Drill{
public:
    static QStringList matList();
    static double Vc(int mat, int bed, int schn);
    static double fu(int mat, double D);
    static int Kc(int mat);
    static double Mc(int mat);
};

#endif // DRILL_H
