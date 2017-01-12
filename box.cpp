#include "box.h"
#include "Vector2.h"
#include "walls.h"


//http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

Box::Box()
{

}

Box::~Box() {

}

//bool Box::intersect() const
//{

//}

//need to also think about case on edge of box - important for bouncing
//may need to change to 'or equal'
//or return which wall its hit
//smaller than or equal to for lowr bounds because inclusive of first pixel value but not last
//?
//partly inside box?
bool Box::InsideBox(Particle &p) const{
    Vector2 pos = p.GetPosition();
    double rad = p.GetRadius();
    bool inside = ((pos.X()-rad < fBounds[1].X())
                    && (pos.Y()-rad < fBounds[1].Y())
                    && (pos.X()+rad > fBounds[0].X())
                    && (pos.Y()+rad > fBounds[0].Y()));
    return inside;
}
