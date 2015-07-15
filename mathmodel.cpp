#include <iostream>
#include <algorithm>
#include <cmath>

const double G = 6.67385 * pow(10, -11); //„‡‚ËÚ‡ˆËÓÌÌ‡ˇ ÔÓÒÚÓˇÌÌ‡ˇ

using namespace std;

double size, //‡ÁÏÂ ÍÓ‡·Îˇ
       maxTorque, //ÏÓÏÂÌÚ ‚‡˘ÂÌËˇ
       maxFuel, //Ï‡ÍÒËÏ‡Î¸Ì˚È ‡ÒıÓ‰ ÚÓÔÎË‚‡
       maxImpulse, //Û‰ÂÎ¸Ì˚È ËÏÛÎ¸Ò
       fuelLevel, //ÛÓ‚ÂÌ¸ Ï‡ÒÒÓ‚Ó„Ó ‡ÒıÓ‰‡ ÚÓÔÎË‚‡
       limOver; //ÔÂ‰ÂÎ¸Ì‡ˇ ÔÂÂ„ÛÁÍ‡

struct vec //ÓËÂÌÚ‡ˆËˇ
{
    double x, y, z;
};
vec position; //ÔÓÎÓÊÂÌËÂ

struct m //Ï‡ÒÒ˚ ÍÓ‡·Îˇ Ë ÚÓÔÎË‚‡
{
    double ship, fuel;
};

vec rSpeed; //ÒÍÓÓÒÚ¸ ‚‡˘ÂÌËˇ

vec momentRotation; //ÏÓÏÂÌÚ ‚‡˘ÂÌËˇ ‚ÓÍÛ„ Í‡Ê‰ÓÈ ÓÒË

vec rageSim; //‰Ë‡ÔÁÓÌ ÏÓ‰ÂÎËÓ‚‡ÌËˇ

struct airD//ÒÓÔÓÚË‚ÎÂÌËÂ ‚ÓÁ‰Ûı‡
{
    double h, p;
};

double scalar(vec t)
{
    double res = sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2));
    return res;
}

double airDens(double H)
{
    airD air[55];
    H -= 6378100; //  ‚ ÏÂÚ‡ı
    air[0].h = 0;
    air[0].p=1.225;
    air[3].h = 50;
    air[3].p=1.219;
    air[6].h = 100;
    air[6].p = 1.213;
    air[9].h = 200;
    air[9].p = 1.202;
    air[12].h = 300;
    air[12].p = 1.190;
    air[15].h = 500;
    air[15].p = 1.167;
    air[18].h = 1000;
    air[18].p = 1.112;
    air[21].h = 2000;
    air[21].p = 1.007;
    air[24].h = 3000;
    air[24].p = 0.909;
    air[27].h = 5000;
    air[27].p = 0.736;
    air[30].h = 8000;
    air[30].p = 0.526;
    air[33].h = 10000;
    air[33].p = 0.414;
    air[36].h = 12000;
    air[36].p = 0.312;
    air[39].h = 15000;
    air[39].p = 0.195;
    air[42].h = 20000;
    air[42].p = 0.089;
    air[45].h = 50000;
    air[45].p = 0.001027;
    air[48].h = 100000;
    air[48].p = 0.000000555;
    air[51].h = 120000;
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
    if (H <= 120000)
    {
        double minH = H;
        for (int i = 1; i < 52; i++)
        {
            if (abs(air[i].h - H) < minH)
            {
                t = i;
                minH = abs(air[i].h - H);
            }
        }
        P = air[t].p;
    }
    return P;
}

vec tracForce(double mLevel, double impulseS, vec v)
{
    vec t;
    double u = scalar(v);
    t.x = mLevel * impulseS * v.x / u;
    t.y = mLevel * impulseS * v.y / u;
    t.z = mLevel * impulseS * v.z / u;
    return t;
}

vec multi(vec t1, double t2)
{
    vec res;
    res.x = t1.x * t2;
    res.y = t1.y * t2;
    res.z = t1.z * t2;
    return res;
}

double mass(double mLevel, double m)
{
    m -= mLevel;
    return m;
}

//вращение объекта
struct quaternion
{
    double w, x, y, z;
};

quaternion quatCoordinates(double x, double y, double z, double w)
{
    quaternion q;
    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
    return q;
}

quaternion createQuat(vec speed) //создание кватерниона из набора скоростей
{
    double c1 = cos(speed.z / 2),
           c2 = cos(speed.y / 2),
           c3 = cos(speed.x / 2),
           s1 = sin(speed.z / 2),
           s2 = sin(speed.y / 2),
           s3 = sin(speed.x / 2);
    quaternion q = quatCoordinates(c1 * c2 * s3 - s1 * s2 * c3, c1 * s2 * c3 + s1 * c2 * s3, s1 * c2 * c3 - c1 * s2 * s3, c1 * c2 * c3 + s1 * s2 * s3);
    return q;
}

quaternion mulQQ(quaternion a, quaternion b) //умножение 2 кватернионов
{
    quaternion res = quatCoordinates(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z, a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y, a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x, a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w);
    return res;
}

quaternion mulVQ(quaternion q, vec v) //умножение вектора на кватернион
{
    quaternion res = quatCoordinates(-q.x * v.x - q.y * v.y - q.z * v.z, q.w * v.x + q.y * v.z - q.z * v.y, q.w * v.y - q.x * v.z + q.z * v.x, q.w * v.z + q.x * v.y - q.y * v.x);
    return res;
}


