struct jShader
{
	GLuint type, shader;

	void load(const char *filepath);

private:
	std::string readFile(const char *filepath);
};

struct jProgram
{
	GLuint program;
	std::vector<jShader> shaders;

	void compile();
};