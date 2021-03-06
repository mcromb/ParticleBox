/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Collision force class header detects collisions between particles and (elastically) bounces them
*/

#ifndef COLLISION_H
#define COLLISION_H

#include "force.h"
#include "Particle.h"

#include <vector>

class Collision : public Force
{
public:
    Collision();

    void ApplyForce(std::vector<Particle*> &);

private:
    bool Collided(Particle &, Particle &);

    void ParticleCollision(Particle &, Particle &);

};

#endif // COLLISION_H
