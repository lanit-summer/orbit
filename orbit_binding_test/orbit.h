#include <vector>

struct vec
{
    double x, y, z;
};

struct Rotation
{
    double rotationAroundX, rotationAroundY, rotationAroundZ;
};

typedef vec Orient;
typedef vec Position;
typedef Rotation RotationSpeed;

struct ShipPosition
{
    Position position;
    Orient orientation;
    vec speedFirst;
};

struct PartOfFlightPlan
{
    int delayTime;
    double impulseValue;
    Rotation rotateValue;
}

struct ShipParams
{
    double shipEdgeLength;
    double shipMass;
    double fuelMass;
    Rotation maxRotation;
    double maxFuelUsagePerSec;
    double impulsePerFuel;
    std::vector<PartOfFlightPlan> flightPlan;
};

struct Quants
{
    int numberOfQuants;
    double quantSizeOfSec;
};

std::vector <Position> computeFlightPlan(ShipPosition initialPosition,
                                         ShipParams shipParams,
                                         Quants quants);