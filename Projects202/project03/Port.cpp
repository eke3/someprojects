//Title: Port.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 3/20/2022
//Description: Function definitions for Port class

#include "Port.h"

// Name: Port() - Default Constructor
// Desc: Used to build a new empty port
Port::Port() {
    m_name = "Default Port";
    m_location = "Default Location";
    m_north = 0;
    m_west = 0;
    m_next = nullptr;
}


// Name: Port(string, string, double, double) - Overloaded Constructor
// Desc: Used to build a new Port passing it a name, location, north, and west
Port::Port(string aName, string aLocation, double aNorth, double aWest) {
    m_name = aName;
    m_location = aLocation;
    m_north = aNorth;
    m_west = aWest;
    m_next = nullptr;
}


// Name: ~Port() - Destructor
// Desc: Used to destruct a port
Port::~Port() {}


// Name: GetName()
// Desc: Returns the name of the port
string Port::GetName() {
    return m_name;
}


// Name: GetLocation()
// Desc: Returns the description of where the port is located
string Port::GetLocation() {
    return m_location;
}


// Name: GetNorth()
// Desc: Returns the northern coordinates of the port
double Port::GetNorth() {
    return m_north;
}


// Name: GetWest()
// Desc: Returns the western coordinates of the port
double Port::GetWest() {
    return m_west;
}


// Name: GetNext()
// Desc: Returns the pointer to the next port
Port* Port::GetNext() {
    return m_next;
}


// Name: SetNext()
// Desc: Updates the pointer to a new target (either a port or nullptr)
void Port::SetNext(Port *aPort) {
    m_next = aPort;
}