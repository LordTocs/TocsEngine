#include "CubeMapArray.h"
#include "GLHeader.h"

#include <sstream>

namespace Tocs {
namespace Graphics {

CubeMapArray::CubeMapArray(unsigned int layers, unsigned int size, TextureFormat format, TextureFiltering filtering)
: ID(0)
{
	Build(layers, size, format, filtering);
}
CubeMapArray::~CubeMapArray()
{
	glDeleteTextures(1, &ID);
}

CubeMapArray::CubeMapArray(CubeMapArray &&moveme)
: ID(moveme.ID)
{
	moveme.ID = 0;
}
CubeMapArray &CubeMapArray::operator= (CubeMapArray &&moveme)
{
	ID = moveme.ID;
	moveme.ID = 0;
	return *this;
}

unsigned int CubeMapArray::GetSize() const
{
	Bind();
	int result = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_TEXTURE_WIDTH,&result);
	UnBind();
	return result;
}

unsigned int CubeMapArray::GetLayers() const
{
	Bind();
	int result = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_TEXTURE_DEPTH, &result);
	UnBind();
	return result/6;
}

void CubeMapArray::Build(unsigned int layers, unsigned int size, TextureFormat format, TextureFiltering filtering)
{
	if (ID == 0)
	{
		glGenTextures(1, &ID);
	}

	Bind();

	if (!format.IsIntegerFormat())
	{
		glTexParameterf(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLErrorCheck();
		if (filtering != TextureFiltering::None)
		{
			glTexParameterf(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			GLErrorCheck();
		}
		else
		{
			glTexParameterf(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GLErrorCheck();
		}

		if (filtering == TextureFiltering::Anisotropic)
		{
			glTexParameterf(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
			GLErrorCheck();
		}
	}
	else
	{
		glTexParameterf(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		GLErrorCheck();
		glTexParameterf(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		GLErrorCheck();
	}

	if (format.IsShadowFormat())
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		GLErrorCheck();
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		GLErrorCheck();
	}



			//Faces
	glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, format.InternalGLFormat(), size, size, layers * 6, 0, format.Format(), format.Type(), nullptr);
	GLErrorCheck();


	UnBind();
}


void CubeMapArray::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, ID);
	GLErrorCheck();
}

void CubeMapArray::Bind(int reg) const
{
	glActiveTexture(GL_TEXTURE0 + reg);
	GLErrorCheck();
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, ID);
	GLErrorCheck();
}

void CubeMapArray::UnBind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);
	GLErrorCheck();
}


void CubeMapArray::Read(void *data, TextureDataFormat dataformat) const
{
	Bind();
	glGetTexImage(GL_TEXTURE_CUBE_MAP_ARRAY, 0, dataformat.Format(), dataformat.DataType(), data);
	GLErrorCheck();
	UnBind();
}


}}
