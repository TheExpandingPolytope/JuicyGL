void pbr_test_object::loadSphere()
{
	const float resolution = 14;
	const float radius = 1;
	float gamma = 0.0f, theta = 0.0f, x, y, z, coverage=360.0f;
	vector3 center = vec3(0,0,0);
	while (gamma <= coverage) {
		theta = 0.0f;
		while (theta <= coverage)
		{
			x = center.x + (radius * cos(theta*3.14 / 180) * sin(gamma*3.14 / 180));
			z = center.z - (radius * cos(theta*3.14 / 180) * cos(gamma*3.14 / 180));
			y = center.y + (radius * sin(theta*3.14 / 180));
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			normals.push_back(x-center.x);
			normals.push_back(y-center.y);
			normals.push_back(z-center.z);
			textureCoordinates.push_back(0);
			textureCoordinates.push_back(0);
			

			x = center.x + (radius * cos(theta*3.14 / 180) * sin((gamma + (coverage / resolution))*3.14 / 180));
			z = center.z - (radius * cos(theta*3.14 / 180) * cos((gamma + (coverage / resolution))*3.14 / 180));
			y = center.y + (radius * sin(theta*3.14 / 180));
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			normals.push_back(x-center.x);
			normals.push_back(y-center.y);
			normals.push_back(z-center.z);
			textureCoordinates.push_back(0);
			textureCoordinates.push_back(0);

			theta += coverage / resolution;
		}
		
		gamma += coverage / resolution;
	}
}

void pbr_test_object::loadUniformData()
{
	lightColors[0] = vec3(1, 0, 0);
	lightColors[1] = vec3(1, 0, 0);
	lightColors[2] = vec3(1, 0, 0);
	lightColors[3] = vec3(1, 0, 0);

	lightPositions[0] = vec3(1, 0, 0);
	lightPositions[1] = vec3(1, 0, 0);
	lightPositions[2] = vec3(1, 0, 0);
	lightPositions[3] = vec3(1, 0, 0);

	albedo = vec3(0, 1, 0);
	metallic = .5;
	roughness = .2;
	ao = .3;
}



pbr_test_object::pbr_test_object(jCamera &ca)
{
	cam = &ca;
	loadSphere();
	loadUniformData();
	jBuffer b;
	jUniformFloat f;
	jUniformVector3 vv;
	object.data.clear();
	object.floats.clear();
	object.vectors3.clear();
	//verts
	b.data = vertices;
	b.attribute_number = vertices.size();
	b.attribute_size = 3;
	b.buffer_type = GL_VERTEX_ARRAY;
	b.attribute_name = "vertex_pos";
	object.data.push_back(b);
	//texcoords
	b.data = textureCoordinates;
	b.attribute_number = textureCoordinates.size();
	b.attribute_size = 2;
	b.buffer_type = GL_VERTEX_ARRAY;
	b.attribute_name = "texture_coords";
	object.data.push_back(b);
	//norms
	b.data = normals;
	b.attribute_number = normals.size();
	b.attribute_size = 3;
	b.buffer_type = GL_VERTEX_ARRAY;
	b.attribute_name = "normal";
	object.data.push_back(b);
	//metallic
	f.set(metallic);
	f.uniform_name = "metallic";
	object.floats.push_back(f);
	//roughness
	f.set(roughness);
	f.uniform_name = "roughness";
	object.floats.push_back(f);
	//ao
	f.set(ao);
	f.uniform_name = "ao";
	object.floats.push_back(f);
	//albedo
	vv.set(albedo);
	vv.uniform_name = "albedo";
	object.vectors3.push_back(vv);
	//lightPositions
	vv.set(lightPositions[0]);
	vv.uniform_name = "lightPositions[0]";
	object.vectors3.push_back(vv);
	vv.set(lightPositions[1]);
	vv.uniform_name = "lightPositions[1]";
	object.vectors3.push_back(vv);
	vv.set(lightPositions[2]);
	vv.uniform_name = "lightPositions[2]";
	object.vectors3.push_back(vv);
	vv.set(lightPositions[3]);
	vv.uniform_name = "lightPositions[3]";
	object.vectors3.push_back(vv);
	//lightColors
	vv.set(lightColors[0]);
	vv.uniform_name = "lightColors[0]";
	object.vectors3.push_back(vv);
	vv.set(lightColors[1]);
	vv.uniform_name = "lightColors[1]";
	object.vectors3.push_back(vv);
	vv.set(lightColors[2]);
	vv.uniform_name = "lightColors[2]";
	object.vectors3.push_back(vv);
	vv.set(lightColors[3]);
	vv.uniform_name = "lightColors[3]";
	object.vectors3.push_back(vv);
	//camPos
	vv.set(cam->eye);
	vv.uniform_name = "camPos";
	object.vectors3.push_back(vv);

}