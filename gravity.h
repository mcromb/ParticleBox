#ifndef GRAVITY_H
#define GRAVITY_H

#include "force.h"
#include "Vector2.h"
#include "Particle.h"

#include <string>

class Gravity : public Force
{
public:
    Gravity();

    virtual ~Gravity();

    void ApplyForce(std::vector<Particle*>&);

    //could set gravitational constant to diff values
private:
    double fGConst = 9.80665; //m s-2
};

#endif // GRAVITY_H
