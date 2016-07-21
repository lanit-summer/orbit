// OrbitLauncher.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <stdio.h>
#include "OrbitSimulator.cpp"
#include<iostream>

int main() {
    ShipPosition initialPosition;
    initialPosition.position.x = 0.0;
    initialPosition.position.y = 0.0;
    initialPosition.position.z = 6553.22;
    initialPosition.orientation.x = 1.0;
    initialPosition.orientation.y = 0.0;
    initialPosition.orientation.z = 0.0;
    initialPosition.speedFirst.x = -7.8375; //-7.83762;
    initialPosition.speedFirst.y = 0.0;
    initialPosition.speedFirst.z = 0.0;
    initialPosition.moment.rotationAroundX = 0.0;
    initialPosition.moment.rotationAroundY = 0.0;
    initialPosition.moment.rotationAroundZ = 0.0;
    ShipParams shipParams;
    Quants quants;
    shipParams.shipEdgeLength = 0.0025;
    shipParams.shipMass = 3725.0;
    shipParams.fuelMass = 1000.0;
    shipParams.maxRotation.rotationAroundX = 0.0;
    shipParams.maxRotation.rotationAroundY = 0.0;
    shipParams.maxRotation.rotationAroundZ = 0.0;
    shipParams.maxFuelUsagePerSec = 100.0;
    shipParams.impulsePerFuel = 2.61;
    shipParams.maxHeating = 5274.0; // 5000Ñ
    quants.quantSizeOfSec = 1;
    quants.numberOfQuants = 6480;
    int i;
    //vector<PartOfFlightPlan> abc(100000);
    shipParams.flightPlan.resize(100000);
	shipParams.flightPlan[0].delayTime = 5420;
	shipParams.flightPlan[1].delayTime = 29;
	shipParams.flightPlan[1].impulseValue = 11;

	/*for (i = 0; i < quants.numberOfQuants; i++)
    {
        abc[i].impulseValue = 0.0;
        abc[i].rotateValue.rotationAroundX = 0.0;
        abc[i].rotateValue.rotationAroundY = 0.0;
        abc[i].rotateValue.rotationAroundZ = 0.0;
        abc[i].delayTime = 1;
    }
	for (i = 5420; i < 5449; i++) {
		abc[i].impulseValue = 11;
	}*/
    
    vector<ReturnValues> result = computeFlightPlan(initialPosition, shipParams, quants);
    

    for (i = 0; i < quants.numberOfQuants; i++) {
		double pos = result[i].position.getScalar() - 6378.1;
		double speed = sqrt(pow(result[i].speed.x, 2) + pow(result[i].speed.y, 2) + pow(result[i].speed.z, 2));
		if (i >= 6440 && i <= 6480) { 
			//cout<<i<<" : "<<pos<<" ";
			//cout<<"Position: "<<result[i].position.x<<" "<<result[i].position.y<<" "<<result[i].position.z<<"\n";
			//cout<<"NormalSpeed = "<<speed<<"\n";
			cout<<"Position: "<<result[i].position.x<<" "<<result[i].position.y<<" "<<result[i].position.z<<"\n";
			cout<<"Speed: "<<result[i].speed.x<<" "<<result[i].speed.y<<" "<<result[i].speed.z<<"\n";
		}
    }
	_gettch(); 
}

