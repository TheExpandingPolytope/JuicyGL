#include "Quaternion.h"

//quaternion struct constructor
quaternion::quaternion()
{
	r = i = j = k = 0;
	r = 1;
}

//returns quaternion as matrix
quaternion quaternion::normalize()
{
	quaternion q; float mag;
	mag = sqrt((i*i) + (j*j) + (k*k) + (r*r));		
	q.i = i / mag;
	q.j = j / mag;
	q.k = k / mag;
	q.r = r / mag;
	return q;
}

//returns quaternion as 3x3 matrix
matrix3 quaternion::matrix()
{
	return mat3(vec3(1-(2*j*j)-(2*k*k), (2*i*j)+(2*k*r), (2*i*k)-(2*j*r)),
		        vec3((2*i*j)-(2*k*r), 1-(2*i*i)-(2*k*k), (2*j*k)-(2*i*r)),
		        vec3((2*i*k)+(2*j*r), (2*j*k)-(2*i*r), 1-(2*i*i)-(2*j*j)));
}

// quaternion = quaternion
quaternion quaternion::operator =(quaternion q)
{
	r = q.r;
	i = q.i;
	j = q.j;
	k = q.k;
	return q;
}

quaternion quaternion::operator+(quaternion q)
{
	quaternion qq; qq.i = i + q.i;  qq.j = j + q.j;  qq.k = k + q.k;  qq.r = r + q.r;

	return qq;
}

quaternion quaternion::operator-(quaternion q)
{
	quaternion qq; qq.i = i - q.i;  qq.j = j - q.j;  qq.k = k - q.k;  qq.r = r - q.r;

	return qq;
}

quaternion quaternion::operator*(quaternion q)
{
	quaternion qq;
	qq.r = (r*q.r) - (i*q.i) - (j*q.j) - (k*q.k);
	qq.i = (r*q.i) + (i*q.r) + (j*q.k) - (k*q.j);
	qq.j = (r*q.j) - (i*q.k) + (j*q.r) + (k*q.i);
	qq.k = (r*q.k) + (i*q.j) - (j*q.i) + (k*q.r);
	return qq;
}


quaternion quaternion::operator*(float f)
{
	quaternion qq; qq.i = i *f;  qq.j = j *f;  qq.k = k *f;  qq.r = r*f;

	return qq;
}

void quaternion::display()
{
	std::cout << "\nQUATERNION\n" << i << " "<< j << " "<< k << " "<< r;	
}

quaternion quat(float i, float j, float k, float r)
{
	quaternion q;
	q.i = i;
	q.j = j;
	q.k = k;
	q.r = r;
	return q;
}