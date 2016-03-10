#include "orbit.h"

vec calculateGravityForce(vec distance, double shipMass)
{
    double distanceScalar = distance.getScalar();
    if (distanceScalar == 0) { 
        vec res = {0, 0, 0};
        return res ;
    }
    double a = G * EarthMass * shipMass / pow(distanceScalar, 3);
    vec res = distance.multiplyWithDouble(a);
    return res;
}

double temperature(double H)
{
    if (H <= 0)
    {
        throw invalid_argument("Height is less than the Earth radius!");
    }
    double T = ZeroCelsius;
    if (H > 145)
    {
        return 0.0;
    }
    if (H > 94)
    {
        T += 140 * (H - 94) / 51 - 90;
    }
    if (H > 84)
    {
        T -= 90;
    }
    if (H > 54)
    {
        T += -3 * H + 162;
    }
    if (H > 47)
    {
        return T;
    }
    if (H > 20)
    {
        T += (20 * H - 940) / 9;
    }
    if (H > 10)
    {
        T -= 60;
    }
    else
    {
        T += -8 * H + 20;
    }
    return T;
}

double airDens(double H)
{
    H -= EarthRadius;
    double T = temperature(H);
    if (T <= 0.0)
    {
        return 0.0;
    }
    else
    {
        double p = 101325,
               g = G * EarthMass / pow(H, 2),
               R = 8.31447,
               M = 0.0289644,
               P = p * exp(-M * g * H * 1000 / (R * T)),
               dens = P * M / (R * T);
        return dens * pow(10.0, 9);
    }
}

vec calculateAerodynamicForce(vec speed, double square, double height)
{
    double v = speed.getScalar();
    double p = airDens(height);
    vec res = speed.multiplyWithDouble(-p * v * square / 2);
    return res;
}

vec calculateTractiveForce(double massLevel, double specificImpulse, vec speed)
{
    double v = speed.getScalar();
    if (v == 0) { 
        vec res = {0, 0, 0};
        return res ;
    }
    vec t = speed.multiplyWithDouble(massLevel * specificImpulse / v);
    return t;
}

vec calculateAngularVelocity(vec g, vec a, vec t, Rotation moment, double quantSizeOfSec,
                             double length, vec prevAngularVelocity)
{
    double x = moment.rotationAroundX, //момент вращения (I)
           y = moment.rotationAroundY,
           z = moment.rotationAroundZ;
    vec l = {length / 2, length / 2, length / 2};
    vec resultForce; //равнодействующая сила
    resultForce.x = g.x + a.x + t.x;
    resultForce.y = g.y + a.y + t.y;
    resultForce.z = g.z + a.z + t.z;
    vec momentForce = l.multiply(resultForce); //момент сил (M)
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
    vec exit; // d(I * w) / dt = M
    exit.x = prevAngularVelocity.x + x;
    exit.y = prevAngularVelocity.y + y;
    exit.z = prevAngularVelocity.z + z;
    return exit; //угловая скорость (w)
}

double aerodynamicHeating(double T, vec speed)
{
    double a = T + pow(speed.getScalar(), 2) / 2;
    return a;
}

vec speed(vec previousSpeed, ShipPosition sPos, double fuelConsumption,
          double mShip, double mFuel, Rotation moment, double specificImpulse,
          double size, double quantSizeOfSec, double maxOverload, double maxHeating)
{
    if (fuelConsumption * quantSizeOfSec > mFuel)
    {
        return previousSpeed;
    }
    else
    {
        double mTotal = mShip + mFuel;
        double H = sPos.position.getScalar();
        double scSpeedFirst = previousSpeed.getScalar();
        double S = size * size;
        vec exit = {0, 0, 0};
        if (mTotal != 0) {
            if (quantSizeOfSec > 0.0)
            {
                double v1 = airDens(H) * scSpeedFirst * S / (2.0 * mTotal),
                       v2 = 1 / quantSizeOfSec  - v1,
                       v3 = calculateTractiveForce(fuelConsumption, specificImpulse, previousSpeed).getScalar() / mTotal,
                       v4 = G * EarthMass / pow(H, 3);
                
                vec t1 = previousSpeed.multiplyWithDouble(v1),
                    t2 = previousSpeed.multiplyWithDouble(v2),
                    t3 = sPos.orientation.multiplyWithDouble(v3),
                    t4 = sPos.position.multiplyWithDouble(v4);
                exit.x = (t2.x + t3.x - t4.x) * quantSizeOfSec;
                exit.y = (t2.y + t3.y - t4.y) * quantSizeOfSec;
                exit.z = (t2.z + t3.z - t4.z) * quantSizeOfSec;
                
                vec overload = {0, 0, 0};
                overload.x = - t1.x + t3.x - t4.x;
                overload.y = - t1.y + t3.y - t4.y;
                overload.z = - t1.z + t3.z - t4.z;
                double g = G * EarthMass / pow(H, 2),
                       over = overload.getScalar() / g;
                
                if (over > maxOverload)
                {
                    throw invalid_argument("Overload");
                }
            }
            else
            {
                return previousSpeed;
            }
        }
        if (H <= 6523.1)
        {
            double a = aerodynamicHeating(temperature(sPos.position.getScalar()), exit);
            if (a > maxHeating)
            {
                throw invalid_argument("Overheating");
            }
        }
        return exit;
    }
}

