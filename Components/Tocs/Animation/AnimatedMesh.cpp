#include "AnimatedMesh.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp> 
#include <assimp/postprocess.h>
#include <memory>
#include <Tocs/Rendering/Vertices.h>

namespace Tocs {
namespace Animation {

AnimatedMesh::AnimatedMesh(Rendering::Mesh &&mesh, SkeletonSource &&armature)
: Mesh_(std::move(mesh)), Armature_(std::move(armature))
{

}

AnimatedMesh::AnimatedMesh(AnimatedMesh &&moveme)
: Mesh_(std::move(moveme.Mesh_)), Armature_(std::move(moveme.Armature_))
{

}

inline bool fexists(const std::string& name) 
{
	if (FILE *file = fopen(name.c_str(), "r")) 
	{
		fclose(file);
		return true;
	}
	else 
	{
		return false;
	}
}

static Math::Matrix4 ConvertMatrix(aiMatrix4x4 mat)
{
	Math::Matrix4 result;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			result(r, c) = mat[r][c];
		}
	}
	return result;
}

static void ParseBone(aiNode *bone, std::map<std::string, unsigned int> &bonemapping, std::vector<BoneSource> &bones, unsigned int parentindex)
{
	unsigned int index = parentindex;
	if (true)
	{
		std::string name(bone->mName.C_Str());
		index = bones.size();
		bonemapping[name] = index;
		Math::Matrix4 bindtrans = ConvertMatrix(bone->mTransformation);
		bones.push_back(BoneSource(name, parentindex, Math::Matrix4::ExtractDualQuaternion(bindtrans)));
	}
	for (int c = 0; c < bone->mNumChildren; ++c)
	{
		ParseBone(bone->mChildren[c], bonemapping, bones, index);
	}
	
}

AnimatedMesh AnimatedMesh::LoadFromFile(const std::string &filename)
{

	Assimp::Importer importer;
	//importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
	if (!fexists(filename))
	{
		std::cout << "Cannot open " << filename;
	}


	const aiScene* scene = importer.ReadFile(filename, aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_Triangulate);

	if (!scene)
	{
		//ERROROROROR
		std::cout << "Didn't load." << std::endl;
	}

	//Load bones
	std::map<std::string, unsigned int> bonemapping;
	std::vector<BoneSource> bones;

	ParseBone(scene->mRootNode, bonemapping, bones, ~0u);
	

	unsigned int vertexcount = 0;
	unsigned int indexcount = 0;

	for (int m = 0; m < scene->mNumMeshes; ++m)
	{
		aiMesh *mesh = scene->mMeshes[m];

		vertexcount += mesh->mNumVertices;
		indexcount += mesh->mNumFaces * 3;
	}

	Rendering::Mesh rmesh(vertexcount, indexcount, Rendering::PositionTextureNormalTangentBone::Format.Get(), Graphics::IndexFormat::ThirtyTwoBit);

	std::unique_ptr<Rendering::PositionTextureNormalTangentBone[]> verts(new Rendering::PositionTextureNormalTangentBone[vertexcount]);
	std::unique_ptr<unsigned int[]> indices(new unsigned int[indexcount]);

	int vertdex = 0;
	int indexdex = 0;

	for (int m = 0; m < scene->mNumMeshes; ++m)
	{
		int meshstart = vertdex;
		aiMesh *mesh = scene->mMeshes[m];

		if (!mesh->HasNormals())
		{
			std::cout << "ERROR: Mesh Has No Normals" << std::endl;
		}

		for (int v = 0; v < mesh->mNumVertices; ++v)
		{
			verts[vertdex].Position(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
			if (mesh->HasTextureCoords(0))
			{
				verts[vertdex].TextureCoordinate(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
			}
			if (mesh->HasNormals())
			{
				verts[vertdex].Normal(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
			}
			if (mesh->HasTangentsAndBitangents())
			{
				verts[vertdex].Tangent(mesh->mTangents[v].x, mesh->mTangents[v].y, mesh->mTangents[v].z);
			}
			++vertdex;
		}

		for (int b = 0; b < mesh->mNumBones; ++b)
		{
			aiBone *bone = mesh->mBones[b];
			unsigned int bonedex = bonemapping[std::string(bone->mName.C_Str())];
			for (int w = 0; w < bone->mNumWeights; ++w)
			{
				aiVertexWeight *weight = &bone->mWeights[w];
				auto &vert = verts[meshstart + weight->mVertexId];
				for (int i = 0; i < 4; ++i)
				{
					if (vert.BoneWeights[i] == 0.0f)
					{
						vert.BoneWeights[i] = weight->mWeight;
						vert.BoneIndices[i] = bonedex;
						break;
					}
				}
			}
		}

		rmesh.AddPart(Rendering::MeshPart(indexdex / 3, mesh->mNumFaces));
		for (int f = 0; f < mesh->mNumFaces; ++f)
		{
			aiFace *face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; ++i)
			{
				indices[indexdex++] = meshstart + face->mIndices[i];
			}
		}
	}

	rmesh.WriteIndices(indices.get(), indexcount);
	rmesh.WriteVertices(verts.get(), vertexcount);
	
	return AnimatedMesh(std::move(rmesh), SkeletonSource(bones));
}

}}