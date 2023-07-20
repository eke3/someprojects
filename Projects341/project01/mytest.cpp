// UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
// Eric Ekey
// eekey1@gl.umbc.edu

#include "railroad.h"

class Tester{ // Tester class to implement test functions
public:

    /**************************************
    * Test function declarations go here! *
    **************************************/

    bool testExtHead(Railroad aRailroad, bool aErrorCase);
    bool testExtTail(Railroad aRailroad, bool aErrorCase);
    bool testRemove(Railroad aRailroad, bool aErrorCase);
    bool testAssignment(Railroad aRailroad, int aEdgeCase = 0);
    bool testCopy(Railroad aRailroad, int aEdgeCase = 0);
    bool testMakeRoute(Railroad aRailroad, int aErrorCase = 0);
    bool testTravel(Railroad aRailroad, int aErrorCase = 0);
    bool testSetPass(Railroad aRailroad, int aErrorCase = 0);
    bool testClearRoutes(Railroad aRailroad);
};


int main() {
    Tester tester;

    // extendAtHead()
    // normal case (300 stations)
    // error case (station code < 0)
    printf("\nTesting extendAtHead()\n");
    {
        Railroad rail, rail2;
        bool normal = tester.testExtHead(rail, false);
        bool error = tester.testExtHead(rail2, true);

        if (normal) {
            printf("\textendAtHead() normal case PASS\n");
        } else {
            printf("\textendAtHead() normal case FAIL\n");
        }

        if (error) {
            printf("\textendAtHead() error case PASS\n");
        } else {
            printf("\textendAtHead() error case FAIL\n");
        }
    }

    // extendAtTail()
    // normal case (300 stations)
    // error case (station code < 0)
    printf("\nTesting extendAtTail()\n");
    {
        Railroad rail, rail2;
        bool normal = tester.testExtTail(rail, false);
        bool error = tester.testExtTail(rail2, true);

        if (normal) {
            printf("\textendAtTail() normal case PASS\n");
        } else {
            printf("\textendAtTail() normal case FAIL\n");
        }

        if (error) {
            printf("\textendAtTail() error case PASS\n");
        } else {
            printf("\textendAtTail() error case FAIL\n");
        }
    }

    // removeStation()
    // normal case (300 stations, remove them all)
    // ^ links to removed station are removed
    // error case (nonexistent station)
    printf("\nTesting removeStation()\n");
    {
        Railroad rail, rail2;
        bool normal = tester.testRemove(rail, false);
        bool error = tester.testRemove(rail2, true);

        if (normal) {
            printf("\tremoveStation() normal cases PASS\n");
        } else {
            printf("\tremoveStation() normal cases FAIL\n");
        }

        if (error) {
            printf("\tremoveStation() error case PASS\n");
        } else {
            printf("\tremoveStation() error case FAIL\n");
        }
    }

    // assignment operator=
    // test self-assignment
    // confirm deep copy
    // confirm copy is accurate
    // normal case (300 stations)
    // edge cases (1 station, 2 stations)
    printf("\nTesting operator=\n");
    {
        Railroad rail, rail2, rail3;
        bool normal = tester.testAssignment(rail);
        bool edge = tester.testAssignment(rail2, 1);
        bool edge2 = tester.testAssignment(rail3, 2);

        if (normal) {
            printf("\toperator= normal cases PASS\n");
        } else {
            printf("\toperator= normal cases FAIL\n");
        }

        if (edge) {
            printf("\toperator= edge case 1 PASS\n");
        } else {
            printf("\toperator= edge case 1 FAIL\n");
        }

        if (edge2) {
            printf("\toperator= edge case 2 PASS\n");
        } else {
            printf("\toperator= edge case 2 FAIL\n");
        }
    }

    // copy constructor
    // confirm deep copy
    // confirm copy is accurate
    // normal case (300 stations)
    // edge case (1 station, 2 stations)
    printf("\nTesting copy constructor\n");
    {
        Railroad rail, rail2, rail3;
        bool normal = tester.testCopy(rail);
        bool edge = tester.testCopy(rail2, 1);
        bool edge2 = tester.testCopy(rail3, 2);

        if (normal) {
            printf("\tcopy constructor normal cases PASS\n");
        } else {
            printf("\tcopy constructor normal cases FAIL\n");
        }

        if (edge) {
            printf("\tcopy constructor edge case 1 PASS\n");
        } else {
            printf("\tcopy constructor edge case 1 FAIL\n");
        }

        if (edge2) {
            printf("\tcopy constructor edge case 2 PASS\n");
        } else {
            printf("\tcopy constructor edge case 2 FAIL\n");
        }
    }

    // makeRoute()
    // error cases (first station in route does not exist in LL, something in route tries to overwrite existing link)
    // normal case (5+ stations)
    printf("\nTesting makeRoute()\n");
    {
        Railroad rail, rail2, rail3;
        bool normal = tester.testMakeRoute(rail);
        bool error = tester.testMakeRoute(rail2, 1);
        bool error2 = tester.testMakeRoute(rail3, 2);

        if (normal) {
            printf("\tmakeRoute() normal case PASS\n");
        } else {
            printf("\tmakeRoute() normal case FAIL\n");
        }

        if (error) {
            printf("\tmakeRoute() error case 1 PASS\n");
        } else {
            printf("\tmakeRoute() error case 1 FAIL\n");
        }

        if (error2) {
            printf("\tmakeRoute() error case 2 PASS\n");
        } else {
            printf("\tmakeRoute() error case 2 FAIL\n");
        }
    }

    // travel()
    // normal case (valid route that has been created previously)
    // error case (invalid route b/c a station or a link doesnt exist)
    printf("\nTesting travel()\n");
    {
        Railroad rail, rail2, rail3;
        bool normal = tester.testTravel(rail);
        bool error = tester.testTravel(rail2, 1);
        bool error2 = tester.testTravel(rail3, 2);

        if (normal) {
            printf("\ttravel() normal case PASS\n");
        } else {
            printf("\ttravel() normal case FAIL\n");
        }

        if (error) {
            printf("\ttravel() error case 1 PASS\n");
        } else {
            printf("\ttravel() error case 1 FAIL\n");
        }

        if (error2) {
            printf("\ttravel() error case 2 PASS\n");
        } else {
            printf("\ttravel() error case 2 FAIL\n");
        }
    }

    // setNumPassengers()
    // normal case
    // error case (station doesnt exist, passengers < 0)
    printf("\nTesting setNumPassengers()\n");
    {
        Railroad rail, rail2, rail3;
        bool normal = tester.testSetPass(rail);
        bool error = tester.testSetPass(rail2, 1);
        bool error2 = tester.testSetPass(rail3, 2);

        if (normal) {
            printf("\tsetNumPassengers() normal case PASS\n");
        } else {
            printf("\tsetNumPassengers() normal case FAIL\n");
        }

        if (error) {
            printf("\tsetNumPassengers() edge case 1 PASS\n");
        } else {
            printf("\tsetNumPassengers() edge case 1 FAIL\n");
        }

        if (error2) {
            printf("\tsetNumPassengers() edge case 2 PASS\n");
        } else {
            printf("\tsetNumPassengers() edge case 2 FAIL\n");
        }
    }

    // clearAllRoutes()
    // normal cases (routes exist, no routes exist)
    printf("\nTesting clearAllRoutes()\n");
    {
        Railroad rail;
        bool normal = tester.testClearRoutes(rail);

        if (normal) {
            printf("\tclearAllRoutes() normal cases PASS\n");
        } else {
            printf("\tclearAllRoutes() normal cases FAIL\n");
        }

    }

    printf("\n***All tests completed***\n\n");

    return 0;
}


