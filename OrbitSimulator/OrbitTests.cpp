// Tests for Orbit Simulator 
//
#pragma once
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
		double H = 6000;
		double result = temperature(H);
		REQUIRE(floor(result) == 245); 
	}
	SECTION("2nd equation - at 15 km") {
		double H = 15000;
		double result = temperature(H);
		REQUIRE(floor(result) == 213); 
	}
	SECTION("3rd equation - at 30 km") {
		double H = 30000;
		double result = temperature(H);
		REQUIRE(floor(result) == 235); 
	}
	SECTION("4th equation - at 50 km") {
		double H = 50000;
		double result = temperature(H);
		REQUIRE(result == ZeroCelsius); 
	}
	SECTION("5th equation - at 80 km") {
		double H = 80000;
		double result = temperature(H);
		REQUIRE(floor(result) == 195); 
	}
	SECTION("6th equation - at 90 km") {
		double H = 90000;
		double result = temperature(H);
		REQUIRE(floor(result) == 183); 
	}
	SECTION("7th equation - at 140 km") {
		double H = 140000;
		double result = temperature(H);
		REQUIRE(floor(result) == 309); 
	}
}

TEST_CASE("Calculate air density", "[airDensity]") {
	SECTION("at 0 km") {
		double H = EarthRadius;
		double result = airDensity(H);
		REQUIRE(result == 1.225);
	}
	SECTION("at 30 km") {
		double H = 30000 + EarthRadius;
		double result = airDensity(H);
		REQUIRE(result <= 0.0201194434);
		REQUIRE(result >= 0.0201194432);
	}
	SECTION("at 50 km") {
		double H = 50000 + EarthRadius;
		double result = airDensity(H);
		REQUIRE(result <= 0.002748035);
		REQUIRE(result >= 0.002748033);
	}
	SECTION("at 80 km") {
		double H = 80000 + EarthRadius;
		double result = airDensity(H);
		REQUIRE(result <= 0.000002129);
		REQUIRE(result >= 0.000002127);
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
		vec position = {6471000, 0, 0};
		double mass = 1;
		vec result = calculateGravityForce(position, mass);
		REQUIRE(result.x >= 9.4);
		REQUIRE(result.x <= 9.6);
	}
}

TEST_CASE("Calculate geostationary orbit", "[computeFlightPlan]") {
	SECTION("If distance is 42164 and speed")
	{
		vec position = {42164000,0,0};
		vec orientation = {1,0,0};
		vec initialSpeed = {0,3070,0};
		Rotation initialRotation = {0,0,0};
		ShipPosition spaceCraftPosition = {position, orientation, initialSpeed, initialRotation};
		Quants flightTime = {86000, 1}; 
		ShipParams spaceCraftParameters = {1000, 2, 0, initialRotation, 0, 0,std::vector<PartOfFlightPlan>(),1000000};
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
		vec speed = {1000, 1000, 1000};
		double square = 2000;
		double height = 100000000;
		vec result = calculateAerodynamicForce (speed, square, height);
		vec zeroVec = {0, 0, 0};
		REQUIRE(result == zeroVec);
	}
	SECTION( "if we have zero speed" ) {
		vec speed = {0, 0, 0};
		double square = 2000;
		double height = 6471000;
		vec result = calculateAerodynamicForce (speed, square, height);
		vec zeroVec = {0, 0, 0};
		REQUIRE(result == zeroVec);
	}
}

TEST_CASE("Calculate speed", "[Speed]") {
	SECTION( "average values" ) {
		vec previousSpeed = {1000, 0, 0};
		vec position = {65500000, 0, 0};
		vec orientation = {1, 0, 0};
		double fuelConsumption = 1;
		double mShip = 100;
		double mFuel = 50;
		Rotation moment = {0, 0, 0};
		double specificImpulse = 1;
		double size = 1000;
		double quantSizeOfSec = 1;
		double maxHeating = 100;
		vec result = speed(previousSpeed, position, orientation, fuelConsumption,
			mShip, mFuel, moment, specificImpulse,
			size, quantSizeOfSec, maxHeating);
		REQUIRE(result.x >= 998);
		REQUIRE(result.x <= 1000);
	}
	SECTION( "if quantSizeOfSec is zero" ) {
		vec previousSpeed = {1000, 0, 0};
		vec position = {6471000, 0, 0};
		vec orientation = {1, 0, 0};
		double fuelConsumption = 1;
		double mShip = 1000;
		double mFuel = 50;
		Rotation moment = {0, 0, 0};
		double specificImpulse = 100;
		double size = 100000;
		double quantSizeOfSec = 0;
		double maxHeating = 100;
		vec result = speed(previousSpeed, position, orientation, fuelConsumption,
			mShip, mFuel, moment, specificImpulse,
			size, quantSizeOfSec, maxHeating);
		REQUIRE(result == previousSpeed);
	}
}

