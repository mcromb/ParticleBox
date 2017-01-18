/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Implementation of the ParticleSystem class
*/

#include "particlesystem.h"

#include "box.h"
#include "Vector2.h"

#include <cstdlib>
#include <algorithm>


ParticleSystem::ParticleSystem()
{
    fBox = Box();
    fWallStatus = kPermeable;
    fTimestep = 0.01;   //time granularity of the system
}

ParticleSystem::~ParticleSystem()
{

}

/* ***FUNCTION***
    Name:   RandomDouble
    OUT:    r - a random double between -1 and 1
    About:  Returns a random double between -1 and 1
*/
double RandomDouble()
{
      double r = (double)rand()/(double)RAND_MAX;
      r = (r*2)-1;
      return r;
}

/* ***METHOD***
    Name:   AddParticles
    IN:     particles   - the number of particles to add
            origin      - the place to add the particles
            radius      - the size of the particles' radius
    About:  Adds particles (on the heap) into the system particle vector
     with specified origin and size. These lifetime of these particles is until
     they leave the box dimensions and are deleted or are cleared with ClearParticles()
*/
void ParticleSystem::AddParticles(int particles, Vector2 origin, double radius )
{
    Particle* particle;
    for( int i = 0; i < particles; i++ )
    {
        particle = new Particle(radius);
        particle->SetPosition(origin);

        //Sets velocity in any direction between +/-fMaxSpeed
        //for a smaller range of directions can use abs(RandomDouble())
        particle->SetVelocity(fMaxSpeed*Vector2(RandomDouble(),RandomDouble()));

        //don't add particle if it happens to be staying still
        if( particle->GetVelocity() == Vector2(0.0, 0.0) )
        {
            delete particle;
            continue;
        }
        //add to fParticles vector
        fParticles.push_back( particle );
    }
}

/* ***METHOD***
    Name:   AddForce
    IN:     force   - the force to add to the system
    About:  Adds a force to the system's container of forces
*/
void ParticleSystem::AddForce(Force *force){
    fForces.push_back( force );
}

/* ***METHOD***
    Name:   RemoveForce
    IN:     name   - the name of the force to remove from the system
    About:  Finds and removes a named force from the system container
     (Uses a different finding algorithm to FindForce)
*/
void ParticleSystem::RemoveForce(std::string name){
    auto it = std::find_if( fForces.begin(), fForces.end(), [&name](Force* force) {return force->GetName() == name;});
    if (it != fForces.end())
    {
        //found an iterator to the first matching force.
        //delete the force
        delete (*it);
        //erase the corresponding element of the force vector
        it = fForces.erase( it );
        //returns iterator to element after the erased one
        //(so if multiple with same name, possible to extend this as a loop)
    }
}

/* ***METHOD***
    Name:   FindForce
    IN:     name    - the name of the force to find in the system
    OUT:    force   - a pointer to the named force if it exists, otherwise NULL
    About:  Finds a named force within the system container
*/
Force* ParticleSystem::FindForce(std::string name){
    Force* force = NULL;
    for (unsigned int i =0; i < fForces.size(); i++){
        if(fForces[i]->GetName().compare(name) == 0){
            force = fForces[i];
        }
    }
    if (force == NULL){
        //function will return NULL
    }
    return force;
}

/* ***METHOD***
    Name:   Update
    About:  Updates the state of the system, evolving it by time fTimestep.
     When this function is called, the force on all particles should be zero,
     so any forces can accumulate on the particle each time.
     This is ensured by clearing the force on the particle after the new
     positions and velocities have been set.
*/
void ParticleSystem::Update() {

    //apply each force to the particles in the system
    for (ForceIterator fit = fForces.begin(); fit != fForces.end(); fit++){
        (*fit)->ApplyForce(fParticles);
    }

    //loop through the particles evolving positions and velocities
    for( ParticleIterator it = fParticles.begin(); it != fParticles.end();)
    {
        //suvat assumes constant acceleration within timestep
        //s = ut + 0.5 at^2
        //v = u + at

        Vector2 pos = (*it)->GetPosition();
        Vector2 vel = (*it)->GetVelocity();
        //convert force to acceleration for each particle
        Vector2 accel = ((*it)->GetForce())*(1/(*it)->GetMass());

        pos += fTimestep*vel + 0.5*accel*fTimestep*fTimestep;
        (*it)->SetPosition(pos);

        vel += fTimestep*accel;
        (*it)->SetVelocity(vel);

        //clear forces for next update
        (*it)->SetForce(Vector2(0.0,0.0));

        if(fWallStatus == kSolid){ WallBounce(*it);}

        //if particle is now outside the box - delete it
        if( !fBox.InsideBox(**it)){
            delete (*it);
            //returns iterator to element after the erased one so
            //should not increment it in this branch
            it = fParticles.erase( it );
            //if at the end, exit
            if( it == fParticles.end() ) return;
        }else {
            it++;
        }
    }
}

/* ***METHOD***
    Name:   WallBounce
    IN:     p   - the particle to check for collision with wall
    About:  If the particle is moving out through a wall, collide the particle
     with the wall and send it back again. If fWallDamping = 1 the collision is elastic,
     otherwise the ball loses energy. This function is only called if the walls are solid.
     This system doesn't find and use the time of collision, so it is flawed - particles can slowly move through the wall.
*/
void ParticleSystem::WallBounce(Particle* p) {
    Vector2 pos = p->GetPosition();
    Vector2 vel = p->GetVelocity();
    double radius = p->GetRadius();

    //if part of particle is outside the X bounds and travelling out of the box
    if ( ( (pos.X()-radius <= fBox.GetLBound().X()) && (vel.X() < 0) )
        || ( (pos.X()+radius >= fBox.GetUBound().X()) && (vel.X() > 0) ) )
    {
        //reverse X velocity
        p->SetVelocity(fWallDamping*Vector2(-(vel.X()), (vel.Y())));
    }
    //if part of particle is outside the Y bounds and travelling out of the box
    if (( (pos.Y()-radius <= fBox.GetLBound().Y()) && (vel.Y() < 0) )
        || ( (pos.Y()+radius >= fBox.GetUBound().Y()) && (vel.Y() > 0) ) )
    {
        //reverse Y velocity
        p->SetVelocity(fWallDamping*Vector2((vel.X()), -(vel.Y())));
    }
}

/* ***METHOD***
    Name:   ClearParticles
    About:  Removes all the particles from the system.
*/
void ParticleSystem::ClearParticles(){
    for( ParticleIterator it = fParticles.begin(); it != fParticles.end();){
        delete (*it);
        //returns iterator to element after the erased one so should not increment it additionally
        it = fParticles.erase( it );
        //if at the end, exit
        if( it == fParticles.end() ) return;
    }
}

/* ***METHOD***
    Name:   Print
    About:  Utility method to print info on all the particles in the system.
        Useful for debugging systems with small numbers of particles.
*/
void ParticleSystem::Print(){
    for( ParticleIterator it = fParticles.begin(); it != fParticles.end(); it++ )
    {
        (*it)->Print();
    }
}