// testExtHead()
// Input: Railroad, Error case(yes/no)
// Output: extendAtHead test passed
bool Tester::testExtHead(Railroad aRailroad, bool aErrorCase) {
    bool extend = false;  // test pass status

    if (!aErrorCase) {
        // normal case does extendAtHead() return true for every insertion
        for (int i = 0; i < 300; i++) {
            extend = aRailroad.extendAtHead(i, DEFNUMPASS);
            if (!extend) { return extend; }
        }

        // check are all nodes inserted afterward
        Station* curr = aRailroad.m_head;
        int count = 0;

        while (curr != nullptr) {
            count++;
            curr = curr->m_next;
        }
        if (count != 300) { return false; }
        extend = true;
    } else {
        // error case station code < 0
        extend = !aRailroad.extendAtHead(-1, DEFNUMPASS);
    }
    return extend;
}

// testExtTail()
// Input: Railroad, Error case(yes/no)
// Output: extendAtTail() test passed
bool Tester::testExtTail(Railroad aRailroad, bool aErrorCase) {
    bool extend = true;  // test pass status

    if (!aErrorCase) {
        // normal case does extendAtHead() return true for every insertion
        for (int i = 0; i < 300; i++) {
            extend = aRailroad.extendAtHead(i, DEFNUMPASS);
            if (!extend) { return extend; }
        }

        // check are all nodes inserted afterward
        Station* curr = aRailroad.m_head;
        int count = 0;

        while (curr != nullptr) {
            count++;
            curr = curr->m_next;
        }
        if (count != 300) { return false; }
        extend = true;
    } else {
        // error case invalid station code
        extend = !aRailroad.extendAtHead(-1, DEFNUMPASS);
        if (!extend) { return extend; }
    }
    return extend;
}

