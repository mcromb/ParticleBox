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

    //virtual void Render();

    void setWallStatus(int status) {fWallStatus = status;}

    void Print();

    //either straight from the vector or update member from the vector?
    int GetNParticles(){return fParticles.size();}

    Particle * GetComponent(int i){ return fParticles[i];}

    void fuel(int particles, Vector2 origin);
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

    void wallBounce(Particle*);


    void Update();
    double GetTimestep() const {return fTimestep;}
    void SetTimestep(double timestep) {fTimestep = (timestep);}

    //not const if changing forces
    const std::vector<Particle*> & GetParticles() const { return fParticles;}

private:
    std::vector<Particle*> fParticles;
    std::vector<Force*> fForces;
    //int fNParticles;
    //max particles? - vectors are dynamic thjo
    //total energy?

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
