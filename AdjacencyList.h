//
// Created by mikec_g1kgiu8 on 10/20/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_ADJACENCYLIST_H
#define INC_21F_FLIGHT_PLANNER_ADJACENCYLIST_H

#include "DSLinkList.h"
#include "OriginatingCity.h"

class AdjacencyList {
    private:
        //Private Variable
        DSLinkList<OriginatingCity> cities;

    public:
        //Functions
        void addFlight(string, string, double, int, string);
        DSLinkList<OriginatingCity>& getCities();
};


#endif //INC_21F_FLIGHT_PLANNER_ADJACENCYLIST_H
