void SkinnedMesh::loadVertAttribData(const char * filepath)
{
	vertices.clear(); boneIndices.clear(); weights.clear();
	const aiScene *s = aiImportFile(filepath, aiProcess_Triangulate);
	for (int i = 0; i < s->mNumMeshes; i++)
	{
		aiVector3D * verts = s->mMeshes[i]->mVertices;
		int jj =0;
		for (int j = 0; j < s->mMeshes[i]->mNumFaces; j++)
		{
			
			aiFace face = s->mMeshes[i]->mFaces[j];

			vector3 vToAdd = aiToVector3(verts[face.mIndices[0]]);
			vertices.push_back(vToAdd.x); vertices.push_back(vToAdd.y); vertices.push_back(vToAdd.z);
			stuff k = findVertexWeightAndBoneIndex(face.mIndices[0], s->mMeshes[i]);
			boneIndices.push_back(k.boneIndex.x); boneIndices.push_back(k.boneIndex.y); boneIndices.push_back(k.boneIndex.z);
			weights.push_back(k.weight.x); weights.push_back(k.weight.y); weights.push_back(k.weight.z);
			
			
			vToAdd = aiToVector3(verts[face.mIndices[1]]);
			vertices.push_back(vToAdd.x); vertices.push_back(vToAdd.y); vertices.push_back(vToAdd.z);
			k = findVertexWeightAndBoneIndex(face.mIndices[1], s->mMeshes[i]);
			boneIndices.push_back(k.boneIndex.x); boneIndices.push_back(k.boneIndex.y); boneIndices.push_back(k.boneIndex.z);
			weights.push_back(k.weight.x); weights.push_back(k.weight.y); weights.push_back(k.weight.z);
			

			vToAdd = aiToVector3(verts[face.mIndices[2]]);
			vertices.push_back(vToAdd.x); vertices.push_back(vToAdd.y); vertices.push_back(vToAdd.z);
			k = findVertexWeightAndBoneIndex(face.mIndices[2], s->mMeshes[i]);
			boneIndices.push_back(k.boneIndex.x); boneIndices.push_back(k.boneIndex.y); boneIndices.push_back(k.boneIndex.z);
			weights.push_back(k.weight.x); weights.push_back(k.weight.y); weights.push_back(k.weight.z);
			
			if (jj == 0) { baryCoords.push_back(1.0); baryCoords.push_back(0.0); baryCoords.push_back(0.0); jj++; }
			if (jj == 1) { baryCoords.push_back(0.0); baryCoords.push_back(1.0); baryCoords.push_back(0.0); jj++; }
			if (jj == 2) { baryCoords.push_back(0.0); baryCoords.push_back(0.0); baryCoords.push_back(1.0);  jj = 0; }
			
		}
	}
	
}

