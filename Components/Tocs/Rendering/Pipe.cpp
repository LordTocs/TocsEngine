#include "Pipe.h"



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


void Pipe::Draw (Graphics::GraphicsContext &context, const Camera &camera)
{
	BeginDraw (context, camera);

	for (auto i = Jobs.BeginObjects (); i != Jobs.EndObjects (); ++i)
	{
		//Check frustum
		/*(*i).DrawShader.Bind ();
		BeginJob (*i,context,camera);
		//(*i).Input.PassToShader();
		(*i).Draw.Execute(context);
		EndJob (*i,context,camera);
		(*i).DrawShader.UnBind();*/
	}

	EndDraw (context, camera);
}

JobProxy Pipe::Add (const Job &job)
{
	return JobProxy (this, Jobs.Add(job));
}

void Pipe::Remove (const JobProxy &proxy)
{
	Jobs.Remove(proxy.Id);
}

}}