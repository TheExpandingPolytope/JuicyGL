struct RigidBody
{
	//constant variables
	float m; //mass of body
	float mInv; // inverse of mass
	matrix3 IBody; //inertial body tensor
	matrix3 IBodyinv; //inverse of body intertial tensor
	mesh mesh;
	jObject object;

	//state
	vector3 x; //global displacement of center of mass aka object (global)
	vector3 c; //local position of center of mass
	quaternion q; //quaternion of orientation
	vector3 p; //linear momentum
	vector3 L; //angular momentum
	matrix3 R; //orientation matrix derived from q
	vector3 v; //linear velocity
	vector3 w; //angular velocity
	matrix3 Iinv; //inverse intertial tensor world coordinates
	vector3 force, torque; //quantities imposed by the space in which this RigidBody exists in
	matrix4 model;

	RigidBody(); //m=mInv=1, Ibody=IBodyInv=1, etc. initializes object to be rendered
	void genInertialTensor(); //generate 'IBody' and 'IBodyinv' based on mesh
	void imposeForce(float &t, float &dt); //calculate current 'x' based on 'force' (semi implicit integration)
	void imposeTorque(float &t, float &dt); //calculate current 'R' based on 'torque' (semi implicit integration)
	void initObject(); //initialize jObject to be rendered
	void updateObject(); //updates the model of the object

};
