#include "Matrix.h"

struct quaternion
{
	float r, i, j, k;

	quaternion();
	quaternion normalize();
	matrix3 matrix();
	quaternion operator =(quaternion q);
	quaternion operator +(quaternion q);
	quaternion operator -(quaternion q);
	quaternion operator *(quaternion q);
	quaternion operator *(float f);
	void display();

};

quaternion quat(float i, float j, float k, float r);
