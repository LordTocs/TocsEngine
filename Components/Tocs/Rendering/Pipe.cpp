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
, ShaderManager(16,0)
{
	CameraState.AddValue("View");
	CameraState.AddValue("Projection");
	CameraState.AddValue("InvView");
	CameraState.AddValue("InvProjection");
}

void Pipe::Draw(const Camera &camera)
{
	CameraState["View"].Ref(camera.GetView());
	CameraState["Projection"].Ref(camera.GetProjection());
	CameraState["InvView"].Ref(camera.GetInverseView());
	CameraState["InvProjection"].Ref(camera.GetInverseProjection());

	ShaderManager.ResetFrame();
	BeginDraw (camera);
	for (auto i = Jobs.BeginObjects (); i != Jobs.EndObjects (); ++i)
	{
		//Check frustum
		ShaderManager.SwitchStateSet(i->StateSet);
		BeginJob(*i, camera);
		(*i).Draw.Execute(System.Context());
		EndJob(*i, camera);
	}

	EndDraw(camera);
}


JobProxy Pipe::Add (DrawCall call, Graphics::Shader &shader)
{
	//std::cout << "Adding Job" << std::endl;
	JobProxy prox (this, Jobs.Add(Job(call,shader)));
	prox.Get().StateSet.MapState(CameraState);
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
	unsigned int statekeys = ShaderManager.GetCommonStateBitfield(job.StateSet);
}

}}