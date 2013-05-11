#include "Model.h"
#include "Job.h"
namespace Tocs {
namespace Rendering {

void Model::MaterialSlot::QueueJobs()
{
	if (Mat == nullptr)
		return;
	auto j = Jobs.begin();
	for (auto i = Mat->GetComponents().begin(); i != Mat->GetComponents().end(); ++i)
	{
		(*i).GetPipe().AppendJob(*j);
		j++;
	}
}

void Model::MaterialSlot::DequeueJobs()
{
	if (Mat == nullptr)
		return;
	auto j = Jobs.begin();
	for (auto i = Mat->GetComponents().begin(); i != Mat->GetComponents().end(); ++i)
	{
		(*i).GetPipe().RemoveJob(*j);
		j++;
	}
}

Model::MaterialSlot::MaterialSlot (Model *model, unsigned int index)
	: ModelInstance (model),
	  Index(index)
{
}

Model::MaterialSlot::MaterialSlot (MaterialSlot &&moveme)
	: ModelInstance(moveme.ModelInstance),
	  Mat(std::move(moveme.Mat)),
	  Jobs(std::move(moveme.Jobs)),
	  Index(moveme.Index)
{
}

void Model::MaterialSlot::SetMaterial (const Asset<Material> &material)
{
	Jobs.clear ();
	Mat = std::unique_ptr<MaterialInstance> (new MaterialInstance (ModelInstance->GetSystem(),material));
	for (auto i = Mat->GetComponents().begin(); i != Mat->GetComponents().end(); ++i)
	{
		Jobs.push_back(Job(ModelInstance->GetGeometry(),(*i).GetShading()));
	}
}

Model::Model(const Asset<Mesh> &mesh, RenderSystem &system)
	: RenderObject (system),
	  ModelMesh(mesh),
	  ModelGeometryType(Asset<StaticGeometryType>::Load("PositionTextureNormal.vert")),
	  ModelGeometry(mesh.Get(),ModelGeometryType.Get())
{
	ModelGeometry["World"].Ref(Transform.GetMatrix());

	for (int i = 0; i < mesh.Get().PartCount(); ++i)
	{
		Materials.push_back(MaterialSlot (this,i));
	}

}

void Model::QueueJobs ()
{
	for (auto i = Materials.begin();  i != Materials.end(); ++i)
	{
		(*i).QueueJobs();
	}
}
void Model::DequeueJobs ()
{
	for (auto i = Materials.begin();  i != Materials.end(); ++i)
	{
		(*i).DequeueJobs();
	}
}



}}