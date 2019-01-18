jCamera::jCamera()
{
	eye = vec3(0.0, 0.0, 1.0);
	target = vec3(0.0, 0.0, 0.0);
	upDir = vec3(0.0, 1.0, 0.0);
}

void jCamera::moveX(float speed)
{
	eye.x += speed;
	target.x += speed;
}

void jCamera::moveY(float speed)
{
	eye.y += speed;
	target.y += speed;
}

void jCamera::moveZ(float speed)
{
	eye.z += speed;
	target.z += speed;
}

std::vector<GLfloat>* jCamera::View()
{
	vector3 forward, left, up;

	forward = eye - target;
	forward = forward.normalize();
	left = upDir.cross(forward);
	left = left.normalize();
	up = forward.cross(left);

	view.clear();

	view.push_back(1);
	view.push_back(0);
	view.push_back(0);
	view.push_back(0);

	view.push_back(0);
	view.push_back(1);
	view.push_back(0);
	view.push_back(0);

	view.push_back(0);
	view.push_back(0);
	view.push_back(1);
	view.push_back(0);

	view.push_back(0);
	view.push_back(0);
	view.push_back(0);
	view.push_back(1);

	view[0] = left.x;
	view[4] = left.y;
	view[8] = left.z;
	view[1] = up.x;
	view[5] = up.y;
	view[9] = up.z;
	view[2] = forward.x;
	view[6] = forward.y;
	view[10] = forward.z;

	// set translation part
	view[12] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
	view[13] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
	view[14] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;
	return &view;
}

std::vector<GLfloat>* jCamera::Perspective(float fov, float aspect, float zNear, float zFar)
{

		float f = tan(3.14159 * .5 - .5*fov);
		float rangInv = 1.0 / (zNear - zFar);
		perspective.clear();

		perspective.push_back(f / aspect);
		perspective.push_back(0);
		perspective.push_back(0);
		perspective.push_back(0);

		perspective.push_back(0);
		perspective.push_back(f);
		perspective.push_back(0);
		perspective.push_back(0);

		perspective.push_back(0);
		perspective.push_back(0);
		perspective.push_back((zNear + zFar)*rangInv);
		perspective.push_back(-1);

		perspective.push_back(0);
		perspective.push_back(0);
		perspective.push_back((zNear*zFar*rangInv * 2));
		perspective.push_back(0);

		return &perspective;
}