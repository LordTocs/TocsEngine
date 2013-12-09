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

Pipe::Pipe()
{

}

void Pipe::Draw(RenderSystem &system, Graphics::GraphicsContext &context, const Camera &camera)
{
	BeginDraw (system, context, camera);

	for (auto i = Jobs.BeginObjects (); i != Jobs.EndObjects (); ++i)
	{
		//Check frustum
		(*i).DrawShader->Bind ();
		BeginJob(*i, system, context, camera);
		(*i).Input.PassToShader();
		(*i).Draw.Execute(context);
		EndJob(*i, system, context, camera);
		(*i).DrawShader->UnBind();
	}

	EndDraw(system, context, camera);
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

}}