//
// Created by mikec_g1kgiu8 on 10/25/2021.
//

#include "FlightPlanner.h"
#include <sstream>
#include <iomanip>

FlightPlanner::FlightPlanner() { //default constructor
    argv = nullptr;
}

FlightPlanner::FlightPlanner(char** files) {
    argv = files;
}

void FlightPlanner::planFlight() { //main functionality of program
    input = openInputFile(1); //opens the first input file

    if (!input.is_open()) {
        cout << "First input file could not be opened" << endl;
        return;
    }

    int numFlights = 0;
    input >> numFlights; //reads the first line and gets the number of flights in the file

    for (int i = 0; i < numFlights; i++) { //adds each direct flight to the adjacency list (along with all data about that flight)
        string origCity, destCity, carrier;
        double cost;
        int time;
        input >> origCity >> destCity >> cost >> time >> carrier;

        planner.addFlight(origCity, destCity, cost, time, carrier); //adds flight from the originating city to the destination city
        planner.addFlight(destCity, origCity, cost, time, carrier); //adds flight from the destination city to the originating city
    }

    input.close(); //closes the first input file

    input = openInputFile(2); //opens the second input file

    if (!input.is_open()) {
        cout << "Second input file could not be opened" << endl;
        return;
    }

    input >> numFlights;
    output = openOutputFile(); //opens the output file
    output << fixed << setprecision(2); //sets the cost to output to two decimal places

    for (int i = 0; i < numFlights; i++) { //goes through all requested flights
        string origCity, destcity;
        char priority;

        input >> origCity >> destcity >> priority;
        if (priority == 'T') { //if the priority was time
            output << "Flight " << i + 1 << ": " << origCity << ", " << destcity << " (Time)" << endl; //output flight header
        } else if (priority == 'C') { //if the priority was cost
            output << "Flight " << i + 1 << ": " << origCity << ", " << destcity << " (Cost)" << endl; //output flight header
        }
        findOptimalFlights(origCity, destcity, priority); //finds the best flights and prints them to the output file
    }
    input.close(); //closes the second input file
    output.close(); //closes the output file

}

ifstream FlightPlanner::openInputFile(int fileNum) { //opens the input file
    ifstream fileIn(argv[fileNum]);
    return fileIn;
}

ofstream FlightPlanner::openOutputFile() { //opens the output file
    ofstream fileOut(argv[3]);
    return fileOut;
}

