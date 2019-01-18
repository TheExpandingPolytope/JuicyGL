RigidBody::RigidBody()
{
	//set mass, mass inverse, inertial tensor, position, etc
	m = mInv = 1.0f;
	IBody = IBodyinv = R = Iinv = mat3(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	q.i = q.j = q.k = q.r = 0.0f;
	q.r = 1.0f;
	x = p = L = v = w = force = torque = vec3(0.0f, 0.0f, 0.0f);
	x = vec3(0.0f, 0.0f, 0.0f);
	model = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
}


void RigidBody::genInertialTensor()
{
	//in the mean time, ill just generate the inertial tensor of a cube 1*1*1 density 1
	float s = 1; //length of a side
	IBody = mat3(vec3(2. / 3., -1. / 4., -1. / 4.),
		vec3(-1. / 4., 2. / 3., -1 / 4),
		vec3(1. / 4., 1. / 4., 2. / 3.));
	IBodyinv = IBody.inverse();
	Iinv = IBodyinv;
}

void RigidBody::imposeForce(float& t, float &dt)
{
	p = p + force*dt; //p = f*dt
	v = p / m; //v = p/m
	x = x + v*dt; //x = x + v*dt
}

void RigidBody::imposeTorque(float& t, float &dt)
{
	R = q.matrix(); //calculate orientation
	Iinv = R*IBodyinv*R.transpose(); //calculate world coordinate
	L = L + torque*dt; //calculate angular momentum
	w = Iinv*L; // calculate angular velocity
	q = (q + (quat(w.x,w.y, w.z, 0)*q * 0.5)).normalize(); //calculate quaternion
	
	
}

void RigidBody::initObject()
{
	//link mesh data
	jBuffer b;
	b.data = mesh.mesh_arr();
	b.attribute_name = "vertex_pos";
	b.attribute_number = b.data.size();
	b.attribute_size = 3;
	object.data.clear();
	object.data.push_back(b);
	//link triangle coordinate dataobj
	struct::mesh bary_coords;
	triangle t; t.p1 = vec3(1., 0., 0.);  t.p2 = vec3(0., 1., 0.);  t.p3 = vec3(0., 0., 1.);
	for (int i = 0; i < mesh.triangles.size(); i++) {  bary_coords.triangles.push_back(t); }
	
	jBuffer b1;
	b1.data = bary_coords.mesh_arr();
	std::cout << "\n";
	for (int i = 0; i < b1.data.size(); i++)
		std::cout << b1.data[i] << " ";
	std::cout << "\n";
	b1.attribute_name = "barycentric_coord";
	b1.attribute_number = b1.data.size();
	b1.attribute_size = 3;
	object.data.push_back(b1);
	//link model matrix
	jUniformMatrix4x4 m;
	m.uniform_name = "model";
	m.set(object.model);
	object.matrices4x4.clear();
	object.matrices4x4.push_back(m);
	//load shaders
	jShader v, f; jProgram p;
	v.type = GL_VERTEX_SHADER; f.type = GL_FRAGMENT_SHADER;
	v.load("RGDBODYvertex_shader.txt"); f.load("RGDBODYfragment_shader.txt");
	p.shaders.clear(); p.shaders.push_back(v); p.shaders.push_back(f);
	p.compile();
	object.material = p;

}


void RigidBody::updateObject()
{
	//set orientation
	object.model.x0 = R.x0;
	object.model.x1 = R.x1;
	object.model.x2 = R.x2;

	object.model.y0 = R.y0;
	object.model.y1 = R.y1;
	object.model.y2 = R.y2;

	object.model.z0 = R.z0;
	object.model.z1 = R.z1;
	object.model.z2 = R.z2;
	
	//set translation
	object.model.w0 = x.x;
	object.model.w1 = x.y;
	object.model.w2 = x.z;

}
RigidBodyContact::RigidBodyContact()
{
	//link mesh data

	//link point of contact
	jUniformVector3 point;
	point.uniform_name = "p";
	point.set(p);
	object.vectors3.clear();
	object.vectors3.push_back(point);
	//link normal of face
	jUniformVector3 normal;
	normal.uniform_name = "n";
	normal.set(n);
	object.vectors3.push_back(normal);
	//link edgeA of contact
	jUniformVector3 edgeA;
	edgeA.uniform_name = "ea";
	edgeA.set(ea);
	object.vectors3.push_back(edgeA);
	//link edgeB of contact
	jUniformVector3 edgeB;
	edgeB.uniform_name = "eb";
	edgeB.set(eb);
	object.vectors3.push_back(edgeB);
	//load shaders
	jShader v, g, f; jProgram p;
	v.type = GL_VERTEX_SHADER; g.type = GL_GEOMETRY_SHADER; f.type = GL_FRAGMENT_SHADER;
	v.load("Contact_vertex_shader.txt"); g.load("Contact_geometry_shader.txt"); f.load("Contact_fragment_shader.txt");
	p.shaders.clear(); p.shaders.push_back(v); p.shaders.push_back(g); p.shaders.push_back(f);
	p.compile();
	object.material = p;
}
