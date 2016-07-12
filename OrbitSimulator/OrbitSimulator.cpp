// OrbitSimulator.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "stdafx.h"
#include "OrbitSimulator.h"

vec calculateGravityForce(vec distance, double shipMass) //G * mEarth * mShip / R^2
{
	double distanceScalar = distance.getScalar();
	if (distanceScalar == 0) {
		vec res = {0, 0, 0};
		return res ;
	}
	double a = G * EarthMass * shipMass / pow(distanceScalar, 3);
	vec res = distance.multiplyWithDouble(a);
	return res; // (N * 10^3)
}
//что было раньше в коде
//double temperature(double height) //calculates the temperature at a certain height (K)
//{
//	if (height < 0)
//	{
//		throw invalid_argument("Height is less than the radius of the Earth");
//	}
//	double temperature = ZeroCelsius;
//	if (height > 145) //at each height there's an equation of temperature calculation
//	{
//		return 0.0;
//	}
//	else if (height > 94)
//	{
//		temperature += 140 * (height - 94) / 51 - 90;
//	}
//	else if (height > 84)
//	{
//		temperature -= 90;
//	}
//	else if (height > 54)
//	{
//		temperature += -3 * height + 162;
//	}
//	else if (height > 47)
//	{
//		return temperature;
//	}
//	else if (height > 20)
//	{
//		temperature += (20 * height - 940) / 9;
//	}
//	else if (height > 10)
//	{
//		temperature -= 60;
//	}
//	else
//	{
//		temperature += -8 * height + 20;
//	}
//	return temperature;
//}
//температура в соответствии с ГОСТ
double temperature(double height) //calculates the temperature at a certain height (K)
{
	if (height < 0)
	{
		throw invalid_argument("Height is less than the radius of the Earth");
	}
	double temperature = ZeroCelsius;
	if (height < 11019)
	{
		temperature = 288.15-0.0065*(height);
	}
	else if (height < 20063)
	{
		temperature = 216-0.0065*(height-11019);
	}
	else if (height < 32162)
	{
		temperature = 216.65;
	}
	else if (height < 47350)
	{
		temperature = 228.65+0.0010*(height-32162);
	}
	else if (height < 51412)
	{
		temperature = 270.65+0.0028*(height-47350);
	}
	else if (height < 71802)
	{
		temperature = 270.65;
	}
	else if (height < 86152)
	{
		temperature = 214.65-0.0028*(height-71802);
	}
	else if (height < 95411)
	{
		temperature = 186.65-0.0020*(height-71802);
	}
	else if (height < 104128)
	{
		temperature = 186.525;
	}
	else if (height < 120000)
	{
		temperature = 203.81;
	}
	else if (height < 140000)
	{
		temperature = 334.42+0.011259*(height-120000);
	}
	else if (height < 160000)
	{
		temperatire = 559.60+0.006800*(height-140000);
	}
	else if (height < 200000)
	{
		temperature = 695.60+0.003970*(height-160000);
	}
	else if (height < 250000)
	{
		temperature = 834.40+0.001750*(height-200000);
	}
	else if (height < 325000)
	{
		temperature = 941.90+0.00057*(height-250000);
	}
	else if (height < 400000)
	{
		temperature = 984.65+0.0001500*(height-325000);
	}
	else if (height < 600000)
	{
		temperature = 995.90+0.00002*(height-400000);
	}
	else if (height < 800000)
	{
		temperature = 999.9-0.0000005*(height-600000);
	}
	else if (height <1200000)
	{
		temperature = 1000;
	}
	return temperature;
}
//
// molar mass 
double molarMass(double height)
{
	if (height < 94000)
	{
		molarMass = 28.964420*pow(10,-3);
	}
	else if (height < 97000)
	{
		molarMass = (28.82+0.158*sqrt(1-7.5*pow(10,-8)*(pow(height-94000),2))-2.479*pow(10,-4)*sqrt(97000-height))*pow(10,-3);
	}
	else if (height < 97500)
	{
		molarMass = (28.91-0.00012*height)*pow(10,-3);
	}
	else if (height < 120000)
	{
		molarMass = (26.21-0.0001511*height)*pow(10,-3);
	}
	else if (height < 250000)
	{
		molarMass = (46.9083-29.71210*pow(10,-5)*height+12.08693*pow(10,-10)*pow(height,2)-1.85675*pow(10,-15)*pow(height,3))*pow(10,-3);
	}
	else if (height < 400000)
	{
		molarMass = (40.4668-15.52722*pow(10,-5)*height+3.55735*pow(10,-10)*pow(height,2)-3.02340*pow(10,-15)*pow(height,3))*pow(10,-3);
	}
	else if (height < 650000)
	{
		molarMass = (6.3770+6.25497*pow(10,-5)*height-1.10144*pow(10,-10)*pow(height,2)+3.36907*pow(10,-17)*pow(height,3))*pow(10,-3);
	}
	else if (height < 900000)
	{
		molarMass = (75.6896-17.61243*pow(10,-5)*height+1.33603*pow(10,-10)*pow(height,2)-2.87884*pow(10,-17)*pow(height,3))*pow(10,-3);
	}
	else if (height < 1050000)
	{
		molarMass = (112.4838-30.68086*pow(10,-5)*height+2.90329*pow(10,-10)*pow(height,2)-9.20616*pow(10,-17)*pow(height,3))*pow(10,-3);
	}
	else if (height < 1200000)
	{
		molarMass = (9.8970-1.19732*pow(10,-5)*height+7.78247*pow(10,-12)*pow(height,2)-1.77541*pow(10,-18)*pow(height,3))*pow(10,-3);
	}
	return molarMass
}

