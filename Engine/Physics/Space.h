struct jScene;
struct Space
{
	std::vector<RigidBody*> RigidBodies; //array of rigid bodies that exist in this space
	std::vector<RigidBodyContact> contacts; //array of contacts between rigid bodies
	float t; //current time in units of "dt" that this space exists in
	float dt; //interval of integration

	void exist(); //generate and impose forces/torque upon all rigid bodies that exist in this space;
	
	void display(); // render RigidBodies and Contacts to the screen
    //contact generation fucntions (collision detection)
	void collision_detection(); //generates contact points
	//contact processing functions (collision response)
	void collision_response(); //generates forces from contact points

	jScene* scene; // scene to display rigid bodie in

};