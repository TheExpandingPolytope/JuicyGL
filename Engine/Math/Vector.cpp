#include "Vector.h"

float vector2::magnitude()
{
	return sqrt((this->x)*(this->x) + (this->y)*(this->y));
}

float vector2::dot(vector2 operand)
{
	return (this->x * operand.x) + (this->y * operand.y);
}

float vector2::cross(vector2 operand)
{
	return (this->x * operand.y) - (this->y * operand.x);
}

vector2 vector2::operator*(vector2 vec)
{
	vector2 fvec;
	fvec.x = x * vec.x;
	fvec.y = y * vec.y;
	return fvec;
}

vector2 vector2::operator/(vector2 vec)
{
	vector2 fvec;
	fvec.x = x / vec.x;
	fvec.y = y / vec.y;
	return fvec;
}

vector2 vector2::operator+(vector2 vec)
{
	vector2 fvec;
	fvec.x = x + vec.x;
	fvec.y = y + vec.y;
	return fvec;
}

vector2 vector2::operator-(vector2 vec)
{
	vector2 fvec;
	fvec.x = x - vec.x;
	fvec.y = y - vec.y;
	return fvec;
}

vector2 vector2::operator=(vector2 vec)
{
	x = vec.x;
	y = vec.y;
	return vec;
}

void vector3::display()
{
	using namespace std;
	cout << "\nVECTOR4\n"
		<< this->x << ", " << this->y << ", " << this->z;
}

float vector3::magnitude()
{
	return sqrt((this->x)*(this->x) + (this->y)*(this->y) + (this->z)*(this->z));
}

float vector3::dot(vector3 operand)
{
	return (this->x * operand.x) + (this->y * operand.y) + (this->z * operand.z);
}

vector3 vector3::cross(vector3 operand)
{
	vector3 fvec;
	fvec.x = (this->y * operand.z) - (this->z * operand.y);
	fvec.y = -(this->x * operand.z) - (this->z * operand.x);
	fvec.z = (this->x * operand.y) - (this->y * operand.x);
	return fvec;
}

vector3 vector3::normalize()
{
	vector3 vec;
	float mag = this->magnitude();
	vec.x = (this->x) / mag;
	vec.y = (this->y) / mag;
	vec.z = (this->z) / mag;
	return vec;
}

std::vector<float> vector3::arr()
{
	std::vector<float> arr;
	arr.push_back(x);
	arr.push_back(y);
	arr.push_back(z);
	return arr;
}

vector3 vector3::operator*(vector3 vec)
{
	vector3 fvec;
	fvec.x = x * vec.x;
	fvec.y = y * vec.y;
	fvec.z = z * vec.z;
	return fvec;
}

vector3 vector3::operator/(vector3 vec)
{
	vector3 fvec;
	fvec.x = x / vec.x;
	fvec.y = y / vec.y;
	fvec.z = z / vec.z;
	return fvec;
}

vector3 vector3::operator+(vector3 vec)
{
	vector3 fvec;
	fvec.x = x + vec.x;
	fvec.y = y + vec.y;
	fvec.z = z + vec.z;
	return fvec;
}

vector3 vector3::operator-(vector3 vec)
{
	vector3 fvec;
	fvec.x = x - vec.x;
	fvec.y = y - vec.y;
	fvec.z = z - vec.z;
	return fvec;
}

vector3 vector3::operator=(vector3 vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return vec;
}

bool vector3::operator==(vector3 vec)
{
	return this->x==vec.x && this->y == vec.y && this->z == vec.z;
}

bool vector3::operator!=(vector3 v)
{
	return this->x !=v.x && this->y !=v.y && this->z != v.z;
}

bool vector3::operator >(vector3 v)
{
	return this->magnitude()>v.magnitude();
}

bool vector3::operator<(vector3 v)
{
	return this->magnitude()<v.magnitude();
}

vector3 vector3::operator*(float f)
{
	return vec3(x*f, y*f, z*f);
}

vector3 vector3::operator/(float f)
{
	return vec3(x/f, y/f, z/f);
}

vector3 vector3::operator+(float f)
{
	return vec3(x+f, y+f, z+f);
}

vector3 vector3::operator-(float f)
{
	return vec3(x-f, y-f, z-f);
}

vector3 vector3::operator=(float f)
{
	x = y = z = f;
	return vec3(f, f, f);
}

quaternion& vector3::operator*(quaternion &q)
{
	return q;
}

void vector4::display()
{
	using namespace std;
	cout << "\nVECTOR4\n"
		<< this->x << ", " << this->y << ", " << this->z << ", " << w;
}

float vector4::magnitude()
{
	return sqrt((this->x)*(this->x) + (this->y)*(this->y) + (this->z)*(this->z) + w*w);
}

float vector4::dot(vector4 operand)
{
	return (this->x * operand.x) + (this->y * operand.y) + (this->z * operand.z) + (w*operand.w);
}

vector4 vector4::cross(vector4 operand)
{
	vector4 fvec;
	fvec.x = (this->y * operand.z) - (this->z * operand.y);
	fvec.y = (this->z * operand.x) - (this->x * operand.z);
	fvec.z = (this->y * operand.y) - (this->y * operand.x);
	fvec.w = 1.0f;
	return fvec;
}

vector4 vector4::normalize()
{
	vector4 vec;
	float mag = this->magnitude();
	vec.x = (this->x) / mag;
	vec.y = (this->y) / mag;
	vec.z = (this->z) / mag;
	vec.w = (this->w) / mag;
	return vec;
}

vector4 vector4::operator*(vector4 vec)
{
	vector4 fvec;
	fvec.x = x * vec.x;
	fvec.y = y * vec.y;
	fvec.z = z * vec.z;
	fvec.w = w * vec.w;
	return fvec;
}

vector4 vector4::operator/(vector4 vec)
{
	vector4 fvec;
	fvec.x = x / vec.x;
	fvec.y = y / vec.y;
	fvec.z = z / vec.z;
	fvec.w = w / vec.w;
	return fvec;
}

vector4 vector4::operator+(vector4 vec)
{
	vector4 fvec;
	fvec.x = x + vec.x;
	fvec.y = y + vec.y;
	fvec.z = z + vec.z;
	fvec.w = w * vec.w;
	return fvec;
}

vector4 vector4::operator-(vector4 vec)
{
	vector4 fvec;
	fvec.x = x - vec.x;
	fvec.y = y - vec.y;
	fvec.z = z - vec.z;
	fvec.w = w * vec.w;
	return fvec;
}

vector4 vector4::operator=(vector4 vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
	return vec;
}

vector2 vec2(float x, float y)
{
	vector2 fvec;
	fvec.x = x;
	fvec.y = y;
	return fvec;
}

vector3 vec3(float x, float y, float z)
{
	vector3 fevec;
	fevec.x = x;
	fevec.y = y;
	fevec.z = z;
	return fevec;
}

vector4 vec4(float x, float y, float z, float w)
{
	vector4 fvec;
	fvec.x = x;
	fvec.z = z;
	fvec.y = y;
	fvec.w = w;
	return fvec;
}