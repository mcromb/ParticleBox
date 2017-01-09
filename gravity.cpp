#include "gravity.h"
#include "Vector2.h"

Gravity::Gravity()
{
    fName = "Gravity";
}

Gravity::~Gravity(){

}

Vector2 Gravity::ApplyForce(){
    //add force in y direction -9.81 (fGConst)
    //only apply once each simulation or every iteration?
    //force/acceleration always adds to base value 9.81
    //or update v +=9.81*dt ?
    Vector2 gravity = Vector2(0.0, -fGConst);
    return gravity;
    //update x +=vx*dt etc?
}
