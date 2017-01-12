#ifndef BOX_H
#define BOX_H

#include "Vector2.h"
#include "walls.h"
#include "Particle.h"

//probably don't actually want walls
class Box : public Walls
{
public:
    Box();
    Box(const Vector2 &b0, const Vector2 &b1){fBounds[0] = b0, fBounds[1] = b1;}

    ~Box();

    //check against particle or particle system?
    //should be virtual method in walls?
    //bool intersect() const;

    bool InsideBox(Particle &) const;

    Vector2 GetUBound() const { return fBounds[1];}
    Vector2 GetLBound() const { return fBounds[0];}

private:
    //upper [1] and lower [0] bounds of the (axis aligned) box
    Vector2 fBounds[2];
};



#endif // BOX_H
