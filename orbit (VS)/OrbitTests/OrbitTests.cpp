// OrbitTests2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "OrbitSimulator.cpp"
using namespace std;

//Check that spaceship is not heating if speed is zero.
TEST_CASE("Calculate Aerodynamic heating", "[AerodynamicHeating]") {
	vec speedZero = {0, 0, 0};
	double T = 100;
	double result = aerodynamicHeating(T, speedZero);
	REQUIRE(result==100); 
}

//Check the temperature at 6 km
TEST_CASE("Calculate temperature", "[temperature]") {
	double H = 6 + EarthRadius;
	double result = temperature(H);
	REQUIRE(result == 255.7); 
}

//Check the air density at 40 km
TEST_CASE("Calculate air density", "[airDensity]") {
	double H = 40 + EarthRadius;
	double result = airDensity(H);
	REQUIRE(result ==  0.004);
}




