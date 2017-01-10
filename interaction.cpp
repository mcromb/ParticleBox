#include "interaction.h"

#include "Particle.h"

#include <cmath>

Interaction::Interaction()
{

}

//p1 = owning particle
//p2 other particle
//only call if particles are close enough to collide
Interaction::ParticleCollision(Particle & p1, Particle & p2) {
    //find moment of collision t
    //quadratic eq: solve
    //(dx + t(dvx))^2 + (dy + t(dvy))^2 = touchdist^2

    //degen case where exactly same position - move on aong a bit to solve
    //check positions the same or just velocity?

    //if gotten to this fn the balls are touching or overlapping (collision already happened p. much)

    Vector2 p1pos = p1.GetPosition();
    Vector2 p2pos = p2.GetPosition();
    Vector2 p1vel = p1.GetVelocity();
    Vector2 p2vel = p2.GetVelocity();

    //maincase
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();
    double dvx = p1.vx() - p2.vx();
    double dvy = p1.vy() - p2.vy();
    double touchdist = p1.GetRadius() + p2.GetRadius();

    //could do more efficiently with vectors

    double a = dvx*dvx + dvy*dvy;
    double b = 2*(dx*dvx + dy*dvy);
    double c = dx*dx + dy*dy - touchdist*touchdist;
    double tp = (-b + sqrt(b*b - 4*a*c))/(2*a);
    double t = (-b - sqrt(b*b - 4*a*c))/(2*a);
    //half?

    //choose which t value - robs want the -ve one?
    //if abs t > abs tp, t = tp??
    if (abs(t) > abs(tp)) {t = tp;}

    //move p1 back to where they collided - t negative?
    //times t by 2 so not moving both?
    //or mmove both and calculate how much to move by?
    //to make total be timestep
    //important is vector?
    p1pos += t*p1vel;
    p2pos += t*p2vel;
    Vector2 bw = (p2pos - p1pos).Unit();

    //COM vel?
    double p1m = p1.GetMass();
    double p2m = p2.GetMass();
    double totMass = p1m + p2m;
    Vector2 CoM = (p1m*p1vel + p2m*p2vel)/totMass;

    //dot product (component for 1d collicion)
    double u1 = bw.Dot(p1vel);
    double u2 = bw.Dot(p2vel);
    //one should be pos and one neg

    Vector2 v1 = (u1(p1m-p2m)+2*p2m*u2)/totMass;
    Vector2 v2 = (u2(p2m-p1m)+2*p1m*u1)/totMass;

    p1vl += ()

    //want to be outputting a force on each

    //norm vector separating centres
    Vector2 bw =;


}

Interaction::ApplyForce(std::vector<Particle*> & particles){
    for (int i =0; i < particles.size(); i++){
        for (int j=i+1; j < particles.size(); j++) {
            //pass the pointer or the object (fn would use by ref if not pointer)
            if (Collided(*(particles[i]),*(particles[j]))){
                ParticleCollision(*(particles[i]), *(particles[j]));
                //this fn should update the acceleration of the particle(s)
            }
        }
    }
}

//this misses (at best) if speed is faster than 2*touchdist/fTimestep
//note cases of offset collisions
Interaction::Collided(Particle & p1, Particle & p2){
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
