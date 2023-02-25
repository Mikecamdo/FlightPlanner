//
// Created by mikec_g1kgiu8 on 10/20/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_ORIGINATINGCITY_H
#define INC_21F_FLIGHT_PLANNER_ORIGINATINGCITY_H

#include "DSLinkList.h"
#include "DestinationCity.h"


class OriginatingCity {
    private:
        //Private Variables
        string name;
        DSLinkList<DestinationCity> flights;

    public:
        //Constructors
        OriginatingCity();
        OriginatingCity(string);

        //Functions
        void addDestination(string, double, int, string);
        string getName();
        DSLinkList<DestinationCity>& getFlights();
};


#endif //INC_21F_FLIGHT_PLANNER_ORIGINATINGCITY_H
