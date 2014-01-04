#include "Query.h"
#include "GLHeader.h"

namespace Tocs {
namespace Graphics {

const QueryTarget QueryTarget::SamplesPassed(GL_SAMPLES_PASSED);
const QueryTarget QueryTarget::AnySamplesPassed(GL_ANY_SAMPLES_PASSED);
const QueryTarget QueryTarget::AnySamplesPassedConservative(GL_ANY_SAMPLES_PASSED_CONSERVATIVE);
const QueryTarget QueryTarget::Time(GL_TIME_ELAPSED);
const QueryTarget QueryTarget::None(0);


Query::Query()
: ID(0), Target(QueryTarget::None)
{
	glGenQueries(1, &ID);
	GLErrorCheck();
}

Query::~Query()
{
	glDeleteQueries(1, &ID);
	GLErrorCheck();
}

void Query::Begin(QueryTarget target)
{
	glBeginQuery(target.GetGLEnum(), ID);
	GLErrorCheck();
	Target = target;
}
void Query::End()
{
	glEndQuery(Target.GetGLEnum());
	GLErrorCheck();
	Target = QueryTarget::None;
}

bool Query::Ready() const
{
	unsigned int result;
	glGetQueryObjectuiv(ID, GL_QUERY_RESULT_AVAILABLE, &result);
	GLErrorCheck();
	return result != 0;
}

unsigned int Query::Result() const
{
	unsigned int result;
	glGetQueryObjectuiv(ID, GL_QUERY_RESULT, &result);
	GLErrorCheck();
	return result;
}

unsigned long long Query::Result64() const
{
	unsigned long long result;
	glGetQueryObjectui64v(ID, GL_QUERY_RESULT_AVAILABLE, &result);
	GLErrorCheck();
	return result;
}

}}