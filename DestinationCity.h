//
// Created by mikec_g1kgiu8 on 10/20/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DESTINATIONCITY_H
#define INC_21F_FLIGHT_PLANNER_DESTINATIONCITY_H

#include <string>

using namespace std;

class DestinationCity {
    private:
        //Private Variables
        string name;
        int flightTime;
        double cost;
        string carrier;

    public:
        //Constructors
        DestinationCity();
        DestinationCity(string, double, int, string);

        //Functions
        string& getName();
        int getFlightTime();
        double getCost();
        string getCarrier();

};


#endif //INC_21F_FLIGHT_PLANNER_DESTINATIONCITY_H
