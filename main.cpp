/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Implementation of the display window of the GUI,
     showing the state of the system of balls
*/

#include <iostream>

#include <QApplication>

#include "displaywindow.h"
#include "controlwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow w;
    w.show();

    return a.exec();
}
