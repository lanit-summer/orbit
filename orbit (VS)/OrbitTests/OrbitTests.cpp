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

//Angular velocity, result values from Maple 14
TEST_CASE("Calculate Angular Velocity", "[AngularVelocity]") {
	//all zero test
	vec tractiveForce = { 0,0,0 },
		aeroDynamicForce = { 0,0,0 },
		gravity = { 0,0,0 },
		previous = { 0,0,0 };
	Rotation rotate = { 0,0,0 };
	double quantSize = 0,
		length = 0;
	
	vec result = { 0,0,0 };
	REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
		quantSize, length, previous));

	//some average values
	tractiveForce = { 100,200,300 };
	aeroDynamicForce = { 100,200,300 };
	gravity = { 100,200,300 };
	previous = { 100,200,300 };
	rotate = { 100,200,300 };
	length = 1000;
	quantSize = 100;
	result = { 150100, -149800, 50300 };
	REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
		quantSize, length, previous));

	//big values (max double value C++ ~e308)
	tractiveForce = { 1e300,1e300,1e300 };
	aeroDynamicForce = { 1e300,1e300,1e300 };
	gravity = { 1e300,1e300,1e300 };
	previous = { 1e300,1e300,1e300 };
	rotate = { 1e300,1e300,1e300 };
	length = 1e300;
	quantSize = 100;
    result = { 1e300,1e300,1e300 };
	REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
		quantSize, length, previous));
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





