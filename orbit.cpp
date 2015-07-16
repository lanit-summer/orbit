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
    double G = 6.67385 * pow(10, -11),
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

double airDens(double H)
{
    struct airD
    {
        double h, p;
    };
    airD air[55];
    H -= 6378.1;
    air[0].h = 0;
    air[0].p=1.225;
    air[3].h = 0.050;
    air[3].p=1.219;
    air[6].h = 0.100;
    air[6].p = 1.213;
    air[9].h = 0.200;
    air[9].p = 1.202;
    air[12].h = 0.300;
    air[12].p = 1.190;
    air[15].h = 0.500;
    air[15].p = 1.167;
    air[18].h = 1.0;
    air[18].p = 1.112;
    air[21].h = 2.0;
    air[21].p = 1.007;
    air[24].h = 3.000;
    air[24].p = 0.909;
    air[27].h = 5.000;
    air[27].p = 0.736;
    air[30].h = 8.000;
    air[30].p = 0.526;
    air[33].h = 10.000;
    air[33].p = 0.414;
    air[36].h = 12.000;
    air[36].p = 0.312;
    air[39].h = 15.000;
    air[39].p = 0.195;
    air[42].h = 20.000;
    air[42].p = 0.089;
    air[45].h = 50.000;
    air[45].p = 0.001027;
    air[48].h = 100.000;
    air[48].p = 0.000000555;
    air[51].h = 120.000;
    air[51].p = 0.0000000244;
    
    for (int i = 0 ; i < 52; i += 3)
    {
        double s = (air[i+3].h - air[i].h) / 3.0;
        air[i+1].h = air[i].h + s;
        air[i+2].h = air[i+1].h + s;
        double t = (air[i+3].p - air[i].p) / 3.0;
        air[i+1].p = air[i].p + t;
        air[i+2].p = air[i+1].p + t;
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
        P = air[t].p;
    }
    return P;
}

vec speed(vec speedFirst, double time, ShipPosition sPos, double mLevel,
          double mShip, double mFuel, Rotation moment, double specificImpulse,double size,
          double quantSizeOfSec)
{
    if (mLevel * time > mFuel)
    {
        cout<<"Not enough fuel!"<<endl;
        return speedFirst;
    }
    else
    {
        double M = mShip + mFuel;
        double mEarth = 5.9742 * pow(10, 24);
        double G = 6.67385 * pow(10, -11);
        double H = scalar (sPos.position);
        double scSpeedFirst = scalar(speedFirst);
        double S = size * size;
        vec exit = {0, 0, 0};
        vec x = transformVec(sPos.orientation,
            createQuaternion(angularVelocity(gravityForce(sPos.position, M),
                aerodynamicForce(airDens(H), speedFirst, S),
                tractiveForce(mLevel, specificImpulse, speedFirst),
                moment, quantSizeOfSec)));
        if (M != 0) {
            double v1 = 1 - airDens(H) * scSpeedFirst * S * time / (2.0 * M);
            double v2 = scalar(tractiveForce(mLevel, specificImpulse, speedFirst)) * time / M;
            double v3 = G * mEarth * time / pow(H, 3);
            vec t1 = multiVecDouble(speedFirst, v1);
            vec t2 = multiVecDouble(x, v2);
            vec t3 = multiVecDouble(sPos.position, v3);
            exit.x = t1.x - t2.x - t3.x;
            exit.y = t1.y - t2.y - t3.y;
            exit.z = t1.z - t2.z - t3.z;
        }
        else
        {
            cout<<"Mass = 0!"<<endl;
        }
        return exit;
    }
}
    
double scalarPosition(Position p)
{
    double res = sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
    return res;
}

//доработать функцию изменения массы топлива
Position outPut(ShipPosition initialPosition, ShipParams shipParams,
                Quants quants)
{
    double S = pow(shipParams.shipEdgeLength, 2);
    double H = scalar (initialPosition.position);
    double fuel = shipParams.fuelMass;
    double m = fuel + shipParams.shipMass;
    vec sp = initialPosition.speedFirst;
    double level;
    Rotation moment;
    int t = 0;
    vec orient = initialPosition.orientation;
    while (H > 9.6)
    {
        if (t > 2)
        {
            level = 0;
            moment.rotationAroundX = 0;
            moment.rotationAroundY = 0;
            moment.rotationAroundZ = 0;
        }
        else
        {
            level = shipParams.impulseFlightPlan[t];
            moment = shipParams.rotateFlightPlan[t];
        }
        sp = speed(sp, 1.0, initialPosition, level,
                   shipParams.shipMass, shipParams.fuelMass, moment,
                   shipParams.impulsePerFuel, shipParams.shipEdgeLength,
                   quants.quantSizeOfSec);
        initialPosition.position.x += sp.x;
        initialPosition.position.y += sp.y;
        initialPosition.position.z += sp.z;
        t++;
        H = scalarPosition(initialPosition.position);
        orient = transformVec(orient, createQuaternion(angularVelocity(
            gravityForce(initialPosition.position, shipParams.shipMass),
            aerodynamicForce(airDens(H), initialPosition.speedFirst, S),
            tractiveForce(level, shipParams.impulsePerFuel, sp),
            moment, quants.quantSizeOfSec)));
        if (level * 1.0 > fuel)// умножить на время работы двигателя
        {
            fuel = 0;
            m -= fuel;
        }
        else
        {
            fuel -= level;
            m -= level;
        }
    }
    return initialPosition.position;
}

int main()
{
    return 0;
}