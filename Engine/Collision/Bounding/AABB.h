struct AABB
{
	vector3 min;
	vector3 max;

	AABB();
	AABB(vector3 vec0, vector3 vec1);
	AABB operator =(AABB operand);

	bool test_intersection(AABB operand);
	bool test_moving_intersection(AABB operand, float& time_first_contact, float& time_last_contact);
	void translate(float x, float y, float z);
	void translate();
	void update(); //update the AABB based on the content of the matrix binded to the AABB
	void update(vector3 min, vector3 max);
	void size_to_mesh();
	void setModel(matrix4& mat);
	void setMeshData(std::vector<float>& data);
	void setVelocity(vector3 &vec);
private:
	matrix4 *model;
	std::vector<float> *mesh_data;
	vector3 *velocity;

	float Max(float op1, float op2);
	float Min(float op1, float op2);
};