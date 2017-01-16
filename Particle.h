/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Particle class that contains information about
     the particle state (position, movement, mass, radius etc),
     and methods to change these states
*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector2.h"

class Particle
{
public:
    Particle();
    Particle(double radius): fRadius(radius) {}
    Particle(Vector2 pos): fPosition(pos){}
    Particle(Vector2 pos, Vector2 vel): fPosition(pos), fVelocity(vel){}
    Particle(double, double, Vector2 pos, Vector2 vel, Vector2 force);

    virtual ~Particle();

    //access methods
    double GetMass() const {return fMass;}
    void SetMass(double mass) {fMass = mass;}

    double GetRadius() const {return fRadius;}
    void SetRadius(double radius) {fRadius=radius;}

    const Vector2& GetPosition() const {return fPosition;}
    void SetPosition(const Vector2& position) {fPosition = (position);}

    double x() const {return fPosition.x();}
    double y() const {return fPosition.y();}

    const Vector2& GetVelocity() const {return fVelocity;}
    void SetVelocity(const Vector2& velocity) {fVelocity = (velocity);}

    double vx() const {return fVelocity.x();}
    double vy() const {return fVelocity.y();}

    const Vector2& GetForce() const {return fForce;}
    void SetForce(const Vector2 & force) {fForce = force;}

    double fx() const {return fForce.x();}
    double fy() const {return fForce.y();}

    void AccumulateForce(const Vector2 & addedForce) {
        fForce += addedForce;
    }

    void Print() const;

private:

    double fMass = 1;       //kg
    double fRadius = 0.1;   //m
    Vector2 fPosition;      //m
    Vector2 fVelocity;      //m s-1
    Vector2 fForce;         //kg m s-2

};

#endif // PARTICLE_H
