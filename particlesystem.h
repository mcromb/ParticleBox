/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Particle system class that contains a set of particles,
     the container of the particles, and the forces active in the system
*/

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include <string>

#include "Particle.h"
#include "box.h"
#include "force.h"

typedef std::vector<Particle*>::iterator ParticleIterator;
typedef std::vector<Force*>::iterator ForceIterator;

class ParticleSystem
{
public:
    ParticleSystem();

    virtual ~ParticleSystem();

    void Update();

    void WallBounce(Particle*);

    //particle access/interaction methods
    int GetNParticles(){return fParticles.size();}

    const std::vector<Particle*> & GetParticles() const { return fParticles;}

    Particle * GetComponent(int i){ return fParticles[i];}

    void AddParticles(int particles, Vector2 origin, double radius);

    void ClearParticles();

    //other access methods
    void AddForce(Force* force);
    Force* FindForce(std::string name);
    void RemoveForce(std::string name);

    double GetMaxColliding() const {return fMaxColliding;}

    void SetWallStatus(int status) {fWallStatus = status;}

    double GetTimestep() const {return fTimestep;}
    void SetTimestep(double timestep) {fTimestep = (timestep);}

    void Print();

private:
    std::vector<Particle*> fParticles;
    std::vector<Force*> fForces;

    int fMaxColliding = 150;

    Box fBox;

    enum{
        kSolid,
        kPermeable
    };
    int fWallStatus;

    double fTimestep;
};

double randomFloat();

#endif // PARTICLESYSTEM_H
