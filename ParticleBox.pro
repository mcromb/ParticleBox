QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp \
    Vector2.cpp \
    Particle.cpp \
    particlesystem.cpp \
    box.cpp \
    gravity.cpp \
    force.cpp \
    displaywindow.cpp \
    controlwindow.cpp \
    collision.cpp

HEADERS += \
    Vector2.h \
    Particle.h \
    particlesystem.h \
    box.h \
    gravity.h \
    force.h \
    displaywindow.h \
    controlwindow.h \
    collision.h

FORMS += \
    displaywindow.ui \
    controlwindow.ui
