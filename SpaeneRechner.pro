QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++14
CONFIG += static

gcc:CONFIG += staticlib
linux-clang:CONFIG += staticlib

INCLUDEPATH += $$PWD/xlnt/

#Debug / Release difference
CONFIG(release, debug|release) {
  message("building in release")
  win32: LIBS += -L$$PWD/x64-Release/source
  win32: LIBS += -lxlnt
}
CONFIG(debug, debug|release) {
  message("building in debug")
  win32: LIBS += -L$$PWD/x64-Debug/source
  win32: LIBS += -lxlntd
}

win32 {
    message("building for Windows")
    #Icon unter Win
    RC_ICONS = src/endmill_altin.ico

    #die xlnt.dll in den release Ordner kopieren
    copydata.commands = $(COPY_FILE) \"$$shell_path($$PWD\\x64-Release\source\xlnt.dll)\" \"$$shell_path($$OUT_PWD\release)\"
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
}

macx {
    message("building for MacOS")
    #Icon unter MacOS
    #ICON = src/endmill_altin.icns <- noch nicht getestet
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Modules/createDatabase.cpp \
    Modules/drill.cpp \
    Modules/dynamic.cpp \
    Modules/misc.cpp \
    Modules/plan.cpp \
    Modules/settings.cpp \
    Modules/simple.cpp \
    Modules/slot.cpp \
    Modules/thread.cpp \
    Modules/turn.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Modules/createDatabase.h \
    Modules/drill.h \
    Modules/dynamic.h \
    Modules/misc.h \
    Modules/plan.h \
    Modules/settings.h \
    Modules/simple.h \
    Modules/slot.h \
    Modules/thread.h \
    Modules/turn.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    SpaeneRechner_de_DE.ts \
    SpaeneRechner_en_EN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

QMAKE_EXTRA_TARGETS += first copydata
