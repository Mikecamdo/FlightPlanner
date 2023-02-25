//
// Created by mikec_g1kgiu8 on 10/25/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H
#define INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H

#include "AdjacencyList.h"
#include "DSStack.h"
#include "DSVector.h"
#include <fstream>

using namespace std;

class FlightPlanner {
    private:
        //Private Variables
        AdjacencyList planner;
        char** argv;
        ifstream input;
        ofstream output;

        //Private Functions
        ifstream openInputFile(int);
        ofstream openOutputFile();
        void findOptimalFlights(string, string, char);
        DSStack<DestinationCity> saveFlight(DSStack<DestinationCity>);
        DSStack<DSStack<DestinationCity>> findAllPaths(string&, string&); //iterative backtracker
        void findBestPaths(int[], double[], DSVector<string>[], DSVector<string>[], DSStack<DSStack<DestinationCity>>&, string&, char&);

    public:
        //Constructors
        FlightPlanner();
        FlightPlanner(char**);

        //Functions
        void planFlight();
};




#endif //INC_21F_FLIGHT_PLANNER_FLIGHTPLANNER_H
