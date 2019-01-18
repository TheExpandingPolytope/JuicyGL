void Skeleton::updateEndPoses()
{
	bones[0].endPose = bones[0].localPose;
	update(bones[0]);
}

void Skeleton::updateEndPoses(float t)
{
	float tIn;
	if (t > max_Duration)
	{
		float weewee = t / max_Duration;
		weewee = weewee - floor(weewee);
		tIn = max_Duration * weewee;
	}
	else
		tIn = t;
	for (int i = 0; i < bones.size(); i++)
	{
		bones[i].updateEndPose(tIn);
	}
	updateEndPoses();
}

void Skeleton::initObject()
{
	object.name = "A-Skeleton";
	object.matrices4x4.clear(); object.vectors3.clear();
	for (int i = 0; i < bones.size(); i++)
	{
		//load children to object
		jUniformVector3 C;
		C.set(bones[i].children);
		std::string z;
		std::string a = "bones[";
		std::string b; 
		switch (i)
		{
		case 0: b = "0";  break;
		case 1: b = "1";  break;
		case 2: b = "2";  break;
		case 3: b = "3";  break;
		case 4: b = "4";  break;
		case 5: b = "5";  break;
		case 6: b = "6";  break;
		case 7: b = "7";  break;
		case 8: b = "8";  break;
		case 9: b = "9"; break;
		case 10: b = "10";  break;
		case 11: b = "11";  break;
		case 12: b = "12";  break;
		case 13: b = "13";  break;
		case 14: b = "14";  break;
		case 15: b = "15";  break;
		case 16: b = "16";  break;
		case 17: b = "17";  break;
		case 18: b = "18";  break;
		case 19: b = "19";  break;
		case 20: b = "20";  break;
		case 21: b = "21";  break;
		case 22: b = "22";  break;
		case 23: b = "23";  break;
		case 24: b = "24";  break;
		case 25: b = "25";  break;
		case 26: b = "26";  break;
		case 27: b = "27";  break;
		case 28: b = "28";  break;
		case 29: b = "29";  break;
		case 30: b = "30";  break;
		case 31: b = "31";  break;
		case 32: b = "32";  break;
		case 33: b = "33";  break;
		case 34: b = "34";  break;
		case 35: b = "35";  break;
		case 36: b = "36";  break;
		case 37: b = "37";  break;
		case 38: b = "38";  break;
		case 39: b = "39";  break;
		case 40: b = "40";  break;
		}
		std::string c = "].children";
		std::string d = "].endPose";
		std::string e = "].color";
		z = a+b+c+z;
		C.uniform_name = z;
		std::cout << "BONE CHILDREN\n" << C.uniform_name << "\n";
		object.vectors3.push_back(C);

		//load color to object
		jUniformVector3 cc;
		cc.set(bones[i].color);
		cc.uniform_name = (std::string)("bones[") + b + (std::string)("].color");
		object.vectors3.push_back(cc);

		//load endPoses to object
		jUniformMatrix4x4 m;
		m.set(bones[i].endPose);
		std::string y;
		y = a + b + d + y;
		m.uniform_name = y;
		std::cout << "BONE ENDPOSES\n" << m.uniform_name << "\n";
		object.matrices4x4.push_back(m);
	}
	jShader v, g, f; jProgram p;
	v.type = GL_VERTEX_SHADER;  v.load("SKELETONvertex_shader.txt");
	g.type = GL_GEOMETRY_SHADER; g.load("SKELETONgeometry_shader.txt");
	f.type = GL_FRAGMENT_SHADER; f.load("SKELETONfragment_shader.txt");
	p.shaders.push_back(v);
	p.shaders.push_back(g);
	p.shaders.push_back(f);
	p.compile();
	object.material = p;
}

