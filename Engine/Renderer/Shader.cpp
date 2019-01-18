void jShader::load(const char *filepath)
{
	GLuint vertShader = glCreateShader(this->type);
	// Read shaders
	std::string vertShaderStr = readFile(filepath);
	const char *vertShaderSrc = vertShaderStr.c_str();
	GLint result = GL_FALSE;
	int logLength;
	// Compile vertex shader
	std::cout << "Compiling shader." << std::endl;
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);
	// Check vertex shader
	char buffer2[512];
	glGetShaderInfoLog(vertShader, 512, NULL, buffer2);
	std::cout << buffer2 << '\n';
	this->shader = vertShader;
}

std::string jShader::readFile(const char *filepath)
{
	std::string content;
	std::ifstream fileStream(filepath, std::ios::in);
	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filepath << ". File does not exist." << std::endl;
		return "";
	}
	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}



void jProgram::compile()
{
	this->program = glCreateProgram();
	for (int i = 0; i < this->shaders.size(); i++)
	{
		glAttachShader(this->program, this->shaders[i].shader);
	}
	glLinkProgram(this->program);

	int Success;
	GLchar ErrorLog[1024] = { 0 };
	glGetProgramiv(this->program, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(this->program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
	}
}