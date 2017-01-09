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
    ui->setupUi(this);
    setStyleSheet("background-color:white");
    setAutoFillBackground(false);
    setWindowTitle(std::string("Box").c_str());

    //Use a timer to trigger a call of update every 10ms
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    show();
    //Prevent implicit redraw of the background
    //setAttribute(Qt::WA_OpaquePaintEvent);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //translate coord system so centre is 0,0
    painter.translate(width()/2, height()/2);
    //scale co-ord system so sides are -1,1
    //(box is -1 to 1)


    //painter.fillRect(QRect(0,0,width() - 1, height() - 1), QPalette::Text);

    //Vector2 position = fParticle->GetPosition();
    //double fScale = 1 / width();

    painter.setPen(palette().dark().color());
//    painter.drawEllipse(0, 0, 1, 1);
//    painter.drawEllipse(-5*0.05*width(), -(-5*0.05*height()), 1, 1);

    if(fParticleSystem){
        int NParticles = fParticleSystem->GetNParticles();
        for (int iP = 0; iP < NParticles; iP++) {
            //Get the position of each particle
            Vector2 position = fParticleSystem->GetComponent(iP)->GetPosition();
//    		std::cout << fScale << " "; position.Print();}
            //Set the color
            painter.setPen(Qt::blue);
            painter.setBrush(Qt::blue);
            //Draw a dark dot
            //minus needed due to coord system)
            painter.drawEllipse(position.x()*0.05*width(), -position.y()*0.05*width(), 3,3);
            //std::cout << "Point drawn" << std::endl;
        }
    }

}
