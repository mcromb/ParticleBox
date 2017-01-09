#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2.h"

class Particle
{
public:
    Particle();
    //want to specify initialisation?
    //want to allow specifically setting variables at creation?
    virtual ~Particle();

    //perhaps public members would be more efficient for the particles
    //no b/c then they can be changed accidentally

    //access methods
    double GetMass() const {return fMass;}

    void SetMass(double mass) {fMass = mass;}

    double GetRadius() const {return fRadius;}

    void SetRadius(double radius) {fRadius =radius;}

    const Vector2& GetPosition() const {
        return fPosition;
    }

    void SetPosition(const Vector2& position) {
        fPosition = position;
    }

    const Vector2& GetVelocity() const {
        return fVelocity;
    }

    void SetVelocity(const Vector2& velocity) {
        fVelocity = velocity;
    }

    const Vector2& GetForce() const {
        return fForce;
    }

    void SetForce(const Vector2 & force) {
        fForce = force;
    }

    void Print() const;

private:

    double fMass;
    double fRadius;
    Vector2 fPosition;
    Vector2 fVelocity;
    //?force
    Vector2 fForce;

    //colour?
    //type? (could determine force or particle system could do)
};

#endif // PARTICLE_H