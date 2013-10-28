#pragma once

namespace Tocs {
namespace Graphics {

class TBO
{
	unsigned int ID;

	void Build (unsigned int bytes);
public:
	TBO(unsigned int bytes);
	TBO(TBO &&moveme);
	~TBO();

	TBO &operator= (TBO &&moveme);

	int GetID () const { return ID; }

	void Bind ();
	void UnBind ();

	void WriteData (unsigned char *data, unsigned int bytes);
	void WriteData (unsigned char *data, unsigned int bytes, unsigned int offset);
};

}}