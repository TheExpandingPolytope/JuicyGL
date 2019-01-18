struct jUniformMatrix4x4
{
	std::string uniform_name;
	matrix4 *uniform_data;

	jUniformMatrix4x4();

	void set(matrix4 &matrix);
	void linkTo(jProgram program);
};




struct jUniformVector3
{
	std::string uniform_name;
	vector3 *uniform_data;

	void set(vector3 &vector);
	void linkTo(jProgram program);
};

//data structure for loading uniform floats to an arbitrary shader
struct jUniformFloat
{
	GLchar *uniform_name; //name as appears in shader
	GLfloat *uniform_data; //data to send to shader

	void set(float &f);
	void linkTo(jProgram program);
};

struct texture2D
{
	GLuint texture;
	GLchar* uniform_name;
	unsigned char* image;
	int width, height;

	texture2D();

	void loadTextureData(char *filename);
	void linkTo(jProgram program);
};