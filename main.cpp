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

//вращение объекта
struct quaternion
{
    double w, x, y, z;
};

quaternion createQuat(vec speed) //создание кватерниона из набора скоростей
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

quaternion normalize(quaternion q)
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

quaternion mulQQ(quaternion a, quaternion b) //умножение 2 кватернионов
{
    quaternion res = {a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
    res = normalize(res);
    return res;
}

quaternion mulVQ(quaternion q, vec v) //умножение вектора на кватернион
{
    quaternion res = {-q.x * v.x - q.y * v.y - q.z * v.z,
        q.w * v.x + q.y * v.z - q.z * v.y,
        q.w * v.y - q.x * v.z + q.z * v.x,
        q.w * v.z + q.x * v.y - q.y * v.x};
    return res;
}

quaternion invertQuat (quaternion q) //обратный кватернион
{
    quaternion p = {0, -q.x, -q.y, -q.z};
    return p;
}

//поворот вектора вокруг 3 осей (тангаж, рыскание, крен)
vec transformVec (vec v, quaternion q)
{
    quaternion res = mulQQ(mulVQ(q, v), invertQuat(q));
    vec t = {res.x, res.y, res.z};
    return t;
}

//вращение под действием маховиков
vec gravityForce(vec r, double m) //r - расстояние до центра Земли
{
    double G = 6.67385 * pow(10, -11);
    double mEarth = 5.9742 * pow(10, 24);
    double R = scalar(r);
    if (R != 0)
    {
        vec g = {G * mEarth * r.x / pow(R, 3), G * mEarth * r.y / pow(R, 3),
            G * mEarth * r.z / pow(R, 3)};
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
    vec a = {-p * u * v.x * S/ 2, -p * u * v.y * S/ 2, -p * u * v.z * S/ 2};
    return a;
}

vec tracForce(double mLevel, double specificImpulse, vec v)
{
    double u = scalar(v);
    if (u != 0)
    {
        vec t = {-mLevel * specificImpulse * v.x / u,
            -mLevel * specificImpulse * v.y / u,
            -mLevel * specificImpulse * v.z / u};
        return t;
    }
    else
    {
        vec t = {0, 0, 0};
        return t;
    }
}

vec angularVelocity(vec g, vec a, vec t, rotation moment) //угловая скорость
{
    double x = moment.rotationAroundX;
    double y = moment.rotationAroundY;
    double z = moment.rotationAroundZ;
    if (x != 0)
    {
        x = (g.x - a.x - t.x)/x;
    }
    if (y != 0)
    {
        y = (g.y - a.y - t.y)/y;
    }
    if (z != 0)
    {
        z = (g.z - a.z - t.z)/z;
    }
    vec exit = {x, y, z};
    return exit;
}

vec multi(vec t1, double t2)
{
    vec res = {t1.x * t2, t1.y * t2, t1.z * t2};
    return res;
}

double mass(double mLevel, double m)
{
    m -= mLevel;
    return m;
}

double airDens(double H)
{
    struct airD
    {
        double h, p;
    };
    airD air[55];
    H -= 6378.1;
    air[0].h = 0; air[0].p=1.225;
    air[3].h = 0.050; air[3].p=1.219;
    air[6].h = 0.100; air[6].p = 1.213;
    air[9].h = 0.200; air[9].p = 1.202;
    air[12].h = 0.300; air[12].p = 1.190;
    air[15].h = 0.500; air[15].p = 1.167;
    air[18].h = 1.0; air[18].p = 1.112;
    air[21].h = 2.0; air[21].p = 1.007;
    air[24].h = 3.000; air[24].p = 0.909;
    air[27].h = 5.000; air[27].p = 0.736;
    air[30].h = 8.000; air[30].p = 0.526;
    air[33].h = 10.000; air[33].p = 0.414;
    air[36].h = 12.000; air[36].p = 0.312;
    air[39].h = 15.000; air[39].p = 0.195;
    air[42].h = 20.000; air[42].p = 0.089;
    air[45].h = 50.000; air[45].p = 0.001027;
    air[48].h = 100.000; air[48].p = 0.000000555;
    air[51].h = 120.000; air[51].p = 0.0000000244;
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

vec speed(vec speedFirst, double time, shipPosition sPos, double mLevel,
          double m, rotation moment,
          double specificImpulse, double size)
{
    double mEarth = 5.9742 * pow(10, 24);
    double G = 6.67385 * pow(10, -11);
    double H = scalar (sPos.position);
    double scSpeedFirst = scalar(speedFirst);
    double S = size * size;
    vec x = transformVec(sPos.orientation,
                         createQuat(angularVelocity(gravityForce(sPos.position, m),
                                                    aerodynamicForce(airDens(H), speedFirst, S),
                                                    tracForce(mLevel, specificImpulse, speedFirst), moment)));
    double v3 = G * mEarth * time / pow(H, 3);
    vec t3 = multi(sPos.position, v3);
    vec exit = {0, 0, 0};
    if (m != 0) {
        double v1 = 1 - airDens(H) * scSpeedFirst * S * time / (2.0 * m);
        double v2 = scalar(tracForce(mLevel, specificImpulse, speedFirst)) * time / m;
        vec t1 = multi(speedFirst, v1);
        vec t2 = multi(x, v2);
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
//пользователь заполняет массив из 100000 нулей своими значениями
vec outPut (shipPosition sPos, vec speedFirst, double m, double mLevel[3],
            rotation momentR[3], double size, double specificImpulse) //задать диапазон!!!
//можно ли так передавать массив?
{
    double S = size * size;
    double H = scalar (sPos.position);
    vec sp;
    double level;
    rotation moment;
    int t = 0;
    vec orient = sPos.orientation;
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
            level = mLevel[t];
            moment = momentR[t];
        }
        sp = speed(speedFirst, 1.0, sPos, level, m,
                   moment, specificImpulse, size);
        m = mass(level, m);
        sPos.position.x += sp.x;
        sPos.position.y += sp.y;
        sPos.position.z += sp.z;
        t++;
        H = scalar (sPos.position); //надо выдать position в файл на каждом шаге!
        orient = transformVec(orient, createQuat(angularVelocity(gravityForce(sPos.position, m), aerodynamicForce(airDens(H), speedFirst, S), tracForce(level, specificImpulse, speedFirst), moment)));
    }
    return sp;
}

int main()
{
    return 0;
}