//концентрация в зависимости от высоты согласно ГОСТ
double concentration(double height)
{
	if (height < 120000) 
	{
		BoltzmannConstant = 1.38064852*pow(10,-23); //J/K
		p0 = 101325; //normal atmospheric pressure at sea level (Pa)
		g = G * EarthMass / pow(height, 2); //acceleration due to gravity
		concentration = (p0*exp(-molarMass*g*height/(R*temperature)));
	}
}

double airDensity(double height) //calculates the air density at a certain height (height = height + EarthRadius)
{
	if (height <= EarthRadius) { return SeaLevelAirDensity; }
	double heightAboveSeaLevel = height - EarthRadius;
	double T = temperature(heightAboveSeaLevel); //temperature at a certain height
	if (T <= 0.0) { return 0.0; }
	else
		// p = p0 * e^(-M * g * H / (R * T)) 
		// airDensity = p * M / (R * T) 
	{ 
		double p0 = 101325, //normal atmospheric pressure at sea level (Pa)
			g = G * EarthMass / pow(height, 2), //acceleration due to gravity
			//on the Earth's surface (km/s^2)
			R = 8.31447, //universal gas constant (J / (mol * K))
			M = 0.0289644, //the molar mass of dry air (kg / mol)
			p = p0 * exp(-M * g * heightAboveSeaLevel * pow(10.0, 6) / (R * T)), //pressure at the certain height (Pa)
			density = p * M * pow(10.0, 9) / (R * T); //air density at the certain height (kg / km^3)
		return density;  
	}
}

//calculates an aerodynamic force 
// p * v^2 * S^2 / 2
vec calculateAerodynamicForce(vec speed, double square, double height) 
{
	double v = speed.getScalar();
	double p = airDensity(height);
	vec result = speed.multiplyWithDouble(-p * v * square / 2);
	return result;
}

// Calculate tractive force using next formula: 
//                  mLevel * impulse * (vectorOrientation / scalarOrientation)
// Input parameters:
// massLevel - fuel mass flow
// impulse - specific impulse
// (vectorOrientation / scalarOrientation) - unit vector of ship orientation
vec calculateTractiveForce(double massLevel, double impulse, vec vectorOrientation) 
{
	double scalarOrientation = vectorOrientation.getScalar();
	if (scalarOrientation == 0) {
		vec result = {0, 0, 0};
		return result;
	}
	vec result = vectorOrientation.multiplyWithDouble(massLevel * impulse / scalarOrientation);
	return result;
}

