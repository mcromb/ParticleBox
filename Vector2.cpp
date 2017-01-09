/*
 * Vector2.cpp
 *
 * cite Sergi
 */

#include <math.h>
#include <iostream>

#include "Vector2.h"

Vector2::Vector2()
: fX(0.0), fY(0.0) {}

Vector2::Vector2(const Vector2 & p)
: fX(p.fX), fY(p.fY){}

Vector2::Vector2(double xx, double yy)
: fX(xx), fY(yy) {}

Vector2::Vector2(const double * x0)
: fX(x0[0]), fY(x0[1]) {}

Vector2::~Vector2() {
}
//_____________________________________________________________________________
double Vector2::Mag() const
{
   // return the magnitude (length of the vector)

   return sqrt(Mag2());
}

//______________________________________________________________________________
//double Vector2::Perp() const
//{
//   //return the transverse component  (R in cylindrical coordinate system)

//   return sqrt(Perp2());
//}

/*//______________________________________________________________________________
double Vector2::Perp(const Vector2 & p) const
{
   //return the transverse component (R in cylindrical coordinate system)

   return sqrt(Perp2(p));
}
//__*///____________________________________________________________________________
/*double Vector2::Theta() const
{
   //return the polar angle
   return fX == 0.0 && fY == 0.0 && fZ == 0.0 ? 0.0 : atan2(Perp(),fZ);
}

//__*///____________________________________________________________________________
Vector2 Vector2::Unit() const
{
   // return unit vector parallel to this.
   double  tot2 = Mag2();
   double tot = (tot2 > 0) ?  1.0/sqrt(tot2) : 1.0;
   Vector2 p(fX*tot,fY*tot);
   return p;
}

//Implementation of the global operators; notice the absence of Vector2::
//They all return a newly constructed Vector2
Vector2 operator + (const Vector2 & a, const Vector2 & b) {
   return Vector2(a.X() + b.X(), a.Y() + b.Y());
}

Vector2 operator - (const Vector2 & a, const Vector2 & b) {
   return Vector2(a.X() - b.X(), a.Y() - b.Y());
}

Vector2 operator * (const Vector2 & p, double a) {
   return Vector2(a*p.X(), a*p.Y());
}

Vector2 operator * (double a, const Vector2 & p) {
   return Vector2(a*p.X(), a*p.Y());
}

bool operator == (const Vector2 & a, const Vector2 & b) {
   return ((a.X() == b.X()) && (a.Y() == b.Y()) );
}

void Vector2::Print()const
{
   //print vector parameters
   std::cout << "(x,y)=(" << X() << "," << Y() << ")" << std::endl;
}


