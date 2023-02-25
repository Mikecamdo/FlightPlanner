//
// Created by mikec_g1kgiu8 on 10/20/2021.
//

#include "AdjacencyList.h"

void AdjacencyList::addFlight(string origCity, string destCity, double cost, int time, string carrier) {
    if (!cities.isEmpty()) { //if the linked list is not empty
        cities.setCurrHead();
        while (!cities.currIsNull()) { //iterate through all current Originating Cities in the linked list
            if (cities.getCurrValue().getName() == origCity) { //if the Originating City is already in the Linked List
                DestinationCity newCity(destCity, cost, time, carrier); //add the Destination City
                cities.getCurrValue().getFlights().add(newCity);
                return;
            } else {
                cities.advanceCurr();
            }
        }
    }

    OriginatingCity newCity(origCity); //if the Originating City is not already in the Linked List, create and add it
    newCity.addDestination(destCity, cost, time, carrier); //add the destination to the Originating City
    cities.add(newCity);
}

DSLinkList<OriginatingCity>& AdjacencyList::getCities() {
    return cities; //returns the Linked List of Originating Cities
}
