//AABB constructors
AABB::AABB() : min(vec3(0,0,0)), max(vec3(0,0,0))
{}
AABB::AABB(vector3 vec0, vector3 vec1) : min(vec0), max(vec1)
{}

AABB AABB::operator =(AABB operand)
{
	min = operand.min;
	max = operand.max;
	return operand;
}

bool AABB::test_intersection(AABB operand)
{
	if (this->max.x < operand.min.x || this->min.x > operand.max.x) return false;
	if (this->max.y < operand.min.y || this->min.y > operand.max.y) return false;
	if (this->max.z < operand.min.z || this->min.z > operand.max.z) return false;
	return true;
}

bool AABB::test_moving_intersection(AABB operand, float &time_first_contact, float &time_last_contact)
{
	if (this->test_intersection(operand))
		return true;

	time_first_contact = 0.0f;
	time_last_contact = 1.0f;

	vector3 v = *velocity - *operand.velocity;
	if (v.x < 0.0f)
	{
		if (max.x < operand.min.x) return false;
		if (min.x > operand.max.x) time_first_contact = Max((operand.max.x - min.x) / v.x, time_first_contact);
	}
	else
		if (v.x > 0.0f)
		{
			if (min.x > operand.max.x) return false;
			if (max.x < operand.min.x) time_first_contact = Max((operand.min.x - max.x) / v.x, time_first_contact);
		}
		else
		{
			//if here...it means that velocity in x direction is zero
			//therefore, the objects cannot collide, unless the x values of each AABB intersect
			if (max.x < operand.min.x || min.x > operand.max.x) return false;
		}


	if (v.y < 0.0f)
	{
		if (max.y < operand.min.y) return false;
		if (min.y > operand.max.y) time_first_contact = Max((operand.max.y - min.y) / v.y, time_first_contact);
	}
	else
		if (v.y > 0.0f)
		{
			if (min.y > operand.max.y) return false;
			if (max.y < operand.min.y) time_first_contact = Max((operand.min.y - max.y) / v.y, time_first_contact);
		}
		else
		{
			//if here...it means that velocity in y direction is zero
			//therefore, the objects cannot collide, unless the y values of each AABB intersect
			if (max.y < operand.min.y || min.y > operand.max.y) return false;
		}


	if (v.z < 0.0f)
	{
		if (max.z < operand.min.z) return false;
		if (min.z > operand.max.z) time_first_contact = Max((operand.max.z - min.z) / v.z, time_first_contact);
	}
	else
		if (v.z > 0.0f)
		{
			if (min.z > operand.max.z) return false;
			if (max.z < operand.min.z) time_first_contact = Max((operand.min.z - max.z) / v.z, time_first_contact);
		}
		else
		{
			//if here...it means that velocity in z direction is zero
			//therefore, the objects cannot collide, unless the z values of each AABB intersect
			if (max.z < operand.min.z || min.z > operand.max.z) return false;
		}

	return true;
}

void AABB::translate(float x, float y, float z)
{
	min = min + vec3(x, y, z);
	max = max + vec3(x, y, z);
}

void AABB::translate()
{
	min = min + *velocity;
	max = max + *velocity;
}

void AABB::update()
{

}

void AABB::update(vector3 min, vector3 max)
{
	this->min = min;
	this->max = max;
}

void AABB::size_to_mesh()
{
	vector3 direction;
	vector3 point;
	vector3 max_pointx, max_pointy, max_pointz;
	vector3 min_pointx, min_pointy, min_pointz;
	float min = FLT_MAX;
	float max = -FLT_MAX;

	float* m = mesh_data->data();

	direction = vec3(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < mesh_data->size(); i += 3)
	{
		vector4 v = *model*vec4(m[i + 0], m[i + 1], m[i + 2], 1.0);
		point = vec3(v.x, v.y, v.z);
		float proj = point.dot(direction);

		if (proj < min)
		{
			min = proj;
			min_pointx = point;
		}

		if (proj > max)
		{
			max = proj;
			max_pointx = point;
		}
	}

	min = FLT_MAX;
	max = -FLT_MAX;

	direction = vec3(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < mesh_data->size(); i += 3)
	{
		vector4 v = *model*vec4(m[i + 0], m[i + 1], m[i + 2], 1.0);
		point = vec3(v.x, v.y, v.z);
		float proj = point.dot(direction);

		if (proj < min)
		{
			min = proj;
			min_pointy = point;
		}

		if (proj > max)
		{
			max = proj;
			max_pointy = point;
		}
	}

	min = FLT_MAX;
	max = -FLT_MAX;

	direction = vec3(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < mesh_data->size(); i += 3)
	{
		vector4 v = *model*vec4(m[i + 0], m[i + 1], m[i + 2], 1.0);
		point = vec3(v.x, v.y, v.z);
		float proj = point.dot(direction);

		if (proj < min)
		{
			min = proj;
			min_pointz = point;
		}

		if (proj > max)
		{
			max = proj;
			max_pointz = point;
		}
	}

	update(vec3(min_pointx.x, min_pointy.y, min_pointz.z), vec3(max_pointx.x, max_pointy.y, max_pointz.z));
}

void AABB::setModel(matrix4& mat)
{
	model = &mat;
}

void AABB::setMeshData(std::vector<float>& data)
{
	mesh_data = &data;
}

void AABB::setVelocity(vector3 &vec)
{
	velocity = &vec;
}

float AABB::Max(float op1, float op2)
{
	if (op1 > op2)
		return op1;
	else
		return op2;
}

float AABB::Min(float op1, float op2)
{
	if (op1 > op2)
		return op2;
	else
		return op1;
}