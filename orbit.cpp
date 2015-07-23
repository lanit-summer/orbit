#include "orbit.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double scalar (vec t)
{
    double res = sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2));
    return res;
}

struct quaternion
{
    double w, x, y, z;
};

quaternion createQuaternion(vec speed)
{
    double c1 = cos(speed.z / 2),
    c2 = cos(speed.y / 2),
    c3 = cos(speed.x / 2),
    s1 = sin(speed.z / 2),
    s2 = sin(speed.y / 2),
    s3 = sin(speed.x / 2);
    
    quaternion q = {c1 * c2 * c3 - s1 * s2 * s3, s1 * s2 * c3 + c1 * c2 * s3,
        c1 * s2 * c3 - s1 * c2 * s3, s1 * c2 * c3 + c1 * s2 * s3};
    return q;
}

quaternion normalizeQuaternion(quaternion q)
{
    double s = sqrt(pow(q.x, 2) + pow(q.y, 2) + pow(q.z, 2) + pow(q.w, 2));
    quaternion p = {0, 0, 0, 0};
    if (s != 0)
    {
        p.w = q.w / s;
        p.x = q.x / s;
        p.y = q.y / s;
        p.z = q.z / s;
    }
    return p;
}

quaternion multiQuaternions(quaternion a, quaternion b)
{
    quaternion res = {a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
    res = normalizeQuaternion(res);
    return res;
}

quaternion multiVecQuaternion(quaternion q, vec v)
{
    quaternion res = {-q.x * v.x - q.y * v.y - q.z * v.z,
        q.w * v.x + q.y * v.z - q.z * v.y,
        q.w * v.y - q.x * v.z + q.z * v.x,
        q.w * v.z + q.x * v.y - q.y * v.x};
    return res;
}

quaternion invertQuaternion(quaternion q)
{
    quaternion p = {q.w, -q.x, -q.y, -q.z};
    return p;
}

vec multiVecDouble(vec t1, double t2)
{
    vec res = {t1.x * t2, t1.y * t2, t1.z * t2};
    return res;
}

//поворот вектора вокруг 3 осей (тангаж, рыскание, крен)
vec transformVec(vec v, quaternion q)
{
    quaternion res = multiQuaternions(multiVecQuaternion(q, v),
                                      invertQuaternion(q));
    vec t = {res.x, res.y, res.z};
    return t;
}

vec gravityForce(vec r, double m) //r - расстояние до центра Земли
{
    double G = 6.67385 * pow(10, -20),
    mEarth = 5.9742 * pow(10, 24);
    double R = pow(scalar(r), 3);
    if (R != 0)
    {
        vec g = multiVecDouble(r, G * mEarth / R);
        return g;
    }
    else
    {
        vec g = {0, 0, 0};
        return g;
    }
}

vec aerodynamicForce(double p, vec v, double S)
{
    double u = scalar(v);
    vec a = multiVecDouble(v, -p * u * S / 2);
    return a;
}

vec tractiveForce(double mLevel, double specificImpulse, vec v)
{
    double u = scalar(v);
    if (u != 0)
    {
        vec t = multiVecDouble(v, -mLevel * specificImpulse / u);
        return t;
    }
    else
    {
        vec t = {0, 0, 0};
        return t;
    }
}

vec angularVelocity(vec g, vec a, vec t, Rotation moment, double quantSizeOfSec)
{
    double x = moment.rotationAroundX,
    y = moment.rotationAroundY,
    z = moment.rotationAroundZ;
    if (x != 0)
    {
        x = (g.x - a.x - t.x) * quantSizeOfSec /x;
    }
    if (y != 0)
    {
        y = (g.y - a.y - t.y) * quantSizeOfSec /y;
    }
    if (z != 0)
    {
        z = (g.z - a.z - t.z) * quantSizeOfSec /z;
    }
    vec exit = {x, y, z};
    return exit;
}

double airDens (double H)
{
    H -= 6378.1;
    double p = 101325; //pascals
    //double t = 288.15; //k
    double g = 9.8; // m/sec^2
    //double L = -0.0065; // K/m
    double R = 8.31447; // dz/(mol*K)
    double M = 0.0289644; // kg/mol
    //int const height = (int) H;
    double T = 273.15;
    if (H > 10)
    {
        if (H > 20)
        {
            if (H > 47)
            {
                if (H > 54)
                {
                    if (H > 84)
                    {
                        if (H > 94)
                        {
                            if (H > 145)
                            {
                                //cout<<"p = 0.0"<<endl;
                                return 0.0;
                            }
                            else
                            {
                                T += 140 * (H - 94) / 51 - 90;
                            }
                        }
                        else
                        {
                            T -= 90;
                        
                        }
                    }
                    else
                    {
                        T += -3 * H + 162;
                    }
                }
            }
            else
            {
                T += (20 * H - 940) / 9;
            }
        }
        else
        {
            T -= 60;
        }
    }
    else
    {
        T += -8 * H + 20;
    }
    //cout<<"r * t = "<<R * T<<endl;
    //cout<<"chislitel = "<<-densCover * g * H * 1000<<endl;
    //cout<<"pressure = "<<P<<endl;
    double P = p * exp(-M * g * H * 1000/ (R * T));
    double dens = P * M / (R * T);
    //cout<<dens * pow(10, 9)<<endl;
    return (dens * pow(10, 9)) ;
}
/*double airDens(double H)
{
    struct airD
    {
        double h, p;
    };
    airD air[55];
    H -= 6378.1;
    air[0].h = 0; air[0].p=1225000000;
    air[3].h = 0.050; air[3].p=1219000000;
    air[6].h = 0.100; air[6].p = 1213000000;
    air[9].h = 0.200; air[9].p = 1202000000;
    air[12].h = 0.300; air[12].p = 1190000000;
    air[15].h = 0.500; air[15].p = 1167000000;
    air[18].h = 1.0; air[18].p = 1112000000;
    air[21].h = 2.0; air[21].p = 1007000000;
    air[24].h = 3.000; air[24].p = 909000000;
    air[27].h = 5.000; air[27].p = 736000000;
    air[30].h = 8.000; air[30].p = 526000000;
    air[33].h = 10.000; air[33].p = 414000000;
    air[36].h = 12.000; air[36].p = 312000000;
    air[39].h = 15.000; air[39].p = 195000000;
    air[42].h = 20.000; air[42].p = 89000000;
    air[45].h = 50.000; air[45].p = 1027000;
    air[48].h = 100.000; air[48].p = 555;
    air[51].h = 120.000; air[51].p = 24.4;
    
    for (int i = 0 ; i < 52; i += 3)
    {
        double s = (air[i+3].h - air[i].h) / 3.0;
        air[i+1].h = air[i].h + s;
        air[i+2].h = air[i+1].h + s;
        double t = (air[i+3].p - air[i].p) / 3.0;
        air[i+1].p = air[i].p + t;
        air[i+2].p = air[i+1].p + t;
        cout<<"air.["<<i<<"] = "<<air[i].p<<endl;
        cout<<"air.["<<i + 1<<"] = "<<air[i + 1].p<<endl;
        cout<<"air.["<<i + 2<<"] = "<<air[i + 2].p<<endl;
    }
    
    int t = 0;
    double P = 0;
    if (H <= 120)
    {
        double minH = H;
        for(int i = 1; i < 52; i++)
        {
            if(abs(air[i].h - H) < minH)
            {
                t = i;
                minH = abs(air[i].h - H);
            }
        }
        cout<<"Height =  "<<H<<endl;
        cout<<"T =  "<<t<<endl;
        cout<<"P = "<<air[t].p<<endl;
        P = air[t].p;
    }
    return P;
} */

vec speed(vec speedFirst, ShipPosition sPos, double mLevel,
          double mShip, double mFuel, Rotation moment, double specificImpulse,
          double size, double quantSizeOfSec)
{
    if (mLevel * quantSizeOfSec > mFuel)
    {
        return speedFirst;
    }
    else
    {
        double M = mShip + mFuel;
        double mEarth = 5.9742 * pow(10, 24);
        double G = 6.67385 * pow(10, -20);
        double H = scalar (sPos.position);
        double scSpeedFirst = scalar(speedFirst);
        double S = size * size;
        vec exit = {0, 0, 0};
        vec x = transformVec(sPos.orientation,
                             createQuaternion(angularVelocity(gravityForce(sPos.position, M),
                                                              aerodynamicForce(airDens(H), speedFirst, S),
                                                              tractiveForce(mLevel, specificImpulse, speedFirst),
                                                              moment, 1.0)));
        if (M != 0) {
            //cout<<"Height =  "<<H - 6378.1<<endl;
            //cout<<"plotnost =  "<<airDens(H)<<"          "<<endl;
            double v1 = 1 - (airDens(H) * scSpeedFirst * S * quantSizeOfSec / (2.0 * M));
            double v2 = scalar(tractiveForce(mLevel, specificImpulse, speedFirst)) * quantSizeOfSec / M;
            double v3 = G * mEarth * quantSizeOfSec / pow(H, 3);
            vec t1 = multiVecDouble(speedFirst, v1);
            vec t2 = multiVecDouble(x, v2);
            vec t3 = multiVecDouble(sPos.position, v3);
            //cout<<"t1 (V0): "<<t1.x<<" "<<t1.y<<" "<<t1.z<<endl;
            //cout<<"t2: "<<t2.x<<" "<<t2.y<<" "<<t2.z<<endl;
            //cout<<"t3 (R): "<<t3.x<<" "<<t3.y<<" "<<t3.z<<endl;
            //cout<<endl;
            exit.x = t1.x - t2.x - t3.x;
            exit.y = t1.y - t2.y - t3.y;
            exit.z = t1.z - t2.z - t3.z;
        }
        else
        {
            cout<<"Mass = 0!"<<endl;
        }
        //cout<<"SPEED: "<<exit.x<<" "<<exit.y<<" "<<exit.z<<endl;
        return exit;
    }
}
//доработать функцию изменения массы топлива
vector <Position> computeFlightPlan(ShipPosition initialPosition,
                                    ShipParams shipParams, Quants quants)
{
    double S = pow(shipParams.shipEdgeLength, 2);
    double H = scalar (initialPosition.position);
    double fuel = shipParams.fuelMass;
    double m = fuel + shipParams.shipMass;
    vec sp = initialPosition.speedFirst;
  //  vec sp = multiVecDouble(initialPosition.speedFirst, quants.quantSizeOfSec);
    double level;
    Rotation moment;
    int b = 0;
    vec orient = initialPosition.orientation;
    vector <Position> position(quants.numberOfQuants);
    int i;
    for (i = 0; i < quants.numberOfQuants && H > 6378.1; i++)
    {
        level = shipParams.impulseFlightPlan[i];
        moment = shipParams.rotateFlightPlan[i];
        //cout<<"SPEED = "<<scalar(sp)<<endl;
        //cout<<"INITIAL: "<<initialPosition.position.x<<" "<<initialPosition.position.y<<" "<<initialPosition.position.z<<endl;
        vec nextH = {initialPosition.position.x +
            sp.x * quants.quantSizeOfSec, initialPosition.position.y +
            sp.y * quants.quantSizeOfSec, initialPosition.position.z +
            sp.z * quants.quantSizeOfSec};
        //cout<<"nextH: "<<scalar(nextH)<<endl;
        if (scalar(nextH) < 6378.1)
        {
            cout<<"--------------------------------- IF"<<endl;
            vec way = {sp.x * quants.quantSizeOfSec, sp.y * quants.quantSizeOfSec,
                sp.z * quants.quantSizeOfSec}; //AC
            double cosA = (pow(scalar(way), 2) + pow(H, 2) -
                           pow(scalar(nextH), 2)) / (2 * scalar(way) * H);
            double extraWay = H * cosA - sqrt(pow(H, 2) * pow(cosA, 2) +
                                              pow(6378.1, 2) - pow(H, 2));
            quants.quantSizeOfSec = extraWay / scalar(sp);
            //cout<<"quant: "<<quants.quantSizeOfSec<<endl;
            nextH.x = initialPosition.position.x +
            sp.x * quants.quantSizeOfSec;
            nextH.y = initialPosition.position.y +
            sp.y * quants.quantSizeOfSec;
            nextH.z = initialPosition.position.z +
            sp.z * quants.quantSizeOfSec;
            initialPosition.position = nextH;
            H = 6378.1;
            break;
        }
        initialPosition.position = nextH;
        //cout<<nextH.x<<" "<<nextH.y<<" "<<nextH.z<<endl;
        H = scalar(nextH);
        cout<<"H = "<<H - 6378.1<<endl;
        orient = transformVec(orient, createQuaternion(angularVelocity(
                                                                       gravityForce(initialPosition.position, m),
                                                                       aerodynamicForce(airDens(H), initialPosition.speedFirst, S),
                                                                       tractiveForce(level, shipParams.impulsePerFuel, sp),
                                                                       moment, quants.quantSizeOfSec)));
        if (level * quants.quantSizeOfSec > fuel)
        {
            
            m -= fuel;
            fuel = 0;
            b = 1;
        }
        else
        {
            fuel -= level;
            m -= level;
        }
        position[i] = initialPosition.position;
        
        if (b == 1)
        {
            cout<<"Not enough fuel!"<<endl;
        }
        b = 0;
        sp = speed(sp, initialPosition, level,
                   shipParams.shipMass, shipParams.fuelMass, moment,
                   shipParams.impulsePerFuel, shipParams.shipEdgeLength,
                   quants.quantSizeOfSec);
        
    }
    if (H <= 6378.1)
    {
        int j;
        for (j = i; j < quants.numberOfQuants; j++)
        {
            position[j] = position[i - 1];
        }
        cout<<"Successful landing!!!"<<endl;
    }
    else if (i >= quants.numberOfQuants)
    {
        cout<<"Time is over!!!"<<endl;
    }
    
    return position;
}

int main()
{
    ShipPosition initialPosition;
    initialPosition.position.x = 0.0;
    initialPosition.position.y = 0.0;
    initialPosition.position.z = 6578.1;
    initialPosition.orientation.x = 1.0;
    initialPosition.orientation.y = 0.0;
    initialPosition.orientation.z = 0.0;
    initialPosition.speedFirst.x = 7.9;
    initialPosition.speedFirst.y = 0.0;
    initialPosition.speedFirst.z = 0.0;
    ShipParams shipParams;
    Quants quants;
    shipParams.shipEdgeLength = 0.001;
    shipParams.shipMass = 3.0;
    shipParams.fuelMass = 1000.0;
    shipParams.maxRotation.rotationAroundX = 10.0;
    shipParams.maxRotation.rotationAroundY = 10.0;
    shipParams.maxRotation.rotationAroundZ = 10.0;
    shipParams.maxFuelUsagePerSec = 100.0;
    shipParams.impulsePerFuel = 20.0;
    quants.quantSizeOfSec = 10;
    quants.numberOfQuants = 100;
    int i;
    vector<double> abc(100000);
    vector<Rotation> a(100000);
    shipParams.impulseFlightPlan.reserve (100000);
    shipParams.rotateFlightPlan.reserve (100000);
    
    abc[0] = 100.0;
    a[0].rotationAroundX = 0.0;
    a[0].rotationAroundY = 0.0;
    a[0].rotationAroundZ = 0.0;
    
    for (i = 1; i < 100000; i++)
    {
        abc[i] = 0.0;
        a[i].rotationAroundX = 0.0;
        a[i].rotationAroundY = 0.0;
        a[i].rotationAroundZ = 0.0;
    }
    shipParams.impulseFlightPlan = abc;
    shipParams.rotateFlightPlan = a;
    vector<Position> result = computeFlightPlan(initialPosition, shipParams, quants);
    
    //cout<<"number = "<<quants.numberOfQuants<<endl;
    
    for (i = 0; i < quants.numberOfQuants; i++){
        //airDens(double (i));
       //cout<<result[i].x<<" "<<result[i].y<<" "<<result[i].z<<endl;
    }
    return 0;
}

/*BOOST_AUTO_TEST_SUITE(TestFuzzyCompare)
BOOST_AUTO_TEST_CASE(computeOrbit)
{
     ShipPosition initialPosition;
     initialPosition.position = {0.0, 0.0, 6478.0};
     initialPosition.orientation = {1.0, 0.0, 0.0};
     initialPosition.speedFirst = {8.0, 0.0, 0.0};
     ShipParams shipParams;
     Quants quants;
     shipParams.shipEdgeLength = 0.001;
     shipParams.shipMass = 10.0;
     shipParams.fuelMass = 0.0;
     shipParams.maxRotation = {10.0, 10.0, 10.0};
     shipParams.maxFuelUsagePerSec = 100.0;
     shipParams.impulsePerFuel = 20.0;
     quants.quantSizeOfSec = 1.0;
     quants.numberOfQuants = 3.0;
     shipParams.impulseFlightPlan = {0.0, 0.0, 0.0};
     shipParams.rotateFlightPlan = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
     vector<Position> res = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
     vector<Position> result = computeFlightPlan(initialPosition, shipParams, quants);
    BOOST_CHECK_EQUAL(1, 1);
}
BOOST_AUTO_TEST_SUITE_END() */