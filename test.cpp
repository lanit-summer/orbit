#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "orbit/orbit.cpp"
 
TEST_CASE("Gravity force") {
    SECTION("Normal situation") {
        vec r = {6478.1, 0, 0};
        double m = 1.0;
        vec grForce = gravityForce(r, m);
        double res = round(scalar(grForce) * 10000)/10000.;
        double compare = 0.00950;
        REQUIRE(res == compare);
    }
    SECTION("No mass situation") {
        vec r = {6478.1, 0, 0};
        double m = 0.0;
        vec grForce = gravityForce(r, m);
        double res = round(scalar(grForce) * 10000)/10000.;
        double compare = 0.00000;
        REQUIRE(res == compare);
    }
    SECTION("Center of the Earth") {
        vec r = {0, 0, 0};
        double m = 50.0;
        vec grForce = gravityForce(r, m);
        double res = round(scalar(grForce) * 10000)/10000.;
        double compare = 0.00000;
        REQUIRE(res == compare);
    }
}