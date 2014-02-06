#include "VertexFormat.h"
#include "GLHeader.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

namespace Tocs {
namespace Graphics {


VertexFormat::VertexFormat()
: Size(0), InputOffset(0)
{

}

VertexFormat::VertexFormat(unsigned int inputoffset)
: Size(0), InputOffset(inputoffset)
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

void VertexFormat::AddMember(const std::string &name, const GPUType &type, bool normalized, bool instancetype)
{
	Members.push_back(VertexMember(name, type, normalized, instancetype));
	Size += Members[Members.size() - 1].Size();
}

void VertexFormat::Apply () const 
{
	int index = InputOffset;
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

void VertexFormat::ApplyStd140() const
{
	//Calculate stride
	unsigned int std140size = 0;
	unsigned int structalignment = Graphics::GPUType::Vector4.Std140BaseAlignment();
	for (auto i = Members.begin(); i != Members.end(); ++i)
	{
		structalignment = std::max(i->GetType().Std140BaseAlignment(), structalignment);
		unsigned int alignment = i->GetType().Std140BaseAlignment();
		unsigned int padding = (std140size % alignment);
		if (padding != 0)
		{
			padding = alignment - padding;
		}
		std140size += padding;
		std140size += i->GetType().SizeInBytes();
	}

	unsigned int structpadding = (std140size % structalignment);
	if (structpadding != 0)
	{
		structpadding = structalignment - structpadding;
	}
	std140size += structpadding;


	int index = InputOffset;
	unsigned int Offset = 0;
	for (auto i = Members.begin(); i != Members.end(); ++i)
	{
		unsigned int alignment = i->GetType().Std140BaseAlignment();
		unsigned int padding = (Offset % alignment);
		if (padding != 0)
		{
			padding = alignment - padding;
		}
		Offset += padding;

		glEnableVertexAttribArray(index);
		GLErrorCheck();
		glVertexAttribPointer(index, (*i).GetType().ComponentCount(), (*i).GetType().GLFormat(), (*i).IsNormalized(), std140size, reinterpret_cast <GLvoid *> (Offset));
		GLErrorCheck();
		if (i->IsInstanceType())
			glVertexAttribDivisor(index, 1);

		//cout << "ApplyAttrib: " << index << " " << (*i).GetName() << " "  << (*i).GetType ().GetComponentCount () << " size: " << (*i).GetType ().GetSize () << " offset: " << Offset << endl;
		Offset += (*i).Size();
		++index;
	}
}

}}
