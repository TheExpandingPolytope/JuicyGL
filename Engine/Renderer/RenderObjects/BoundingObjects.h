struct jAABB
{
	jObject object;
	AABB  *box;
	vector3 *color;

	jAABB();

	void setAABB(AABB &c);
	void setColor(vector3 &c);
private:
	jProgram material;
};

struct jSphere
{
	jObject object;
	Sphere *sphere;
	vector3 color;

	jSphere();

	void setSphere(Sphere& s);
	void setColor(vector3 &c);
};

struct jOBB
{

};

struct jDOP
{

};