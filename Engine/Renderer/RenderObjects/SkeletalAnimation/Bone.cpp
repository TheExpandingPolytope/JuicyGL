void Bone::updateEndPose()
{
	if (parent != NULL) {
		if (isUpdated) {
			parent->updateEndPose();
			endPose = parent->endPose*localPose;
			isUpdated = true;
		}
		else
			endPose = endPose;

	}
	else
		endPose = localPose;

}

void Bone::updateEndPose(float t)
{
	//find position value
	float dt, tweight;
	vector3 position, dpos;
    bonePosKey pi,pf;
	pi = posKeys[findLessThanAndClosestToPosKey(t)];
	pf = posKeys[findGreaterThanAndClosestToPosKey(t)];
	dt = pf.t - pi.t;
	dpos = pf.pos - pi.pos;
	tweight = (t - pi.t) / dt;
	position = pi.pos + (dpos*tweight);
	
	//find rotation value
	quaternion rotation, drot;
	boneRotKey ri, rf;
	ri = rotKeys[findLessThanAndClosestToRotKey(t)];
	rf = rotKeys[findGreaterThanAndClosestToRotKey(t)];
	dt = rf.t - ri.t;
	drot = rf.quat - ri.quat;
	tweight = (t - ri.t) / dt;
	rotation = ri.quat + (drot*tweight);

	//find scaling value
	vector3 scale,dscale;
	boneScaleKey si, sf;
	si = scaleKeys[findLessThanAndClosestToScaleKey(t)];
	sf = scaleKeys[findGreaterThanAndClosestToScaleKey(t)];
	dt = sf.t - si.t;
	dscale = sf.scale - si.scale;
	tweight = (t - si.t) / dt;
	scale = si.scale + (dscale*tweight);
	matrix3 rr = rotation.matrix();
	matrix4 matrix = translate(position.x, position.y, position.z)*mat4(vec4(rr.x0,rr.y0,rr.z0,0), vec4(rr.x1, rr.y1, rr.z1, 0), vec4(rr.x2, rr.y2, rr.z2, 0), vec4(0,0,0,1)).transpose()* mat4(vec4(scale.x,0,0,0),vec4(0,scale.y,0,0),vec4(0,0,scale.z,0),vec4(0,0,0,1));
	localPose = matrix;
}


int Bone::findGreaterThanAndClosestToRotKey(float t)
{
	
	float delta, smallestDelta = FLT_MAX;
	int index = 0;
	for (int i = 0; i < rotKeys.size(); i++)
	{
		delta = t - rotKeys[i].t;
		if (delta < 0 && abs(delta) < abs(smallestDelta))
		{
			smallestDelta = delta;
			index = i;
		}
	}
	return index;
}

int Bone::findGreaterThanAndClosestToPosKey(float t)
{
	float delta, smallestDelta = FLT_MAX;
	int index = 0;
	for (int i = 0; i < posKeys.size(); i++)
	{
		delta = t - posKeys[i].t;
		if (delta < 0 && abs(delta) < abs(smallestDelta))
		{
			smallestDelta = delta;
			index = i;
		}
	}
	return index;
}

int Bone::findGreaterThanAndClosestToScaleKey(float t)
{
	float delta, smallestDelta = FLT_MAX;
	int index = 0;
	for (int i = 0; i < scaleKeys.size(); i++)
	{
		delta = t - scaleKeys[i].t;
		if (delta < 0 && abs(delta) < abs(smallestDelta))
		{
			smallestDelta = delta;
			index = i;
		}
	}
	return index;
}

int Bone::findLessThanAndClosestToRotKey(float t)
{
	float delta, smallestDelta = FLT_MAX;
	int index = 0;
	for (int i = 0; i < rotKeys.size(); i++)
	{
		delta = t - rotKeys[i].t;
		if (delta > 0 && abs(delta) < abs(smallestDelta))
		{
			smallestDelta = delta;
			index = i;
		}
	}
	return index;
}

int Bone::findLessThanAndClosestToPosKey(float t)
{
	float delta, smallestDelta = FLT_MAX;
	int index = 0;
	for (int i = 0; i < posKeys.size(); i++)
	{
		delta = t - posKeys[i].t;
		if (delta > 0 && abs(delta) < abs(smallestDelta))
		{
			smallestDelta = delta;
			index = i;
		}
	}
	return index;
}

int Bone::findLessThanAndClosestToScaleKey(float t)
{
	float delta, smallestDelta = FLT_MAX;
	int index = 0;
	for (int i = 0; i < scaleKeys.size(); i++)
	{
		delta = t - scaleKeys[i].t;
		if (delta > 0 && abs(delta) < abs(smallestDelta))
		{
			smallestDelta = delta;
			index = i;
		}
	}
	return index;
}

void Bone::display()
{
	std::cout <<"\n\nBONE NAME:\n" <<name;
	std::cout << "\nBONE CHILDREN:\n"; children.display();
	std::cout << "\nBONE LOCALPOSE:\n"; localPose.display();
	std::cout << "\nBONE BIND POSE:\n"; bindPose.display();
	std::cout << "\nBONE INV BIND POSE:\n"; invBindPose.display();
	std::cout << "\nBONE ENDPOSE:\n"; endPose.display();
}

Bone::Bone()
{
	parent = NULL;
	isUpdated = false;
}