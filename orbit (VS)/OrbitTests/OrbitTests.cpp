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
	SECTION("all zero test") {
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
	}

	SECTION("some average values") {
		vec	tractiveForce = { 100,200,300 },
			aeroDynamicForce = { 100,200,300 },
			gravity = { 100,200,300 },
			previous = { 100,200,300 },
			result = { 150100, -149800, 50300 };
		Rotation rotate = { 100,200,300 };
		double	length = 1000,
			quantSize = 100;

		REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
			quantSize, length, previous));
	}
}

TEST_CASE("Calculate temperature", "[temperature]") {
	SECTION("1st equation - at 6 km") {
		double H = 6;
		double result = temperature(H);
		REQUIRE(floor(result) == 245); 
	}
	SECTION("2nd equation - at 15 km") {
		double H = 15;
		double result = temperature(H);
		REQUIRE(floor(result) == 213); 
	}
	SECTION("3rd equation - at 30 km") {
		double H = 30;
		double result = temperature(H);
		REQUIRE(floor(result) == 235); 
	}
	SECTION("4th equation - at 50 km") {
		double H = 50;
		double result = temperature(H);
		REQUIRE(result == ZeroCelsius); 
	}
	SECTION("5th equation - at 80 km") {
		double H = 80;
		double result = temperature(H);
		REQUIRE(floor(result) == 195); 
	}
	SECTION("6th equation - at 90 km") {
		double H = 90;
		double result = temperature(H);
		REQUIRE(floor(result) == 183); 
	}
	SECTION("7th equation - at 140 km") {
		double H = 140;
		double result = temperature(H);
		REQUIRE(floor(result) == 309); 
	}
}

TEST_CASE("Calculate air density", "[airDensity]") {
	SECTION("at 0 km") {
		double H = EarthRadius;
		double result = airDensity(H);
		REQUIRE(result == 1225000000);
	}
	SECTION("at 30 km") {
		double H = 30 + EarthRadius;
		double result = airDensity(H);
		REQUIRE(floor(result) == 20119443);
	}
	SECTION("at 50 km") {
		double H = 50 + EarthRadius;
		double result = airDensity(H);
		REQUIRE(floor(result) == 2748034);
	}
	SECTION("at 80 km") {
		double H = 80 + EarthRadius;
		double result = airDensity(H);
		REQUIRE(floor(result) == 2128);
	}
}

TEST_CASE("Calculate Gravity force", "[GravityForce]") {
	SECTION( "if position is the center of the Earth" ) {
		vec position = {0, 0, 0};
		double mass = 100;
		vec result = calculateGravityForce(position, mass);
		vec zeroVec = {0, 0, 0};
		REQUIRE(result == zeroVec);
	}
	SECTION( "normal values" ) {
		vec position = {6471, 0, 0};
		double mass = 1;
		vec result = calculateGravityForce(position, mass);
		REQUIRE(result.x >= 0.0094);
		REQUIRE(result.x <= 0.0096);
	}
}

TEST_CASE("Calculate geostationary orbit", "[computeFlightPlan]") {
	SECTION("If distance is 42164 and speed")
	{
		vec position = {42164,0,0};
		vec orientation = {1,0,0};
		vec initialSpeed = {-2.17,2.17,0};
		Rotation initialRotation = {0,0,0};
		ShipPosition spaceCraftPosition = {position, orientation, initialSpeed, initialRotation};
		 
		ShipParams spaceCraftParameters = {1, 2, 0, initialRotation, 0, 0,std::vector<PartOfFlightPlan>(),1000000,1000000};
		Quants flightTime = {300, 60};
		std::vector<ReturnValues> calculationResults = computeFlightPlan(spaceCraftPosition, spaceCraftParameters, flightTime);   
	}
}

TEST_CASE("Calculate Tractive force", "[TractiveForce]") {
	SECTION( "if the orientation is zero" ) {
		vec orientation = {0, 0, 0};
		double massLevel = 1;
		double specificImpulse = 1;
		vec result = calculateTractiveForce(massLevel, specificImpulse, orientation);
		vec zeroVec = {0, 0, 0};
		REQUIRE(result == zeroVec);
	}
	SECTION( "normal values" ) {
		vec orientation = {10, 0, 0};
		double massLevel = 0.3;
		double specificImpulse = 21;
		vec result = calculateTractiveForce(massLevel, specificImpulse, orientation);
		vec calculatedVec = {6.3, 0, 0};
		REQUIRE(result == calculatedVec);
	}
	SECTION( "calculation doesn't depend on scalar of the orientation, only on it's direction)" ) {
		vec orientation1 = {0, 1, 0};
		vec orientation2 = {0, 10, 0};
		double massLevel = 2;
		double specificImpulse = 5;
		vec result1 = calculateTractiveForce(massLevel, specificImpulse, orientation1);
		vec result2 = calculateTractiveForce(massLevel, specificImpulse, orientation2);
		vec calculatedVec = {0, 10, 0};
		REQUIRE(result1 == calculatedVec);
		REQUIRE(result2 == calculatedVec);
	}
}

TEST_CASE("Calculate Aerodynamic force", "[AerodynamicForce]") {
	SECTION( "if we are too far from Earth" ) {
		vec speed = {1, 1, 1};
		double square = 2;
		double height = 100000;
		vec result = calculateAerodynamicForce (speed, square, height);
		vec zeroVec = {0, 0, 0};
		REQUIRE(result == zeroVec);
	}
	SECTION( "if we have zero speed" ) {
		vec speed = {0, 0, 0};
		double square = 2;
		double height = 6471;
		vec result = calculateAerodynamicForce (speed, square, height);
		vec zeroVec = {0, 0, 0};
		REQUIRE(result == zeroVec);
	}
}

TEST_CASE("Calculate speed", "[Speed]") {
	SECTION( "average values" ) {
		vec previousSpeed = {1, 0, 0};
		vec position = {6550, 0, 0};
		vec orientation = {1, 0, 0};
		double fuelConsumption = 1;
		double mShip = 100;
		double mFuel = 50;
		Rotation moment = {0, 0, 0};
		double specificImpulse = 1;
		double size = 1;
		double quantSizeOfSec = 1;
		double maxOverload = 10;
		double maxHeating = 100;
		vec result = speed(previousSpeed, position, orientation, fuelConsumption,
			mShip, mFuel, moment, specificImpulse,
			size, quantSizeOfSec, maxOverload, maxHeating);
		REQUIRE(result.x >= 0.997);
		REQUIRE(result.x <= 0.998);
	}
	SECTION( "if quantSizeOfSec is zero" ) {
		vec previousSpeed = {1, 0, 0};
		vec position = {6471, 0, 0};
		vec orientation = {1, 0, 0};
		double fuelConsumption = 1;
		double mShip = 1000;
		double mFuel = 50;
		Rotation moment = {0, 0, 0};
		double specificImpulse = 100;
		double size = 100;
		double quantSizeOfSec = 0;
		double maxOverload = 10;
		double maxHeating = 100;
		vec result = speed(previousSpeed, position, orientation, fuelConsumption,
			mShip, mFuel, moment, specificImpulse,
			size, quantSizeOfSec, maxOverload, maxHeating);
		REQUIRE(result == previousSpeed);
	}
}
