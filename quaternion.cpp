#include <cmath>

struct quaternion
{
    double w, x, y, z;
    
    quaternion normalize()
    {
        double s = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
        if (s != 0)
        {
            quaternion p;
            p.w = w / s;
            p.x = x / s;
            p.y = y / s;
            p.z = z / s;
            return p;
        }
        quaternion res = {0, 0, 0, 0};
        return res;
    }
    
    quaternion multiply(quaternion b)
    {
        quaternion res;
        res.w = w * b.w - x * b.x - y * b.y - z * b.z;
        res.x = w * b.x + x * b.w + y * b.z - z * b.y;
        res.y = w * b.y - x * b.z + y * b.w + z * b.x;
        res.z = w * b.z + x * b.y - y * b.x + z * b.w;
        res = res.normalize();
        return res;
    }
    
    quaternion invert()
    {
        quaternion p = {w, -x, -y, -z}; //перед w не нужен минус
        return p;
    }
};