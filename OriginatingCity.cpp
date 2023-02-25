//
// Created by mikec_g1kgiu8 on 10/20/2021.
//

#include "OriginatingCity.h"

OriginatingCity::OriginatingCity() { //default constructor
    name = "";
}

OriginatingCity::OriginatingCity(string cityName) {
    name = cityName;
}

void OriginatingCity::addDestination(string destinationCity, double cost, int time, string carrier) { //adds a destination to the city
    DestinationCity newCity(destinationCity, cost, time, carrier);
    flights.add(newCity);
}

string OriginatingCity::getName() {
    return name; //returns the city's name
}

DSLinkList<DestinationCity>& OriginatingCity::getFlights() {
    return flights; //returns all possible outgoing flights from the city
}
