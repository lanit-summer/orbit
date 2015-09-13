#include "gtest/gtest.h"
#include "orbit.h"
#include <vector>
#include <cmath>

class CTest : public ::testing::Test
{
};


TEST_F(CTest, CheckSimple)
{
	ShipPosition initialPosition;
    initialPosition.position.x = 0.0;
    initialPosition.position.y = 0.0;
    initialPosition.position.z = 6578.1;
    initialPosition.orientation.x = 0.0;
    initialPosition.orientation.y = 0.0;
    initialPosition.orientation.z = 1.0;
    initialPosition.speedFirst.x = 0.0;
    initialPosition.speedFirst.y = 0.0;
    initialPosition.speedFirst.z = 0.0;
    ShipParams shipParams;
    Quants quants;
    shipParams.shipEdgeLength = 0.001;
    shipParams.shipMass = 3.0;
    shipParams.fuelMass = 10.0;
    shipParams.maxRotation.rotationAroundX = 10.0;
    shipParams.maxRotation.rotationAroundY = 10.0;
    shipParams.maxRotation.rotationAroundZ = 10.0;
    shipParams.maxFuelUsagePerSec = 100.0;
    shipParams.impulsePerFuel = 20.0;
    shipParams.maxOverload = 2.0;
    shipParams.maxHeating = 100.0;
    quants.quantSizeOfSec = 10;
    quants.numberOfQuants = 10;
    int i;
    std::vector<PartOfFlightPlan> abc(100000);
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
    std::vector<ReturnValues> result = computeFlightPlan(initialPosition, shipParams, quants);
    double zres[] = {6577.18, 6575.34, 6572.57, 6568.88, 6564.27,
                     6558.73, 6552.27, 6544.87, 6536.55, 6527.29};
    for (i = 0; i < quants.numberOfQuants; i++)
    {
        ASSERT_TRUE(result[i].position.x == 0);
        ASSERT_TRUE(result[i].position.y == 0);
        ASSERT_TRUE(fabs(result[i].position.z - zres[i]) < 0.01);
    }
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
    return 0;
}
