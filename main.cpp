/**
 * Fall 2021 PA 04 - Flight Planner Template Repo.
 * Based on PA 02 Template repo
 */

/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
#include "FlightPlanner.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc == 1) { //runs CATCH tests when no command line arguments are provided
        runCatchTests();
    }
    else {
        FlightPlanner myTrip(argv); //FlightPlanner object where the main functionality occurs
        myTrip.planFlight(); //starts the program
    }
    return 0;
}