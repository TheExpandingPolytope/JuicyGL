struct jCamera
{
	vector3 eye, target, upDir;


	jCamera();

	void moveX(float speed);
	void moveY(float speed);
	void moveZ(float speed);

	std::vector<GLfloat>* View();
	std::vector<GLfloat>* Perspective(float fov, float aspect, float zNear, float zFar);
	std::vector<GLfloat> view, perspective;

};