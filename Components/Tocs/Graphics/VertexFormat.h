#pragma once
#include <string>
#include <vector>
namespace Tocs {
namespace Graphics {

class VertexType
{
	enum InternalFormat
	{
		vec3,
		vec2
	};
	InternalFormat Internal;

	VertexType (InternalFormat format)
		: Internal(format) {}
public:
	const static VertexType Vec3;
	const static VertexType Vec2;

	unsigned int GetSize () const;
	int GetComponentCount () const;
	int GetGLFormat () const;

	bool operator ==  (const VertexType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const VertexType &op2) const {return Internal != op2.Internal;}
};

class VertexMember
{
	std::string Name;
	VertexType Type;
	bool Normalized;
public:
	VertexMember (std::string name, const VertexType &type, bool normalized)
		: Name (name), Type(type), Normalized(normalized)
	{}

	unsigned int Size () const { return Type.GetSize (); }
	const std::string &GetName () const { return Name; }
	bool IsNormalized () const { return Normalized; }
	const VertexType &GetType () const { return Type; }
};

class VertexFormat
{
	unsigned int Size;
	std::vector <VertexMember> Members;
public:
	VertexFormat();

	unsigned int SizeInBytes () const { return Size; }

	void AddMember (const std::string &name, const VertexType &type);
	void AddMember (const std::string &name, const VertexType &type, bool normalized);

	void Apply () const;
};

}}