vector <ReturnValues> computeFlightPlan(ShipPosition initialPosition,
                                        ShipParams shipParams, Quants quants)
{
    double S = pow(shipParams.shipEdgeLength, 2),
           H = initialPosition.position.getScalar(),
           fuel = shipParams.fuelMass,
           m = fuel + shipParams.shipMass;
    double level;
    vec sp = initialPosition.speedFirst;
    Rotation moment = initialPosition.moment;
    vec orient = initialPosition.orientation;
    vec prevAngularVelocity = {0, 0, 0};
    
    vector<ReturnValues> returnValue(quants.numberOfQuants);
    int i = 0,
        j = 0;
    double count = shipParams.flightPlan[0].delayTime;
    for (i = 0; i < quants.numberOfQuants && H > 6378.1; i++,
         count -= quants.quantSizeOfSec)
    {
        level = shipParams.flightPlan[j].impulseValue;
        moment = shipParams.flightPlan[j].rotateValue;
        prevAngularVelocity = calculateAngularVelocity(
                                calculateGravityForce(initialPosition.position, m),
                                calculateAerodynamicForce(sp, S, H),
                                calculateTractiveForce(level, shipParams.impulsePerFuel, sp),
                                moment, 1.0, shipParams.shipEdgeLength, prevAngularVelocity);
        orient = orient.rotate(prevAngularVelocity.createQuaternion());
        if (level * quants.quantSizeOfSec > fuel)
        {
            double time = fuel / quants.quantSizeOfSec,
                   timeOut = quants.quantSizeOfSec - time;
            sp = speed(sp, initialPosition, level,
                       shipParams.shipMass, fuel, moment,
                       shipParams.impulsePerFuel, shipParams.shipEdgeLength,
                       time, shipParams.maxOverload, shipParams.maxHeating);
            returnValue[i].speed = sp;
            
            m -= fuel;
            fuel = 0.0;
            vec nextH = {initialPosition.position.x +
                sp.x * time, initialPosition.position.y +
                sp.y * time, initialPosition.position.z +
                sp.z * time};
            if (nextH.getScalar() < 6378.1)
            {
                vec way = {sp.x * time, sp.y * time, sp.z * time};
                double cosA = (pow(way.getScalar(), 2) + pow(H, 2) -
                    pow(nextH.getScalar(), 2)) / (2 * way.getScalar() * H);
                double extraWay = H * cosA - sqrt(pow(H, 2) * pow(cosA, 2) +
                                                  pow(6378.1, 2) - pow(H, 2));
                time = extraWay / sp.getScalar();
                nextH.x = initialPosition.position.x + sp.x * time;
                nextH.y = initialPosition.position.y + sp.y * time;
                nextH.z = initialPosition.position.z + sp.z * time;
                initialPosition.position = nextH;
                H = 6378.1;
                returnValue[i].position = initialPosition.position;
                break;
            }
            initialPosition.position = nextH;
            H = initialPosition.position.getScalar();
            sp = speed(sp, initialPosition, 0.0,
                       shipParams.shipMass, fuel, moment,
                       shipParams.impulsePerFuel, shipParams.shipEdgeLength,
                       timeOut, shipParams.maxOverload, shipParams.maxHeating);
        }
        else
        {
            sp = speed(sp, initialPosition, level,
                       shipParams.shipMass, fuel, moment,
                       shipParams.impulsePerFuel, shipParams.shipEdgeLength,
                       quants.quantSizeOfSec, shipParams.maxOverload,
                       shipParams.maxHeating);
            returnValue[i].speed = sp;
            fuel -= level * quants.quantSizeOfSec;
            m -= level * quants.quantSizeOfSec;
        }
        vec nextH = {initialPosition.position.x +
            sp.x * quants.quantSizeOfSec, initialPosition.position.y +
            sp.y * quants.quantSizeOfSec, initialPosition.position.z +
            sp.z * quants.quantSizeOfSec};
        if (nextH.getScalar() < 6378.1)
        {
            vec way = {sp.x * quants.quantSizeOfSec, sp.y * quants.quantSizeOfSec,
                sp.z * quants.quantSizeOfSec};
            double cosA = (pow(way.getScalar(), 2) + pow(H, 2) -
                pow(nextH.getScalar(), 2)) / (2 * way.getScalar() * H);
            double extraWay = H * cosA - sqrt(pow(H, 2) * pow(cosA, 2) +
                                              pow(6378.1, 2) - pow(H, 2));
            double landingTime = extraWay / sp.getScalar();
            nextH.x = initialPosition.position.x +
            sp.x * landingTime;
            nextH.y = initialPosition.position.y +
            sp.y * landingTime;
            nextH.z = initialPosition.position.z +
            sp.z * landingTime;
            initialPosition.position = nextH;
            H = 6378.1;
            returnValue[i].position = initialPosition.position;
            break;
        }
        initialPosition.position = nextH;
        H = initialPosition.position.getScalar();
        returnValue[i].position = initialPosition.position;
        if (count == 0)
        {
            j++;
            count = shipParams.flightPlan[j].delayTime;
        }
    }
    if (H <= 6378.1)
    {
        int j;
        for (j = i; j < quants.numberOfQuants; j++)
        {
            
            returnValue[j].position = returnValue[i].position;
        }
    }
    
    return returnValue;
}

//минимальная плотность куба = 3 кг/м^3 */