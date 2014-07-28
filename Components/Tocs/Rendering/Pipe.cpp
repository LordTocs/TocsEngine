#include "Pipe.h"
#include "RenderSystem.h"


namespace Tocs {
namespace Rendering {

Job &JobProxy::Get ()
{
	return PipeRef->Jobs.Get(Id);
}

const Job &JobProxy::Get () const
{
	return PipeRef->Jobs.Get(Id);
}

void JobProxy::Remove()
{
	PipeRef->Remove(*this);
	PipeRef = nullptr;
	Id = PackedFreeList<Job>::Id();
}

Pipe::Pipe(RenderSystem &system)
: System(system)
{

}

void Pipe::Draw(const Camera &camera)
{
	BeginDraw (camera);

	for (auto i = Jobs.BeginObjects (); i != Jobs.EndObjects (); ++i)
	{
		//Check frustum
		(*i).DrawShader->Bind ();
		BeginJob(*i, camera);
		(*i).Input.PassToShader();
		(*i).Draw.Execute(System.Context());
		EndJob(*i, camera);
		(*i).DrawShader->UnBind();
	}

	EndDraw(camera);
}


JobProxy Pipe::Add (DrawCall call, Graphics::Shader &shader)
{
	//std::cout << "Adding Job" << std::endl;
	JobProxy prox (this, Jobs.Add(Job(call,shader)));
	JobAdded(prox.Get());
	return prox;
}

void Pipe::Remove (const JobProxy &proxy)
{
	Jobs.Remove(proxy.Id);
}

void Pipe::UpdateSortKey(Job &job, const Camera &camera)
{
	Math::Vector3 ProjPos = camera.GetView() * camera.GetProjection() * job.Bounds.Center();
}

}}