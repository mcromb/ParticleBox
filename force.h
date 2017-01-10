#ifndef FORCES_H
#define FORCES_H

//#include "particlesystem.h"
#include "Vector2.h"

#include <string>

#include "Particle.h"

class Force
{
public:
    Force();

    virtual ~Force();

    virtual Vector2 ApplyForce(std::vector<Particle*> & ) = 0;

    const std::string& GetName() const {return fName;}
    void SetName(const std::string& name) {fName = name;}

private:

    std::string fName;
    //not a vector?
    //ParticleSystem* fParticleSystem;
    //int fDummy;
};

#endif // FORCES_H
