/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Implementation of the Particle class
*/

#include "Particle.h"
#include "Vector2.h"

#include <iostream>

Particle::Particle()
{
    //Mass and radius initialised in header
}

Particle::Particle(double mass,
                   double radius,
                   Vector2 pos,
                   Vector2 vel,
                   Vector2 force):
    fMass(mass),
    fRadius(radius),
    fPosition(pos),
    fVelocity(vel),
    fForce(force) {}

Particle::~Particle(){
}

void Particle::Print() const{
    std::cout << "Mass: " << fMass << std::endl;
    std::cout << "Radius: " << fRadius <<std::endl;
    std::cout << "Position: " << std::endl;
    fPosition.Print();
    std::cout << "Velocity: " << std::endl;
    fVelocity.Print();
    std::cout << "Force: " << std::endl;
    fForce.Print();
}
