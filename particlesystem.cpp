#include "particlesystem.h"

#include "box.h"
#include "Vector2.h"

#include <cstdlib>
#include <algorithm>


ParticleSystem::ParticleSystem()
{
    //not ideal - use a default box constructor here?
    fBox = Box(Vector2(-10,-10), Vector2(10,10));
    fWallStatus = kPermeable;
    fTimestep = 0.01;
}

ParticleSystem::~ParticleSystem()
{
//remove vector of particles? - and the particles themselves (not just the pointers)
}

double randomFloat()
{
      double r = (double)rand()/(double)RAND_MAX;
      return r;
}

void ParticleSystem::fuel( int particles, Vector2 origin )
{
    //float angle;
    Particle* particle;
    for( int i = 0; i < particles; i++ )
    {
        //heap allocation - make sure no memory leak
        particle = new Particle();
        particle->SetPosition(origin);

        //for any direction
        //for one direction remove offset
        particle->SetVelocity(Vector2(-3+6*randomFloat(),-3+6*randomFloat()));
        //particle->SetVelocity(Vector2(0.5,0.5)); // Easily detected

        //randomise this velocity

        if( particle->GetVelocity() == Vector2(0.0, 0.0) )
        {
            delete particle;
            continue;
        }

        fParticles.push_back( particle );
    }
}

void ParticleSystem::AddForce(Force *force){
    fForces.push_back( force );
}

void ParticleSystem::RemoveForce(std::string name){
    //hmm
    //could use find force instead
    auto it = std::find_if( fForces.begin(), fForces.end(), [&name](Force* force) {return force->GetName() == name;});
    if (it != fForces.end())
    {
        // found element. it is an iterator to the first matching element.
        delete (*it);
        //returns iterator to element after the erased one
        it = fForces.erase( it );
        //if multiple with same name - keep going
    }
}

//more than one force with same name?
//can prevent when adding forces - check unique
Force* ParticleSystem::FindForce(std::string name){
    Force* force = NULL;
    for (unsigned int i =0; i < fForces.size(); i++){
        if(fForces[i]->GetName().compare(name) == 0){
            force = fForces[i];
        }
    }
    if (force == NULL){
        printf("Error, force not found\n");
        //will return NULL
    }
    return force;
}

void ParticleSystem::Update() {
    //elapsed time or just timestep?

    //force at this point has to be zero
    //either loop through and blank all the particles force
    //or set force to zero at end
    for (ForceIterator fit = fForces.begin(); fit != fForces.end(); fit++){
        (*fit)->ApplyForce(fParticles);
    }

    for( ParticleIterator it = fParticles.begin(); it != fParticles.end();)
    {
        //set position or velocity first?

        //suvat assumes constant acceleration within timestep
        //s = ut + 0.5 at^2
        //v = u + at

        //conversion factor of pixels per second?
        //position += velocity*time?
        Vector2 pos = (*it)->GetPosition();
        Vector2 vel = (*it)->GetVelocity();
        Vector2 accel = ((*it)->GetForce())*(1/(*it)->GetMass());

        pos += fTimestep*vel + 0.5*accel*fTimestep*fTimestep;
        (*it)->SetPosition(pos);

        //get velocity then += force*timestep ?
        vel += fTimestep*accel;
        (*it)->SetVelocity(vel);

        //clear forces for next update
        (*it)->SetForce(Vector2(0.0,0.0));

        //if particle is outside the box - delete
        //need to deref arg again?
        if( !fBox.InsideBox(**it)){
            if(fWallStatus == kPermeable)
            {
                delete (*it);
                //returns iterator to element after the erased one so should not increment it after this
                it = fParticles.erase( it );
                //if at the end, exit (not really a necessary check)
                if( it == fParticles.end() ) return;
            } else {
                //bounce
                wallBounce(*it);
                //increment here due to erasure in other arm
                it++;
            }
         }else {
            it++;
        }
    }
}

void ParticleSystem::wallBounce(Particle* p) {
    //simple wall bounce (many flaws) - if force pulling outof box, could get trapped outside
    //also no way to get particles to stay at bottom
    //should use particle radii etc
    double damping = 0.95;

    if (( (p->GetPosition()).X() <= fBox.GetLBound().X() )
        || ( (p->GetPosition()).X() >= fBox.GetUBound().X() ) )
    {
        //reverse X velocity
        p->SetVelocity(damping*Vector2(-(p->GetVelocity().X()), (p->GetVelocity().Y())));
    }
    if (( (p->GetPosition()).Y() <= fBox.GetLBound().Y() )
        || ( (p->GetPosition()).Y() >= fBox.GetUBound().Y() ) )
    {
        //reverse Y velocity
        p->SetVelocity(damping*Vector2((p->GetVelocity().X()), -(p->GetVelocity().Y())));
    }
}


void ParticleSystem::Print(){
    for( ParticleIterator it = fParticles.begin(); it != fParticles.end(); it++ )
    {
        (*it)->Print();
    }
}
