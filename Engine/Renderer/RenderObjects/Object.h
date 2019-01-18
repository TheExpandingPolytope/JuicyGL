struct jObject
{
	std::string name;
	std::vector<jBuffer> data;
	std::vector<jUniformMatrix4x4> matrices4x4;
	std::vector<jUniformVector3> vectors3;
	std::vector<jUniformFloat> floats; //list of uniform floats to load to shader
	jProgram material;
	matrix4 model;

	jObject();
};