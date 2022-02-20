#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "Modules/createDatabase.cpp"
#include "Modules/settings.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SpaeneRechner_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    a.setApplicationName("SpaeneRechner");
    a.setApplicationVersion("v0.5.4");

    return a.exec();
}
