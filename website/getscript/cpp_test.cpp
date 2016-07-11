#include <iostream>
#include "orbit.h"

int main()
{
	ShipPosition initialPosition;
	initialPosition.position = {0.5, 0.6, 0.7};
	initialPosition.orientation = {1.5, 1.6, 1.7};
	initialPosition.speedFirst = {1, 2, 3};

	Quants quants = {3, 10};

	ShipParams shipParams;
	shipParams.shipEdgeLength = 1.1;
	shipParams.shipMass = 2.5;
	shipParams.fuelMass = 1.3;
	shipParams.maxFuelUsagePerSec = 3.3;
	shipParams.impulsePerFuel = 2.2;

	Rotation maxrat = {4.4, 5.5, 6.6};
	shipParams.maxRotation = maxrat;

	shipParams.impulseFlightPlan = std::vector<double>(4, 2.5);
	shipParams.rotateFlightPlan =  std::vector<Rotation>(4, {0.1, 0.2, 0.3});

	std::vector<Position> res = outPut(initialPosition, shipParams, quants);

	std::cout << res.size() << std::endl;
	for (int i = 0; i < res.size(); ++i)
	{
		std::cout << res[i].x << " ";
		std::cout << res[i].y << " ";
		std::cout << res[i].z << " ";
		std::cout << std::endl;
	}
	std::cout << "end" << std::endl;
	return 0;
}