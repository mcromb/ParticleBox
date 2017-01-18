/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Particle system class that contains a set of particles,
     the box containing the particles, and the forces active in the system
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

    void SetWallDamping(double damping) {fWallDamping = damping;}

    const Box & GetBox() const {return fBox;}

    void SetWallStatus(int status) {fWallStatus = status;}

    double GetTimestep() const {return fTimestep;}
    void SetTimestep(double timestep) {fTimestep = (timestep);}

    void Print();

private:
    std::vector<Particle*> fParticles;
    std::vector<Force*> fForces;

    //Limits number of colliding particles
    //The program can deal with ~150 before lagging
    int fMaxColliding = 150;

    double fMaxSpeed = 3.0;

    double fWallDamping = 0.95; //1 corresponds to no damping

    Box fBox;

    enum{
        kSolid,
        kPermeable
    };
    int fWallStatus;

    double fTimestep;
};

double RandomDouble();

#endif // PARTICLESYSTEM_H
