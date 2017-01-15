/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Implementation of the display window of the GUI,
     showing the state of the system of balls
*/

#include "displaywindow.h"
#include "ui_displaywindow.h"

#include "Vector2.h"
#include "particlesystem.h"
#include "Particle.h"

#include <iostream>

#include <QPainter>
#include <QTimer>

DisplayWindow::DisplayWindow(ParticleSystem* sys, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow), fParticleSystem(sys)
{
    fBoxSize = fParticleSystem->GetBox().GetWidth();

    ui->setupUi(this);
    setStyleSheet("background-color:white");
    setAutoFillBackground(false);
    setWindowTitle(std::string("Box").c_str());

    //Use a timer to trigger a call of update every 10ms
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    show();

    //calculate width after opening window
    fScale = (this->height())/(fBoxSize);
}

DisplayWindow::~DisplayWindow()
{
    //constructor has placed ui on heap
    //so destructor must delete to prevent memory leak
    delete ui;
}

/* ***METHOD***
    Name:  paintEvent
    About: Draws the current state of the particle system into the display window.
*/
void DisplayWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //translate coord system so the centre is 0,0
    painter.translate((width()/2), (height()/2));

    //Set the color (for all particles)
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);

    //if there is a particle system to show, draw each particle in it
    if(fParticleSystem){
        int NParticles = fParticleSystem->GetNParticles();
        for (int iP = 0; iP < NParticles; iP++) {
            //Get the position and radius of each particle
            Vector2 position = fParticleSystem->GetComponent(iP)->GetPosition();
            double radius = fParticleSystem->GetComponent(iP)->GetRadius();
            double pxDiameter = 2*radius*fScale;
            //draw a circle at each particle position
            //(minus y needed due to QT coord system)
            painter.drawEllipse(position.x()*fScale, -position.y()*fScale, pxDiameter, pxDiameter);
        }
    }
}
