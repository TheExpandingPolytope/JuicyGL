//struct for mesh data

struct mesh
{
	std::vector<vector3> points; //array of points that this mesh has
	
	std::vector<triangle> triangles; // array of triangles
	jObject object; //object to be rendered
	std::vector<float> mesh_arr(); //updates and then returns the value of
	bool test_intersection(mesh operand);
	RigidBodyContact contact(mesh operand);
	vector3 dist_from(mesh operand);
	int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
	void loadObj(std::string filename); //set mesh data to object file

	mesh operator +(vector3 v);

private:
	std::vector<float> mesh_ar;
};