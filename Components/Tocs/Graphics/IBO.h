#pragma once

#include <string>


namespace Tocs {
namespace Graphics {

class IndexFormat
{
	enum InternalEnum
	{
		sixteen,
		thirtytwo
	};
	InternalEnum Internal;

	IndexFormat (InternalEnum filtering)
		: Internal(filtering)
	{
	}
public:
	const static IndexFormat SixteenBit;
	const static IndexFormat ThirtyTwoBit;

	bool IsSupported () const;
	std::string ToString () const;

	bool operator ==  (const IndexFormat op2) const {return Internal == op2.Internal;}
	bool operator !=  (const IndexFormat op2) const {return Internal != op2.Internal;}

	unsigned int GetSize () const;

	int GLType () const;
};

class IBO
{
	unsigned int ID;
	IndexFormat Format;
	int IndiceCount;
	void Build ();
	IBO (const IBO &);
public:
	IBO(int indicecount);
	IBO(int indicecount, IndexFormat format);
	IBO(IBO &&moveme);
	~IBO();

	void Write (unsigned int *indices, int indexcount);
	void Write (unsigned int *indices, int indexcount, int offset);
	void Write (unsigned short *indices, int indexcount);
	void Write (unsigned short *indices, int indexcount, int offset);

	void Bind () const;
	void UnBind () const;

	const IndexFormat &GetFormat () const { return Format; }
	const unsigned int GetID () const { return ID; }
	const unsigned int GetIndexCount () const { return IndiceCount; }

	IBO &operator= (IBO &&moveme);

};

}}