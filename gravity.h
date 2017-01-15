/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: 'Gravity' class that calculates the weight of particles
    within a constant gravity field
*/

#ifndef GRAVITY_H
#define GRAVITY_H

#include "force.h"
#include "Vector2.h"
#include "Particle.h"

#include <string>
#include <vector>

class Gravity : public Force
{
public:
    Gravity();

    virtual ~Gravity();

    void ApplyForce(std::vector<Particle*>&);

    void SetGravity(double grav) {fGConst = grav;}

    double GetGEarth() {return fGEarth;}

private:
    double fGConst = 9.80665;   //initialising to earth's
    const double fGEarth = 9.80665; //m s-2
};

#endif // GRAVITY_H
