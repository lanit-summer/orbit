#include "orbit.cpp"
#include "orbit_JOrbit.h"
#include <fstream>

JNIEXPORT void JNICALL Java_orbit_JOrbit_CreateTrajectory
  (JNIEnv * env,
   jobject obj,
   jdouble initX,jdouble initY, jdouble initZ,
   jdouble orX, jdouble orY, jdouble orZ,
   jdouble shipmass, jdouble fuelmass, jdouble length,
   jdouble maxrotX, jdouble maxrotY, jdouble maxrotZ,
   jdouble fuelusage, jdouble impulse, 
   jdouble overload, jdouble heating, 
   jint quantsizeofsec, jint quantnumber){

  	ShipPosition initialPosition;
	initialPosition.position.x = initX;
	initialPosition.position.y = initY;
	initialPosition.position.z = initZ;

	initialPosition.orientation.x = orX;
	initialPosition.orientation.y = orY;
	initialPosition.orientation.z = orZ;

	initialPosition.speedFirst.x = 0.0;
	initialPosition.speedFirst.y = 0.0;
	initialPosition.speedFirst.z = 0.0;

	ShipParams shipParams;
	Quants quants;
	shipParams.shipEdgeLength = length;
	shipParams.shipMass = shipmass;
	shipParams.fuelMass = fuelmass;

	shipParams.maxRotation.rotationAroundX = maxrotX;
	shipParams.maxRotation.rotationAroundY = maxrotY;
	shipParams.maxRotation.rotationAroundZ = maxrotZ;

	shipParams.maxFuelUsagePerSec = fuelusage;
	shipParams.impulsePerFuel = impulse;
	shipParams.maxOverload = overload;
	shipParams.maxHeating = heating;
	quants.quantSizeOfSec = quantsizeofsec;
	quants.numberOfQuants = quantnumber;

	int i;

	vector<PartOfFlightPlan> abc(100000);
	shipParams.flightPlan.resize(100000);
	for (i = 0; i < 100000; i++)
	{
		abc[i].impulseValue = 0.0;
		abc[i].rotateValue.rotationAroundX = 0.0;
		abc[i].rotateValue.rotationAroundY = 0.0;
		abc[i].rotateValue.rotationAroundZ = 0.0;
		shipParams.flightPlan[i].delayTime = 1.0;
	}

	shipParams.flightPlan = abc;
	vector<ReturnValues> result = computeFlightPlan(initialPosition, shipParams, quants);
	ofstream fout("trajectory.xyzv"); 
	
	for (i = 0; i < quants.numberOfQuants; i++)
	{
		fout <<"Position "<<result[i].position.x<<" "<<result[i].position.y<<" "<<result[i].position.z<<"\n";
	}
	fout.close();
  }

