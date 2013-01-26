#include "Pipeline.h"

using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

Pipeline::Pipeline(GraphicsContext &context)
	: Deferred (context),
	  Lights(context,Deferred.GetBuffer ())
{
	
}

}}