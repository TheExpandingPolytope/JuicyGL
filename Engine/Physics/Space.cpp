void Space::exist()
{
	//apply whatever needs to be applied to all the rigidbodies that exist in this space
	for (int i = 0; i < RigidBodies.size(); i++)
	{
		RigidBodies[i]->force = 0;
		RigidBodies[i]->torque = vec3(.001,0,0);
		RigidBodies[i]->imposeForce(t, dt); //Impose force on rigid body
		RigidBodies[i]->imposeTorque(t, dt); //Impose torque on rigid body
		RigidBodies[i]->updateObject(); //Apply changes to the "object to be rendered"
		display();
	}
}

void Space::display()
{
	//reset 
	scene->objects.clear();
	
	//re-add objects
	for (int i = 0; i < RigidBodies.size(); i++)
	{
		scene->objects.push_back(&RigidBodies[i]->object);
	}
	for (int i = 0; i < contacts.size(); i++)
	{
		scene->objects.push_back(&contacts[i].object);
	}

	scene->render();
}

void Space::collision_detection()
{
	for (int i = 0; i < RigidBodies.size(); i++)
	{
		RigidBody rb1 = *RigidBodies[i];
		mesh mesh1 = rb1.object.model*rb1.mesh;
		for (int j = 0; j < RigidBodies.size(); j++)
		{
			if (i != j)
			{
				RigidBody rb2 = *RigidBodies[j];
				mesh mesh2 = rb2.object.model*rb2.mesh;

				if (mesh1.test_intersection(mesh2))
					contacts.push_back(mesh1.contact(mesh2));
			}
		}
	}
}

void Space::collision_response()
{
	for (int i = 0; i < contacts.size(); i++)
	{
		//compute impulsive force from contact data
		RigidBodyContact c = contacts[i];
		float e = 1.0f; //coefficient of restitution
		vector3 rA = c.p - (c.a->x + c.a->c); //point of contact in body A's local coordinates
		vector3 rB = c.p - (c.b->x + c.b->c); //point of contact in body B's local coordinates
		vector3 kA = rA.cross(c.n);
		vector3 kB = rB.cross(c.n);
		vector3 uA = c.a->Iinv * kA;
		vector3 uB = c.b->Iinv * kB;
		float fnumer = -(1 + e) * (c.n.dot(c.a->v - c.b->v) + c.a->w.dot(kA) - c.b->w.dot(kB));
		float fdenom = c.a->mInv + c.b->mInv + kA.dot(uA) + kB.dot(uB);
		float f = fnumer / fdenom;
		vector3 impulse = c.n * f;
		
		//apply impulse
		c.a->p = c.a->p + impulse;
		c.b->p = c.b->p - impulse;

		//compute angular and linear velocity
		c.a->v = c.a->p * c.a->mInv;
		c.b->v = c.b->p * c.b->mInv;
		c.a->w = c.a->w + uA*f;
		c.b->w = c.b->w + uB*f;
	}
}