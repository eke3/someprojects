// UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
// Eric Ekey
// eekey1@gl.umbc.edu

#include "railroad.h"

Railroad::Railroad(){
    m_head = nullptr;
    m_tail = nullptr;
    m_numStations = 0;
}

Railroad::~Railroad(){
    clearNetwork();
}

void Railroad::clearNetwork(){
    // trailing delete of each Station
    Station* curr = m_head;
    Station* prev;

    while (curr != nullptr) {
        prev = curr;
        curr = curr->m_next;
        delete prev;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_numStations = 0;
}

bool Railroad::extendAtHead(int aNewCode, int aNumPassengers){
    if (aNewCode < 0) { return false; }  // invalid code protection

    Station* newStation = new Station(aNewCode, aNumPassengers);
    Station* curr = m_tail;

    if (!m_numStations) {
        // empty linked list
        m_tail = newStation;
    } else {
        // populated linked list
        if (curr->m_code == newStation->m_code) {
            return false;  // duplicate station protection
        }
        while (curr->m_previous != nullptr) {
            curr = curr->m_previous;
            if (curr->m_code == newStation->m_code) {
                return false;  // duplicate station protection
            }
        }
        curr->m_previous = newStation;
        newStation->m_next = curr;
    }
    m_head = newStation;
    m_numStations++;
    return true;
}

bool Railroad::extendAtTail(int aNewCode, int aNumPassengers){
    if (aNewCode < 0) { return false; }  // invalid code protection

    Station* newStation = new Station(aNewCode, aNumPassengers);
    Station* curr = m_head;

    if (m_head == nullptr) {
        // empty linked list
        m_head = newStation;
    } else {
        // populated linked list
        if (curr->m_code == newStation->m_code) {
            return false;  // duplicate station protection
        }
        while (curr->m_next != nullptr) {
            curr = curr->m_next;
            if (curr->m_code == newStation->m_code) {
                return false;  // duplicate station protection
            }
        }
        curr->m_next = newStation;
        newStation->m_previous = curr;
    }
    m_tail = newStation;
    m_numStations++;
    return true;
}

void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station* temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}

bool Railroad::makeRoute(list<pair<int,DIRECTION>> aRoute){
    // check linked list for every pair in route
    for (list<pair<int,DIRECTION>>::iterator i = aRoute.begin(); i != aRoute.end(); i++) {
        Station* search = findStation(i->first);  // nonexistent station protection

        if (search != nullptr) {
            // if any directions to change are already filled then fail and return false
            switch (i->second) {
                case NORTH:
                    if (search->m_north != nullptr) {
                        return false;
                    }
                    break;
                case EAST:
                    if (search->m_east != nullptr) {
                        return false;
                    }
                    break;
                case SOUTH:
                    if (search->m_south != nullptr) {
                        return false;
                    }
                    break;
                case WEST:
                    if (search->m_west != nullptr) {
                        return false;
                    }
                    break;
                case NONE:
                    break;

            }
        }
    }

    Station* first = findStation(aRoute.begin()->first);

    if (first != nullptr) {
        list<pair<int,DIRECTION>>::iterator it = aRoute.begin();
        it++;
        list<pair<int,DIRECTION>>::iterator it2 = it;
        it--;

        while (it2 != aRoute.end()) {
            Station* curr = findStation(it->first);
            Station* next = findStation(it2->first);

            if (curr == next) { return false; } // protect against station pointing traveling to itself
            if (curr == nullptr) {
                extendAtTail(it->first, DEFNUMPASS);
            }
            if (next == nullptr) {
                extendAtTail(it2->first, DEFNUMPASS);
            }


            switch(it->second) {
                case NORTH:
                    curr->m_north = next;
                    break;
                case EAST:
                    curr->m_east = next;
                    break;
                case SOUTH:
                    curr->m_south= next;
                    break;
                case WEST:
                    curr->m_west = next;
                    break;
                case NONE:
                    break;

            }
            it++;
            it2++;
        }
        return true;
    }
    return false;
}

