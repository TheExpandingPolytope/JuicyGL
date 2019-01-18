struct jBuffer
{
	GLuint buffer, buffer_type;
	GLchar* attribute_name;
	GLuint attribute_type;
	int attribute_size;
	int attribute_number;
	std::vector<float> data;

	jBuffer();

	void importObj(std::string filename);
	void importVector(std::vector<float> mesh); //load std::vector array as data for this buffer
	void linkTo(jProgram program);

private:
	int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
};