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
    About:
*/
void Gravity::ApplyForce(std::vector<Particle*>& particles){
    //add acceleration in y direction -9.81 (fGConst)
    //Force is the weight not acceleration
    Vector2 gravity = Vector2(0.0, -fGConst);
    Vector2 weight = gravity;
    for (unsigned int i =0; i < particles.size(); i++){
        weight = (particles[i]->GetMass())*gravity;
        particles[i]->AccumulateForce(weight);
    }
}
