struct jScene
{
	jCamera *camera;
	std::vector<jObject*> objects;
	GLchar* perspective_uniform_name;
	GLchar* view_uniform_name;

	jScene();
	void setCamera(jCamera& cam);
	void render();
	void addObject(jObject &object);
private:
	std::vector<float> view;
	float perspective[16];
	void setView();
	void setPerspective(float fov, float aspect, float zNear, float zFar);
};