quaternion invertQuat(quaternion q)  //обратный кватернион
{
    quaternion p = quatCoordinates(0, -q.x, -q.y, -q.z);
    return p;
}

vec vecCoordinates(double x, double y, double z)
{
    vec t;
    t.x = x;
    t.y = y;
    t.z = z;
    return t;
}

vec transformVec(vec v, quaternion q)  //поворот вектора вокруг 3 осей (тангаж, рыскание, крен)
{
    quaternion res = mulQQ(mulVQ(q, v), invertQuat(q));
    vec s = vecCoordinates(res.x, res.y, res.z);
    double n = scalar(s);
    vec t = vecCoordinates(s.x / n, s.y / n, s.z / n);
    return t;
}

//вращение под действием маховиков
vec gravityForce(vec r, double m) //r - расстояние до центра Земли
{
    double R = scalar(r);
    const double mEarth = 5.9742 * pow(10, 24), //масса Земли
                 G = 6.67385 * pow(10, -11);
    vec g = vecCoordinates(G * mEarth * r.x / pow(R, 3), G * mEarth * r.y / pow(R, 3), G * mEarth * r.z / pow(R, 3));
    return g;
}

vec aerodynamicForce(double p, vec v, double S)
{
    double u = scalar(v);
    vec a = vecCoordinates(-p * u * v.x * S/ 2, -p * u * v.y * S/ 2, -p * u * v.z * S/ 2);
    return a;
}

vec angularVelocity(vec g, vec a, vec t, vec moment) //угловая скорость
{
    vec v = vecCoordinates((g.x - a.x - t.x)/moment.x, (g.y - a.y - t.y)/moment.y, (g.z - a.z - t.z)/moment.z);
    return v;
}

vec flywheelON(vec v, vec a)  //вращение с включенными маховиками
{
    vec f = vecCoordinates(v.x + a.x, v.y + a.y, v.z + a.z);
    return f;
}

vec speed(vec speedFirst, double time, vec position, double mLevel, double impulseS, double m, vec orientation, vec moment, vec speedRotation) //Í‡Í Á‡‰‡ÂÚÒˇ t ÔÓÍ‡ ÌÂ Â¯ËÎË!!!
{
    double H = scalar(position);
    double scSpeedFirst = scalar(speedFirst);
    double S = size*size;
    vec x = flywheelON(transformVec(orientation, createQuat(speedRotation)), angularVelocity(gravityForce(position, m), aerodynamicForce(airDens(H), speedFirst, S), tracForce(mLevel, impulseS, speedFirst), moment));
    double v1 = 1 - airDens(H) * scSpeedFirst / 2.0 * S * time / m; // ËÒÔÓÎ¸ÁÛÂÏ ÍÓ˝ÙÙËˆËÂÌÚ ‡˝Ó‰ËÌ‡ÏË˜ÂÒÍÓ„Ó ÒÓÔÓÚË‚ÎÂÌËˇ 1
    double v2 = scalar(tracForce(mLevel, impulseS, speedFirst)) * time / m;
    double mEarth = 5.9742 * pow(10, 24);
    double v3 = G * mEarth / pow(H, 3) * time;
    vec t1 = multi(speedFirst, v1);
    vec t2 = multi(x, v2);
    vec t3 = multi(position, v3);
    vec exit;
    exit.x = t1.x - t2.x + t3.x;
    return exit;
}

//ÔÓÎ¸ÁÓ‚‡ÚÂÎ¸ Á‡ÔÓÎÌˇÂÚ Ï‡ÒÒË‚ ËÁ 100000 ÌÛÎÂÈ Ò‚ÓËÏË ÁÌ‡˜ÂÌËˇÏË

vec ABC(vec position, vec speedFirst, double m, double mLevel[3], double impulse[3],vec orientation, vec moment, double size, vec speedRotation)  //ÏÓÊÌÓ ÎË Ú‡Í ÔÂÂ‰‡‚‡Ú¸ Ï‡ÒÒË‚?
{
    double S = size * size;
    double H = scalar(position);
    vec sp;
    double impulseS, level;
    int t = 0;
    vec orient = orientation;
    while (H > 9600)
    {
        if (t > 2)
        {
            level = 0;
            impulseS = 0;
        }
        else
        {
            level = mLevel[t];
            impulseS = impulse[t];
        }
        sp = speed(speedFirst, 1.0, position, level, impulseS, m, orient, moment, speedRotation);
        m = mass(level, m);
        position.x += sp.x;
        position.y += sp.y;
        position.z += sp.z;
        t++;
        H = scalar(position);  //Ì‡‰Ó ‚˚‰‡Ú¸ position ‚ Ù‡ÈÎ Ì‡ Í‡Ê‰ÓÏ ¯‡„Â!!!!!
        cout<<position.x<<' '<<position.y<<' '<<position.z<<endl;
        orient = flywheelON(transformVec(orient, createQuat(speedRotation)), angularVelocity(gravityForce(position, m), aerodynamicForce(airDens(H), speedFirst, S), tracForce(level, impulseS, speedFirst), moment));
    }
    return sp;
}

int main()
{
    vec position;
    position.x = 0;
    position.y = 0;
    position.z = 6388100;
    vec speedFirst;
    speedFirst.x = 8000;
    speedFirst.y = 0;
    speedFirst.z = 0;
    double arr[3] = {0, 0, 0};
    vec o;
    o.x = 1;
    o.y = 0;
    o.z = 0;
    vec oo;
    oo.x = 0;
    oo.y = 0;
    oo.z = 0;
    ABC(position, speedFirst, 50, arr, arr, o, oo, 2, o);
    return 0;
}
