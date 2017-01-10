#include "interaction.h"

#include "Particle.h"

#include <cmath>

Interaction::Interaction()
{

}

//p1 = owning particle
//p2 other particle
//only call if particles are close enough to collide
Interaction::ParticleCollision(Particle p1, Particle p2) {
    //find moment of collision t
    //quadratic eq: solve
    //(dx + t(dvx))^2 + (dy + t(dvy))^2 = touchdist^2

    //degen case where exactly same position - move on aong a bit to solve
    //check positions the same or just velocity?


    //maincase
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();
    double dvx = p1.vx() - p2.vx();
    double dvy = p1.vy() - p2.vy();
    double touchdist = p1.GetRadius() + p2.GetRadius();

    double a = dvx*dvx + dvy*dvy;
    double b = 2*(dx*dvx + dy*dvy);
    double c = dx*dx + dy*dy - touchdist*touchdist;
    double tp = (-b + sqrt(b*b - 4*a*c))/(2*a);
    double tm = (-b - sqrt(b*b - 4*a*c))/(2*a);

    //choose which t value
    //if abs tm > abs tp, t = tp??

    //move p1 back to where they collided
    //have to make sure surely don't then caluclate for p2 nother time?
    //or just use a different value then change back again?

    //want to be outputting a force on each

    //norm vector separating centres
    Vector2 bw =;


}

Interaction::ApplyForce(){

}
