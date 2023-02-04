#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "Modules/createDatabase.cpp"
#include "Modules/settings.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("SpaeneRechner");
    QCoreApplication::setApplicationVersion("0.7.4");
    QCoreApplication::setOrganizationDomain("https://github.com/EinRainerZufall/SpaeneRechner");

    qDebug() << "Das Programm wurde mit QT Version:" << QT_VERSION_STR << "kompiliert!";
    qDebug() << "Das Kompilierungsdatum ist der:" << __DATE__ << "um:" << __TIME__;

    QApplication a(argc, argv);
    MainWindow w;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SpaeneRechner_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    w.show();

    return a.exec();
}
