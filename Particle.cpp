#include "Particle.h"
#include "Vector2.h"

#include <iostream>

Particle::Particle()
{
    fMass = 1;
    fRadius = 1;
}

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
