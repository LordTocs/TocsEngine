#include "Mesh.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp> 
#include <assimp/postprocess.h>
#include "Vertices.h"

namespace Tocs {
namespace Rendering {

Mesh::Mesh(unsigned int vertexcount, unsigned int indexcount, const Graphics::VertexFormat &format)
	: VertexBuffer (vertexcount * format.SizeInBytes ()),
	  IndexBuffer (indexcount),
	  Format (format)
{
	VertexArray.Bind ();
	VertexArray.AddVBO (VertexBuffer,Format);
	VertexArray.UnBind ();

}

/*Mesh::Mesh(unsigned int vertexcount, unsigned int indexcount, const Graphics::VertexFormat &format, const Graphics::IndexFormat &iformat)
	: VertexBuffer (vertexcount * format.SizeInBytes ()),
	  IndexBuffer (indexcount, iformat),
	  Format (format)
{
	VertexArray.Bind ();
	VertexArray.AddVBO (VertexBuffer,Format);
	VertexArray.UnBind ();
}*/

Mesh::Mesh (Mesh &&moveme)
	: VertexBuffer(std::move(moveme.VertexBuffer)),
	  IndexBuffer (std::move(moveme.IndexBuffer)),
	  VertexArray (std::move(moveme.VertexArray)),
	  Parts (std::move(moveme.Parts))
{
}

Mesh &Mesh::operator= (Mesh &&moveme)
{
	VertexBuffer = std::move(moveme.VertexBuffer);
	IndexBuffer = std::move(moveme.IndexBuffer);
	VertexArray = std::move(moveme.VertexArray);
	Parts = std::move(moveme.Parts);
	return *this;
}

unsigned int Mesh::GetVerticeCount () const
{
	return VertexBuffer.SizeInBytes () / Format.SizeInBytes ();
}
unsigned int Mesh::GetIndexCount () const
{
	return IndexBuffer.SizeInBytes() / sizeof(unsigned int); //fixdis
}

DrawCall Mesh::GetDrawCall (unsigned int partindex) const
{
	return DrawCall (VertexArray,IndexBuffer,Parts[partindex].GetOffset (), Parts[partindex].GetLength ());
}

void Mesh::Bind () const
{
	VertexArray.Bind ();
	IndexBuffer.Bind (Graphics::BufferTarget::Index);
}

void Mesh::UnBind () const
{
	IndexBuffer.UnBind ();
	VertexArray.UnBind ();
}

void Mesh::AddPart(const MeshPart &part)
{
	Parts.push_back(part);
}

Mesh Mesh::LoadFromFile (const std::string &filename)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename,aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (!scene)
	{
		//ERROROROROR
	}

	unsigned int vertexcount = 0;
	unsigned int indexcount = 0;

	for (int m = 0; m < scene->mNumMeshes; ++m)
	{
		aiMesh *mesh = scene->mMeshes[m];

		vertexcount += mesh->mNumVertices;
		indexcount += mesh->mNumFaces * 3;
	}

	Mesh result (vertexcount,indexcount,PositionTextureNormal::Format.Get());//, Graphics::IndexFormat::ThirtyTwoBit);

	std::unique_ptr<PositionTextureNormal []> verts (new PositionTextureNormal[vertexcount]);
	std::unique_ptr<unsigned int []> indices (new unsigned int [indexcount]);

	int vertdex = 0;
	int indexdex = 0;

	for (int m = 0; m < scene->mNumMeshes; ++m)
	{
		int meshstart = vertdex;
		aiMesh *mesh = scene->mMeshes[m];
		for (int v = 0; v < mesh->mNumVertices; ++v)
		{
			verts[vertdex].Position(mesh->mVertices[v].x,mesh->mVertices[v].y,mesh->mVertices[v].z);
			verts[vertdex].TextureCoordinate(mesh->mTextureCoords[0][v].x,mesh->mTextureCoords[0][v].y);
			verts[vertdex].Normal(mesh->mNormals[v].x,mesh->mNormals[v].y,mesh->mNormals[v].z);
			++vertdex;
		}
		result.AddPart(MeshPart(indexdex/3,mesh->mNumFaces));
		for (int f = 0; f < mesh->mNumFaces; ++f)
		{
			aiFace *face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; ++i)
			{
				indices[indexdex++] = meshstart + face->mIndices[i];
			}
		}
	}

	result.WriteIndices(indices.get(),indexcount,0);
	result.WriteVertices(verts.get(),vertexcount);
	return result;
}

}}