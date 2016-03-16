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


