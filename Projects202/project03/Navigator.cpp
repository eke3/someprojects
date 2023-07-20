//Title: Navigator.cpp
//Author: Eric Ekey
//Email: eekey1@gl.umbc.edu
//Section: 52
//Date: 3/20/2022
//Description: Function definitions for Navigator class

#include "Navigator.h"

// Name: Navigator (string) - Overloaded Constructor
// Desc: Creates a navigator object to manage routes
Navigator::Navigator(string aFileName) {
    m_fileName = aFileName;
}


// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
Navigator::~Navigator() {
    unsigned int numPorts = m_ports.size();  // size of m_ports vector
    unsigned int numRoutes = m_routes.size();  // size of m_routes vector

    // traverse m_ports vector and destroy ports
    cout << "\nDestroying ports...\n";
    for (unsigned int i = 0; i < numPorts; i++) {
        delete m_ports.at(i);
        m_ports.at(i) = nullptr;
    }
    cout << "Ports destroyed successfully\n\n";

    // traverse m_routes vector and destroy routes
    cout << "Destroying routes...\n";
    for (unsigned int i = 0; i < numRoutes; i++) {
        delete m_routes.at(i);
        m_routes.at(i) = nullptr;
    }
    cout << "Routes destroyed successfully\n\n";
}


// Name: Start
// Desc: Loads the file and calls the main menu
void Navigator::Start() {
    ReadFile();
    MainMenu();
}


// Name: DisplayPorts
// Desc: Displays each port in m_ports
void Navigator::DisplayPorts() {
    int portNum = 1;  // numbers for displaying numbered list

    cout << "\n\t***PORTS***\n";
    for (Port* port : m_ports) {
        cout << portNum << ". " << *port << "\n";
        portNum++;
    }
    cout << "\n";
}


// Name: ReadFile
// Desc: Reads in a file that has data about each port including name, location, degrees
//       north and degrees west. Dynamically allocates ports and stores them in m_ports
void Navigator::ReadFile() {
    ifstream dataFile(m_fileName);  // datafile
    string line;    // lines of the datafile, for counting lines
    int numLines = 0, counter = 0;  // line count of datafile
                                    // counter for while loop
    string name, location;  // name of port read from file
                            // location of port read from file
    double north = 0, west = 0; // north coordinates of port, read from datafile
                                // west coordinates of port, read from datafile

    if (dataFile.is_open()) {
        // count number of lines
        while (getline(dataFile, line, '\n')) {
            numLines++;
        }
        dataFile.close();

        // reopen data file
        dataFile.open(m_fileName);
        // read in ports and populate m_ports vector
        while (counter < numLines) {
            getline(dataFile, name, ',');
            getline(dataFile, location, ',');
            dataFile >> north;
            dataFile.ignore();
            dataFile.clear();
            dataFile >> west;
            dataFile.ignore();
            dataFile.clear();

            Port *newPort = new Port(name, location, north, west);  // pointer to new port read from file
            m_ports.push_back(newPort);
            counter++;
        }
    } else {
            cout << "\nData file is not open\n";
    }
    dataFile.close();
}

// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each port in the route.
void Navigator::InsertNewRoute() {
    int portNum = -1;   // user input for port
    Route* newRoute = new Route;    // pointer to new Route object

    DisplayPorts();
    do {
        // prompt user for ports to add to route
        cout << "Which port would you like to add to this route? (-1 to stop)\n";
        while (!(cin >> portNum) || portNum > int(m_ports.size()) || (portNum < 1 && portNum != -1)) {
            cout << "Invalid port\n";
            cin.ignore(10000, '\n');
            cin.clear();
        }

        if (portNum != -1) {
            // align number with vector index
            portNum--;
            string name = m_ports.at(portNum)->GetName();   // port name
            string loc = m_ports.at(portNum)->GetLocation();// port location
            double north = m_ports.at(portNum)->GetNorth(); // port north coordinate
            double west = m_ports.at(portNum)->GetWest();   // port west coordinate

            // add user's selected port to route
            newRoute->InsertEnd(name, loc, north, west);
            cout << "*Added " << name << " to route!*\n";
        }
    } while (portNum != -1);

    // add route to m_routes vector
    m_routes.push_back(newRoute);
}