int Railroad::travel(list<pair<int,DIRECTION>> aRoute){
    // go through the route
    // if the links are valid (exist in linked list member variables) then continue
    // sum the number of passengers
    // if a station doesnt exist return -1
    // if a link doesnt exist in the linkedlist return -1
    // return number of passengers
    Station* first = findStation(aRoute.begin()->first);
    int passengers = -1;

    if (first != nullptr) {
        passengers = 0;
        list<pair<int,DIRECTION>>::iterator it = aRoute.begin();
        it++;
        list<pair<int,DIRECTION>>::iterator it2 = it;
        it--;

        while (it2 != aRoute.end()) {
            if (!stationExists(it->first) || !stationExists(it2->first)) {
                return -1;
            }
            switch (it->second) {
                case NORTH:
                    if (findStation(it->first)->m_north != findStation(it2->first)) {
                        return -1;
                    }
                    passengers += findStation(it->first)->m_passengers;
                    break;
                case EAST:
                    if (findStation(it->first)->m_east != findStation(it2->first)) {
                        return -1;
                    }
                    passengers += findStation(it->first)->m_passengers;
                    break;
                case SOUTH:
                    if (findStation(it->first)->m_south != findStation(it2->first)) {
                        return -1;
                    }
                    passengers += findStation(it->first)->m_passengers;
                    break;
                case WEST:
                    if (findStation(it->first)->m_west != findStation(it2->first)) {
                        return -1;
                    }
                    passengers += findStation(it->first)->m_passengers;
                    break;
                case NONE:
                    break;
            }
            it++;
            it2++;
        }

        if (!stationExists(it->first) || !stationExists(it2->first)) {
            return -1;
        }
        switch (it->second) {
            case NORTH:
                if (findStation(it->first)->m_north != findStation(it2->first)) {
                    return -1;
                }
                passengers += findStation(it->first)->m_passengers;
                break;
            case EAST:
                if (findStation(it->first)->m_east != findStation(it2->first)) {
                    return -1;
                }
                passengers += findStation(it->first)->m_passengers;
                break;
            case SOUTH:
                if (findStation(it->first)->m_south != findStation(it2->first)) {
                    return -1;
                }
                passengers += findStation(it->first)->m_passengers;
                break;
            case WEST:
                if (findStation(it->first)->m_west != findStation(it2->first)) {
                    return -1;
                }
                passengers += findStation(it->first)->m_passengers;
                break;
            case NONE:
                break;
        }
        passengers += findStation(it->first)->m_passengers;
    }
    return passengers;
}

bool Railroad::setNumPassengers(int aCode, int aNumPassengers){
    Station* curr = m_head;

    if (aNumPassengers < 0) { return false; }  // invalid argument protection

    // find station with specified code and change m_passengers
    if (stationExists(aCode)) {  // nonexistent station protection
        if (curr->m_code == aCode) {
            curr->m_passengers = aNumPassengers;
            return true;
        }
        while (curr->m_next != nullptr) {
            curr = curr->m_next;
            if (curr->m_code == aCode) {
                curr->m_passengers = aNumPassengers;
                return true;
            }
        }
    }
    // return false if station doesnt exist
    return false;
}

bool Railroad::removeStation(int aCode){
    if (stationExists(aCode)) {  // nonexistent station protection
        Station* theStation = findStation(aCode);
        Station* curr = m_head;

        if (m_numStations == 1) {
            // only 1 station
            delete theStation;
            m_head = nullptr;
            m_tail = nullptr;
        } else if (m_numStations > 1) {
            // if there is anything in the linked list with a route going to deleted Station, null that route
            while (curr != nullptr) {
                if (curr->m_north == theStation) {
                    curr->m_north = nullptr;
                }
                if (curr->m_east == theStation) {
                    curr->m_east = nullptr;
                }
                if (curr->m_south == theStation) {
                    curr->m_south = nullptr;
                }
                if (curr->m_west == theStation) {
                    curr->m_west = nullptr;
                }
                curr = curr->m_next;
            }

            // deletion and relinking of list
            if (m_head == theStation) {
                m_head = theStation->m_next;
                m_head->m_previous = nullptr;
                delete theStation;
            } else if (m_tail == theStation) {
                m_tail = theStation->m_previous;
                m_tail->m_next = nullptr;
                delete theStation;
            } else {
                theStation->m_previous->m_next = theStation->m_next;
                theStation->m_next->m_previous = theStation->m_previous;
                delete theStation;
            }
        }
        // return true if removal successful
        m_numStations--;
        return true;
    }
    // return false if the node does not exist
    return false;
}

void Railroad::clearAllRoutes(){
    Station* curr = m_head;

    // traverse list and clear route members
    if (m_head != nullptr) {
        while (curr != nullptr) {
            curr->m_north = nullptr;
            curr->m_east = nullptr;
            curr->m_south = nullptr;
            curr->m_west = nullptr;
            curr = curr->m_next;
        }
    }
}

const Railroad& Railroad::operator=(const Railroad &rhs){
    if (&rhs != this) {  // self assignment protection
        clearNetwork();
        if (rhs.m_numStations == 1) {
            // if 1 station
            Station* curr = rhs.m_head;
            Station* newStation = new Station(curr->m_code, curr->m_passengers);
            int north, east, south, west;

            m_head = newStation;
            m_tail = newStation;

            // remake the routes
            if (curr->m_north) {
                north = curr->m_north->m_code;
                newStation->m_north = findStation(north);
            }
            if (curr->m_east) {
                east = curr->m_east->m_code;
                newStation->m_east = findStation(east);
            }
            if (curr->m_south) {
                south = curr->m_south->m_code;
                newStation->m_south = findStation(south);
            }
            if (curr->m_west) {
                west = curr->m_west->m_code;
                newStation->m_west = findStation(west);
            }
        } else if (rhs.m_numStations > 1) {
            // more than 1 station
            Station* curr = rhs.m_head;
            Station* newStation = new Station(curr->m_code, curr->m_passengers);
            int north, east, south, west;

            m_head = newStation;

            // remake the routes
            if (curr->m_north) {
                north = curr->m_north->m_code;
                newStation->m_north = findStation(north);
            }
            if (curr->m_east) {
                east = curr->m_east->m_code;
                newStation->m_east = findStation(east);
            }
            if (curr->m_south) {
                south = curr->m_south->m_code;
                newStation->m_south = findStation(south);
            }
            if (curr->m_west) {
                west = curr->m_west->m_code;
                newStation->m_west = findStation(west);
            }

            while (curr->m_next != nullptr) {
                curr = curr->m_next;
                Station* newerStation = new Station(curr->m_code, curr->m_passengers);
                extendAtTail2(newerStation);

                // remake the routes
                if (curr->m_north) {
                    north = curr->m_north->m_code;
                    newerStation->m_north = findStation(north);
                }
                if (curr->m_east) {
                    east = curr->m_east->m_code;
                    newerStation->m_east = findStation(east);
                }
                if (curr->m_south) {
                    south = curr->m_south->m_code;
                    newerStation->m_south = findStation(south);
                }
                if (curr->m_west) {
                    west = curr->m_west->m_code;
                    newerStation->m_west = findStation(west);
                }
            }
            Station* newerStation = new Station(curr->m_code, curr->m_passengers);
            extendAtTail2(newerStation);
        }
        m_numStations = rhs.m_numStations;
    }
    return *this;
}

