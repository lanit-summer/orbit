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
    initialPosition.position.y = 6378.2;
    initialPosition.position.z = 0.0;
    initialPosition.orientation.x = 1.0;
    initialPosition.orientation.y = 0.0;
    initialPosition.orientation.z = 0.0;
    initialPosition.speedFirst.x = 0.0;
    initialPosition.speedFirst.y = 0.0;
    initialPosition.speedFirst.z = 0.0;
    initialPosition.moment.rotationAroundX = 0.0;
    initialPosition.moment.rotationAroundY = 0.0;
    initialPosition.moment.rotationAroundZ = 0.0;
    ShipParams shipParams;
    Quants quants;
    shipParams.shipEdgeLength = 0.0001;
    shipParams.shipMass = 1.0;
    shipParams.fuelMass = 0.0;
    shipParams.maxRotation.rotationAroundX = 0.0;
    shipParams.maxRotation.rotationAroundY = 0.0;
    shipParams.maxRotation.rotationAroundZ = 0.0;
    shipParams.maxFuelUsagePerSec = 100.0;
    shipParams.impulsePerFuel = 20.0;
    shipParams.maxOverload = 18000000.0;
    shipParams.maxHeating = 900000.0;
    quants.quantSizeOfSec = 1;
    quants.numberOfQuants = 100;
    int i;
    vector<PartOfFlightPlan> abc(100000);
    shipParams.flightPlan.resize(100000);
    for (i = 0; i < 100000; i++)
    {
        abc[i].impulseValue = 0.0;
        abc[i].rotateValue.rotationAroundX = 0.0;
        abc[i].rotateValue.rotationAroundY = 0.0;
        abc[i].rotateValue.rotationAroundZ = 0.0;
        shipParams.flightPlan[i].delayTime = 1;
    }
    shipParams.flightPlan = abc;
    vector<ReturnValues> result = computeFlightPlan(initialPosition, shipParams, quants);
    
    for (i = 0; i < quants.numberOfQuants; i++) {
        cout<<"Position: "<<result[i].position.x<<" "<<result[i].position.y<<" "<<result[i].position.z<<"\n";
        cout<<"NormalSpeed = "<<sqrt(pow(result[i].speed.x, 2) + pow(result[i].speed.y, 2) + pow(result[i].speed.z, 2))<<"\n";
    }
	_gettch(); 
}

