#ifndef SETTINGS_H
#define SETTINGS_H

#include <QCoreApplication>
#include <xlnt/xlnt.hpp>
#include <QMessageBox>
#include <QSysInfo>
#include <QStandardPaths>
#include <QSettings>
#include <QFile>

class Settings{
public:
    static void showDis();
    static bool readDis();
    static int maxRpmFr();
    static int maxRpmDr();
    static double maxKw();
    static double maxKwDr();
    static int condition();
    static int cutMat();
    static int angleDrill();
    static int cooling();
    static bool xlsxCheck();
    static void write(int dis, int maxRpmFr, double maxKw, int con, int cutMat, int spiWi, int cooling, int maxRpmDr, double maxKwDr, int index, bool update);
    static bool INIcheck();
    static void create();
    static int readIndex();
    static bool autoUpdate();
    static void deleteAll();
    static void test();
};

#endif // SETTINGS_H
