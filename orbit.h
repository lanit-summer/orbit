const int sizeOfArray = 10000;
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
    vec speedFirst;
};

struct ShipParams
{
    double shipEdgeLength;
    double shipMass;
    double shipFuel;
    rotation maxRotation;
    double maxFuelUsagePerSec;
    double impulsePerFuel;
    double impulseFlightPlan[sizeOfArray];
    rotation rotateFlightPlan[sizeOfArray];
    shipPosition * position; //в структуру соответствующей команде
};

struct quants
{
    int numberOfQuants;
    double quantSizeOfSec;
};

Position outPut(shipPosition initialPosition,
           ShipParams shipParams,
           quants Quants);