// testRemove()
// Input: Railroad, Error case(yes/no)
// Output: removeStation() test passed
bool Tester::testRemove(Railroad aRailroad, bool aErrorCase) {
    bool remove = false;  // test pass status

    if (!aErrorCase) {
        // normal case
        for (int i = 0; i < 300; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        for (int i = 0; i < 300; i++) {
            remove = aRailroad.removeStation(i);
            if (!remove) { return remove; }
        }
    } else {
        // error case station doesnt exist
        for (int i = 0; i < 300; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }
        remove = !aRailroad.removeStation(500);
        if (!remove) { return remove; }
    }
    return remove;
}

// testAssignment()
// Input: Railroad, Edge case code (0-2)
// Output: operator= test passed
bool Tester::testAssignment(Railroad aRailroad, int aEdgeCase) {
    bool assign = false;  // test pass status
    Railroad rail, emptyRail;

    if (!aEdgeCase) {
        // normal case
        for (int i = 0; i < 300; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        // deep copy checks
        rail = aRailroad;
        if (&rail == &aRailroad) { return false; }

        Station* curr = aRailroad.m_head;
        Station* curr2 = rail.m_head;
        while (curr != nullptr) {
            if (curr->m_code != curr2->m_code) { return false; }
            if (curr->m_passengers != curr2->m_passengers) { return false; }
            if (curr->m_north != nullptr) {
                if (curr->m_north->m_code != curr2->m_north->m_code) { return false; }
            } else {
                if (curr2->m_north != nullptr) { return false; }
            }

            if (curr->m_east != nullptr) {
                if (curr->m_east->m_code != curr2->m_east->m_code) { return false; }
            } else {
                if (curr2->m_east != nullptr) { return false; }
            }

            if (curr->m_south != nullptr) {
                if (curr->m_south->m_code != curr2->m_south->m_code) { return false; }
            } else {
                if (curr2->m_south != nullptr) { return false; }
            }

            if (curr->m_west != nullptr) {
                if (curr->m_west->m_code != curr2->m_west->m_code) { return false; }
            } else {
                if (curr2->m_west != nullptr) { return false; }
            }
            curr = curr->m_next;
            curr2 = curr2->m_next;
        }

        // self assignment check
        rail = emptyRail;
        rail = rail;
        assign = true;
    } else if (aEdgeCase == 1) {
        // edge case 1 station
        aRailroad.extendAtTail(0, DEFNUMPASS);

        // deep copy checks
        rail = aRailroad;
        if (&rail == &aRailroad) { return false; }
        Station* curr = aRailroad.m_head;
        Station* curr2 = rail.m_head;
        while (curr != nullptr) {
            if (curr->m_code != curr2->m_code) { return false; }
            if (curr->m_passengers != curr2->m_passengers) { return false; }
            if (curr->m_north != nullptr) {
                if (curr->m_north->m_code != curr2->m_north->m_code) { return false; }
            } else {
                if (curr2->m_north != nullptr) { return false; }
            }

            if (curr->m_east != nullptr) {
                if (curr->m_east->m_code != curr2->m_east->m_code) { return false; }
            } else {
                if (curr2->m_east != nullptr) { return false; }
            }

            if (curr->m_south != nullptr) {
                if (curr->m_south->m_code != curr2->m_south->m_code) { return false; }
            } else {
                if (curr2->m_south != nullptr) { return false; }
            }

            if (curr->m_west != nullptr) {
                if (curr->m_west->m_code != curr2->m_west->m_code) { return false; }
            } else {
                if (curr2->m_west != nullptr) { return false; }
            }
            curr = curr->m_next;
            curr2 = curr2->m_next;
        }

        // self assignment check
        rail = emptyRail;
        rail = rail;
        assign = true;
    } else if (aEdgeCase == 2) {
        // edge case 2 stations
        aRailroad.extendAtTail(0, DEFNUMPASS);
        aRailroad.extendAtTail(1, DEFNUMPASS);

        // deep copy checks
        rail = aRailroad;
        if (&rail == &aRailroad) { return false; }
        Station* curr = aRailroad.m_head;
        Station* curr2 = rail.m_head;
        while (curr != nullptr) {
            if (curr->m_code != curr2->m_code) { return false; }
            if (curr->m_passengers != curr2->m_passengers) { return false; }
            if (curr->m_north != nullptr) {
                if (curr->m_north->m_code != curr2->m_north->m_code) { return false; }
            } else {
                if (curr2->m_north != nullptr) { return false; }
            }

            if (curr->m_east != nullptr) {
                if (curr->m_east->m_code != curr2->m_east->m_code) { return false; }
            } else {
                if (curr2->m_east != nullptr) { return false; }
            }

            if (curr->m_south != nullptr) {
                if (curr->m_south->m_code != curr2->m_south->m_code) { return false; }
            } else {
                if (curr2->m_south != nullptr) { return false; }
            }

            if (curr->m_west != nullptr) {
                if (curr->m_west->m_code != curr2->m_west->m_code) { return false; }
            } else {
                if (curr2->m_west != nullptr) { return false; }
            }
            curr = curr->m_next;
            curr2 = curr2->m_next;
        }
        // self assigment check
        rail = emptyRail;
        rail = rail;
        assign = true;
    }
    return assign;
}

// testCopy()
// Input: Railroad, Edge case code (0-2)
// Output: Railroad( Railroad& ) test passed
bool Tester::testCopy(Railroad aRailroad, int aEdgeCase) {
    bool copy = false;  // test pass status

    if (!aEdgeCase) {
        // normal case
        for (int i = 0; i < 300; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        // deep copy checks
        Railroad rail(aRailroad);
        if (&rail == &aRailroad) { return false; }

        Station* curr = aRailroad.m_head;
        Station* curr2 = rail.m_head;

        while (curr != nullptr) {
            if (curr->m_code != curr2->m_code) { return false; }
            if (curr->m_passengers != curr2->m_passengers) { return false; }
            if (curr->m_north != nullptr) {
                if (curr->m_north->m_code != curr2->m_north->m_code) { return false; }
            } else {
                if (curr2->m_north != nullptr) { return false; }
            }

            if (curr->m_east != nullptr) {
                if (curr->m_east->m_code != curr2->m_east->m_code) { return false; }
            } else {
                if (curr2->m_east != nullptr) { return false; }
            }

            if (curr->m_south != nullptr) {
                if (curr->m_south->m_code != curr2->m_south->m_code) { return false; }
            } else {
                if (curr2->m_south != nullptr) { return false; }
            }

            if (curr->m_west != nullptr) {
                if (curr->m_west->m_code != curr2->m_west->m_code) { return false; }
            } else {
                if (curr2->m_west != nullptr) { return false; }
            }
            curr = curr->m_next;
            curr2 = curr2->m_next;
        }
        copy = true;
    } else if (aEdgeCase == 1) {
        // edge case 1 station
        aRailroad.extendAtTail(0, DEFNUMPASS);

        // deep copy checks
        Railroad rail(aRailroad);
        if (&rail == &aRailroad) { return false; }

        Station* curr = aRailroad.m_head;
        Station* curr2 = rail.m_head;

        while (curr != nullptr) {
            if (curr->m_code != curr2->m_code) { return false; }
            if (curr->m_passengers != curr2->m_passengers) { return false; }
            if (curr->m_north != nullptr) {
                if (curr->m_north->m_code != curr2->m_north->m_code) { return false; }
            } else {
                if (curr2->m_north != nullptr) { return false; }
            }

            if (curr->m_east != nullptr) {
                if (curr->m_east->m_code != curr2->m_east->m_code) { return false; }
            } else {
                if (curr2->m_east != nullptr) { return false; }
            }

            if (curr->m_south != nullptr) {
                if (curr->m_south->m_code != curr2->m_south->m_code) { return false; }
            } else {
                if (curr2->m_south != nullptr) { return false; }
            }

            if (curr->m_west != nullptr) {
                if (curr->m_west->m_code != curr2->m_west->m_code) { return false; }
            } else {
                if (curr2->m_west != nullptr) { return false; }
            }
            curr = curr->m_next;
            curr2 = curr2->m_next;
        }
        copy = true;
    } else if (aEdgeCase == 2) {
        // edge case 2 stations
        aRailroad.extendAtTail(0, DEFNUMPASS);
        aRailroad.extendAtTail(1, DEFNUMPASS);

        // deep copy checks
        Railroad rail(aRailroad);
        if (&rail == &aRailroad) { return false; }

        Station* curr = aRailroad.m_head;
        Station* curr2 = rail.m_head;

        while (curr != nullptr) {
            if (curr->m_code != curr2->m_code) { return false; }
            if (curr->m_passengers != curr2->m_passengers) { return false; }
            if (curr->m_north != nullptr) {
                if (curr->m_north->m_code != curr2->m_north->m_code) { return false; }
            } else {
                if (curr2->m_north != nullptr) { return false; }
            }

            if (curr->m_east != nullptr) {
                if (curr->m_east->m_code != curr2->m_east->m_code) { return false; }
            } else {
                if (curr2->m_east != nullptr) { return false; }
            }

            if (curr->m_south != nullptr) {
                if (curr->m_south->m_code != curr2->m_south->m_code) { return false; }
            } else {
                if (curr2->m_south != nullptr) { return false; }
            }

            if (curr->m_west != nullptr) {
                if (curr->m_west->m_code != curr2->m_west->m_code) { return false; }
            } else {
                if (curr2->m_west != nullptr) { return false; }
            }
            curr = curr->m_next;
            curr2 = curr2->m_next;
        }
        copy = true;
    }
    return copy;
}

// testMakeRoute()
// Input: Railroad, Error case code (0-2)
// Output: makeRoute() test passed
bool Tester::testMakeRoute(Railroad aRailroad, int aErrorCase) {
    bool make = false;  // test pass status

    if (!aErrorCase) {
        // normal case
        for (int i = 0; i < 10; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        list<pair<int,DIRECTION>> aRoute;
        aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
        aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute.push_back(pair<int,DIRECTION>(8,EAST));
        aRoute.push_back(pair<int,DIRECTION>(7,EAST));
        aRoute.push_back(pair<int,DIRECTION>(0,WEST));
        aRoute.push_back(pair<int,DIRECTION>(9,NONE));

        make = aRailroad.makeRoute(aRoute);
    } else if (aErrorCase == 1) {
        // error case first station in route does not exist in Linked List
        for (int i = 0; i < 10; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        list<pair<int,DIRECTION>> aRoute;
        aRoute.push_back(pair<int,DIRECTION>(11,NORTH));  // conflict
        aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute.push_back(pair<int,DIRECTION>(8,EAST));
        aRoute.push_back(pair<int,DIRECTION>(7,EAST));
        aRoute.push_back(pair<int,DIRECTION>(0,WEST));
        aRoute.push_back(pair<int,DIRECTION>(9,NONE));

        make = !aRailroad.makeRoute(aRoute);
    } else if (aErrorCase == 2) {
        // error case tries to overwrite existing link
        for (int i = 0; i < 10; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        list<pair<int,DIRECTION>> aRoute, aRoute2;
        aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
        aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute.push_back(pair<int,DIRECTION>(8,NONE));

        aRailroad.makeRoute(aRoute);

        aRoute2.push_back(pair<int,DIRECTION>(3,NORTH));
        aRoute2.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute2.push_back(pair<int,DIRECTION>(6,NONE));  // conflict
        make = !aRailroad.makeRoute(aRoute2);
    }
    return make;
}

// testTravel()
// Input: Railroad, case code (0-2)
// Output: travel() test passed
bool Tester::testTravel(Railroad aRailroad, int aErrorCase) {
    bool travel = true;  // test pass status

    if (!aErrorCase) {
        // normal case traveling existing route
        for (int i = 0; i < 10; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        list<pair<int,DIRECTION>> aRoute;
        aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
        aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute.push_back(pair<int,DIRECTION>(8,EAST));
        aRoute.push_back(pair<int,DIRECTION>(7,EAST));
        aRoute.push_back(pair<int,DIRECTION>(0,WEST));
        aRoute.push_back(pair<int,DIRECTION>(9,NONE));
        aRailroad.makeRoute(aRoute);

        int valid = aRailroad.travel(aRoute);  // traverse route that was just made
        if (valid > -1) { travel = true; }
    } else if (aErrorCase == 1) {
        // error case a station doesn't exist
        for (int i = 0; i < 10; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        list<pair<int,DIRECTION>> aRoute;
        aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
        aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute.push_back(pair<int,DIRECTION>(8,EAST));
        aRoute.push_back(pair<int,DIRECTION>(11,EAST)); // conflict
        aRoute.push_back(pair<int,DIRECTION>(0,WEST));
        aRoute.push_back(pair<int,DIRECTION>(9,NONE));
        aRailroad.makeRoute(aRoute);

        int valid = aRailroad.travel(aRoute);  // travel conflicting route
        if (valid > -1) { travel = false;}
    } else if (aErrorCase == 2) {
        // error case a link doesn't exist
        for (int i = 0; i < 10; i++) {
            aRailroad.extendAtTail(i, DEFNUMPASS);
        }

        list<pair<int,DIRECTION>> aRoute, aRoute2;
        aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
        aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute.push_back(pair<int,DIRECTION>(8,EAST));
        aRoute.push_back(pair<int,DIRECTION>(7,EAST));
        aRoute.push_back(pair<int,DIRECTION>(0,WEST));
        aRoute.push_back(pair<int,DIRECTION>(9,NONE));
        aRailroad.makeRoute(aRoute);

        aRoute2.push_back(pair<int,DIRECTION>(2,NORTH));
        aRoute2.push_back(pair<int,DIRECTION>(5,SOUTH));
        aRoute2.push_back(pair<int,DIRECTION>(8,EAST));
        aRoute2.push_back(pair<int,DIRECTION>(7,NORTH));  // conflict
        aRoute2.push_back(pair<int,DIRECTION>(0,WEST));
        aRoute2.push_back(pair<int,DIRECTION>(9,NONE));

        int valid = aRailroad.travel(aRoute2);  // travel conflicting route
        if (valid > -1) { travel = false; }
    }
    return travel;
}

// testSetPass()
// Input: Railroad, Error case code (0-2)
// Output: setNumPassengers() test passed
bool Tester::testSetPass(Railroad aRailroad, int aErrorCase) {
    bool set = true;  // test pass status

    if (!aErrorCase) {
        // normal case
        for (int i = 0; i < 300; i++) {
            aRailroad.extendAtHead(i, DEFNUMPASS);
            set = aRailroad.setNumPassengers(i, 9);
            if (!set) { return set; }
        }
    } else if (aErrorCase == 1) {
        // error case station doesnt exist
            aRailroad.extendAtHead(0, DEFNUMPASS);
            set = !aRailroad.setNumPassengers(1, 9);
            if (!set) { return set; }
    } else if (aErrorCase == 2) {
        // error case passengers < 0
        aRailroad.extendAtHead(0, DEFNUMPASS);
        set = !aRailroad.setNumPassengers(0, -1);
        if (!set) { return set; }
    }
    return set;
}

// testClearRoutes()
// Input: Railroad, Error case code (0-2)
// Output: clearAllRoutes() test passed
bool Tester::testClearRoutes(Railroad aRailroad) {
    bool clear = true;  // test pass status

    // normal case no routes exist
    aRailroad.clearAllRoutes();
    if (aRailroad.m_head != nullptr || aRailroad.m_tail != nullptr || aRailroad.m_numStations) { return !clear; }

    // normal case routes exist
    for (int i = 0; i < 300; i++) {
        aRailroad.extendAtHead(i, DEFNUMPASS);
    }
    aRailroad.clearAllRoutes();

    // check routes successfully cleared
    Station* curr = aRailroad.m_head;
    while (curr != nullptr) {
        if (curr->m_north || curr->m_east || curr->m_south || curr->m_west) { return !clear; }
        curr = curr->m_next;
    }
    return clear;
}