/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Box class header - defines a rectangular boundary and interactions with it.
*/

#ifndef BOX_H
#define BOX_H

#include "Vector2.h"
#include "Particle.h"

class Box
{
public:
    Box();
    Box(const Vector2 &b0, const Vector2 &b1){fBounds[0] = b0, fBounds[1] = b1;}

    ~Box();

    bool InsideBox(const Particle &) const;

    //Query methods
    Vector2 GetUBound() const { return fBounds[1];}
    Vector2 GetLBound() const { return fBounds[0];}

private:
    //upper [1] and lower [0] bounds of the (axis aligned) box
    Vector2 fBounds[2];
};

#endif // BOX_H
