#include "Texture3D.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {


Texture3D::Texture3D(unsigned int width, unsigned int height, unsigned int depth, const TextureFiltering &filtering, const TextureFormat &format)
	: _Width(width), _Height(height), _Depth(depth), _Filtering (filtering), _Format(format), ID(0)
{
	glGenTextures (1, &ID);
	BuildTexture(width,height,depth,filtering,format);
}
Texture3D::Texture3D(Texture3D &&moveme)
	: _Width(moveme._Width), _Height(moveme._Height), _Depth(moveme._Depth), _Filtering(moveme._Filtering), _Format(moveme._Format), ID(moveme.ID)
{
	moveme.ID = 0;
}
Texture3D::~Texture3D()
{
	glDeleteTextures (1,&ID);
	GLErrorCheck ();
}

Texture3D &Texture3D::operator= (Texture3D &&moveme)
{
	ID = moveme.ID;
	_Width = moveme._Width;
	_Height = moveme._Height;
	_Depth = moveme._Depth;

	moveme.ID = 0;
	return *this;
}

void Texture3D::BuildTexture (unsigned int width, unsigned int height, unsigned int depth, const TextureFiltering &filtering, const TextureFormat &format)
{
	Bind ();

	_Filtering = filtering;
	_Format = format;

	glTexParameterf (GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLErrorCheck ();
	
	if (filtering != TextureFiltering::None)
	{
		glTexParameterf (GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		GLErrorCheck ();
	}
	else
	{
		glTexParameterf (GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		GLErrorCheck ();
	}

	if (filtering == TextureFiltering::Anisotropic)
	{
		glTexParameterf (GL_TEXTURE_3D, GL_EXT_texture_filter_anisotropic,2.0f); //Get from context?
		GLErrorCheck ();
	}

	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	GLErrorCheck ();

	glTexImage3D (GL_TEXTURE_3D,0,format.InternalGLFormat (),width,height,depth,0,format.Format (),format.Type (),nullptr);
	GLErrorCheck ();
}

void Texture3D::SetData (TextureDataFormat format, void *data)
{
	Bind ();
	cout << &glTexSubImage3D << endl;
	cout << hex <<  format.Format () << ", " << hex << format.DataType () << endl;
	glTexSubImage3D (GL_TEXTURE_3D,0,0,0,0,_Width, _Height,_Depth,format.Format (),format.DataType (),data);
	GLErrorCheck ();
	if (Filtering () != TextureFiltering::None)
	{
		glGenerateMipmap (GL_TEXTURE_3D);
		GLErrorCheck ();
	}
	UnBind ();
}

bool Texture3D::HasMipMaps () const
{
	return false;
}

void Texture3D::Bind () const
{
	glBindTexture (GL_TEXTURE_3D,ID);
	GLErrorCheck ();
}
void Texture3D::Bind (int Register) const
{
	glActiveTexture (GL_TEXTURE0 + Register);
	GLErrorCheck ();
	glBindTexture (GL_TEXTURE_3D,ID);
	GLErrorCheck ();
}

void Texture3D::UnBind () const
{
	glBindTexture (GL_TEXTURE_3D,0);
	GLErrorCheck ();
}

}}