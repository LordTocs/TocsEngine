#include "Model.h"
#include "StaticGeometryHandlers.h"
namespace Tocs {
namespace Rendering {

Model::Model(Mesh &mesh)
	: ModelMesh(mesh),
	  Handler(GetStaticGeometryHandler<PositionTextureNormal> ()),
	  Materials(new MaterialJobs [mesh.PartCount ()])
{
	for (int i = 0; i < ModelMesh.PartCount (); ++i)
	{
		Materials[i].SetModel(this);
	}
}


Model::~Model(void)
{
}

void Model::Show ()
{
	for (int i = 0; i < ModelMesh.PartCount (); ++i)
	{
		Materials[i].Show ();
	}
}

void Model::Hide ()
{
	for (int i = 0; i < ModelMesh.PartCount (); ++i)
	{
		Materials[i].Hide ();
	}
}


void Model::MaterialJobs::Show ()
{
	for (auto i = Jobs.begin (); i != Jobs.end (); ++i)
	{
		(*i)->Show ();
	}
}

void Model::MaterialJobs::Hide ()
{
	for (auto i = Jobs.begin (); i != Jobs.end (); ++i)
	{
		(*i)->Hide ();
	}
}


void Model::MaterialJobs::CreateJobs (Pipeline &pipeline)
{
	if (ModelMaterial == nullptr)
		return;

	Jobs.clear ();

	for (auto i = ModelMaterial->BeginPasses (); i != ModelMaterial->EndPasses (); ++i)
	{
		MeshJob *job = new MeshJob(ThisModel->ModelMesh,Index,(*i),ThisModel->Transform,ThisModel->Handler);
		Jobs.push_back(std::unique_ptr<MeshJob> (job));
		Pipe &pipe = (*i)->GetPipe(pipeline);
		pipe.AddJob (*job);
	}
}

}}