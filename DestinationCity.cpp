//
// Created by mikec_g1kgiu8 on 10/20/2021.
//

#include "DestinationCity.h"

DestinationCity::DestinationCity() { //default constructor
    name = "";
    flightTime = -1;
    cost = -1;
    carrier = "";
}

DestinationCity::DestinationCity(string cityName, double price, int time, string carrierName) {
    name = cityName;
    flightTime = time;
    cost = price;
    carrier = carrierName;
}

string& DestinationCity::getName() {
    return name; //returns the name of the city
}

int DestinationCity::getFlightTime() {
    return flightTime; //returns the flight time of the flight to the city
}

double DestinationCity::getCost() {
    return cost; //returns the cost of the flight to the city
}

string DestinationCity::getCarrier() {
    return carrier; //returns the airline/carrier name of the flight to the city
}
