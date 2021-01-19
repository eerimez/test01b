TARGET = model
TEMPLATE = lib
CONFIG += shared c++14 x86_64
QT += sql qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers
DEPENDPATH  += ../helpers
LIBS += -L../lib -lhelper
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)
HEADERS += sqlobjects/tabelle001object.h
HEADERS += tabelle001.h
SOURCES += tabelle001.cpp
HEADERS += sqlobjects/tabelle002object.h
HEADERS += tabelle002.h
SOURCES += tabelle002.cpp