void FlightPlanner::findOptimalFlights(string origCity, string destCity, char priority) {
    if (origCity == destCity) { //if a flight was requested from a city to itself
        output << "  Error: Cannot schedule flights from " << origCity << " to itself" << endl;
        return;
    }

    planner.getCities().setCurrHead();
    while (planner.getCities().getCurrValue().getName() != origCity) { //finds the originating city in the adjacency list
        planner.getCities().advanceCurr();
        if ((!planner.getCities().hasNext()) && (planner.getCities().getCurrValue().getName() != origCity)) { //if the originating city has no flight (and thus isn't in the adjacency list)
            output << "  Error: No flights found originating from " << origCity << endl;
            return;
        }
    }

    DSStack<DSStack<DestinationCity>> allFlights = findAllPaths(origCity, destCity); //finds every possible flight path

    int times[3]; //array for the times of the 3 optimal flight paths
    times[0] = -1;
    times[1] = -1; //placeholder is -1 (since time should never be negative)
    times[2] = -1;

    double costs[3]; //array for the costs of the 3 optimal flight paths
    costs[0] = -1;
    costs[1] = -1; //placeholder is -1 (since cost should never be negative)
    costs[2] = -1;

    DSVector<string> bestCityNames[3]; //array for the names of the cities in the 3 optimal flight paths

    DSVector<string> bestAirlineNames[3]; //array for the airline names in the 3 optimal flight paths

    findBestPaths(times, costs, bestCityNames, bestAirlineNames, allFlights, origCity, priority); //finds the 3 best flight paths (based on priority)

    if ((times[0] < 0) && (times[1] < 0) && (times[2] < 0)) { //if no flight paths were found
        output << "  Error: No flights found from " << origCity << " to " << destCity << endl;
    } else {
        int counter, otherCounter; //variables used to determine when to output arrows, parentheses, and newlines
        if (times[0] > 0) { //only prints if times[0] isn't the placeholder (meaning there is a flight to print)
            output << "  Itinerary 1:" << endl;
            counter = 0;
            otherCounter = bestAirlineNames[0].length() - 1;
            output << "    ";
            for (int i = bestCityNames[0].length() - 1; i >= 0; i--) {
                output << bestCityNames[0].at(i) << " ";
                counter++;
                if (counter == 1) {
                    output << "-> ";
                } else if (counter >= 2 && i != 0) {
                    output << "(" << bestAirlineNames[0].at(otherCounter) << ")" << endl;
                    otherCounter--;
                    output << "    " << bestCityNames[0].at(i) << " -> ";
                } else if (i == 0) {
                    output << "(" << bestAirlineNames[0].at(otherCounter) << ")";
                }
            }
            output << endl;
            output << "    Totals for Itinerary 1:  Time: " << times[0] << " Cost: " << costs[0] << endl;
        }
        if (times[1] > 0) { //only prints if times[1] isn't the placeholder (meaning there is a flight to print)
            output << "  Itinerary 2:" << endl;
            counter = 0;
            otherCounter = bestAirlineNames[1].length() - 1;
            output << "    ";
            for (int i = bestCityNames[1].length() - 1; i >= 0; i--) {
                output << bestCityNames[1].at(i) << " ";
                counter++;
                if (counter == 1) {
                    output << "-> ";
                } else if (counter >= 2 && i != 0) {
                    output << "(" << bestAirlineNames[1].at(otherCounter) << ")" << endl;
                    otherCounter--;
                    output << "    " << bestCityNames[1].at(i) << " -> ";
                } else if (i == 0) {
                    output << "(" << bestAirlineNames[1].at(otherCounter) << ")";
                }
            }
            output << endl;
            output << "    Totals for Itinerary 2:  Time: " << times[1] << " Cost: " << costs[1] << endl;
        }

        if (times[2] > 0) { //only prints if times[2] isn't the placeholder (meaning there is a flight to print)
            output << "  Itinerary 3:" << endl;
            counter = 0;
            otherCounter = bestAirlineNames[2].length() - 1;
            output << "    ";
            for (int i = bestCityNames[2].length() - 1; i >= 0; i--) {
                output << bestCityNames[2].at(i) << " ";
                counter++;
                if (counter == 1) {
                    output << "-> ";
                } else if (counter >= 2 && i != 0) {
                    output << "(" << bestAirlineNames[2].at(otherCounter) << ")" << endl;
                    otherCounter--;
                    output << "    " << bestCityNames[2].at(i) << " -> ";
                } else if (i == 0) {
                    output << "(" << bestAirlineNames[2].at(otherCounter) << ")";
                }
            }
            output << endl;
            output << "    Totals for Itinerary 3:  Time: " << times[2] << " Cost: " << costs[2] << endl;
        }
    }
}

DSStack<DestinationCity> FlightPlanner::saveFlight(DSStack<DestinationCity> flight) {
    return flight; //returns a copy of the flight path
}

