#include <iostream>

#include <Particle.h>
#include <particlesystem.h>
#include <Vector2.h>
#include "gravity.h"

#include <thread>
#include <chrono>

#include <QApplication>
#include <displaywindow.h>
#include <controlwindow.h>
#include <QTimer>

void dostuff();

int main(int argc, char *argv[])
{
//    Particle ball;
//    Vector2 position = Vector2(0,0);
//    Vector2 velocity = Vector2(0.4,0.4);
//    Vector2 force = Vector2(-0.1,0.1);

//    ball.Print();

//    std::cout << "Mass" << ball.GetMass() << std::endl;
//    std::cout << "Radius" << ball.GetRadius() << std::endl;

//    ball.SetPosition(position);
//    ball.SetVelocity(velocity);
//    ball.SetForce(force);

//    ball.Print();
    QApplication a(argc, argv);
    ControlWindow w;
    w.show();

    //dostuff();

    return a.exec();
}


void dostuff () {
    ParticleSystem system;

    DisplayWindow* Win = new DisplayWindow((ParticleSystem*)&system);

    std::cout << "Particles: " << system.GetNParticles() << std::endl;

    system.fuel(2, Vector2(0.0,0.0));

    std::cout << "Particles: " << system.GetNParticles() << std::endl;

    Gravity *grav = new Gravity();
    system.AddForce(grav);

    //std::this_thread::sleep_for(std::chrono::milliseconds(20));

    for (int i =0; i < 10; i++){
        system.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Particles: " << system.GetNParticles() << std::endl;

//    system.Update();
//    system.Print();

//    std::cout << "Particles: " << system.GetNParticles() << std::endl;

//    system.Update();
//    system.Print();

//    std::cout << "Particles: " << system.GetNParticles() << std::endl;
//    system.Update();
//    system.Print();
//    std::cout << "Particles: " << system.GetNParticles() << std::endl;

}