//calculates an angular velocity by the moment of inertia
//momentForce* sizeOfSec / momentInertia + previousVelocity 
vec calculateAngularVelocity(vec gravityForce, vec aerodynamicForce,
							 vec tractiveForce, Rotation moment, double quantSizeOfSec,
							 double length, vec previousAngularVelocity)
{
	double x = moment.rotationAroundX, //moment of inertia
		y = moment.rotationAroundY,
		z = moment.rotationAroundZ;
	vec distance = {length / 2, length / 2, length / 2}; //distance to the center of rotation
	vec resultForce;
	resultForce.x = gravityForce.x + aerodynamicForce.x + tractiveForce.x;
	resultForce.y = gravityForce.y + aerodynamicForce.y + tractiveForce.y;
	resultForce.z = gravityForce.z + aerodynamicForce.z + tractiveForce.z;
	vec momentForce = distance.multiply(resultForce); //moment of force
	if (x != 0)
	{
		x = momentForce.x * quantSizeOfSec / x;
	}
	if (y != 0)
	{
		y = momentForce.y * quantSizeOfSec / y;
	}
	if (z != 0)
	{
		z = momentForce.z * quantSizeOfSec / z;
	}
	vec currentAngularVelocity;
	currentAngularVelocity.x = previousAngularVelocity.x + x;
	currentAngularVelocity.y = previousAngularVelocity.y + y;
	currentAngularVelocity.z = previousAngularVelocity.z + z;
	return currentAngularVelocity;
}

//Calculate aerodynamic heating for spaceship. 
//Formula: Tn=T0+0.2*M^2
double aerodynamicHeating(double temperature, vec speed)
{
	double heating = temperature + 0.2*pow(speed.getScalar()/speedofsound.getScalar(), 2); // (K)
	return heating;
}

//Calculate acceleration scalar value
//for current ship parameters and position.
vec CalculateAcceleration(
	double size,
	double totalMass,
	double fuelConsumption,
	double impulse,
	vec previousSpeed,
	vec position,
	vec orientation)
{
	const double Cx = 1;
	double currentHeight = position.getScalar(); 
	double accFromAirScalar =
		- Cx*airDensity(currentHeight) * previousSpeed.getScalar()  * (size*size) / (2.0 * totalMass);
	vec accFromAir = previousSpeed*accFromAirScalar;
	double speedGravityComponent = -G * EarthMass / pow(currentHeight, 3);
	vec acc =
		accFromAir +
		calculateTractiveForce(fuelConsumption, impulse, orientation)*( 1 / totalMass) +
		position*speedGravityComponent;
	return acc;
}

//calculates a speed at each time interval
vec speed(vec previousSpeed, vec position, vec orientation, double fuelConsumption,
		  double mShip, double mFuel, Rotation moment, double impulse,
		  double size, double quantSizeOfSec, double maxOverload, double maxHeating)
{			
	double mTotal = mShip + mFuel;
	double H = position.getScalar();
	double scSpeedFirst = previousSpeed.getScalar();
	double S = size * size;
	vec exit = {0, 0, 0};
	if (mTotal != 0) {
		if (quantSizeOfSec <= 0.0)
		{
			return previousSpeed;
		}

		try
		{
			vec acceleration =
				CalculateAcceleration(
				size, mTotal, fuelConsumption, impulse, previousSpeed, position, orientation);
			double currentOverloadScalar =	acceleration.getScalar()/g; 	// calculate overload in proportions to g.
			if(currentOverloadScalar <0)
			{
				int t = 0;
			}
			if (currentOverloadScalar > maxOverload) //TODO: Check on the site that maxOverload set in proportions to g.
			{
				throw invalid_argument("Overload");
			}
			exit = previousSpeed + acceleration*quantSizeOfSec;   
		}
		catch(...)
		{
		}
		//double v1 = airDensity(H) * scSpeedFirst * S / (2.0 * mTotal);
		////Change of speed because of 
		//double v2 = 1 / quantSizeOfSec  - v1,
		//	v3 = calculateTractiveForce(fuelConsumption, impulse,
		//	orientation).getScalar() / mTotal,
		//	v4 = G * EarthMass / pow(H, 3);

		/*
		double accFromAirScalar =  - Cx ( = 1) * airDensity(H) * scSpeedFirst * S / (2.0 * mTotal) ;
		veс accFromAir = previousSpeed.multiplyWithDouble(deltaVFromAirCoeff);
		vec acc = accFromAir + calculateTractiveForce(fuelConsumption, impulse,
		orientation).multiplyWith( 1 / mTotalv3) + position.multiplyWithDouble(v4)
		vec exit = previousSpeed + acc * quantSizeOfSec;
		double currentOverload = acc.getScalar() / g;
		*/

		//vec t1 = previousSpeed.multiplyWithDouble(v1),
		//	t2 = previousSpeed.multiplyWithDouble(v2),
		//	t3 = orientation.multiplyWithDouble(v3),
		//	t4 = position.multiplyWithDouble(v4);
		//exit.x = (t2.x + t3.x - t4.x) * quantSizeOfSec;
		//exit.y = (t2.y + t3.y - t4.y) * quantSizeOfSec;
		//exit.z = (t2.z + t3.z - t4.z) * quantSizeOfSec;

		//vec overload = {0, 0, 0};
		//overload.x = - t1.x + t3.x - t4.x;
		//overload.y = - t1.y + t3.y - t4.y;
		//overload.z = - t1.z + t3.z - t4.z;
		//Calculate current overload proportional to g.
		//double currentOverload = overload.getScalar() / g;
	}

	if (H <= AtmosphereBoundary)
	{
		double a = aerodynamicHeating(temperature(position.getScalar()), exit);
		if (a > maxHeating)
		{
			throw invalid_argument("Overheating");
		}
	}
	return exit;
}

