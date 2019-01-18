struct vector2
{
	float x;
	float y;
	const float length = 2;

	float magnitude();
	float dot(vector2 operand);
	float cross(vector2 operand);

	vector2 normalize();
	vector2 operator *(vector2 vec);
	vector2 operator /(vector2 vec);
	vector2 operator +(vector2 vec);
	vector2 operator -(vector2 vec);
	vector2 operator =(vector2 vec);
};


struct quaternion;
struct vector3
{
	float x;
	float y;
	float z;
	const float length = 3;

	void display();
	float magnitude();
	float dot(vector3 operand);

	vector3 cross(vector3 operand);
	vector3 normalize();
	vector3 operator *(vector3 vec);
	vector3 operator /(vector3 vec);
	vector3 operator +(vector3 vec);
	vector3 operator -(vector3 vec);
	vector3 operator =(vector3 vec);
	bool operator ==(vector3 vec);
	bool operator != (vector3 v);
	bool operator >(vector3 v);
	bool operator < (vector3 v);
	vector3 operator *(float f);
	vector3 operator /(float f);
	vector3 operator +(float f);
	vector3 operator -(float f);
	vector3 operator =(float f);
	quaternion &operator *(quaternion &q);
	std::vector<float> arr();
};

struct vector4
{
	float x, y, z, w;
	int const length = 4;

	void display();
	float magnitude();
	float dot(vector4 operand);

	vector4 cross(vector4 operand);
	vector4 normalize();
	vector4 operator *(vector4 vec);
	vector4 operator /(vector4 vec);
	vector4 operator +(vector4 vec);
	vector4 operator -(vector4 vec);
	vector4 operator =(vector4 vec);
};

vector2 vec2(float x, float y);
vector3 vec3(float x, float y, float z);
vector4 vec4(float x, float y, float z, float w);
