#include <iostream>
#include <algorithm>
#include <cmath>

const double G = 6.67385 * pow(10, -11), //гравитационная постоянная
mEarth = 5.9742 * pow(10, 24), //масса Земли
rEarth = 6365, //радиус Земли
uEarth = 398600.44159; //гравитационный параметр Земли

using namespace std;

double size, //размер корабля
maxTorque, //момент вращения
maxFuel, //максимальный расход топлива
maxImpulse, //удельный имульс
fuelLevel, //уровень массового расхода топлива
limOver; //предельная перегрузка

struct vec //ориентация
{
double x, y, z;
};
vec position; //положение

struct m //массы корабля и топлива
{
double ship, fuel;
};

vec rSpeed; //скорость вращения


vec momentRotation; //момент вращения вокруг каждой оси

vec rageSim; //диапзон моделирования

struct airD//сопротивление воздуха
{
	double h, p;
};

double scalar (vec t)
{
    double res = sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2));
    return res;
}

double airDens(double H)
{
	airD air[55];
	H -= 6378100; //  в метрах
	air[0].h = 0;       air[0].p=1.225;
	air[3].h = 50;      air[3].p=1.219;
	air[6].h = 100;     air[6].p = 1.213;
	air[9].h = 200;     air[9].p = 1.202;
	air[12].h = 300;    air[12].p = 1.190;
	air[15].h = 500;    air[15].p = 1.167;
	air[18].h = 1000;   air[18].p = 1.112;
	air[21].h = 2000;   air[21].p = 1.007;
	air[24].h = 3000;   air[24].p = 0.909;
	air[27].h = 5000;   air[27].p = 0.736;
	air[30].h = 8000;   air[30].p = 0.526;
	air[33].h = 10000;  air[33].p = 0.414;
	air[36].h = 12000;  air[36].p = 0.312;
	air[39].h = 15000;  air[39].p = 0.195;
	air[42].h = 20000;  air[42].p = 0.089;
	air[45].h = 50000;  air[45].p = 0.001027;
	air[48].h = 100000; air[48].p = 0.000000555;
	air[51].h = 120000; air[51].p = 0.0000000244;
	for (int i = 0 ; i < 52; i += 3)
	{
		double s = (air[i+3].h - air[i].h) / 3.0;
		air[i+1].h = air[i].h + s;
		air[i+2].h = air[i+1].h + s;
		double t = (air[i+3].p - air[i].p) / 3.0;
		air[i+1].p = air[i].p + t;
		air[i+2].p = air[i+1].p + t;
	}
	int t = -1;
	double minH = 1000000000.0;
	for(int i = 0; i < 52; i++)
	{
		if(abs(air[i].h - H) < minH)
		{
			t = i;
			minH = abs(air[i].h - H);
		}
	}
	double P = air[t].p;
	if(t == -1)
        P = 0.0;
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
vec speed(vec speedFirst, double t, vec position, double mLevel, double impulseS )//как задается t пока не решили!!!
{

    vec v;
    double H = scalar (position);
    double scSpeedFirst = scalar(speedFirst);
    double S = size*size;
    double t1 = tracForce(mLevel, impulseS, speedFirst) / scSpeedFirst + airDens(H) * scSpeedFirst / 2.0 * S;
    t1 = 1.0 - t1 * t / mass();
    vec t2;
    double t3 = G * mEarth / pow(H, 3) * t;
    t2 = multi(position, t3);
    vec t4 = multi(speedFirst, t1);
    t2.x += t4.x;
    t2.y += t4.y;
    t2.z += t4.z;
    return t2;
}

/*
struct momentRotation { //момент вращения вокруг каждой оси
    double x, y, z;
};
struct rageSim { //диапазон моделирования
    double x, y, z;
};
*/

//вращение объекта
struct quat {
    double w, x, y, z;
};

vec normalvec(vec v){ //нормализация вектора
    double length = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
    v.x = v.x / length;
    v.y = v.y / length;
    v.z = v.z / length;
    return v;
}

quat createQuat(vec speed){ //создание кватерниона из набора скоростей
    quat q;
    double c1, c2, c3, s1, s2, s3;
    c1 = cos(speed.z / 2);
    c2 = cos(speed.y / 2);
    c3 = cos(speed.x / 2);
    s1 = sin(speed.z / 2);
    s2 = sin(speed.y / 2);
    s3 = sin(speed.x / 2);
    q.x = c1 * c2 * s3 - s1 * s2 * c3;
    q.y = c1 * s2 * c3 + s1 * c2 * s3;
    q.z = s1 * c2 * c3 - c1 * s2 * s3;
    q.w = c1 * c2 * c3 + s1 * s2 * s3;
    return q;
}

quat mulQQ(quat a, quat b){ //умножение 2 кватернионов
    quat res;
    res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    return res;
}

quat mulVQ(quat q, vec v){ //умножение вектора на кватернион
    quat res;
    res.w = -q.x * v.x - q.y * v.y - q.z * v.z;
    res.x = q.w * v.x + q.y * v.z - q.z * v.y;
    res.y = q.w * v.y - q.x * v.z + q.z * v.x;
    res.z = q.w * v.z + q.x * v.y - q.y * v.x;
    return res;
}

quat invertQuat (quat q){ //обратный кватернион
    q.x = -q.x;
    q.y = -q.y;
    q.z = -q.z;
    return q;
}

vec transformvec (vec v, quat q){ //поворот вектора вокруг 3 осей (тангаж, рыскание, крен)
    quat res = mulQQ(mulVQ(q, v), invertQuat(q));
    vec t;
    t.x = res.x;
    t.y = res.y;
    t.z = res.z;
    return t;
}

//вращение под действием маховиков

vec gravity(vec r, double m){ //r - расстояние до центра Земли
    vec g;
    double R = scalar(r);
    g.x = G * mEarth * r.x / pow(R, 3);
    g.y = G * mEarth * r.y / pow(R, 3);
    g.z = G * mEarth * r.z / pow(R, 3);
    return g;
}



vec aerodynamic(double p, vec v, double S){
    vec a;
    double u = scalar(v);
    a.x = -p * u * v.x * S/ 2;
    a.y = -p * u * v.y * S/ 2;
    a.z = -p * u * v.z * S/ 2;
    return a;
}

vec angularVelocity(vec g, vec a, vec t, vec moment){ //угловая скорость
    vec v;
    v.x = (g.x - a.x - t.x)/moment.x;
    v.y = (g.y - a.y - t.y)/moment.y;
    v.z = (g.z - a.z - t.z)/moment.z;
    return v;
}

vec flywheelON(vec v, vec a){ //вращение с включенными маховиками
    vec f;
    f.x = v.x + a.x;
    f.y = v.y + a.y;
    f.z = v.z + a.z;
    return f;
}
/*int Eccentricity(double speed, double x, double y, double z) {
    double e = pow(speed, 2)/2 - uEarth/sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    return e;
}
int MajorAxis(double u, double e) {
    double a = u / 2 * e;
    return a;
}
 */

int main()
{
	cout<<airDens(6388100.0);
	return 0;
}
