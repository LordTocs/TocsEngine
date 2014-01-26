#pragma once
#include <string>
#include <vector>
#include "GPUTypes.h"
namespace Tocs {
namespace Graphics {

class VertexMember
{
	std::string Name;
	GPUType Type;
	bool Normalized;
	bool InstanceType;
public:
	VertexMember(std::string name, const GPUType &type, bool normalized, bool instancetype)
		: Name(name), Type(type), Normalized(normalized), InstanceType(instancetype)
	{}

	unsigned int Size () const { return Type.SizeInBytes (); }
	const std::string &GetName () const { return Name; }
	bool IsNormalized () const { return Normalized; }
	bool IsInstanceType() const { return InstanceType; }
	const GPUType &GetType() const { return Type; }
};

class VertexFormat
{
	unsigned int Size;
	std::vector <VertexMember> Members;
public:
	VertexFormat();

	unsigned int SizeInBytes () const { return Size; }

	void AddMember(const std::string &name, const GPUType &type);
	void AddMember(const std::string &name, const GPUType &type, bool normalized);
	void AddMember(const std::string &name, const GPUType &type, bool normalized, bool instancetype);

	void Apply () const;
};

}}