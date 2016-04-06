#include "quaternion.cpp"

struct vec
{
    double x, y, z;
    
    double getScalar() //returns a scalar of a vector
    {
        double result = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        return result;
    }
    
    vec multiplyWithDouble(double number) //multiplication with double
    {
        vec result;
        result.x = x * number;
        result.y = y * number;
        result.z = z * number;
        return result;
    }
    
    vec rotate(quaternion rotationQuaternion) //rotates vector by quaternion
    {
        quaternion quaternion1 = multiplyWithQuaternion(rotationQuaternion);
        quaternion quaternion2 = rotationQuaternion.invert();
        quaternion quaternionResult = quaternion1.multiply(quaternion2);
        vec result = {quaternionResult.x, quaternionResult.y, quaternionResult.z};
        return result;
    }
    
    vec multiply(vec b) //multiplication of 2 vectors
    {
        vec result;
        result.x = y * b.z - z * b.y;
        result.y = z * b.x - x * b.z;
        result.z = x * b.y - y * b.x;
        return result;
    }
    
    quaternion createQuaternion() //creates a quaternion from vector
    {
        double cosZ = cos(z / 2),
               cosY = cos(y / 2),
               cosX = cos(x / 2),
               sinZ = sin(z / 2),
               sinY = sin(y / 2),
               sinX = sin(x / 2);
        quaternion result;
        result.w = cosZ * cosY * cosX - sinZ * sinY * sinX;
        result.x = sinZ * sinY * cosX + cosZ * cosY * sinX;
        result.y = cosZ * sinY * cosX - sinZ * cosY * sinX;
        result.z = sinZ * cosY * cosX + cosZ * sinY * sinX;
        result = result.normalize();
        return result;
    }
    
    quaternion multiplyWithQuaternion(quaternion quat) //multiplication with quaternion
    {
        quaternion result;
        result.w = -quat.x * x - quat.y * y - quat.z * z;
        result.x =  quat.w * x + quat.y * z - quat.z * y;
        result.y =  quat.w * y - quat.x * z + quat.z * x;
        result.z =  quat.w * z + quat.x * y - quat.y * x;
        result = result.normalize();
        return result;
    }

	bool operator == (vec b) {
		return x == b.x & y == b.y & z == b.z;
	}
};