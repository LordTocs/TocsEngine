#include "VertexFormat.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {

const VertexType VertexType::Vec3 (vec3);
const VertexType VertexType::Vec2 (vec2);

unsigned int VertexType::GetSize () const
{
	switch (Internal)
	{
	case vec3:
		return 12;
	case vec2:
		return 8;
	}
}

int VertexType::GetComponentCount () const
{
	switch (Internal)
	{
	case vec3:
		return 3;
	case vec2:
		return 2;
	}
}
int VertexType::GetGLFormat () const
{
	switch (Internal)
	{
	case vec3:
		return GL_FLOAT;
	case vec2:
		return GL_FLOAT;
	}
}

VertexFormat::VertexFormat()
	: Size (0)
{

}

void VertexFormat::AddMember (const std::string &name, const VertexType &type)
{
	Members.push_back (VertexMember (name,type,true));
	Size += Members[Members.size () - 1].Size ();
}
void VertexFormat::AddMember (const std::string &name, const VertexType &type, bool normalized)
{
	Members.push_back(VertexMember (name,type,normalized));
	Size += Members[Members.size () - 1].Size ();
}

void VertexFormat::Apply () const 
{
	int index = 0;
	unsigned int Offset = 0;
	for (auto i = Members.begin (); i != Members.end (); ++i)
	{
		glEnableVertexAttribArray (index);
		GLErrorCheck ();
		glVertexAttribPointer (index,(*i).GetType ().GetComponentCount (), (*i).GetType ().GetGLFormat (),(*i).IsNormalized (),Size,reinterpret_cast <GLvoid *> (Offset));
		GLErrorCheck ();
		cout << "ApplyAttrib: " << index << " " << (*i).GetName() << " "  << (*i).GetType ().GetComponentCount () << " size: " << (*i).GetType ().GetSize () << " offset: " << Offset << endl;
		Offset += (*i).Size();
		++index;
	}
}

}}
