#include "ShaderUniformBlock.h"
#include "GLHeader.h"
#include "Shader.h"
#include "UBO.h"

namespace Tocs {
namespace Graphics {

unsigned int ShaderUniformBlock::SizeInBytes () const
{
	int result;
	glGetActiveUniformBlockiv (OwningShader.GetID (), BlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE,&result);
	GLErrorCheck ();
	return result;
}

bool ShaderUniformBlock::UsedInShader (ShaderType type) const
{
	bool result;
	GLenum referencedbyquery = 0;

	if (type == ShaderType::Pixel)
	{
		referencedbyquery = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER;
	}
	else if (type == ShaderType::Vertex)
	{
		referencedbyquery = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER;
	}
	else if (type == ShaderType::Geometry)
	{
		referencedbyquery = GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER;
	}

	if (referencedbyquery == 0)
		return false;

	glGetActiveUniformBlockiv (OwningShader.GetID (),BlockIndex,referencedbyquery,reinterpret_cast<GLint*> (&result));
	GLErrorCheck ();
	return result;
}

ShaderUniformBlock &ShaderUniformBlock::operator= (UBO &ubo)
{
	glUniformBlockBinding (OwningShader.GetID (),BlockIndex,BufferBindingIndex);

	ubo.Bind (BufferBindingIndex); 

	return *this;
}

}}