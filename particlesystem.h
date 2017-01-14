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

#include <Particle.h>
#include <box.h>
#include <force.h>


typedef std::vector<Particle*>::iterator ParticleIterator;
typedef std::vector<Force*>::iterator ForceIterator;

class ParticleSystem
{
public:
    ParticleSystem();

    virtual ~ParticleSystem();

    //process input?
    //virtual?

    void setWallStatus(int status) {fWallStatus = status;}

    void wallBounce(Particle*);

    int GetNParticles(){return fParticles.size();}

    const std::vector<Particle*> & GetParticles() const { return fParticles;}

    Particle * GetComponent(int i){ return fParticles[i];}

    void ClearParticles();

    void fuel(int particles, Vector2 origin, double radius);
    //pointer to particle?

    //void AddParticle(Particle p); //or int particles

    //void RemParticle(int pn); //best way to access?

    void AddForce(Force* force);
    void RemoveForce(std::string name);

    Force* FindForce(std::string name);

    //void ComputeForce();
    //set force on all to zero then move through forces to compute
    //void Integrate(double dt); //RK2? calc and update accell, veloc
    //print method?
    void Print();

    void Update();
    double GetTimestep() const {return fTimestep;}
    void SetTimestep(double timestep) {fTimestep = (timestep);}

    //not const if changing forces


private:
    std::vector<Particle*> fParticles;
    std::vector<Force*> fForces;

    //max particles? - vectors are dynamic thjo

    Box fBox;
    //not pointer
    enum{
        kSolid,
        kPermeable
    };
    int fWallStatus;

    //fine clock if this is controlling class
    //#define MS_PER_UPDATE

    double fTimestep;

};

double randomFloat();

#endif // PARTICLESYSTEM_H
