TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core
QT += sql

HEADERS += pet.h \
           petowner.h \
shelter.h \
    simplecrypt.h \
    globals.h \
    shelterowner.h

SOURCES += main.cpp \
           pet.cpp \
           petowner.cpp \
shelter.cpp \
    simplecrypt.cpp \
    globals.cpp \
    shelterowner.cpp

