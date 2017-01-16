/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Collision force class implementation.
*/

#include "collision.h"

#include "force.h"
#include "Particle.h"

#include <cmath>
#include <iostream>

Collision::Collision(): Force("Collision"){}

/* ***METHOD***
    Name:   ParticleCollision
    IN:     p1,p2   - particles that are colliding
    About:  Called when two particles are close enough that they have collided.
     Backtracks time to where they just touch, then conserving momenta, changes
     their velocity so they have bounced off each other, then advances time again
     to keep the system consistent
*/
void Collision::ParticleCollision(Particle & p1, Particle & p2) {
    //to find moment of collision t solve the quadratic eq:
    //(dx + t(dvx))^2 + (dy + t(dvy))^2 = touchdist^2

    Vector2 p1pos = p1.GetPosition();
    Vector2 p2pos = p2.GetPosition();
    Vector2 p1vel = p1.GetVelocity();
    Vector2 p2vel = p2.GetVelocity();
    double p1m = p1.GetMass();
    double p2m = p2.GetMass();

    double touchdist = p1.GetRadius() + p2.GetRadius();
    Vector2 d = p2pos - p1pos;
    Vector2 dv = p2vel - p1vel;

    //calculate coefficients of the quadratic
    double a = dv.Mag2();
    double b = 2*dv.Dot(d);
    double c = d.Mag2() - touchdist*touchdist;

    //solve the quadratic
    double tp = (-b + sqrt(b*b - 4*a*c))/(2*a);
    double t = (-b - sqrt(b*b - 4*a*c))/(2*a);

    //pick the correct root
    if (abs(t) > abs(tp)) {t = tp;}

    //move the particles back to just touching
    //t is generally negative
    p1pos += t*p1vel;
    p2pos += t*p2vel;

    //elastically collide the particles conserving momentum

    double totMass = p1m + p2m;
    Vector2 bw = (p2pos - p1pos).Unit();
    //find the initial velocity components along the line between the
    //particle centres to convert into a 1D collision
    double u1 = bw.Dot(p1vel);
    double u2 = bw.Dot(p2vel);
    //find the final velocity components
    double v1 = (u1*(p1m-p2m)+2*p2m*u2)/totMass;
    double v2 = (u2*(p2m-p1m)+2*p1m*u1)/totMass;

    //add the velocity changes to the particle
    p1vel += (v1-u1)*bw;
    p2vel += (v2-u2)*bw;

    //iterate positions forward to the right time
    p1pos -= t*p1vel;
    p2pos -= t*p2vel;

    //update particles
    //collision forces are impulses so change velocity instantaneously
    p1.SetPosition(p1pos);
    p2.SetPosition(p2pos);
    p1.SetVelocity(p1vel);
    p2.SetVelocity(p2vel);

}

/* ***METHOD***
    Name:   ApplyForce
    IN:     particles - set of particles that can collide with each other
    About:  checks each particle for collisions against the rest of the particles, one by one
     if a collision is found, their velocities are updated in ParticleCollisions.
     This 'Force' actual changes the velocities not the forces of the particles because it is an impulse
     and so happens instantaneously
*/
void Collision::ApplyForce(std::vector<Particle*> & particles){
    for (unsigned int i =0; i < particles.size(); i++){
        // loop over j=i+1 means it doesn't check for collision with itself
        // and also only checks itself (i) against those that haven't already
        //checked themselves against others
        for (unsigned int j=i+1; j < particles.size(); j++) {
            if (Collided(*(particles[i]),*(particles[j]))){
                ParticleCollision(*(particles[i]), *(particles[j]));
            }
        }
    }
}

/* ***METHOD***
    Name:   Collided
    IN:     p1,p2   - particles testing for collision
    OUT:    rtn     - true if the particles are overlapping and thus have collided
    About:  Tests whether two particles have overlapped and so should be colliding
        (note: at high particle speeds or short timesteps this can miss collisions)
*/
bool Collision::Collided(Particle & p1, Particle & p2){
    bool rtn;
    Vector2 between = p2.GetPosition() - p1.GetPosition();
    double touchdist = p1.GetRadius() + p2.GetRadius();
    if (between.Mag() <= touchdist){
        //collision occurred
        rtn = true;
    }
    else{rtn = false;}
    return rtn;
}
