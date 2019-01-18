struct matrix2
{
	float x0, y0,
		x1, y1;
};

struct matrix3
{
	float x0, y0, z0,
		x1, y1, z1,
		x2, y2, z2;

	matrix3();
	void display();

	matrix3 transpose();
	matrix3 inverse();
	matrix3 operator =(matrix3 mat);
	matrix3 operator *(matrix3 mat);
	vector3 operator *(vector3 vec);
};

struct triangle;
struct mesh;
struct matrix4
{
	float x0, y0, z0, w0,
		x1, y1, z1, w1,
		x2, y2, z2, w2,
		x3, y3, z3, w3;

	void display();
	matrix4 transpose();
	std::vector<float> column_major_arr();
	matrix4 inverse();
	matrix4 operator =(matrix4 mat);
	matrix4 operator +(matrix4 mat);
	matrix4 operator -(matrix4 mat);
	matrix4 operator *(matrix4 mat);
	vector4 operator *(vector4 vec);
	triangle& operator *(triangle& t);
	mesh& operator *(mesh& m);
};

matrix2 mat2(vector2 vec0, vector2 vec1);
matrix3 mat3(vector3 vec0, vector3 vec1, vector3 vec2);
matrix3 star(vector3 a);
matrix4 mat4(vector4 vec0, vector4 vec1, vector4 vec2, vector4 vec3);
matrix4 translate(float x, float y, float z);
