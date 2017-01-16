/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Starts the application by opening the control window
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
