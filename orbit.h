#include <vector>

using namespace std;

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

struct ShipParams
{
    double shipEdgeLength;
    double shipMass;
    double fuelMass;
    Rotation maxRotation;
    double maxFuelUsagePerSec;
    double impulsePerFuel;
    vector <double> impulseFlightPlan;
    vector <Rotation> rotateFlightPlan;
    vector <ShipPosition> position;
};

struct Quants
{
    int numberOfQuants;
    double quantSizeOfSec;
};

Position outPut(ShipPosition initialPosition, ShipParams shipParams,
                Quants quants);