QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
CONFIG += static

gcc:CONFIG += staticlib
linux-clang:CONFIG += staticlib

INCLUDEPATH += $$PWD/xlnt/


#Debug / Release difference
CONFIG(release, debug|release) {
  message( "release" )
  win32: LIBS += -L$$PWD/x64-Release/source
  win32: LIBS += -lxlnt
}
CONFIG(debug, debug|release) {
  message( "debug" )
  win32: LIBS += -L$$PWD/x64-Debug/source
  win32: LIBS += -lxlntd
}

#Icon unter Win
RC_ICONS = endmill_altin.ico

#Icon unter MacOS
#ICON = myapp.icns <- noch nicht getestet

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Modules/createDatabase.cpp \
    Modules/drill.cpp \
    Modules/dynamic.cpp \
    Modules/plan.cpp \
    Modules/settings.cpp \
    Modules/simple.cpp \
    Modules/slot.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Modules/module.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Daten.xlsx \

RESOURCES += \
    ressources.qrc
