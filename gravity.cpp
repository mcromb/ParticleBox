/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Implementation of the Gravity force class
*/

#include "gravity.h"

#include "Vector2.h"
#include "Particle.h"

#include <vector>

Gravity::Gravity(): Force("Gravity") {}

Gravity::~Gravity(){

}

/* ***METHOD***
    Name:   ApplyForce
    IN:     particles - the particles subject to gravity
    About:  Adds the force due to the weight of the particle.
     Assumes gravity is acting straight downwards.
*/
void Gravity::ApplyForce(std::vector<Particle*>& particles){
    //gravitational constant, g, is the acceleration in y direction
    //Force is the weight (F = Mass*g) not just the acceleration
    Vector2 gravity = Vector2(0.0, -fGConst);
    Vector2 weight = gravity;
    for (unsigned int i =0; i < particles.size(); i++){
        weight = (particles[i]->GetMass())*gravity;
        particles[i]->AccumulateForce(weight);
    }
}
