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
	bool IntegerType;
public:
	VertexMember(std::string name, const GPUType &type, bool normalized, bool instancetype, bool integertype)
		: Name(name), Type(type), Normalized(normalized), InstanceType(instancetype), IntegerType(integertype)
	{}

	unsigned int Size () const { return Type.SizeInBytes (); }
	const std::string &GetName () const { return Name; }
	bool IsNormalized () const { return Normalized; }
	bool IsInstanceType() const { return InstanceType; }
	bool IsIntegerType() const { return IntegerType; }
	const GPUType &GetType() const { return Type; }
};

class VertexFormat
{
	unsigned int Size;
	std::vector <VertexMember> Members;
	unsigned int InputOffset;
public:
	VertexFormat();
	VertexFormat(unsigned int inputoffset);

	unsigned int SizeInBytes () const { return Size; }

	void AddMember(const std::string &name, const GPUType &type);
	void AddMember(const std::string &name, const GPUType &type, bool normalized);
	void AddMember(const std::string &name, const GPUType &type, bool normalized, bool instancetype);
	void AddMember(const std::string &name, const GPUType &type, bool normalized, bool instancetype, bool integertype);

	void Apply () const;
	void ApplyStd140() const;
};

}}