TEST_CASE("Calculate Explorer 6 orbit (russian/deutsch wikipedia)", "[computeFlightPlan]") {
	SECTION("Launched from 245000 m, start speed = 10296 m/s")
	{
		vec position = {0, 6623100, 0};
		vec orientation = {-1, 0, 0};
		vec initialSpeed = {-10296.099, 0, 0};
		Rotation initialRotation = {0, 0, 0};
		ShipPosition spaceCraftPosition = {position, orientation, initialSpeed, initialRotation};
		Quants flightTime = {45910, 1};
		vector<PartOfFlightPlan> flightPlan(flightTime.numberOfQuants);
		PartOfFlightPlan plan = {45910, 0, {0, 0, 0}};
		flightPlan[0] = plan;
		ShipParams spaceCraftParameters = {1, 64, 0, initialRotation, 0, 0,
			flightPlan,1000000};
		vector<ReturnValues> calculationResults = computeFlightPlan(spaceCraftPosition, spaceCraftParameters, flightTime);   
		double max = 0;
		for (int i = 0; i < flightTime.numberOfQuants; i++) {
			double height = calculationResults[i].position.getScalar();
			double speed  = calculationResults[i].speed.getScalar();
			if (height > max) { max = height; }
			REQUIRE(height < EarthRadius + 42400100);
			REQUIRE(height > EarthRadius + 244998);
			REQUIRE(speed < 11200);
			if ((height - EarthRadius) <= 245000 && i > 60) { 
				double period = (double) i / 60;
				REQUIRE(period < 766.0);
				REQUIRE(period >= 764.0);
			}
		}
	}
}

TEST_CASE("Calculate Explorer 6 orbit (english wikipedia)", "[computeFlightPlan]") {
	SECTION("Launched from 237000 m, start speed = 10290 m/s")
	{
		vec position = {0, 6615100, 0};
		vec orientation = {-1, 0, 0};
		vec initialSpeed = {-10296.7, 0, 0};
		Rotation initialRotation = {0, 0, 0};
		ShipPosition spaceCraftPosition = {position, orientation, initialSpeed, initialRotation};
		Quants flightTime = {45300, 1};
		vector<PartOfFlightPlan> flightPlan(flightTime.numberOfQuants);
		PartOfFlightPlan plan = {45300, 0, {0, 0, 0}};
		flightPlan[0] = plan;
		ShipParams spaceCraftParameters = {1, 64, 0, initialRotation, 0, 0,
			flightPlan,1000000};
		vector<ReturnValues> calculationResults = computeFlightPlan(spaceCraftPosition, spaceCraftParameters, flightTime);   
		double max = 0;
		for (int i = 0; i < flightTime.numberOfQuants; i++) {
			double height = calculationResults[i].position.getScalar();
			double speed  = calculationResults[i].speed.getScalar();
			if (height > max) { max = height; }
			REQUIRE(height < EarthRadius + 41900000);
			REQUIRE(height > EarthRadius + 236998);
			REQUIRE(speed < 11200);
			if ((height - EarthRadius) <= 237000 && i > 60) { 
				double period = (double) i / 60;
				REQUIRE(period < 755.0);
				REQUIRE(period >= 753.0);
			}
		}
	}
}

TEST_CASE("Calculate Vostok 1 orbit", "[computeFlightPlan]") {
	SECTION("Launched from 175000 m, start speed = 7837.5 m/s")
	{
		vec position = {0, 0, 6553220};
		vec orientation = {1, 0, 0};
		vec initialSpeed = {-7837.5, 0, 0};
		Rotation initialRotation = {0, 0, 0};
		ShipPosition spaceCraftPosition = {position, orientation, initialSpeed, initialRotation};
		Quants flightTime = {6480, 1};
		vector<PartOfFlightPlan> flightPlan(flightTime.numberOfQuants);
		PartOfFlightPlan plan = {5352, 0, {0, 0, 0}};
		flightPlan[0] = plan;
		ShipParams spaceCraftParameters = {2.5, 3725.0, 1000, initialRotation, 100.0, 2.61,
			flightPlan,5274.0};
		vector<ReturnValues> calculationResults = computeFlightPlan(spaceCraftPosition, spaceCraftParameters, flightTime);  
		double max = 0;
		for (int i = 0; i < flightTime.numberOfQuants; i++) {
			double height = calculationResults[i].position.getScalar();
			double speed  = calculationResults[i].speed.getScalar();
			double overload = calculationResults[i].overload;
			REQUIRE(overload < 10);
			REQUIRE(height < EarthRadius + 301970.0);
			REQUIRE(height > EarthRadius + 174998.0);
			REQUIRE(speed < 7900);
			if ((height - EarthRadius)<175000 && i > 60)  { 
				double period = (double) i / 60;
				REQUIRE(period < 90.2);
				REQUIRE(period >= 89.0);
			}
		}
	}
}
