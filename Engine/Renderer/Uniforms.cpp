jUniformMatrix4x4::jUniformMatrix4x4()
{

}

void jUniformMatrix4x4::set(matrix4 &matrix)
{
	uniform_data = &matrix;
}

void jUniformMatrix4x4::linkTo(jProgram program)
{
	glUniformMatrix4fv(glGetUniformLocation(program.program, uniform_name.data()), 1, GL_FALSE, uniform_data->column_major_arr().data());
}

void jUniformVector3::set(vector3 &vector)
{
	uniform_data = &vector;
}

void jUniformVector3::linkTo(jProgram program)
{
	glUniform3fv(glGetUniformLocation(program.program, uniform_name.data()), 1, uniform_data->arr().data());
}

void jUniformFloat::set(float &f)
{
	uniform_data = &f;
}

void jUniformFloat::linkTo(jProgram program)
{
	glUniform1f(glGetUniformLocation(program.program, uniform_name), *uniform_data);
}

texture2D::texture2D()
{
	glGenTextures(1, &texture);
}

void texture2D::loadTextureData(char *filename)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void texture2D::linkTo(jProgram program) 
{
	glUniform1i(glGetUniformLocation(program.program, uniform_name), 1);
}




