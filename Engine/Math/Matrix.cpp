#include "Matrix.h"
#include "Vector.h"
matrix3::matrix3()
{
	x0 = 1.0f;
	y0 = 0.0f;
	z0 = 0.0f;

	x1 = 0.0f;
	y1 = 1.0f;
	z1 = 0.0f;

	x2 = 0.0f;
	y2 = 0.0f;
	z2 = 1.0f;
}

void matrix3::display()
{
	using namespace std;
	cout << "\nMATRIX3\n"
		<< x0 << ", " << y0 << ", " << z0 << ",\n"
		<< x1 << ", " << y1 << ", " << z1 << ",\n"
		<< x2 << ", " << y2 << ", " << z2;
}

matrix3 matrix3::transpose()
{
	matrix3 m;
	m.x0 = x0; m.y0 = x1; m.z0 = x2;
	m.x1 = y0; m.y1 = y1; m.z1 = y2;
	m.x2 = z0; m.y2 = z1; m.z2 = z2;
	return m;
}

matrix3 matrix3::inverse()
{
	matrix3 m;
	float invDet;
	invDet = 1.0 / (x0*(y1*z2 - z1*y2) - y0*(x1*z2 - z1*x2) + z0*(x1*y2 - y1*x2));
	std::cout << "invDet " << invDet << "\n";
	return mat3(vec3(y1*z2-z1*y2, z0*y2-y0*z2, y0*z1-z0*y1)*invDet,
		        vec3(z1*x2-x1*z2, x0*z2-z0*x2, z0*x1-x0*z1)*invDet,
		        vec3(x1*y2-y1*x2, y0*x2-x0*y2, x0*y1-y0*x1)*invDet);
}

matrix3 matrix3::operator =(matrix3 mat)
{
	x0 = mat.x0;
	y0 = mat.y0;
	z0 = mat.z0;
	x1 = mat.x1;
	y1 = mat.y1;
	z1 = mat.z1;
	x2 = mat.x2;
	y2 = mat.y2;
	z2 = mat.z2;

	return mat;
}

matrix3 matrix3::operator *(matrix3 mat)
{
	matrix3 fmat;
	fmat.x0 = (x0*mat.x0) + (y0*mat.x1) + (z0 * mat.x2);
	fmat.x1 = (x1*mat.x0) + (y1*mat.x1) + (z1 * mat.x2);
	fmat.x2 = (x2*mat.x0) + (y2*mat.x1) + (z2 * mat.x2);

	fmat.y0 = (x0*mat.y0) + (y0*mat.y1) + (z0 * mat.y2);
	fmat.y1 = (x1*mat.y0) + (y1*mat.y1) + (z1 * mat.y2);
	fmat.y2 = (x2*mat.y0) + (y2*mat.y1) + (z2 * mat.y2);

	fmat.z0 = (x0*mat.z0) + (y0*mat.z1) + (z0 * mat.z2);
	fmat.z1 = (x1*mat.z0) + (y1*mat.z1) + (z1 * mat.z2);
	fmat.z2 = (x2*mat.z0) + (y2*mat.z1) + (z2 * mat.z2);
	return fmat;
}

vector3 matrix3::operator *(vector3 vec)
{
	vector3 fvec;
	fvec.x = (this->x0*vec.x) + (this->y0*vec.y) + (this->z0*vec.z);
	fvec.y = (this->x1*vec.x) + (this->y1*vec.y) + (this->z1*vec.z);
	fvec.z = (this->x2*vec.x) + (this->y2*vec.y) + (this->z2*vec.z);
	return fvec;
}

