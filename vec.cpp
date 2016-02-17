#include "quaternion.cpp"

struct vec
{
    double x, y, z;
    double getScalar()
    {
        double res = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        return res;
    }
    
    vec multiplyWithDouble(double d)
    {
        vec res;
        res.x = x * d;
        res.y = y * d;
        res.z = z * d;
        return res;
    }
    
    vec rotate(quaternion q)
    {
        quaternion q1 = multiplyWithQuaternion(q);
        quaternion q2 = q.invert();
        vec res = {q1.multiply(q2).x, q1.multiply(q2).y, q1.multiply(q2).z};
        return res;
    }
    
    vec multiply(vec b)
    {
        vec res;
        res.x = y * b.z - z * b.y;
        res.y = z * b.x - x * b.z;
        res.z = x * b.y - y * b.x;
        return res;
    }

    quaternion createQuaternion()
    {
        double cosZ = cos(z / 2),
               cosY = cos(y / 2),
               cosX = cos(x / 2),
               sinZ = sin(z / 2),
               sinY = sin(y / 2),
               sinX = sin(x / 2);
        quaternion q;
        q.w = cosZ * cosY * cosX - sinZ * sinY * sinX;
        q.x = sinZ * sinY * cosX + cosZ * cosY * sinX;
        q.y = cosZ * sinY * cosX - sinZ * cosY * sinX;
        q.z = sinZ * cosY * cosX + cosZ * sinY * sinX;
        return q;
    }

    quaternion multiplyWithQuaternion(quaternion quat)
    {
        quaternion res;
        res.w = -quat.x * x - quat.y * y - quat.z * z;
        res.x =  quat.w * x + quat.y * z - quat.z * y;
        res.y =  quat.w * y - quat.x * z + quat.z * x;
        res.z =  quat.w * z + quat.x * y - quat.y * x;
        return res;
    }
};