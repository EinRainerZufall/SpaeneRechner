#ifndef PLAN_H
#define PLAN_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Plan{
public:
    static QStringList matList(int schnForm);
    static double Vc(int mat, int bed, int schnForm);
    static double fz(int mat, int bed, int schnForm, double D, double Ae);
    static int Kc(int mat, int schnForm);
    static double Mc(int mat, int schnForm);
};

#endif // PLAN_H
