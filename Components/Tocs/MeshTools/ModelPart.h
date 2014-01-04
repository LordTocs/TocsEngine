#pragma once

namespace Tocs {
namespace MeshTools {

class ModelPart
{
public:
	ModelPart();
	virtual ~ModelPart () {}

	virtual void QueueJobs () = 0;
	virtual void DequeueJobs () = 0;
};

}}