//
// Created by mikec_g1kgiu8 on 10/24/2021.
//

#include "catch.hpp"
#include "DSStack.h"

using namespace std;

TEST_CASE("DSStack class", "[DSStack]") {
    DSStack<int> tester1;
    tester1.push(4);
    tester1.push(65);
    tester1.push(-78596);

    DSStack<char> tester2;
    tester2.push('A');
    tester2.push('n');
    tester2.push('?');

    DSStack<string> tester3;
    tester3.push("Yes");
    tester3.push("No");
    tester3.push("Maybe so");

    SECTION("push function") {
        tester1.push(14);
        tester2.push('/');
        tester3.push("Bonjour");

        CHECK(tester1.pop() == 14);
        CHECK(tester2.pop() == '/');
        CHECK(tester3.pop() == "Bonjour");

        CHECK(tester1.peek() == -78596);
        CHECK(tester2.peek() == '?');
        CHECK(tester3.peek() == "Maybe so");
    }

    SECTION("pop function") {
        CHECK(tester1.pop() == -78596);
        CHECK(tester2.pop() == '?');
        CHECK(tester3.pop() == "Maybe so");

        CHECK(tester1.pop() == 65);
        CHECK(tester2.pop() == 'n');
        CHECK(tester3.pop() == "No");
    }

    SECTION("peek function") {
        CHECK(tester1.peek() == -78596);
        CHECK(tester2.peek() == '?');
        CHECK(tester3.peek() == "Maybe so");

        tester1.pop();
        tester1.pop();
        tester2.pop();
        tester2.pop();
        tester3.pop();
        tester3.pop();

        CHECK(tester1.peek() == 4);
        CHECK(tester2.peek() == 'A');
        CHECK(tester3.peek() == "Yes");
    }

    SECTION("isEmpty function") {
        CHECK(tester1.isEmpty() == false);
        tester1.pop();
        tester1.pop();
        tester1.pop();
        CHECK(tester1.isEmpty() == true);

        CHECK(tester2.isEmpty() == false);
        CHECK(tester3.isEmpty() == false);

        DSStack<bool> tester4;
        CHECK(tester4.isEmpty() == true);
    }
}