// Name: MainMenu
// Desc: Displays the main menu and manages exiting
void Navigator::MainMenu() {
    enum menuChoices {
        newRoute = 1,
        displayRoute,
        removePort,
        reverseRoute,
        exitGame
    };  // menu choices
    int menuChoice = 0; // user's menu selection

    do {
        // prompt user to choose a menu option
        cout << "\nWhat would you like to do?\n"
        << "1. Create a new Route\n"
        << "2. Display Route\n"
        << "3. Remove Port from Route\n"
        << "4. Reverse Route\n"
        << "5. Exit\n";

        while (!(cin >> menuChoice) || menuChoice < newRoute || menuChoice > exitGame) {
            cout << "-Invalid menu option-\n";
            cin.ignore(10000, '\n');
            cin.clear();
        }

        // game reacts according to user's menu choice
        switch (menuChoice) {
            case newRoute:
                InsertNewRoute();
                break;
            case displayRoute:
                DisplayRoute();
                break;
            case removePort:
                RemovePortFromRoute();
                break;
            case reverseRoute:
                ReverseRoute();
                break;
            default:
                // handles exitGame, because no other inputs can get to this point
                break;
        }
    } while (menuChoice != exitGame);
}


// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with by displaying numbered list
int Navigator::ChooseRoute() {
    int userInput = -1, routeNum = 1;   // user input
                                        // numbers for displaying numbered list of routes
    if (!m_routes.empty()) {
        // display numbered list of routes
        cout << "\n";
        for (Route *route: m_routes) {
            cout << routeNum << ". " << route->GetName() << "\n";
            routeNum++;
        }
        cout << "\n";

        // prompt user to select a route
        cout << "Which route would you like to use?\n";
        while (!(cin >> userInput) || userInput < 1 || userInput > int(m_routes.size())) {
            cout << "\n-Invalid route-\n";
            cin.ignore(10000, '\n');
            cin.clear();
        }
        // align route number with vector indices
        userInput--;
    }

    return userInput;
}


// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
void Navigator::DisplayRoute() {
    if (!m_routes.empty()) {
        int routeIndex = ChooseRoute(); // index of route chosen by user
        double routeDistance = RouteDistance(m_routes.at(routeIndex));  // total distance of route selected

        m_routes.at(routeIndex)->DisplayRoute();
        cout << "The distance of this route is " << routeDistance << " miles.\n";
    } else {
        cout << "\n-There are no routes to display-\n";
    }
}


// Name: RemovePortFromRoute()
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       User selects one of the routes to remove a port from.
//       Displays a numbered list of all ports in selected route.
//       User selects port to remove from list.
//       Removes port from route. If first or last port removed, updates name of route.
void Navigator::RemovePortFromRoute() {
    if (!m_routes.empty()) {
        int routeIndex = ChooseRoute(); // index of route chosen by user

        if (m_routes.at(routeIndex)->GetSize() > 1) {
            int portIndex = 0;  // number of port to choose

            // display ports in selected route
            m_routes.at(routeIndex)->DisplayRoute();

            // prompt user to choose a port to remove
            cout << "Which port would you like to remove?\n";
            while (!(cin >> portIndex) || portIndex > m_routes.at(routeIndex)->GetSize() || portIndex < 1) {
                cout << "\n-Invalid port-\n";
                cin.ignore(10, '\n');
                cin.clear();
            }
            // align port number with vector indices
            portIndex--;

            // remove the selected port and display the modified route
            m_routes.at(routeIndex)->RemovePort(portIndex);
            m_routes.at(routeIndex)->DisplayRoute();
        } else {
            cout << "\n-Need more than 1 port to modify-\n";
        }
    } else {
        cout << "\n-No routes available to modify-\n";
    }
}


// Name: RouteDistance
// Desc: Calculates the total distance of a route
double Navigator::RouteDistance(Route* aRoute) {
    double totalDistance = 0;   // total distance of route

    if (aRoute->GetSize() > 1) {
        int portIndex = 0;  // index of first port in route
        Port* current = aRoute->GetData(portIndex); // pointer to current port in route
        Port* next = current->GetNext();    // pointer to next port in route

        // traverse route and sum distance between ports
        while (next != nullptr) {
            double north1 = current->GetNorth();
            double west1 = current->GetWest();
            double north2 = next->GetNorth();
            double west2 = next->GetWest();
            double dist = CalcDistance(north1, west1, north2, west2);

            totalDistance += dist;
            current = next;
            next = next->GetNext();
        }
    }

    return totalDistance;
}


// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route  and the route is reversed
void Navigator::ReverseRoute() {
    if (!m_routes.empty()) {
        int routeIndex = ChooseRoute(); // index of user's selected route

        // reverse selected route and display updated route
        m_routes.at(routeIndex)->ReverseRoute();
        cout << "*Route " << routeIndex + 1 << " reversed!*\n";
        m_routes.at(routeIndex)->DisplayRoute();
    } else {
        cout << "\n-No routes available to reverse-\n";
    }
}