Railroad::Railroad(const Railroad &rhs){
    if (rhs.m_numStations == 1) {
        // if 1 station only
        Station* curr = rhs.m_head;
        Station* newStation = new Station(curr->m_code, curr->m_passengers);
        int north, east, south, west;

        m_head = newStation;
        m_tail = newStation;

        // remake the routes
        if (curr->m_north) {
            north = curr->m_north->m_code;
            newStation->m_north = findStation(north);
        }
        if (curr->m_east) {
            east = curr->m_east->m_code;
            newStation->m_east = findStation(east);
        }
        if (curr->m_south) {
            south = curr->m_south->m_code;
            newStation->m_south = findStation(south);
        }
        if (curr->m_west) {
            west = curr->m_west->m_code;
            newStation->m_west = findStation(west);
        }
    } else if (rhs.m_numStations > 1) {
        // if more than 1 station
        Station* curr = rhs.m_head;
        Station* next = curr->m_next;
        Station* newStation = new Station(curr->m_code, curr->m_passengers);
        int north, east, south, west;

        m_head = newStation;

        // remake the routes
        if (curr->m_north) {
            north = curr->m_north->m_code;
            newStation->m_north = findStation(north);
        }
        if (curr->m_east) {
            east = curr->m_east->m_code;
            newStation->m_east = findStation(east);
        }
        if (curr->m_south) {
            south = curr->m_south->m_code;
            newStation->m_south = findStation(south);
        }
        if (curr->m_west) {
            west = curr->m_west->m_code;
            newStation->m_west = findStation(west);
        }

        while (next != nullptr) {
            curr = next;
            next = next->m_next;
            Station* newerStation = new Station(curr->m_code, curr->m_passengers);
            extendAtTail2(newerStation);

            // remake the routes
            if (curr->m_north) {
                north = curr->m_north->m_code;
                newerStation->m_north = findStation(north);
            }
            if (curr->m_east) {
                east = curr->m_east->m_code;
                newerStation->m_east = findStation(east);
            }
            if (curr->m_south) {
                south = curr->m_south->m_code;
                newerStation->m_south = findStation(south);
            }
            if (curr->m_west) {
                west = curr->m_west->m_code;
                newerStation->m_west = findStation(west);
            }
        }
        Station* newerStation = new Station(curr->m_code, curr->m_passengers);
        extendAtTail2(newerStation);

        if (curr->m_north) {
            north = curr->m_north->m_code;
            newerStation->m_north = findStation(north);
        }
        if (curr->m_east) {
            east = curr->m_east->m_code;
            newerStation->m_east = findStation(east);
        }
        if (curr->m_south) {
            south = curr->m_south->m_code;
            newerStation->m_south = findStation(south);
        }
        if (curr->m_west) {
            west = curr->m_west->m_code;
            newerStation->m_west = findStation(west);
        }
    }
    m_numStations = rhs.m_numStations;
}

void Railroad::extendAtTail2(Station* aNewStation) {
    // duplicate station protection
    if (stationExists(aNewStation->m_code)) {
        delete aNewStation;
        return;
    }

    Station* curr = m_head;

    // append to tail
    if (m_head != nullptr) {
        while (curr->m_next != nullptr) {
            curr = curr->m_next;
        }
    }
    curr->m_next = aNewStation;
    aNewStation->m_previous = curr;
    m_tail = aNewStation;
}

Station* Railroad::findStation(int aCode) {
    Station* curr = m_head;

    // search list for station and return Station*
    while ((curr != nullptr) && (curr->m_code != aCode)) {
        curr = curr->m_next;
    }
    return curr;
}

bool Railroad::stationExists(int aCode) {
    if (m_head) {
        Station* curr = m_head;

        // search list for station, return true if it exists
        while ((curr != nullptr) && (curr->m_code != aCode)) {
            curr = curr->m_next;
        }
        if (curr != nullptr) {
            return true;
        }
    }
    return false;
}