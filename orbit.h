#include <vector>

using namespace std;

struct vec
{
    double x, y, z;
};
struct rotation
{
    double rotationAroundX, rotationAroundY, rotationAroundZ;
};
typedef vec Orient;
typedef vec Position;
typedef rotation RotationSpeed;
struct shipPosition
{
    Position position;
    Orient orientation;
};

struct ShipParams
{
    double shipEdgeLength;
    double shipMass;
    rotation maxRotation;
    double maxFuelUsagePerSec;
    double impulsePerFuel;
    vector <double> impulseFlightPlan;
    vector <rotation> rotateFlightPlan;
    vector <shipPosition> position;
};

struct Quants
{
    int numberOfQuants;
    double quantSizeOfSec;
};

vector <vec> ABC(shipPosition initialPosition,
                 ShipParams shipParams,
                 Quants quants);