void matrix4::display()
{
	using namespace std;
	cout << "\nMATRIX4\n"
		<< this->x0 << ", " << this->y0 << ", " << this->z0 << ", " << this->w0 << ",\n"
		<< this->x1 << ", " << this->y1 << ", " << this->z1 << ", " << this->w1 << ",\n"
		<< this->x2 << ", " << this->y2 << ", " << this->z2 << ", " << this->w2 << ",\n"
		<< this->x3 << ", " << this->y3 << ", " << this->z3 << ", " << this->w3;
}
matrix4 matrix4::transpose()
{
	matrix4 m;
	m.x0 = x0; m.y0 = x1; m.z0 = x2; m.w0 = x3;
	m.x1 = y0; m.y1 = y1; m.z1 = y2; m.w1 = y3;
	m.x2 = z0; m.y2 = z1; m.z2 = z2; m.w2 = z3;
	m.x3 = w0; m.y3 = w1; m.z3 = w2; m.w3 = w3;
	return m;
}
//RETURN MATRIX AS A COLUMN MAJOR ARRAY
std::vector<float> matrix4::column_major_arr()
{
	std::vector<float> vec;

	vec.push_back(this->x0);
	vec.push_back(this->x1);
	vec.push_back(this->x2);
	vec.push_back(this->x3);

	vec.push_back(this->y0);
	vec.push_back(this->y1);
	vec.push_back(this->y2);
	vec.push_back(this->y3);

	vec.push_back(this->z0);
	vec.push_back(this->z1);
	vec.push_back(this->z2);
	vec.push_back(this->z3);

	vec.push_back(this->w0);
	vec.push_back(this->w1);
	vec.push_back(this->w2);
	vec.push_back(this->w3);

	return vec;
}
//RETURN INVERSE OF MATRIX
matrix4 matrix4::inverse()
{
	matrix4 fmat;

	fmat.x0 =y1  *z2 *w3 -
		y1  *z3 *w2 -
		z1  *y2  *w3 +
		z1  *y3  *w2 +
		w1 *y2  *z3 -
		w1 *y3  *z2;

	fmat.y0 = -y0  *z2 *w3 +
		y0  *z3 *w2 +
		z0  *y2  *w3 -
		z0  *y3  *w2 -
		w0 *y2  *z3 +
		w0 *y3  *z2;

	fmat.z0 =y0  *z1 *w3 -
		y0  *z3 *w1 -
		z0  *y1 *w3 +
		z0  *y3 *w1 +
		w0 *y1 *z3 -
		w0 *y3 *z1;

	fmat.w0 = -y0  *z1 *w2 +
		y0  *z2 *w1 +
		z0  *y1 *w2 -
		z0  *y2 *w1 -
		w0 *y1 *z2 +
		w0 *y2 *z1;

	fmat.x1 = -x1  *z2 *w3 +
		x1  *z3 *w2 +
		z1  *x2 *w3 -
		z1  *x3 *w2 -
		w1 *x2 *z3 +
		w1 *x3 *z2;

	fmat.y1 =x0  *z2 *w3 -
		x0  *z3 *w2 -
		z0  *x2 *w3 +
		z0  *x3 *w2 +
		w0 *x2 *z3 -
		w0 *x3 *z2;

	fmat.z1 = -x0  *z1 *w3 +
		x0  *z3 *w1 +
		z0  *x1 *w3 -
		z0  *x3 *w1 -
		w0 *x1 *z3 +
		w0 *x3 *z1;

	fmat.w1 =x0  *z1 *w2 -
		x0  *z2 *w1 -
		z0  *x1 *w2 +
		z0  *x2 *w1 +
		w0 *x1 *z2 -
		w0 *x2 *z1;

	fmat.x2 =x1  *y2 *w3 -
		x1  *y3 *w2 -
		y1  *x2 *w3 +
		y1  *x3 *w2 +
		w1 *x2 *y3 -
		w1 *x3 *y2;

	fmat.y2 = -x0  *y2 *w3 +
		x0  *y3 *w2 +
		y0  *x2 *w3 -
		y0  *x3 *w2 -
		w0 *x2 *y3 +
		w0 *x3 *y2;

	fmat.z2 =x0  *y1 *w3 -
		x0  *y3 *w1 -
		y0  *x1 *w3 +
		y0  *x3 *w1 +
		w0 *x1 *y3 -
		w0 *x3 *y1;

	fmat.w2 = -x0  *y1 *w2 +
		x0  *y2 *w1 +
		y0  *x1 *w2 -
		y0  *x2 *w1 -
		w0 *x1 *y2 +
		w0 *x2 *y1;

	fmat.x3 = -x1 *y2 *z3 +
		x1 *y3 *z2 +
		y1 *x2 *z3 -
		y1 *x3 *z2 -
		z1 *x2 *y3 +
		z1 *x3 *y2;

	fmat.y3 =x0 *y2 *z3 -
		x0 *y3 *z2 -
		y0 *x2 *z3 +
		y0 *x3 *z2 +
		z0 *x2 *y3 -
		z0 *x3 *y2;

	fmat.z3 = -x0 *y1 *z3 +
		x0 *y3 *z1 +
		y0 *x1 *z3 -
		y0 *x3 *z1 -
		z0 *x1 *y3 +
		z0 *x3 *y1;

	fmat.w3 =x0 *y1 *z2 -
		x0 *y2 *z1 -
		y0 *x1 *z2 +
		y0 *x2 *z1 +
		z0 *x1 *y2 -
		z0 *x2 *y1;

	float det =x0 * fmat.x0 +x1 * fmat.y0 +x2 * fmat.z0 +x3 * fmat.w0;

	if (det == 0)
		return *this;

	det = 1.0 / det;

	fmat.x0 = fmat.x0 * det; fmat.x1 = fmat.x1 * det; fmat.x2 = fmat.x2 * det; fmat.x3 = fmat.x3 * det;
	fmat.y0 = fmat.y0 * det; fmat.y1 = fmat.y1 * det; fmat.y2 = fmat.y2 * det; fmat.y3 = fmat.y3 * det;
	fmat.z0 = fmat.z0 * det; fmat.z1 = fmat.z1 * det; fmat.z2 = fmat.z2 * det; fmat.z3 = fmat.z3 * det;
	fmat.w0 = fmat.w0 * det; fmat.w1 = fmat.w1 * det; fmat.w2 = fmat.w2 * det; fmat.w3 = fmat.w3 * det;
	return fmat;
}
//matrix4 = matrix4
matrix4 matrix4::operator = (matrix4 mat)
{
	x0 = mat.x0;
	y0 = mat.y0;
	z0 = mat.z0;
	w0 = mat.w0;

	x1 = mat.x1;
	y1 = mat.y1;
	z1 = mat.z1;
	w1 = mat.w1;

	x2 = mat.x2;
	y2 = mat.y2;
	z2 = mat.z2;
	w2 = mat.w2;

	x3 = mat.x3;
	y3 = mat.y3;
	z3 = mat.z3;
	w3 = mat.w3;

	return mat;
}
//matrix4 + matrix4
matrix4 matrix4::operator + (matrix4 mat)
{
	matrix4 fmat;
	fmat.x0 = x0 + mat.x0; fmat.x1 = x1 + mat.x1; fmat.x2 = x2 + mat.x2; fmat.x3 = x3 + mat.x3;
	fmat.y0 = y0 + mat.y0; fmat.y1 = y1 + mat.y1; fmat.y2 = y2 + mat.y2; fmat.y3 = y3 + mat.y3;
	fmat.z0 = z0 + mat.z0; fmat.z1 = z1 + mat.z1; fmat.z2 = z2 + mat.z2; fmat.z3 = z3 + mat.z3;
	fmat.w0 = w0 + mat.w0; fmat.w1 = w1 + mat.w1; fmat.w2 = w2 + mat.w2; fmat.w3 = w3 + mat.w3;

	return fmat;
}
//matrix4 - matrix4
matrix4 matrix4::operator - (matrix4 mat)
{
	matrix4 fmat;
	fmat.x0 = x0 - mat.x0; fmat.x1 = x1 - mat.x1; fmat.x2 = x2 - mat.x2; fmat.x3 = x3 - mat.x3;
	fmat.y0 = y0 - mat.y0; fmat.y1 = y1 - mat.y1; fmat.y2 = y2 - mat.y2; fmat.y3 = y3 - mat.y3;
	fmat.z0 = z0 - mat.z0; fmat.z1 = z1 - mat.z1; fmat.z2 = z2 - mat.z2; fmat.z3 = z3 - mat.z3;
	fmat.w0 = w0 - mat.w0; fmat.w1 = w1 - mat.w1; fmat.w2 = w2 - mat.w2; fmat.w3 = w3 - mat.w3;

	return fmat;
}
//matrix4 * matrix4
matrix4 matrix4::operator * (matrix4 mat)
{
	matrix4 fmat;
	fmat.x0 = (x0*mat.x0) + (y0*mat.x1) + (z0 * mat.x2) + (w0 * mat.x3);
	fmat.x1 = (x1*mat.x0) + (y1*mat.x1) + (z1 * mat.x2) + (w1 * mat.x3);
	fmat.x2 = (x2*mat.x0) + (y2*mat.x1) + (z2 * mat.x2) + (w2 * mat.x3);
	fmat.x3 = (x3*mat.x0) + (y3*mat.x1) + (z3 * mat.x2) + (w3 * mat.x3);

	fmat.y0 = (x0*mat.y0) + (y0*mat.y1) + (z0 * mat.y2) + (w0 * mat.y3);
	fmat.y1 = (x1*mat.y0) + (y1*mat.y1) + (z1 * mat.y2) + (w1 * mat.y3);
	fmat.y2 = (x2*mat.y0) + (y2*mat.y1) + (z2 * mat.y2) + (w2 * mat.y3);
	fmat.y3 = (x3*mat.y0) + (y3*mat.y1) + (z3 * mat.y2) + (w3 * mat.y3);

	fmat.z0 = (x0*mat.z0) + (y0*mat.z1) + (z0 * mat.z2) + (w0 * mat.z3);
	fmat.z1 = (x1*mat.z0) + (y1*mat.z1) + (z1 * mat.z2) + (w1 * mat.z3);
	fmat.z2 = (x2*mat.z0) + (y2*mat.z1) + (z2 * mat.z2) + (w2 * mat.z3);
	fmat.z3 = (x3*mat.z0) + (y3*mat.z1) + (z3 * mat.z2) + (w3 * mat.z3);

	fmat.w0 = (x0*mat.w0) + (y0*mat.w1) + (z0 * mat.w2) + (w0 * mat.w3);
	fmat.w1 = (x1*mat.w0) + (y1*mat.w1) + (z1 * mat.w2) + (w1 * mat.w3);
	fmat.w2 = (x2*mat.w0) + (y2*mat.w1) + (z2 * mat.w2) + (w2 * mat.w3);
	fmat.w3 = (x3*mat.w0) + (y3*mat.w1) + (z3 * mat.w2) + (w3 * mat.w3);
	return fmat;
}
//matrix4 * vector4
vector4 matrix4::operator * (vector4 vec)
{
	vector4 fvec;
	fvec.x = (this->x0*vec.x) + (this->y0*vec.y) + (this->z0*vec.z) + (this->w0*vec.w);
	fvec.y = (this->x1*vec.x) + (this->y1*vec.y) + (this->z1*vec.z) + (this->w1*vec.w);
	fvec.z = (this->x2*vec.x) + (this->y2*vec.y) + (this->z2*vec.z) + (this->w2*vec.w);
	fvec.w = (this->x3*vec.x) + (this->y3*vec.y) + (this->z3*vec.z) + (this->w3*vec.w);
	return fvec;
}
triangle& matrix4::operator*(triangle& t)
{
	vector4 p1, p2, p3;
	p1 = *this*vec4(t.p1.x, t.p1.y, t.p1.z, 1.0f);
	p2 = *this*vec4(t.p2.x, t.p2.y, t.p2.z, 1.0f);
	p3 = *this*vec4(t.p3.x, t.p3.y, t.p3.z, 1.0f);
	triangle tri;
	tri.p1 = vec3(p1.x, p1.y, p1.z);
	tri.p2 = vec3(p2.x, p2.y, p2.z);
	tri.p3 = vec3(p3.x, p3.y, p3.z);
	return tri;
}
mesh& matrix4::operator*(mesh& m)
{
	mesh m1;
	for (int i = 0; i < m.triangles.size(); i++)
	{
		triangle t = *this*m.triangles[i];
		m1.triangles.push_back(t);
	}
	return m1;
}
//return matrix2
matrix2 mat2(vector2 vec0, vector2 vec1)
{
	matrix2 fmat;
	fmat.x0 = vec0.x;
	fmat.y0 = vec0.y;

	fmat.x1 = vec1.x;
	fmat.y1 = vec1.y;

	return fmat;
}

