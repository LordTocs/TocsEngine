#pragma once
#include <Tocs/Rendering/RenderObject.h>
namespace Tocs {
namespace MeshTools {

class CompoundModel : public Rendering::RenderObject
{
protected:
	void QueueJobs ();
	void DequeueJobs ();
public:
	CompoundModel(Rendering::RenderSystem &system);
	
};

}}

