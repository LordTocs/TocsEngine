#pragma once

namespace Tocs {
namespace Graphics {

class UBO
{
	unsigned int ID;
public:
	UBO(unsigned int size);
	UBO(UBO &&moveme);
	~UBO();
	UBO &operator= (UBO &&moveme);

	int GetID () const { return ID; }

	void Bind () const;
	void Bind (unsigned int index) const;
	void UnBind () const;

	void WriteData (unsigned char *data, unsigned int bytes);
	void WriteData (unsigned char *data, unsigned int bytes, unsigned int offset);
};

}}