DSStack<DSStack<DestinationCity>> FlightPlanner::findAllPaths(string& origCity, string& destCity) { //finds every possible flight path
    DSStack<DestinationCity> possibleFlight; //stack for the iterative backtracking
    DSStack<DSStack<DestinationCity>> allFlights; //stack that holds every flight path
    DSVector<string> onTheStack; //vector that holds the names of the cities on the stack

    DestinationCity tempCity(origCity, -1, -1, ""); //empty variable that represents the originating city on the stack
    possibleFlight.push(tempCity);
    onTheStack.push_back(origCity);

    planner.getCities().setCurrHead();
    while (!planner.getCities().currIsNull()) { //resets each current pointer in the Destination Cities Linked List to head
        planner.getCities().getCurrValue().getFlights().setCurrHead();
        planner.getCities().advanceCurr();
    }
    planner.getCities().setCurrHead(); //sets the current pointer in the Originating Cities Linked List to head

    while (!possibleFlight.isEmpty()) { //goes through every possible flight path (iterative backtracking)
        if (possibleFlight.peek().getName() !=
            planner.getCities().getCurrValue().getName()) { //resets iterator when a new city is on the top of the stack
            planner.getCities().setCurrHead();
            while (planner.getCities().getCurrValue().getName() != possibleFlight.peek().getName()) {
                planner.getCities().advanceCurr();
            }
        }
        if (possibleFlight.peek().getName() == destCity) { //when the top of the stack is the destination city
            allFlights.push(saveFlight(possibleFlight)); //saves the flight path
            possibleFlight.pop(); //pop the top off
            onTheStack.pop_back(); //remove the city name from the vector
        } else {
            if (planner.getCities().getCurrValue().getFlights().currIsNull()) { //when the end of a linked list is reached
                possibleFlight.pop(); //pop the top off
                onTheStack.pop_back(); //remove the city name from the vector
                planner.getCities().getCurrValue().getFlights().setCurrHead(); //reset the current pointer to head
            } else if (onTheStack.find(planner.getCities().getCurrValue().getFlights().getCurrValue().getName()) != -1) { //if the destination city is already on the stack
                planner.getCities().getCurrValue().getFlights().advanceCurr(); //advance curr
            } else { //if a city not on the stack is found
                possibleFlight.push(planner.getCities().getCurrValue().getFlights().getCurrValue()); //add the city to the stack
                onTheStack.push_back(planner.getCities().getCurrValue().getFlights().getCurrValue().getName()); //add the city name to the vector
                planner.getCities().getCurrValue().getFlights().advanceCurr(); //advance curr
            }
        }
    }
    return allFlights; //return all possible flight paths
}

