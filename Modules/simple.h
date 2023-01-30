#ifndef SIMPLE_H
#define SIMPLE_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Simple{
public:
    static QStringList matList();
    static QStringList dList();
    static double Vc(int row);
    static double fz(int column, int row);
};

#endif // SIMPLE_H
