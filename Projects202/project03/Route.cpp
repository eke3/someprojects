//Title: Route.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 3/20/2022
//Description: Function definitions for Route class

#include "Route.h"

// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of ports
Route::Route() {
    m_name = "Default Route";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}


// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
Route::~Route() {
    if (GetSize()) {
        Port *current = m_head;  // pointer to first port on route
        Port *next = nullptr;  // pointer to next port on route

        // traverse route, deleting each element
        while (current != nullptr) {
            next = current->GetNext();
            delete current;
            current = next;
        }
    }
}


// Name: SetName(string)
// Desc: Sets the name of the route (usually first port to last port)
void Route::SetName(string aName) {
    m_name = aName;
}


// Name: InsertEnd (string, string, double double)
// Desc: Creates a new port using the data passed to it.
//       Inserts the new port at the end of the route
void Route::InsertEnd(string aName, string aLocation, double aNorth, double aWest) {
    Port* pNewPort = new Port(aName, aLocation, aNorth, aWest);  // pointer to new port
    if (!GetSize()) {
        // if this is the first port to be put in the route
        m_head = pNewPort;
        m_tail = pNewPort;
        pNewPort->SetNext(nullptr);
    } else {
        m_tail->SetNext(pNewPort);
        m_tail = pNewPort;
    }
    pNewPort->SetNext(nullptr);

    // increment size of route and update name
    m_size++;
    SetName(UpdateName());
}


// Name: RemovePort(int index)
// Desc: Removes a port from the route at the index provided
void Route::RemovePort(int aIndex) {
    if (GetSize() < 3) {
        cout << "\n-Cannot make route less than 2 ports-\n";
    } else if (aIndex >= GetSize()) {
        cout << "\n-Invalid port-\n";
    } else {
        Port* delPort = GetData(aIndex);  // pointer to the port you want to delete
        Port* current = m_head; // pointer to current port in route
        Port* prev = current;   // pointer to previous port on route

        if (delPort == current) {
            // removing the first port on a route

            m_head = current->GetNext();
        } else if (delPort == m_tail) {
            // removing the last port on a route

            while (current != m_tail) {
                prev = current;
                current = current->GetNext();
            }
            m_tail = prev;
            prev->SetNext(nullptr);
        } else {
            // removing a port from the middle of the route
            while (current != delPort) {
                prev = current;
                current = current->GetNext();
            }
            prev->SetNext(current->GetNext());

        }
        // delete the removed port
        delete current;
        current = nullptr;
        prev = nullptr;

        // update size and name of route
        m_size--;
        SetName(UpdateName());
    }
}

// Name: GetName()
// Desc: Returns the name of the route (Usually starting port to last port)
string Route::GetName() {
    return m_name;
}


// Name: UpdateName()
// Desc: Updates m_name based on the name of the first and last ports in the route
string Route::UpdateName() {
    string newName = m_name;    // new name for route

    // formulate the new name
    if (GetSize() > 1) {
        string headName = m_head->GetName();    // name of first port on route
        string tailName = m_tail->GetName();    // name of last port on route
        newName = (headName + " to " + tailName);
    }

    return newName;
}

// Name: GetSize()
// Desc: Returns the number of ports in a route
int Route::GetSize() {
    return m_size;
}


// Name: ReverseRoute
// Desc: Reverses a route
void Route::ReverseRoute() {
    Port* current = m_head; // pointer to current port on route
    Port* prev = nullptr;   // pointer to previous port on route
    Port* next = nullptr;   // pointer to next port on route
    Port* oldHead = m_head; // head pointer before reversal
    Port* oldTail = m_tail; // tail pointer before reversal

    // reverse the route in place
    while (current != nullptr) {
        next = current->GetNext();
        current->SetNext(prev);
        prev = current;
        current = next;
    }
    // switch head and tail pointers
    m_head = oldTail;
    m_tail = oldHead;

    // update name of route to reflect changes
    SetName(UpdateName());
}


// Name: GetData (int)
// Desc: Returns a port at a specific index
Port* Route::GetData(int aIndex) {
    int currIndex = 0;  // current index for route traversal
    Port* current = m_head;    // pointer to current port in route

    // traverse route to find port at specified index
    while (currIndex < aIndex) {
        current = current->GetNext();
        currIndex++;
    }

    return current;
}


// Name: DisplayRoute
// Desc: Displays all of the ports in a route
void Route::DisplayRoute() {
    Port* current = m_head;    // pointer to current port in route
    string routeName = GetName();   // name of route to display
    int portNum = 1;   // numbers for displaying numbered list of ports

    cout << "\n\t***" << routeName << "***\n";
    while (current != nullptr) {
        cout << portNum << ". " << *current
             << " (N" << current->GetNorth()
             << " W" << current->GetWest()
             << ")\n";
        current = current->GetNext();
        portNum++;
    }
    cout << "\n";
}