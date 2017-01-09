#ifndef FORCES_H
#define FORCES_H

//#include "particlesystem.h"
#include "Vector2.h"

#include <string>

class Force
{
public:
    Force();

    virtual ~Force();

    virtual Vector2 ApplyForce() = 0;
    virtual std::string GetName() = 0;

private:
    //not a vector?
    //ParticleSystem* fParticleSystem;
    //int fDummy;
};

#endif // FORCES_H
