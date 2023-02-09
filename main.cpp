#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QTime>
#include <QDate>
#include <QMutex>

#include "Modules/createDatabase.cpp"
#include "Modules/settings.cpp"

const QString logFileName = "debug.log";

void customeMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){

    static QMutex mutex;
    QMutexLocker lock(&mutex);

    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
    QByteArray localMsg = msg.toLocal8Bit();
    QByteArray time = QTime::currentTime().toString("hh:mm:ss.zzz").toLocal8Bit();
    QByteArray date = QDate::currentDate().toString("yyyy-MM-dd").toLocal8Bit();
    QString logLevelName = msgLevelHash[type];
    QByteArray logLevelMsg = logLevelName.toLocal8Bit();

#ifdef QT_DEBUG
    bool logToFile = false;
#else
    bool logToFile = true;
#endif

    if(logToFile){
        QString txt = QString("%0  %1 | %2: %3 (%4)").arg(date, time, logLevelName, msg,  context.file);
        QFile out(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/.log");
        out.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream stream(&out);
        stream << txt << Qt::endl;
    }else{
        fprintf(stderr, "%s  %s | %s: %s (%s:%u, %s)\n", date.constData(), time.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
        fflush(stderr);
    }

    if(type == QtFatalMsg){abort();}
}

int main(int argc, char *argv[]){
    qInstallMessageHandler(customeMessageOutput);
    QCoreApplication::setApplicationName("SpaeneRechner");
    QCoreApplication::setApplicationVersion("0.7.4");
    QCoreApplication::setOrganizationDomain("https://github.com/EinRainerZufall/SpaeneRechner");

    qInfo() << "Das Programm wurde mit QT Version:" << QT_VERSION_STR << "kompiliert!";
    qInfo() << "Kompiliert wurde am:" << __DATE__ << "um:" << __TIME__ << "Uhr";

    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle(w.windowTitle() +" "+ QCoreApplication::applicationVersion());
    w.setWindowIcon(QIcon(":/img/src/endmill_altin.ico"));

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
