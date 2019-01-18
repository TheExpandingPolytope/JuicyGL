std::vector<float> mesh::mesh_arr()
{
	std::vector<float> f;
	for (int i = 0; i < triangles.size(); i++)
	{
		f.push_back(triangles[i].p1.x); f.push_back(triangles[i].p1.y); f.push_back(triangles[i].p1.z);
		f.push_back(triangles[i].p2.x); f.push_back(triangles[i].p2.y); f.push_back(triangles[i].p2.z);
		f.push_back(triangles[i].p3.x); f.push_back(triangles[i].p3.y); f.push_back(triangles[i].p3.z);

	}
	mesh_ar = f;
	return mesh_ar;
}

bool mesh::test_intersection(mesh operand)
{
	return false;
}

RigidBodyContact mesh::contact(mesh operand)
{
	return RigidBodyContact();
}

vector3 mesh::dist_from(mesh operand)
{
	return vector3();
}

int mesh::nthOccurrence(const std::string & str, const std::string & findMe, int nth)
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

void mesh::loadObj(std::string filename)
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

triangle t;
triangles.clear();

while (!lastFace) {
	startLine = nthOccurrence(data, "f ", inc);

	endLine = data.find("\n", startLine);

	line = data.substr(startLine, endLine);

	vElement = atoi(line.substr(2, nthOccurrence(line, "/", 1)).c_str());
	vertex = data.substr(nthOccurrence(data, "v ", vElement), data.find("\n", nthOccurrence(data, "v ", vElement)));
	stringstream ss(vertex);
	ss >> state >> t.p1.x >> t.p1.y >> t.p1.z;

	vElement = atoi(line.substr(nthOccurrence(line, " ", 2) + 1, nthOccurrence(line, "/", 3)).c_str());
	vertex = data.substr(nthOccurrence(data, "v ", vElement), data.find("\n", nthOccurrence(data, "v ", vElement)));
	stringstream ss3(vertex);
	ss3 >> state >> t.p2.x >> t.p2.y >> t.p2.z;

	vElement = atoi(line.substr(nthOccurrence(line, " ", 3) + 1, nthOccurrence(line, "/", 5)).c_str());
	vertex = data.substr(nthOccurrence(data, "v ", vElement), data.find("\n", nthOccurrence(data, "v ", vElement)));
	stringstream ss6(vertex);
	ss6 >> state >> t.p3.x >> t.p3.y >> t.p3.z;

	triangles.push_back(t);

	inc++;

	if (nthOccurrence(data, "f ", inc) == -1) {
		lastFace = true;
	}
}
}

mesh mesh::operator+(vector3 v)
{
	return mesh();
}