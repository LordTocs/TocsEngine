#include "Model.h"
#include "Job.h"
namespace Tocs {
namespace Rendering {

void Model::MaterialSlot::QueueJobs()
{
	auto j = Jobs.begin();
	for (auto i = Mat->GetComponents().begin(); i != Mat->GetComponents().end(); ++i)
	{
		(*i).GetPipe().AppendJob(*j++);
	}
}

void Model::MaterialSlot::DequeueJobs()
{
	
}

Model::MaterialSlot::MaterialSlot (Model *model, unsigned int index)
	: ModelInstance (model),
	  Index(index)
{
}

void Model::MaterialSlot::SetMaterial (const Material &material)
{
	Jobs.clear ();
	Mat = std::shared_ptr<MaterialInstance> (material.CreateInstance ());
	for (auto i = Mat->GetComponents().begin(); i != Mat->GetComponents().end(); ++i)
	{
		Jobs.push_back(Job(ModelInstance->GetGeometry(),(*i).GetShading()));
	}
}


}}