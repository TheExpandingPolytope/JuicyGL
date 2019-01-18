struct stuff { vector3 weight; vector3 boneIndex; };
struct SkinnedMesh
{
	//attributes ot pass to the shader
	std::vector<float> vertices; //array of triangles
	std::vector<float> weights; //array of weights
	std::vector<float> boneIndices; //array of bone indices
	std::vector<float> baryCoords; //array of barycentric coordinates
	Skeleton armature;
	jObject object; //object to be rendered
	
	void loadVertAttribData(const char*filepath);
	void initObject(); //initialize object

	vector3 aiToVector3(aiVector3D vec);
	
	stuff findVertexWeightAndBoneIndex(int vertexID, aiMesh * meshToSearchIn);
};