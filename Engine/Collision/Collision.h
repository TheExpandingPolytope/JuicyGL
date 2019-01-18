struct Shape 
{
	virtual vector3 support(vector3 direction);
	virtual vector3 center();
};
 
struct Sphere: public Shape
{
	vector3 Center;
	float radius;
	
	vector3 support(vector3 direction);
	vector3 center();
};

struct Simplex
{
	void add(vector3 point);
	bool contains(vector3 point);

	vector3 directionToOrigin;
	vector3 getLast();
	std::vector<vector3> points;
};

struct Polytope3D
{

};

//test if two shapes have collided
bool gjk_test(Shape *a, Shape *b);

struct RigidBody;
//data structure that describes the collision between two RigidBodies
struct RigidBodyContact
{
	//rigid bodies of collision
	RigidBody *a; 
	RigidBody *b;
	vector3 p; // point of contact
	vector3 n; // normal of face
	vector3 ea, eb; //edges of contact
	jObject object;

	RigidBodyContact();
};

struct triangle
{
	vector3 p1, p2, p3;

	bool test_intersection(triangle operand);
	vector3 contact_point(triangle operand);
	vector3 dist_from(triangle operand);
	triangle operator +(vector3 v);
};

struct face
{
	vector3 p1, p2, p3, p1_p2, p2_p3, p3_p1;
};

struct polytope
{
	std::vector<face> faces;
	std::vector<vector3> points;

	void expand(vector3 point);
	vector3 center();
	polytope operator =(Simplex s);

	vector3 pointInside;
};

struct contact
{
	vector3 normal, point;
	float penetration;
};

//returns the penetration vector of a collision between to different shapes
contact epa_test(Simplex s, Shape *a, Shape *b);