void Skeleton::loadCollada(const char* filename)
{

	//load file data
	const aiScene* s = aiImportFile(filename, aiProcess_Triangulate);
	
		std::vector<aiBone*> aibones;
		std::vector<aiNode*> nodes;
		aiNode* root = s->mRootNode;
		GlobalInvTransform = aiToMat4(root->mTransformation).transpose().inverse();
		GlobalInvTransform.display();

		for (int i = 0; i < s->mNumMeshes; i++)
		{
			for (int j = 0; j < s->mMeshes[i]->mNumBones; j++)
			{
				aibones.push_back(s->mMeshes[i]->mBones[j]);
				nodes.push_back(root->FindNode(aibones[j]->mName));
			}
		}
		
		bones.clear();
		std::vector<int> parentIDs;
		for (int i = 0; i < nodes.size(); i++)
		{
			Bone b;
			//load local bone matrix data
			b.localPose = aiToMat4(nodes[i]->mTransformation).transpose();
			b.isUpdated = false;
			//load children ids
			b.children = -1;
			if (nodes[i]->mNumChildren > 0)
				b.children.x = getID(nodes[i]->mChildren[0]->mName, nodes);
			if (nodes[i]->mNumChildren > 1)
				b.children.y = getID(nodes[i]->mChildren[1]->mName, nodes);
			if (nodes[i]->mNumChildren > 2)
				b.children.z = getID(nodes[i]->mChildren[2]->mName, nodes);
			//load parent id
			if (i > 0)
				parentIDs.push_back(getID(nodes[i]->mParent->mName, nodes));
			else
				parentIDs.push_back(-1);
			//load name
			b.name = nodes[i]->mName.C_Str();
			b.color.x = (float)rand() / (float)RAND_MAX; b.color.y = (float)rand() / (float)RAND_MAX; b.color.z = (float)rand() / (float)RAND_MAX;

			//load animations
			for (int k = 0; k < s->mNumAnimations; k++)
			{
				max_Duration = s->mAnimations[k]->mDuration;
				for (int y = 0; y < s->mAnimations[k]->mNumChannels; y++)
				{
					if (s->mAnimations[k]->mChannels[y]->mNodeName == nodes[i]->mName)
					{
						for (int p = 0; p < s->mAnimations[k]->mChannels[y]->mNumPositionKeys; p++)
						{
							bonePosKey f;
							f.t = s->mAnimations[k]->mChannels[y]->mPositionKeys[p].mTime;
							f.pos.x = s->mAnimations[k]->mChannels[y]->mPositionKeys[p].mValue.x;
							f.pos.y = s->mAnimations[k]->mChannels[y]->mPositionKeys[p].mValue.y;
							f.pos.z = s->mAnimations[k]->mChannels[y]->mPositionKeys[p].mValue.z;

							std::cout << "\n" + b.name + "\nt = " << f.t << "\nposition = " << f.pos.x << ", " << f.pos.y << ", " << f.pos.z;
							b.posKeys.push_back(f);
						}
						for (int pp = 0; pp < s->mAnimations[k]->mChannels[y]->mNumRotationKeys; pp++)
						{
							boneRotKey f;
							f.t = s->mAnimations[k]->mChannels[y]->mRotationKeys[pp].mTime;
							f.quat.i = s->mAnimations[k]->mChannels[y]->mRotationKeys[pp].mValue.x;
							f.quat.j = s->mAnimations[k]->mChannels[y]->mRotationKeys[pp].mValue.y;
							f.quat.k = s->mAnimations[k]->mChannels[y]->mRotationKeys[pp].mValue.z;
							f.quat.r = s->mAnimations[k]->mChannels[y]->mRotationKeys[pp].mValue.w;
							std::cout << "\n" + b.name + "\nt = " << f.t << "\nrotation = " << f.quat.i << ", " << f.quat.j << ", " << f.quat.k << ", " << f.quat.r;
							b.rotKeys.push_back(f);
						}
						for (int ppp = 0; ppp < s->mAnimations[k]->mChannels[y]->mNumScalingKeys; ppp++)
						{
							boneScaleKey f;
							f.t = s->mAnimations[k]->mChannels[y]->mPositionKeys[ppp].mTime;
							f.scale.x = s->mAnimations[k]->mChannels[y]->mScalingKeys[ppp].mValue.x;
							f.scale.y = s->mAnimations[k]->mChannels[y]->mScalingKeys[ppp].mValue.y;
							f.scale.z = s->mAnimations[k]->mChannels[y]->mScalingKeys[ppp].mValue.z;
							std::cout << "\n" + b.name + "\nt = " << f.t << "\nscale = " << f.scale.x << ", " << f.scale.y << ", " << f.scale.z;
							b.scaleKeys.push_back(f);
						}
					}
				}
			}
			b.invBindPose = aiToMat4(aibones[i]->mOffsetMatrix).transpose();
			bones.push_back(b);
		}

		//load parent info 
		for (int i = 0; i < bones.size(); i++)
		{
			if (parentIDs[i] != -1)
				bones[i].parent = &bones[parentIDs[i]];
			else
				bones[i].parent = NULL;
		}

		//load endPose information
		bones[0].endPose = bones[0].localPose;
		update(bones[0]);

		//load bindPose and inverse Bind Pose information
		for (int i = 0; i < bones.size(); i++)
		{
			bones[i].bindPose = bones[i].endPose;
		}

		for (int i = 0; i < bones.size(); i++)
		{
			bones[i].display();	
		}
		aiReleaseImport(s);
	
}



