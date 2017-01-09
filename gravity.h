#ifndef GRAVITY_H
#define GRAVITY_H

#include "force.h"
#include "Vector2.h"
#include <string>

class Gravity : public Force
{
public:
    Gravity();

    virtual ~Gravity();

    Vector2 ApplyForce();

    //could set gravitational constant to diff values
private:
    double fGConst = 9.80665; //m s-2
};

#endif // GRAVITY_H
