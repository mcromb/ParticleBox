/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Box class implementation.
*/

#include "box.h"
#include "Vector2.h"


Box::Box()
{
    //create a 20x20 square box centered at 0,0.
    fBounds[0] = Vector2(-10,-10);
    fBounds[1] = Vector2(10,10);
}

Box::~Box() {

}

/* ***METHOD***
    Name:   InsideBox
    IN:     p       - particle to test
    OUT:    inside  - true if the particle is partly or wholly in the box
    About:  Tests if any part of particle p is in the box
*/
bool Box::InsideBox(const Particle &p) const{
    Vector2 pos = p.GetPosition();
    double rad = p.GetRadius();
    bool inside = ((pos.X()-rad < fBounds[1].X())
                    && (pos.Y()-rad < fBounds[1].Y())
                    && (pos.X()+rad > fBounds[0].X())
                    && (pos.Y()+rad > fBounds[0].Y()));
    return inside;
}
