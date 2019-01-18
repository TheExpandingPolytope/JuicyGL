struct Skeleton
{
	matrix4 GlobalInvTransform;
	float max_Duration;
	std::vector<Bone> bones;
	jObject object;
	
	void updateEndPoses(); //update the value of the endPose model in each bone from localPoses and their parents
	void updateEndPoses(float t);
	void update(Bone root); //update end poses
	void initObject(); //initialize the object ot be rendered
	void loadCollada(const char* filename); //load bone information from collada file

	Skeleton(); //constructor
private:
	int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
	void addAllChildNodes(aiNode* rootNode, std::vector<aiNode*> *nodeArray);
	int getID(aiString name, std::vector<aiNode*> &nodeArray);
	matrix4 aiToMat4(aiMatrix4x4 mat);
};