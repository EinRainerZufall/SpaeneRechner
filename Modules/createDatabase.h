#ifndef CREATEDATABASE_H
#define CREATEDATABASE_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QStandardPaths>
#include <QFile>

class createDatabase{
public:
    static void createSimple();
    static void createDynamic();
    static void createDrill();
    static void createSlot();
    static void createPlan90();
    static void createPlan45();
    static void createTurn();
    static void createThread();
    static void deleteWorkbook();
};

#endif // CREATEDATABASE_H
