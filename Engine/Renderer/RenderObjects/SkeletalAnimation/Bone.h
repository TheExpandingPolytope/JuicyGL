struct Bone
{
	//array of bone animations
	std::vector<bonePosKey> posKeys;
	std::vector<boneRotKey> rotKeys;
	std::vector<boneScaleKey> scaleKeys;

	std::string name; //name of bone
	Bone* parent;//pointer to parent
	vector3 children; //indices of children
	vector3 color; //color of this particular bone
	
	//poses that the cpu augments
	matrix4 localPose; //pose in local coordinates (relative ot parent) this pose change
	
	//poses to be sent to the shader
	matrix4 bindPose; //bind pose in world coordinates
	matrix4 invBindPose; //inverse of bind pose in world coordinates
	matrix4 endPose; //final pose in world coordinates

	bool isUpdated; //has the endPose been updated
	   
	void updateEndPose(); //update based on the values of the localposes
	void updateEndPose(float t);//update endposes based on time and animations
	void display();
	Bone();
private:
	int findGreaterThanAndClosestToRotKey(float t);
	int findGreaterThanAndClosestToPosKey(float t);
	int findGreaterThanAndClosestToScaleKey(float t);
	int findLessThanAndClosestToRotKey(float t);
	int findLessThanAndClosestToPosKey(float t);
	int findLessThanAndClosestToScaleKey(float t);
};