void SkinnedMesh::initObject()
{
    object.name = "A-Skinned-Mesh";
	object.data.clear(); object.matrices4x4.clear();
	//initialize shaders
	jProgram p; jShader v, g, f;
	v.type = GL_VERTEX_SHADER; v.load("SKINNEDMESHvertex_shader.txt");
	g.type = GL_GEOMETRY_SHADER; g.load("SKINNEDMESHgeometry_shader.txt");
	f.type = GL_FRAGMENT_SHADER; f.load("SKINNEDMESHfragment_shader.txt");
	p.shaders.clear(); p.shaders.push_back(v);
     p.shaders.push_back(f);
	p.compile();
	glDeleteProgram(object.material.program);
	object.material = p;
	//LOAD IN VERTEX WEIGHT, POSITIONS, AND BON	EINDICES
	jBuffer vpos;
	vpos.buffer_type = GL_ARRAY_BUFFER;
	vpos.attribute_name = "vert_position";
	vpos.attribute_number = vertices.size();
	vpos.attribute_type = GL_FLOAT;
	vpos.attribute_size = 3;
	vpos.data = vertices;
	jBuffer vweight;
	vweight.attribute_name = "vert_weights";
	vweight.buffer_type = GL_ARRAY_BUFFER;
	vweight.attribute_number = weights.size();
	vweight.attribute_size = 3;
	vweight.attribute_type = GL_FLOAT;
	vweight.data = weights;
	jBuffer vboneIndices;
	vboneIndices.attribute_name = "vert_boneIndices";
	vboneIndices.buffer_type = GL_ARRAY_BUFFER;
	vboneIndices.attribute_number = boneIndices.size();
	vboneIndices.attribute_type = GL_FLOAT;
	vboneIndices.attribute_size = 3;
	vboneIndices.data = boneIndices;
	jBuffer vbarcoord;
	vbarcoord.attribute_name = "bary_Coordinates";
	vbarcoord.buffer_type = GL_ARRAY_BUFFER;
	vbarcoord.attribute_number = baryCoords.size();
	vbarcoord.attribute_type = GL_FLOAT;
	vbarcoord.attribute_size = 3;
	vbarcoord.data = baryCoords;
	object.data.push_back(vpos); object.data.push_back(vweight); object.data.push_back(vboneIndices);
	object.data.push_back(vbarcoord);
	for (int i = 0; i < armature.bones.size(); i++)
	{
		//determine index to load
		std::string index;
		switch (i)
		{
		case 0:index = "0";  break;
		case 1:index = "1";  break;
		case 2:index = "2";  break;
		case 3:index = "3";  break;
		case 4:index = "4";  break;
		case 5:index = "5";  break;
		case 6:index = "6";  break;
		case 7:index = "7";  break;
		case 8:index = "8";  break;
		case 9:index = "9"; break;
		case 10:index = "10";  break;
		case 11:index = "11";  break;
		case 12:index = "12";  break;
		case 13:index = "13";  break;
		case 14:index = "14";  break;
		case 15:index = "15";  break;
		case 16:index = "16";  break;
		case 17:index = "17";  break;
		case 18:index = "18";  break;
		case 19:index = "19";  break;
		case 20:index = "20";  break;
		case 21:index = "21";  break;
		case 22:index = "22";  break;
		case 23:index = "23";  break;
		case 24:index = "24";  break;
		case 25:index = "25";  break;
		case 26:index = "26";  break;
		case 27:index = "27";  break;
		case 28:index = "28";  break;
		case 29:index = "29";  break;
		case 30:index = "30";  break;
		case 31:index = "31";  break;
		case 32:index = "32";  break;
		case 33:index = "33";  break;
		case 34:index = "34";  break;
		case 35:index = "35";  break;
		case 36:index = "36";  break;
		case 37:index = "37";  break;
		case 38:index = "38";  break;
		case 39:index = "39";  break;
		case 40:index = "40";  break;
		}

		//load endposes as uniforms to shader
		jUniformMatrix4x4 eps;
		eps.set(armature.bones[i].endPose);
		eps.uniform_name = (std::string)("bones[") + index + (std::string)("].endPose");
		object.matrices4x4.push_back(eps);

		//load invBindPoses as uniform to shader
		jUniformMatrix4x4 invP;
		invP.set(armature.bones[i].invBindPose);
		invP.uniform_name = (std::string)("bones[") + index + (std::string)("].invBindPose");
		object.matrices4x4.push_back(invP);

		//load bone colors as uniform to shader
		jUniformVector3 bColor;
		bColor.set(armature.bones[i].color);
		bColor.uniform_name = (std::string)("bones[") + index + (std::string)("].color");
		object.vectors3.push_back(bColor);
	}
}

vector3 SkinnedMesh::aiToVector3(aiVector3D vec)
{
	return vec3(vec.x, vec.y, vec.z);
}

stuff SkinnedMesh::findVertexWeightAndBoneIndex(int vertexID, aiMesh * meshToSearchIn)
{
	stuff tin;
	std::vector<float> weight, boneIndex;
	for (int i = 0; i < meshToSearchIn->mNumBones; i++)
	{
		aiBone* bone = meshToSearchIn->mBones[i];
		for (int j = 0; j < bone->mNumWeights; j++)
		{
			if (vertexID == bone->mWeights[j].mVertexId)
			{
				
				weight.push_back(bone->mWeights[j].mWeight);
				for (int jj = 0; jj < armature.bones.size(); jj++)
				{
					if (armature.bones[jj].name == bone->mName.C_Str())
					{
						boneIndex.push_back(jj);
						jj = armature.bones.size();
					}
						
					
				}
			}
				
		}
	}
	if (weight.size() >= 1)
		tin.weight.x = weight[0];
	if (weight.size() >= 2)
		tin.weight.y = weight[1];
	if (weight.size() >= 3)
		tin.weight.z = weight[2];

	if (boneIndex.size() >= 1)
		tin.boneIndex.x = boneIndex[0];
	if (boneIndex.size() >= 2)
		tin.boneIndex.y = boneIndex[1];
	if (boneIndex.size() >= 3)
		tin.boneIndex.z = boneIndex[2];

	return tin;
}