//return matrix3
matrix3 mat3(vector3 vec0, vector3 vec1, vector3 vec2)
{
	matrix3 fmat;
	fmat.x0 = vec0.x;
	fmat.y0 = vec0.y;
	fmat.z0 = vec0.z;

	fmat.x1 = vec1.x;
	fmat.y1 = vec1.y;
	fmat.z1 = vec1.z;

	fmat.x2 = vec2.x;
	fmat.y2 = vec2.y;
	fmat.z2 = vec2.z;

	return fmat;
}

//return matrix4
matrix4 mat4(vector4 vec0, vector4 vec1, vector4 vec2, vector4 vec3)
{
	matrix4 fmat;

	fmat.x0 = vec0.x;
	fmat.y0 = vec0.y;
	fmat.z0 = vec0.z;
	fmat.w0 = vec0.w;

	fmat.x1 = vec1.x;
	fmat.y1 = vec1.y;
	fmat.z1 = vec1.z;
	fmat.w1 = vec1.w;

	fmat.x2 = vec2.x;
	fmat.y2 = vec2.y;
	fmat.z2 = vec2.z;
	fmat.w2 = vec2.w;

	fmat.x3 = vec3.x;
	fmat.y3 = vec3.y;
	fmat.z3 = vec3.z;
	fmat.w3 = vec3.w;

	return fmat;
}

//return the star of a vector3
matrix3 star(vector3 a)
{
	return mat3(vec3(0, -a.z, a.y),
		vec3(a.z, 0, -a.x),
		vec3(-a.y, a.x, 0));
}

//RETURN TRANSLATION MATRIX
matrix4 translate(float x, float y, float z)
{
	return mat4(vec4(1, 0, 0, x), vec4(0, 1, 0, y), vec4(0, 0, 1, z), vec4(0, 0, 0, 1));
}
