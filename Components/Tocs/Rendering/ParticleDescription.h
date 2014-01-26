#pragma once
#include <string>
#include <vector>
#include <Tocs/Graphics/GPUTypes.h>

namespace Tocs {
namespace Rendering {

class ParticleDescription
{
	unsigned int TotalSize;
public:
	class Variable
	{
		std::string Name_;
		Graphics::GPUType Type_;
		unsigned int Offset_;
	public:
		Variable(std::string name, Graphics::GPUType type, unsigned int offset)
			: Name_(name), Type_(type), Offset_(offset) {}

		const std::string &Name() const { return Name_; }
		const Graphics::GPUType &Type() const { return Type_; }
		unsigned int Offset() const { return Offset_; }

	};

	ParticleDescription();

	std::vector<Variable> Variables;

	void AddVariable(const std::string &name, Graphics::GPUType type);

	unsigned int ParticleDataSize() const { return TotalSize; }
};

}}