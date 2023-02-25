//
// Created by mikec_g1kgiu8 on 10/24/2021.
//

#include "catch.hpp"
#include "DSLinkList.h"

using namespace std;

TEST_CASE("DSLinkList class", "[DSLinkList]") {
    DSLinkList<int> tester1;
    tester1.add(2);
    tester1.add(17);
    tester1.add(2001);

    DSLinkList<char> tester2;
    tester2.add('c');
    tester2.add('Z');
    tester2.add('w');

    DSLinkList<string> tester3;
    tester3.add("Hello");
    tester3.add("This is a pretty long string");
    tester3.add("Yes");

    SECTION("add function") {

        int temp1[] = {2, 17, 2001};
        tester1.setCurrHead();

        CHECK(temp1[0] == tester1.getCurrValue());
        tester1.advanceCurr();
        CHECK(temp1[1] == tester1.getCurrValue());
        tester1.advanceCurr();
        CHECK(temp1[2] == tester1.getCurrValue());

        tester1.add(4);
        tester1.advanceCurr();
        CHECK(tester1.getCurrValue() == 4);



        char temp2[] = {'c', 'Z', 'w'};
        tester2.setCurrHead();

        CHECK(temp2[0] == tester2.getCurrValue());
        tester2.advanceCurr();
        CHECK(temp2[1] == tester2.getCurrValue());
        tester2.advanceCurr();
        CHECK(temp2[2] == tester2.getCurrValue());

        tester2.add('!');
        tester2.advanceCurr();
        CHECK(tester2.getCurrValue() == '!');


        string temp3[] = {"Hello", "This is a pretty long string", "Yes"};

        tester3.setCurrHead();

        CHECK(temp3[0] == tester3.getCurrValue());
        tester3.advanceCurr();
        CHECK(temp3[1] == tester3.getCurrValue());
        tester3.advanceCurr();
        CHECK(temp3[2] == tester3.getCurrValue());

        tester3.add("Oh yeah!");
        tester3.advanceCurr();
        CHECK(tester3.getCurrValue() == "Oh yeah!");
    }

    SECTION("getLastData function") {
        CHECK(tester1.getLastData() == 2001);
        CHECK(tester2.getLastData() == 'w');
        CHECK(tester3.getLastData() == "Yes");
    }

    SECTION("removeLast function") {
        tester1.add(57);
        tester2.add('D');
        tester3.add("Ha");

        tester1.setCurrHead();
        for(int i = 0; i < 3; i++) {
            tester1.advanceCurr();
        }

        tester2.setCurrHead();
        for(int i = 0; i < 3; i++) {
            tester2.advanceCurr();
        }

        tester3.setCurrHead();
        for(int i = 0; i < 3; i++) {
            tester3.advanceCurr();
        }

        CHECK(tester1.getCurrValue() == 57);
        CHECK(tester2.getCurrValue() == 'D');
        CHECK(tester3.getCurrValue() == "Ha");

        tester1.removeLast();
        tester2.removeLast();
        tester3.removeLast();

        CHECK(tester1.getLastData() == 2001);
        CHECK(tester2.getLastData() == 'w');
        CHECK(tester3.getLastData() == "Yes");

    }

    SECTION("isEmpty function") {
        DSLinkList<bool> tester4;

        CHECK(tester1.isEmpty() == false);
        CHECK(tester2.isEmpty() == false);
        CHECK(tester3.isEmpty() == false);
        CHECK(tester4.isEmpty() == true);
    }

    SECTION("setCurrHead function") {
        tester1.setCurrHead();
        tester2.setCurrHead();
        tester3.setCurrHead();

        CHECK(tester1.getCurrValue() == 2);
        CHECK(tester2.getCurrValue() == 'c');
        CHECK(tester3.getCurrValue() == "Hello");

        DSLinkList<bool> tester4;
        tester4.add(true);
        tester4.add(false);
        tester4.add(false);

        tester4.setCurrHead();
        tester4.advanceCurr();
        tester4.advanceCurr();

        tester4.setCurrHead();
        CHECK(tester4.getCurrValue() == true);
    }

    SECTION("advanceCurr function") {
        tester1.setCurrHead();
        tester1.advanceCurr();
        CHECK(tester1.getCurrValue() == 17);

        tester2.setCurrHead();
        tester2.advanceCurr();
        CHECK(tester2.getCurrValue() == 'Z');

        tester3.setCurrHead();
        tester3.advanceCurr();
        CHECK(tester3.getCurrValue() == "This is a pretty long string");

        DSLinkList<bool> tester4;
        tester4.add(true);
        tester4.add(false);
        tester4.add(false);

        tester4.setCurrHead();
        tester4.advanceCurr();
        CHECK(tester4.getCurrValue() == false);
    }

    SECTION("fallBackCurr function") {
        tester1.setCurrHead();
        tester1.advanceCurr();
        tester1.advanceCurr();
        tester1.fallBackCurr();

        CHECK(tester1.getCurrValue() == 17);

        tester1.fallBackCurr();
        CHECK(tester1.getCurrValue() == 2);

        tester2.setCurrHead();
        tester2.advanceCurr();
        tester2.advanceCurr();
        tester2.fallBackCurr();

        CHECK(tester2.getCurrValue() == 'Z');

        tester2.fallBackCurr();
        CHECK(tester2.getCurrValue() == 'c');

        tester3.setCurrHead();
        tester3.advanceCurr();
        tester3.advanceCurr();
        tester3.fallBackCurr();

        CHECK(tester3.getCurrValue() == "This is a pretty long string");

        tester3.fallBackCurr();
        CHECK(tester3.getCurrValue() == "Hello");
    }

    SECTION("getCurrValue function") {
        tester1.setCurrHead();
        CHECK(tester1.getCurrValue() == 2);

        tester1.advanceCurr();
        tester1.advanceCurr();
        CHECK(tester1.getCurrValue() == 2001);

        tester2.setCurrHead();
        CHECK(tester2.getCurrValue() == 'c');

        tester2.advanceCurr();
        CHECK(tester2.getCurrValue() == 'Z');

        tester3.setCurrHead();
        tester3.advanceCurr();
        CHECK(tester3.getCurrValue() == "This is a pretty long string");

        tester3.advanceCurr();
        CHECK(tester3.getCurrValue() == "Yes");
    }

    SECTION("hasNext function") {
        tester1.setCurrHead();
        tester2.setCurrHead();
        tester3.setCurrHead();

        CHECK(tester1.hasNext() == true);
        CHECK(tester2.hasNext() == true);
        CHECK(tester3.hasNext() == true);

        tester3.advanceCurr();
        CHECK(tester3.hasNext() == true);

        tester3.advanceCurr();
        CHECK(tester3.hasNext() == false);

        DSLinkList<bool> tester4;
        tester4.add(true);
        tester4.add(false);
        tester4.add(false);

        tester4.setCurrHead();
        CHECK(tester4.hasNext() == true);

        tester4.advanceCurr();
        CHECK(tester4.hasNext() == true);

        tester4.advanceCurr();
        CHECK(tester4.hasNext() == false);
    }

    SECTION("Copy Constructor") {
        DSLinkList<int> tester4(tester1);
        DSLinkList<char> tester5(tester2);
        DSLinkList<string> tester6(tester3);

        tester4.setCurrHead();
        tester1.setCurrHead();
        CHECK(tester4.getCurrValue() == tester1.getCurrValue());

        tester4.advanceCurr();
        tester1.advanceCurr();
        CHECK(tester4.getCurrValue() == tester1.getCurrValue());

        tester4.advanceCurr();
        tester1.advanceCurr();
        CHECK(tester4.getCurrValue() == tester1.getCurrValue());

        tester1.add(27);
        CHECK(tester4.hasNext() == false);

        tester5.setCurrHead();
        tester2.setCurrHead();
        CHECK(tester5.getCurrValue() == tester2.getCurrValue());

        tester5.advanceCurr();
        tester2.advanceCurr();
        CHECK(tester5.getCurrValue() == tester2.getCurrValue());

        tester5.advanceCurr();
        tester2.advanceCurr();
        CHECK(tester5.getCurrValue() == tester2.getCurrValue());

        tester2.add(';');
        CHECK(tester5.hasNext() == false);

        tester6.setCurrHead();
        tester3.setCurrHead();
        CHECK(tester6.getCurrValue() == tester3.getCurrValue());

        tester6.advanceCurr();
        tester3.advanceCurr();
        CHECK(tester6.getCurrValue() == tester3.getCurrValue());

        tester6.advanceCurr();
        tester3.advanceCurr();
        CHECK(tester6.getCurrValue() == tester3.getCurrValue());

        tester3.add("Oh yeah");
        CHECK(tester6.hasNext() == false);
    }

    SECTION("= Operator") {
        DSLinkList<int> tester4 = tester1;
        DSLinkList<char> tester5 = tester2;
        DSLinkList<string> tester6 = tester3;

        tester4.setCurrHead();
        tester1.setCurrHead();
        CHECK(tester4.getCurrValue() == tester1.getCurrValue());

        tester4.advanceCurr();
        tester1.advanceCurr();
        CHECK(tester4.getCurrValue() == tester1.getCurrValue());

        tester4.advanceCurr();
        tester1.advanceCurr();
        CHECK(tester4.getCurrValue() == tester1.getCurrValue());

        tester1.add(27);
        CHECK(tester4.hasNext() == false);

        tester5.setCurrHead();
        tester2.setCurrHead();
        CHECK(tester5.getCurrValue() == tester2.getCurrValue());

        tester5.advanceCurr();
        tester2.advanceCurr();
        CHECK(tester5.getCurrValue() == tester2.getCurrValue());

        tester5.advanceCurr();
        tester2.advanceCurr();
        CHECK(tester5.getCurrValue() == tester2.getCurrValue());

        tester2.add(';');
        CHECK(tester5.hasNext() == false);

        tester6.setCurrHead();
        tester3.setCurrHead();
        CHECK(tester6.getCurrValue() == tester3.getCurrValue());

        tester6.advanceCurr();
        tester3.advanceCurr();
        CHECK(tester6.getCurrValue() == tester3.getCurrValue());

        tester6.advanceCurr();
        tester3.advanceCurr();
        CHECK(tester6.getCurrValue() == tester3.getCurrValue());

        tester3.add("Oh yeah");
        CHECK(tester6.hasNext() == false);
    }

    SECTION("currIsNull function") {
        tester1.setCurrHead();
        tester2.setCurrHead();
        tester3.setCurrHead();

        CHECK(tester1.currIsNull() == false);
        CHECK(tester2.currIsNull() == false);
        CHECK(tester3.currIsNull() == false);

        tester1.advanceCurr();
        tester1.advanceCurr();
        tester1.advanceCurr();

        CHECK(tester1.currIsNull() == true);

        tester3.advanceCurr();
        tester3.advanceCurr();
        tester3.advanceCurr();

        CHECK(tester3.currIsNull() == true);
    }

}