void FlightPlanner::findBestPaths(int times[], double costs[], DSVector<string> bestCityNames[],
                                  DSVector<string> bestAirlineNames[], DSStack<DSStack<DestinationCity>>& allFlights,
                                  string& origCity, char& priority) { //finds and stores the 3 optimal flight paths

    while (!allFlights.isEmpty()) { //goes through all possible flight paths
        if (priority == 'T') { //when the priority is time
            DSStack<DestinationCity> path = allFlights.pop(); //removes the top flight path and stores it

            int totalTime = 0; //time for this flight path
            double totalCost = 0.0; //cost for this flight path
            DSVector<string> cityNames; //every city visited in this flight path
            DSVector<string> airlineNames; //every airline name used for each flight in this flight path

            while (!path.isEmpty()) { //goes through each city in the flight path
                DestinationCity temp = path.pop(); //removes the top city and stores it
                if (temp.getName() == origCity) { //when the bottom of the stack is reached
                    cityNames.push_back(origCity); //store only the name from the dummy variable
                } else {
                    totalTime += temp.getFlightTime(); //add the flight time to the total time of the flight path
                    totalCost += temp.getCost(); //add the flight cost to the total cost of the flight path
                    cityNames.push_back(temp.getName()); //add the city name to the vector

                    if (airlineNames.length() > 0 && temp.getCarrier() != airlineNames.at(airlineNames.length() - 1)) {
                        totalTime += 27; //adds time penalty for changing airline carrier
                    }
                    airlineNames.push_back(temp.getCarrier()); //add the airline name to the vector
                }
            }
            int numLayovers = cityNames.length() - 2; //adds layover penalties
            totalCost += (numLayovers * 23.0);
            totalTime += (numLayovers * 43);

            if (totalTime == times[0] || totalTime == times[1] || totalTime == times[2]) { //if the flight path's time equals an already stored flight path's time
                if (totalTime == times[0]) { //if the flight path's time equals the first stored flight path's time
                    if (totalCost < costs[0]) { //if the flight path's cost is less than the first stored flight path's cost
                        //adds the flight path's data to the front, shifting other data back
                        times[2] = times[1];
                        costs[2] = costs[1];
                        bestCityNames[2] = bestCityNames[1];
                        bestAirlineNames[2] = bestAirlineNames[1];

                        times[1] = times[0];
                        costs[1] = costs[0];
                        bestCityNames[1] = bestCityNames[0];
                        bestAirlineNames[1] = bestAirlineNames[0];

                        times[0] = totalTime;
                        costs[0] = totalCost;
                        bestCityNames[0] = cityNames;
                        bestAirlineNames[0] = airlineNames;
                        continue;
                    }
                } if (totalTime == times[1]) { //if the flight path's time equals the second stored flight path's time
                    if (totalCost < costs[1]) { //if the flight path's cost is less than the second stored flight path's cost
                        //adds the flight path's data to the middle, shifting other data back
                        times[2] = times[1];
                        costs[2] = costs[1];
                        bestCityNames[2] = bestCityNames[1];
                        bestAirlineNames[2] = bestAirlineNames[1];

                        times[1] = totalTime;
                        costs[1] = totalCost;
                        bestCityNames[1] = cityNames;
                        bestAirlineNames[1] = airlineNames;
                        continue;
                    }
                } if (totalTime == times[2]) { //if the flight path's time equals the third stored flight path's time
                    if (totalCost < costs[2]) { //if the flight path's cost is less than the third stored flight path's cost
                        //adds the flight path's data to the back
                        times[2] = totalTime;
                        costs[2] = totalCost;
                        bestCityNames[2] = cityNames;
                        bestAirlineNames[2] = airlineNames;
                        continue;
                    }
                }
            }
            if (totalTime < times[0] || times[0] == -1) { //if the flight's path time is the fastest yet, or if only the placeholder is stored
                //adds the flight path's data to the front, shifting other data back
                times[2] = times[1];
                costs[2] = costs[1];
                bestCityNames[2] = bestCityNames[1];
                bestAirlineNames[2] = bestAirlineNames[1];

                times[1] = times[0];
                costs[1] = costs[0];
                bestCityNames[1] = bestCityNames[0];
                bestAirlineNames[1] = bestAirlineNames[0];

                times[0] = totalTime;
                costs[0] = totalCost;
                bestCityNames[0] = cityNames;
                bestAirlineNames[0] = airlineNames;
            } else if (totalTime < times[1] || times[1] == -1) { //if the flight's path time is the second fastest yet, or if only the placeholder is stored
                //adds the flight path's data to the middle, shifting other data back
                times[2] = times[1];
                costs[2] = costs[1];
                bestCityNames[2] = bestCityNames[1];
                bestAirlineNames[2] = bestAirlineNames[1];

                times[1] = totalTime;
                costs[1] = totalCost;
                bestCityNames[1] = cityNames;
                bestAirlineNames[1] = airlineNames;
            } else if (totalTime < times[2] || times[2] == -1) { //if the flight's path time is the third fastest yet, or if only the placeholder is stored
                //adds the flight path's data to the back
                times[2] = totalTime;
                costs[2] = totalCost;
                bestCityNames[2] = cityNames;
                bestAirlineNames[2] = airlineNames;
            }

        } else if (priority == 'C') { //when the priority is cost
            DSStack<DestinationCity> path = allFlights.pop(); //removes the top flight path and stores it

            int totalTime = 0; //time for this flight path
            double totalCost = 0.0; //cost for this flight path
            DSVector<string> cityNames; //every city visited in this flight path
            DSVector<string> airlineNames; //every airline name used for each flight in this flight path

            while (!path.isEmpty()) {
                DestinationCity temp = path.pop(); //removes the top city and stores it
                if (temp.getName() == origCity) { //when the bottom of the stack is reached
                    cityNames.push_back(origCity); //only store the name of the dummy variable
                } else {
                    totalTime += temp.getFlightTime(); //add the flight time to the total time of the flight path
                    totalCost += temp.getCost(); //add the flight cost to the total cost of the flight path
                    cityNames.push_back(temp.getName()); //add the city name to the vector

                    if (airlineNames.length() > 0 && temp.getCarrier() != airlineNames.at(airlineNames.length() - 1)) {
                        totalTime += 27; //adds time penalty for changing airline carrier
                    }
                    airlineNames.push_back(temp.getCarrier()); //add the airline name to the vector
                }
            }
            int numLayovers = cityNames.length() - 2; //adds layover penalties
            totalCost += (numLayovers * 23.0);
            totalTime += (numLayovers * 43);

            if (totalCost == costs[0] || totalCost == costs[1] || totalCost == costs[2]) { //if the flight path's cost equals an already stored flight path's cost
                if (totalCost == costs[0]) { //if the flight path's cost equals the first stored flight path's cost
                    if (totalTime < times[0]) { //if the flight path's time is less than the first stored flight path's time
                        //adds the flight path's data to the front, shifting other data back
                        times[2] = times[1];
                        costs[2] = costs[1];
                        bestCityNames[2] = bestCityNames[1];
                        bestAirlineNames[2] = bestAirlineNames[1];

                        times[1] = times[0];
                        costs[1] = costs[0];
                        bestCityNames[1] = bestCityNames[0];
                        bestAirlineNames[1] = bestAirlineNames[0];

                        times[0] = totalTime;
                        costs[0] = totalCost;
                        bestCityNames[0] = cityNames;
                        bestAirlineNames[0] = airlineNames;
                        continue;
                    }
                } if (totalCost == costs[1]) { //if the flight path's cost equals the second stored flight path's cost
                    if (totalTime < times[1]) { //if the flight path's time is less than the second stored flight path's time
                        //adds the flight path's data to the middle, shifting other data back
                        times[2] = times[1];
                        costs[2] = costs[1];
                        bestCityNames[2] = bestCityNames[1];
                        bestAirlineNames[2] = bestAirlineNames[1];

                        times[1] = totalTime;
                        costs[1] = totalCost;
                        bestCityNames[1] = cityNames;
                        bestAirlineNames[1] = airlineNames;
                        continue;
                    }
                } if (totalCost == costs[2]) { //if the flight path's cost equals the third stored flight path's cost
                    if (totalTime < times[2]) { //if the flight path's time is less than the third stored flight path's time
                        //adds the flight path's data to the back
                        times[2] = totalTime;
                        costs[2] = totalCost;
                        bestCityNames[2] = cityNames;
                        bestAirlineNames[2] = airlineNames;
                        continue;
                    }
                }
            }
            if (totalCost < costs[0] || costs[0] == -1) { //if the flight's path cost is the cheapest yet, or if only the placeholder is stored
                //adds the flight path's data to the front, shifting other data back
                times[2] = times[1];
                costs[2] = costs[1];
                bestCityNames[2] = bestCityNames[1];
                bestAirlineNames[2] = bestAirlineNames[1];

                times[1] = times[0];
                costs[1] = costs[0];
                bestCityNames[1] = bestCityNames[0];
                bestAirlineNames[1] = bestAirlineNames[0];

                times[0] = totalTime;
                costs[0] = totalCost;
                bestCityNames[0] = cityNames;
                bestAirlineNames[0] = airlineNames;
            } else if (totalCost < costs[1] || costs[1] == -1) { //if the flight's path cost is the second cheapest yet, or if only the placeholder is stored
                //adds the flight path's data to the middle, shifting other data back
                times[2] = times[1];
                costs[2] = costs[1];
                bestCityNames[2] = bestCityNames[1];
                bestAirlineNames[2] = bestAirlineNames[1];

                times[1] = totalTime;
                costs[1] = totalCost;
                bestCityNames[1] = cityNames;
                bestAirlineNames[1] = airlineNames;
            } else if (totalCost < costs[2] || costs[2] == -1) { //if the flight's path cost is the third cheapest yet, or if only the placeholder is stored
                //adds the flight path's data to the back
                times[2] = totalTime;
                costs[2] = totalCost;
                bestCityNames[2] = cityNames;
                bestAirlineNames[2] = airlineNames;
            }
        }
    }
}
