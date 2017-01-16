/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Force class header: Purely virtual class that defines the
     common interface for forces within the system which inherit from this class
*/

#ifndef FORCES_H
#define FORCES_H

#include "Vector2.h"
#include "Particle.h"

#include <string>
#include <vector>


class Force
{
public:
    Force();
    Force(std::string name): fName(name){}

    virtual ~Force();

    virtual void ApplyForce(std::vector<Particle*> & ) = 0;

    const std::string& GetName() const {return fName;}
    void SetName(const std::string& name) {fName = name;}

private:
    std::string fName;

};

#endif // FORCES_H