//Form flight plan for whole flight traectory.
//using initial flight plan set in ship parameters
//and time quants. 
vector<PartOfFlightPlan> GetTraectoryFlightPlan(
	vector<PartOfFlightPlan> flightPlan, Quants quants)
{
	double fullFlightTime = quants.numberOfQuants * quants.quantSizeOfSec;
	double controlledFlightTime = 0;
	for(int i = 0; i<flightPlan.size(); i++)
	{
		controlledFlightTime +=flightPlan[i].delayTime;  
	}
	double uncontrolledFlightTime = fullFlightTime - controlledFlightTime;
	if(uncontrolledFlightTime >0)
	{
		PartOfFlightPlan lastPartOfFlightStub = {uncontrolledFlightTime, 0, {0,0,0}};
		flightPlan.push_back(lastPartOfFlightStub); 
	}
	return flightPlan;
}

//calculates a flight plan for the ship with specified parameters.
//input parameters:
//ShipPosition - Starting position of the ship (position, orientation, speedFirst, rotationalMoment)
//ShipParams - Parameters of the ship (edge length, ship mass without fuel, fuel mass, 
//             maximum moment of inertia, maximum fuel mass flow rate, 
//             specific impulse of the engine, an array of commands, maximum overload,
//             maximum heating)
//Quants - Represents a time period the ship's path is calculated for 
//         (number of time intervals, size of interval (sec))
//
//output: structure of vector of position and scalar of speed at each time interval  

