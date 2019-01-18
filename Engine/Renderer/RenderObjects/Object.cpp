jObject::jObject()
{
	name = "default";
	jBuffer buf;
	data.push_back(buf);
	jShader vert;
	vert.type = GL_VERTEX_SHADER;
	vert.load("vertex_shader.txt");
	jShader frag;
	frag.type = GL_FRAGMENT_SHADER;
	frag.load("fragment_shader.txt");
	material.shaders.push_back(vert);
	material.shaders.push_back(frag);
	material.compile();
	model = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
}



jScene::jScene()
{
	glGenVertexArrays(1, &VAO);
}

void jScene::setCamera(jCamera &cam)
{
	camera = &cam;
}

void jScene::render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 0.8f, 0.7f, 0.51f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAO);

	for (int j = 0; j < objects.size(); j++)
	{
		jObject o = *objects[j];
		glUseProgram(objects[j]->material.program);
		setPerspective(2.14, (float)height / (float)width, .001, 100);
		setView();
		perspective_uniform_name = "perspective";
		view_uniform_name = "view";

		glUniformMatrix4fv(glGetUniformLocation(this->objects[j]->material.program, perspective_uniform_name), 1, GL_FALSE, this->perspective);
		glUniformMatrix4fv(glGetUniformLocation(this->objects[j]->material.program, view_uniform_name), 1, GL_FALSE, this->view.data());
		//load uniform matrix4 to shader
		for (int i = 0; i < objects[j]->matrices4x4.size(); i++) objects[j]->matrices4x4[i].linkTo(objects[j]->material);
		//load uniform vector3 to shader
		for (int i = 0; i < objects[j]->vectors3.size(); i++) objects[j]->vectors3[i].linkTo(objects[j]->material);
		//load uniform floats to shader
		for (int i = 0; i < objects[j]->floats.size(); i++) objects[j]->floats[i].linkTo(objects[j]->material);
		//load vertex attributes to shader
		for (int i = 0; i < objects[j]->data.size(); i++) objects[j]->data[i].linkTo(objects[j]->material);

		glDrawArrays(GL_TRIANGLES, 0, objects[j]->data[0].attribute_number);
	}
	glBindVertexArray(0);
}

void jScene::addObject(jObject &object)
{
	objects.push_back(&object);
}

void jScene::setView()
{

	vector3 forward, left, up;

	forward = camera->eye - camera->target;
	forward = forward.normalize();
	left = camera->upDir.cross(forward);
	left = left.normalize();
	up = forward.cross(left);

	this->view.clear();

	this->view.push_back(1);
	this->view.push_back(0);
	this->view.push_back(0);
	this->view.push_back(0);

	this->view.push_back(0);
	this->view.push_back(1);
	this->view.push_back(0);
	this->view.push_back(0);

	this->view.push_back(0);
	this->view.push_back(0);
	this->view.push_back(1);
	this->view.push_back(0);

	this->view.push_back(0);
	this->view.push_back(0);
	this->view.push_back(0);
	this->view.push_back(1);

	this->view[0] = left.x;
	this->view[4] = left.y;
	this->view[8] = left.z;
	this->view[1] = up.x;
	this->view[5] = up.y;
	this->view[9] = up.z;
	this->view[2] = forward.x;
	this->view[6] = forward.y;
	this->view[10] = forward.z;

	// set translation part
	this->view[12] = -left.x * camera->eye.x - left.y * this->camera->eye.y - left.z * this->camera->eye.z;
	this->view[13] = -up.x * this->camera->eye.x - up.y * this->camera->eye.y - up.z * this->camera->eye.z;
	this->view[14] = -forward.x * this->camera->eye.x - forward.y * this->camera->eye.y - forward.z * this->camera->eye.z;
}

void jScene::setPerspective(float fov, float aspect, float zNear, float zFar)
{
	float f = tan(3.14159 * .5 - .5*fov);
	float rangInv = 1.0 / (zNear - zFar);

	this->perspective[0] = f / aspect;
	this->perspective[1] = 0;
	this->perspective[2] = 0;
	this->perspective[3] = 0;

	this->perspective[4] = 0;
	this->perspective[5] = f;
	this->perspective[6] = 0;
	this->perspective[7] = 0;

	this->perspective[8] = 0;
	this->perspective[9] = 0;
	this->perspective[10] = (zNear + zFar)*rangInv;
	this->perspective[11] = -1;

	this->perspective[12] = 0;
	this->perspective[13] = 0;
	this->perspective[14] = (zNear*zFar*rangInv * 2);
	this->perspective[15] = 0;
}
