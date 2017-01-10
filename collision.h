#ifndef COLLISION_H
#define COLLISION_H

#include "force.h"
#include "Particle.h"

#include <vector>

class Collision : public Force
{
public:
    Collision();

    void ParticleCollision(Particle &, Particle &);

    void ApplyForce(std::vector<Particle*> &);

    bool Collided(Particle &, Particle &);
};

#endif // COLLISION_H
