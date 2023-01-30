#ifndef THREAD_H
#define THREAD_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStringList>
#include <QStandardPaths>

class Thread{
public:
    static QStringList matList();
    static double Vc(int mat, int Dindex);
    static QStringList dList();
    static double threadPitch(int Dindex);
    static double Diameter(int Dindex);
};

#endif // THREAD_H
