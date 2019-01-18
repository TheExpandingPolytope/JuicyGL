struct jCamera;
struct pbr_test_object
{
	jCamera *cam;

	//vertex attributes to load to shader
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> textureCoordinates;

	//uniform variable to load to shader
	vector3 lightPositions[4];
	vector3 lightColors[4];
	vector3 albedo;
	GLfloat metallic;
	GLfloat roughness;
	GLfloat ao;

	void loadSphere();
	void loadUniformData();
	
	jObject object;
	pbr_test_object(jCamera &ca);
};