#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Dynamic{
public:
    static QStringList matList();
    static double Vc(int mat, int bed);
    static double fz(int mat, int bed, double D);
    static double ae(int mat, int bed, double D);
    static int Kc(int mat);
    static double Mc(int Mat);
};

#endif // DYNAMIC_H
