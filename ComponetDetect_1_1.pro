#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T10:00:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComponetDetect_1_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

FORMS += \
    src/dialog.ui

HEADERS += \
    src/dialog.h \
    src/gui.h \
    src/forcesensor.h \
    src/common.h \
    src/system.h \
    src/robot.h

SOURCES += \
    src/dialog.cpp \
    src/gui.cpp \
    src/main.cpp \
    src/forcesensor.cpp \
    src/common.cpp \
    src/system.cpp \
    src/robot.cpp \
    3rd-party/NI-ATI/ATIDAQ/dom.c \
    3rd-party/NI-ATI/ATIDAQ/expatls.c \
    3rd-party/NI-ATI/ATIDAQ/ftconfig.c \
    3rd-party/NI-ATI/ATIDAQ/ftrt.c \
    3rd-party/NI-ATI/ATIDAQ/node.c \
    3rd-party/NI-ATI/ATIDAQ/stack.c \
    3rd-party/NI-ATI/ATIDAQ/xmlparse.c \
    3rd-party/NI-ATI/ATIDAQ/xmlrole.c \
    3rd-party/NI-ATI/ATIDAQ/xmltok.c


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rd-party/NI-ATI/NIDAQ/lib/msvc/ -lNIDAQmx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rd-party/NI-ATI/NIDAQ/lib/msvc/ -lNIDAQmxd

INCLUDEPATH += $$PWD/3rd-party/NI-ATI/NIDAQ/lib/msvc
DEPENDPATH += $$PWD/3rd-party/NI-ATI/NIDAQ/lib/msvc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rd-party/motocom32/ -lMOTOCOMES
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rd-party/motocom32/ -lMOTOCOMESd

INCLUDEPATH += $$PWD/3rd-party/motocom32
DEPENDPATH += $$PWD/3rd-party/motocom32