Skeleton::Skeleton()
{
	//initialize bone 1
	Bone b1;
	b1.bindPose = translate(0.0, 0.0, 0.0);
	b1.invBindPose = translate(0.0, 0.0, 0.0);
	b1.endPose = translate(0.0, 0.0, 0.0);
	b1.localPose = translate(0.0, 0.0, 0.0);
	b1.children = vec3(1.0, -1.0, -1.0);
	
	//initialize bone 2
	Bone b2; 
	b2.parent = &b1;
	b2.bindPose = translate(1.0, 0.0, 0.0);
	b2.invBindPose = translate(-1.0, 0.0, 0.0);
	b2.endPose = translate(1.0, 1.0, 1.0);
	b2.localPose = translate(1.0, 1.0, 1.0);
	b2.children = vec3(2, -1.0, -1.0);

	//initialize bone 3
	Bone b3;
	b3.parent = &b2;
	b3.bindPose = translate(1.0, 0.0, 0.0);
	b3.invBindPose = translate(-1.0, 0.0, 0.0);
	b3.endPose = translate(4.0, 3.0, 2.0);
	b3.localPose = translate(1.0, 1.0, 1.0);
	b3.children = vec3(-1.0, -1.0, -1.0);

	bones.push_back(b1);
	bones.push_back(b2);
	bones.push_back(b3);
}

int Skeleton::nthOccurrence(const std::string & str, const std::string & findMe, int nth)
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

void Skeleton::addAllChildNodes(aiNode * rootNode, std::vector<aiNode*>* nodeArray)
{
	nodeArray->push_back(rootNode);
	for (int i = 0; i < rootNode->mNumChildren; i++)
	{
		addAllChildNodes(rootNode->mChildren[i], nodeArray);
	}
}

int Skeleton::getID(aiString name, std::vector<aiNode*>& nodeArray)
{
	for (int i = 0; i < nodeArray.size(); i++)
	{
		if (nodeArray[i]->mName == name)
			return i;
		
	}
	return -1;
}

matrix4 Skeleton::aiToMat4(aiMatrix4x4 mat)
{
	matrix4 m;
	m.x0 = mat.a1;
	m.y0 = mat.b1;
	m.z0 = mat.c1;
	m.w0 = mat.d1;

	m.x1 = mat.a2;
	m.y1 = mat.b2;
	m.z1 = mat.c2;
	m.w1 = mat.d2;

	m.x2 = mat.a3;
	m.y2 = mat.b3;
	m.z2 = mat.c3;
	m.w2 = mat.d3;

	m.x3 = mat.a4;
	m.y3 = mat.b4;
	m.z3 = mat.c4;
	m.w3 = mat.d4;
	return m;
}

void Skeleton::update(Bone root)
{
	//for each child
	if (root.children.x >= 0)
	{
		Bone *childx = &bones[int(root.children.x)];
		childx->endPose = root.endPose * childx->localPose;
		update(*childx);
	}
	
	if (root.children.y >= 0)
	{
		Bone *childy = &bones[int(root.children.y)];
		childy->endPose = root.endPose * childy->localPose;
		update(*childy);
	}

	if (root.children.z >= 0)
	{
		Bone *childz = &bones[int(root.children.z)];
		childz->endPose = root.endPose * childz->localPose;
		update(*childz);
	}
}