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
    walls.cpp \
    gravity.cpp \
    clock.cpp \
    force.cpp \
    displaywindow.cpp \
    controlwindow.cpp \
    interaction.cpp \
    collision.cpp

HEADERS += \
    Vector2.h \
    Particle.h \
    particlesystem.h \
    box.h \
    walls.h \
    gravity.h \
    clock.h \
    force.h \
    displaywindow.h \
    controlwindow.h \
    interaction.h \
    collision.h

FORMS += \
    displaywindow.ui \
    controlwindow.ui
