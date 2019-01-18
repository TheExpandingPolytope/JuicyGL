jAABB::jAABB()
{
	jShader vert, frag, geo;

	vert.type = GL_VERTEX_SHADER;
	vert.load("AABBvertex_shader.txt");

	frag.type = GL_FRAGMENT_SHADER;
	frag.load("AABBfragment_shader.txt");

	geo.type = GL_GEOMETRY_SHADER;
	geo.load("AABBgeometry_shader.txt");

	object.material.shaders.clear();
	object.material.shaders.push_back(vert);
	object.material.shaders.push_back(geo);
	object.material.shaders.push_back(frag);

	glDeleteProgram(object.material.program);
	object.material.compile();
}

void jAABB::setAABB(AABB &c)
{
	box = &c;

	jUniformVector3 min, max;
	min.uniform_name = "min";
	min.set(box->min);
	max.uniform_name = "max";
	max.set(box->max);

	object.vectors3.push_back(min);
	object.vectors3.push_back(max);
}

void jAABB::setColor(vector3 &c)
{
	color = &c;
	jUniformVector3 color_uniform;
	color_uniform.uniform_name = "color";
	color_uniform.set(*color);
	object.vectors3.push_back(color_uniform);
}

jSphere::jSphere()
{
	jShader vert, frag, geo;

	vert.type = GL_VERTEX_SHADER;
	vert.load("SPHEREvertex_shader.txt");

	frag.type = GL_FRAGMENT_SHADER;
	frag.load("SPHEREfragment_shader.txt");

	geo.type = GL_GEOMETRY_SHADER;
	geo.load("SPHEREgeometry_shader.txt");

	object.material.shaders.clear();
	object.material.shaders.push_back(vert);
	object.material.shaders.push_back(geo);
	object.material.shaders.push_back(frag);

	glDeleteProgram(object.material.program);
	object.material.compile();
}

void jSphere::setSphere(Sphere& s)
{
	//point to values of actual jPhysics sphere
	sphere = &s;
	//point content of jPhysics sphere to  renderingobject
	jUniformVector3 centerr;
	centerr.uniform_name = "center";
	centerr.set(sphere->Center);
	jUniformFloat radius;
	radius.uniform_name = "radius";
	radius.set(sphere->radius);
	object.floats.push_back(radius);
	object.vectors3.push_back(centerr);
}

void jSphere::setColor(vector3 &c)
{
	color = c;
	jUniformVector3 color_uniform;
	color_uniform.uniform_name = "color";
	color_uniform.set(color);
	object.vectors3.push_back(color_uniform);
}