#pragma once

namespace Tocs {
namespace Graphics {

class VBO
{
	unsigned int ID;
	int Size;

	void Build ();
public:
	VBO(int size);
	VBO(VBO &&moveme);
	~VBO();

	void WriteData (void *data, int size);
	void WriteData (void *data, int size, int offset);

	template <class T>
	void Write (T *data, int count) { WriteData (static_cast <void *> (data),count * sizeof(T)); }
	template <class T>
	void Write (T *data, int count, int offset) { WriteData (static_cast <void *> (data),count * sizeof(T), offset * sizeof (T)); }

	int GetID () const { return ID; }

	int GetSize () const { return Size; }

	void Bind () const;
	void UnBind () const;

	VBO &operator= (VBO &&moveme);
};

}}