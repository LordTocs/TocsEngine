#include "VertexFormat.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {


VertexFormat::VertexFormat()
	: Size (0)
{

}

void VertexFormat::AddMember (const std::string &name, const GPUType &type)
{
	Members.push_back (VertexMember (name,type,true,false));
	Size += Members[Members.size () - 1].Size ();
}
void VertexFormat::AddMember(const std::string &name, const GPUType &type, bool normalized)
{
	Members.push_back(VertexMember (name,type,normalized,false));
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
		glVertexAttribPointer (index,(*i).GetType ().ComponentCount (), (*i).GetType ().GLFormat (),(*i).IsNormalized (),Size,reinterpret_cast <GLvoid *> (Offset));
		GLErrorCheck ();
		if (i->IsInstanceType())
			glVertexAttribDivisor(index, 1);

		//cout << "ApplyAttrib: " << index << " " << (*i).GetName() << " "  << (*i).GetType ().GetComponentCount () << " size: " << (*i).GetType ().GetSize () << " offset: " << Offset << endl;
		Offset += (*i).Size();
		++index;
	}
}

}}