vector <ReturnValues> computeFlightPlan(ShipPosition initialPosition,
										ShipParams shipParams, Quants quants)
{
	double S = pow(shipParams.shipEdgeLength, 2),
		height = initialPosition.position.getScalar(),
		fuel = shipParams.fuelMass,
		m = fuel + shipParams.shipMass;
	double level,currentFlightPlanTime;
	vec currentSpeed = initialPosition.speedFirst;
	Rotation moment = initialPosition.moment;
	vec currentOrientation = initialPosition.orientation;
	vec previousAngularVelocity = {0, 0, 0};
	vec currentPosition = initialPosition.position;
	vector<PartOfFlightPlan> flightCommands = GetTraectoryFlightPlan(shipParams.flightPlan, quants); 

	int i = 0,
		j = 0;
	ReturnValues currentFlightPlan;
	vector<ReturnValues> calculatedFlightPlan;
	currentFlightPlanTime = flightCommands[0].delayTime;
	for (i = 0; i < quants.numberOfQuants && height > EarthRadius; i++)
	{
		level = flightCommands[j].impulseValue;
		moment = flightCommands[j].rotateValue;
		vec gravityForce = calculateGravityForce(currentPosition, m);
		vec aerodynamicForce = calculateAerodynamicForce(currentSpeed, S, height);
		vec tractiveForce = calculateTractiveForce(level, shipParams.impulsePerFuel, currentOrientation);
		previousAngularVelocity = calculateAngularVelocity(
			gravityForce, aerodynamicForce, tractiveForce,
			moment, quants.quantSizeOfSec, shipParams.shipEdgeLength,
			previousAngularVelocity);
		currentOrientation = currentOrientation.rotate(previousAngularVelocity.createQuaternion());
		if (level * quants.quantSizeOfSec > fuel) //if we don't have enough fuel
		{
			double time = fuel / level, //time of flight with fuel
				timeOut = quants.quantSizeOfSec - time; //time of flight without fuel
			currentSpeed = speed(currentSpeed, currentPosition, currentOrientation,
				level, shipParams.shipMass, fuel, moment,
				shipParams.impulsePerFuel, shipParams.shipEdgeLength,
				time, shipParams.maxOverload, shipParams.maxHeating);
			currentFlightPlan.speed = currentSpeed;
			m -= fuel;
			fuel = 0.0;
			currentPosition.x = currentPosition.x + currentSpeed.x * time;
			currentPosition.y = currentPosition.y + currentSpeed.y * time;
			currentPosition.z = currentPosition.z + currentSpeed.z * time;
			currentSpeed = speed(currentSpeed, currentPosition, currentOrientation, 0.0,
				shipParams.shipMass, fuel, moment,
				shipParams.impulsePerFuel, shipParams.shipEdgeLength,
				timeOut, shipParams.maxOverload, shipParams.maxHeating);
		}
		else //if we have enough fuel
		{
			currentSpeed = speed(currentSpeed, currentPosition, currentOrientation,
				level, shipParams.shipMass, fuel, moment,
				shipParams.impulsePerFuel, shipParams.shipEdgeLength,
				quants.quantSizeOfSec, shipParams.maxOverload,
				shipParams.maxHeating);
			currentFlightPlan.speed = currentSpeed;
			fuel -= level * quants.quantSizeOfSec;
			m -= level * quants.quantSizeOfSec;
		}
		currentPosition.x = currentPosition.x + currentSpeed.x * quants.quantSizeOfSec;
		currentPosition.y = currentPosition.y + currentSpeed.y * quants.quantSizeOfSec;
		currentPosition.z = currentPosition.z + currentSpeed.z * quants.quantSizeOfSec;
		height = currentPosition.getScalar();
		if (height < EarthRadius + 0.12 && height >= EarthRadius) //too small value to calculate the exact
		{
			height = EarthRadius;
			currentFlightPlan.position = currentPosition;
			currentFlightPlan.speed.x = 0.0;
			currentFlightPlan.speed.y = 0.0;
			currentFlightPlan.speed.z = 0.0;
			break;
		}
		if (height < EarthRadius) //we are below the level of the ground surface
			//so we need to calculate an exact position of landing
		{
			vec way = {currentSpeed.x * quants.quantSizeOfSec,
				currentSpeed.y * quants.quantSizeOfSec,
				currentSpeed.z * quants.quantSizeOfSec};
			double cosA = (pow(way.getScalar(), 2) + pow(height, 2) -
				pow(currentPosition.getScalar(), 2)) / (2 * way.getScalar() * height);
			double extraWay = height * cosA - sqrt(pow(height, 2) * pow(cosA, 2) +
				pow(EarthRadius, 2) - pow(height, 2));
			double landingTime = extraWay / currentSpeed.getScalar();
			currentPosition.x = currentPosition.x + currentSpeed.x * landingTime;
			currentPosition.y = currentPosition.y + currentSpeed.y * landingTime;
			currentPosition.z = currentPosition.z + currentSpeed.z * landingTime;
			height = EarthRadius;
			currentFlightPlan.position = currentPosition;
			currentFlightPlan.speed.x = 0.0;
			currentFlightPlan.speed.y = 0.0;
			currentFlightPlan.speed.z = 0.0;
			break;
		}

		height = currentPosition.getScalar();
		currentFlightPlan.position = currentPosition;
		if (currentFlightPlanTime <= quants.quantSizeOfSec) //delay time is over, so we need to take the next pack of commands
		{
			j++;
			currentFlightPlanTime = flightCommands[j].delayTime;
		}
		else
		{
			currentFlightPlanTime -= quants.quantSizeOfSec;
		}
		calculatedFlightPlan.push_back(currentFlightPlan);
	}

	if (height <= EarthRadius) //we have landed, so position & speed will not be changed
	{
		for (int k = i; k < quants.numberOfQuants; k++)
		{
			calculatedFlightPlan.push_back(currentFlightPlan);
		}
	} 
	return calculatedFlightPlan;
}
