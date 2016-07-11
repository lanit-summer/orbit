#pragma once
#include <cmath>

struct quaternion
{
    double w, x, y, z;
    
    quaternion normalize() //makes a unit quaternion (quaternion of norm one)
    {
        double norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
        if (norm != 0)
        {
            quaternion unitQuaternion;
            unitQuaternion.w = w / norm;
            unitQuaternion.x = x / norm;
            unitQuaternion.y = y / norm;
            unitQuaternion.z = z / norm;
            return unitQuaternion;
        }
        quaternion result = {0, 0, 0, 0};
        return result;
    }
    
    quaternion multiply(quaternion multiplier) //multiplication of 2 quaternions
    {
        quaternion result;
        result.w = w * multiplier.w - x * multiplier.x - y * multiplier.y - z * multiplier.z;
        result.x = w * multiplier.x + x * multiplier.w + y * multiplier.z - z * multiplier.y;
        result.y = w * multiplier.y - x * multiplier.z + y * multiplier.w + z * multiplier.x;
        result.z = w * multiplier.z + x * multiplier.y - y * multiplier.x + z * multiplier.w;
        return result;
    }
    
    quaternion invert() //makes an inverse quaternion
    {
        quaternion inverseQuaternion = {w, -x, -y, -z}; //no minus before w - it's OK
        return inverseQuaternion;
    }
};
