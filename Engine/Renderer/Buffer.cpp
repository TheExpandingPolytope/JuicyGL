jBuffer::jBuffer()
{
	buffer_type = GL_ARRAY_BUFFER;
	glGenBuffers(1, &buffer);
	attribute_name = "vertex_pos";
	attribute_size = 3;
	attribute_type = GL_FLOAT;
	attribute_number = 3;

	float vertices[] = { -0.5,-1.0,0.0, 1.0,-1.0,0.0, 0.0,1.0,0.0 };
	for (int i = 0; i < 9; i++)
	{
		data.push_back(vertices[i]);
	}
	glBindBuffer(buffer_type, buffer);
	glBufferData(buffer_type, 9 * sizeof(float), vertices, GL_DYNAMIC_DRAW);

}

void jBuffer::importVector(std::vector<float> mesh)
{
	data = mesh;
}

void jBuffer::importObj(std::string filename)
{
	int inc = 1;
	int startLine;
	int endLine;
	float vX;
	float vY;
	float vZ;
	float uv;
	float uv1;
	float vn;
	float vn1;
	float vn2;
	int vElement;
	int uvElement;
	int vnElement;
	bool lastFace = false;

	using namespace std;
	vector<float> vertices;
	vector<float> textureCoords;
	vector<float> normals;
	vector<int> indices;
	string state;
	string line;
	string vertex;
	string normal;
	string textureCoord;
	string data;
	string coco = "\n";
	std::ifstream file(filename.c_str());
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string str = buffer.str();
	data = str;

	while (!lastFace) {
		startLine = nthOccurrence(data, "f ", inc);

		endLine = data.find("\n", startLine);

		line = data.substr(startLine, endLine);

		vElement = atoi(line.substr(2, nthOccurrence(line, "/", 1)).c_str());
		uvElement = atoi(line.substr(nthOccurrence(line, "/", 1) + 1, nthOccurrence(line, "/", 2)).c_str());
		vnElement = atoi(line.substr(nthOccurrence(line, "/", 2) + 1, nthOccurrence(line, " ", 2)).c_str());
		vertex = data.substr(nthOccurrence(data, "v ", vElement), data.find("\n", nthOccurrence(data, "v ", vElement)));
		textureCoord = data.substr(nthOccurrence(data, "vt ", uvElement), data.find("\n", nthOccurrence(data, "vt ", uvElement)));
		normal = data.substr(nthOccurrence(data, "vn ", vnElement), data.find("\n", nthOccurrence(data, "vn ", vnElement)));
		stringstream ss(vertex);
		ss >> state >> vX >> vY >> vZ;
		stringstream ss1(textureCoord);
		ss1 >> state >> uv >> uv1;
		stringstream ss2(normal);
		ss2 >> state >> vn >> vn1 >> vn2;

		vertices.push_back(vX);
		cout << vX << " ";
		vertices.push_back(vY);
		cout << vY << " ";
		vertices.push_back(vZ);
		cout << vZ << " ";
		textureCoords.push_back(uv);
		textureCoords.push_back(uv1);
		normals.push_back(vn);
		normals.push_back(vn1);
		normals.push_back(vn2);

		indices.push_back(inc);

		vElement = atoi(line.substr(nthOccurrence(line, " ", 2) + 1, nthOccurrence(line, "/", 3)).c_str());
		uvElement = atoi(line.substr(nthOccurrence(line, "/", 3) + 1, nthOccurrence(line, "/", 4)).c_str());
		vnElement = atoi(line.substr(nthOccurrence(line, "/", 4) + 1, nthOccurrence(line, " ", 3)).c_str());
		vertex = data.substr(nthOccurrence(data, "v ", vElement), data.find("\n", nthOccurrence(data, "v ", vElement)));
		textureCoord = data.substr(nthOccurrence(data, "vt ", uvElement), data.find("\n", nthOccurrence(data, "vt ", uvElement)));
		normal = data.substr(nthOccurrence(data, "vn ", vnElement), data.find("\n", nthOccurrence(data, "vn ", vnElement)));
		stringstream ss3(vertex);
		ss3 >> state >> vX >> vY >> vZ;
		stringstream ss4(textureCoord);
		ss4 >> state >> uv >> uv1;
		stringstream ss5(normal);
		ss5 >> state >> vn >> vn1 >> vn2;

		vertices.push_back(vX);
		cout << vX << " ";
		vertices.push_back(vY);
		cout << vY << " ";
		vertices.push_back(vZ);
		cout << vZ << " ";
		textureCoords.push_back(uv);
		textureCoords.push_back(uv1);
		normals.push_back(vn);
		normals.push_back(vn1);
		normals.push_back(vn2);

		indices.push_back(inc);

		vElement = atoi(line.substr(nthOccurrence(line, " ", 3) + 1, nthOccurrence(line, "/", 5)).c_str());
		uvElement = atoi(line.substr(nthOccurrence(line, "/", 5) + 1, nthOccurrence(line, "/", 6)).c_str());
		vnElement = atoi(line.substr(nthOccurrence(line, "/", 6) + 1, line.find("\n")).c_str());
		vertex = data.substr(nthOccurrence(data, "v ", vElement), data.find("\n", nthOccurrence(data, "v ", vElement)));
		textureCoord = data.substr(nthOccurrence(data, "vt ", uvElement), data.find("\n", nthOccurrence(data, "vt ", uvElement)));
		normal = data.substr(nthOccurrence(data, "vn ", vnElement), data.find("\n", nthOccurrence(data, "vn ", vnElement)));
		stringstream ss6(vertex);
		ss6 >> state >> vX >> vY >> vZ;
		stringstream ss7(textureCoord);
		ss7 >> state >> uv >> uv1;
		stringstream ss8(normal);
		ss8 >> state >> vn >> vn1 >> vn2;

		vertices.push_back(vX);
		cout << vX << " ";
		vertices.push_back(vY);
		cout << vY << " ";
		vertices.push_back(vZ);
		cout << vZ << " ";
		textureCoords.push_back(uv);
		textureCoords.push_back(uv1);
		normals.push_back(vn);
		normals.push_back(vn1);
		normals.push_back(vn2);

		indices.push_back(inc);

		inc++;

		if (nthOccurrence(data, "f ", inc) == -1) {
			lastFace = true;
		}
	}

	glBindBuffer(buffer_type, this->buffer);
	glBufferData(buffer_type, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
	this->data = vertices;
	attribute_number = vertices.size();

}

void jBuffer::linkTo(jProgram program)
{
	glBindBuffer(buffer_type, buffer);
	glBufferData(buffer_type, data.size()*sizeof(float), data.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(glGetAttribLocation(program.program, attribute_name));
	glVertexAttribPointer(glGetAttribLocation(program.program, attribute_name), attribute_size, attribute_type, GL_FALSE, attribute_size * sizeof(attribute_type), (void*)(0));

}

int jBuffer::nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
	size_t  pos = 0;
	int     cnt = 0;
	while (cnt != nth)
	{
		pos += 1;
		pos = str.find(findMe, pos);
		if (pos == std::string::npos)
			return -1;
		cnt++;
	}
	return pos;
}