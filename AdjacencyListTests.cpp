//
// Created by mikec_g1kgiu8 on 10/26/2021.
//

#include "catch.hpp"
#include "AdjacencyList.h"

TEST_CASE("AdjacencyList Class", "[AdjacencyList]") {
    AdjacencyList tester1;

    SECTION("addFlight and getCities functions") {
        tester1.addFlight("Dallas", "Houston", 37, 42, "American");

        tester1.getCities().setCurrHead();
        CHECK(tester1.getCities().getCurrValue().getName() == "Dallas");

        tester1.getCities().getCurrValue().getFlights().setCurrHead();
        CHECK(tester1.getCities().getCurrValue().getFlights().getCurrValue().getName() == "Houston");
        CHECK(tester1.getCities().getCurrValue().getFlights().getCurrValue().getCost() == 37);
        CHECK(tester1.getCities().getCurrValue().getFlights().getCurrValue().getFlightTime() == 42);
        CHECK(tester1.getCities().getCurrValue().getFlights().getCurrValue().getCarrier() == "American");
    }

    SECTION("OriginatingCity") {
        OriginatingCity tester2("Houston");
        tester2.addDestination("Chicago", 49, 52, "Southwest");
        tester2.addDestination("Boston", 78, 77, "Delta");

        CHECK(tester2.getName() == "Houston");

        tester2.getFlights().setCurrHead();
        CHECK(tester2.getFlights().getCurrValue().getName() == "Chicago");
        CHECK(tester2.getFlights().getCurrValue().getCost() == 49);
        CHECK(tester2.getFlights().getCurrValue().getFlightTime() == 52);
        CHECK(tester2.getFlights().getCurrValue().getCarrier() == "Southwest");

        tester2.getFlights().advanceCurr();
        CHECK(tester2.getFlights().getCurrValue().getName() == "Boston");
        CHECK(tester2.getFlights().getCurrValue().getCost() == 78);
        CHECK(tester2.getFlights().getCurrValue().getFlightTime() == 77);
        CHECK(tester2.getFlights().getCurrValue().getCarrier() == "Delta");
    }

    SECTION("DestinationCity") {
        DestinationCity tester2("Dallas", 66, 43, "American");
        CHECK(tester2.getName() == "Dallas");
        CHECK(tester2.getCost() == 66);
        CHECK(tester2.getFlightTime() == 43);
        CHECK(tester2.getCarrier() == "American");
    }

    SECTION("Additional Testing") {
        DSLinkList<OriginatingCity> tester2;
        OriginatingCity temp1("Houston");
        OriginatingCity temp2("Dallas");

        tester2.add(temp1);
        tester2.add(temp2);

        tester2.setCurrHead();

        tester2.getCurrValue().addDestination("Fresno", 37, 37, "American");
        tester2.getCurrValue().addDestination("Chicago", 65, 98, "Southwest");
        tester2.getCurrValue().addDestination("Norfolk", 54, 77, "Delta");

        tester2.advanceCurr();

        tester2.getCurrValue().addDestination("Seattle", 44, 56, "Southwest");
        tester2.getCurrValue().addDestination("Boise", 67, 25, "Southwest");
        tester2.getCurrValue().addDestination("Austin", 54, 22, "Delta");

        tester2.setCurrHead();
        tester2.getCurrValue().getFlights().setCurrHead();
        tester2.getCurrValue().getFlights().advanceCurr();
        CHECK(tester2.getCurrValue().getFlights().getCurrValue().getName() == "Chicago");

        tester2.advanceCurr();
        tester2.getCurrValue().getFlights().setCurrHead();
        CHECK(tester2.getCurrValue().getFlights().getCurrValue().getName() == "Seattle");

        tester2.setCurrHead();
        tester2.getCurrValue().getFlights().advanceCurr();
        CHECK(tester2.getCurrValue().getFlights().getCurrValue().getName() == "Norfolk");
    }
}
