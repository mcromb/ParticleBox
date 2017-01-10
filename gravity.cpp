#include "gravity.h"

#include "Vector2.h"
#include "Particle.h"

#include <vector>

Gravity::Gravity(): Force("Gravity") {}

Gravity::~Gravity(){

}

void Gravity::ApplyForce(std::vector<Particle*>& particles){
    //add acceleration in y direction -9.81 (fGConst)
    //apply every iteration - recalculate all each time
    //force/acceleration always adds to base value 9.81
    //or update v +=9.81*dt ?
    //Force is the weight not acceleration
    Vector2 gravity = Vector2(0.0, -fGConst);
    Vector2 weight = gravity;
    for (unsigned int i =0; i < particles.size(); i++){
        weight = (particles[i]->GetMass())*gravity;
        particles[i]->AccumulateForce(weight);
    }
}
