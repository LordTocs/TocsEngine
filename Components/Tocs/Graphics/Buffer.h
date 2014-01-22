#pragma once
#include <vector>

namespace Tocs {
namespace Graphics {

class BufferTarget
{
	unsigned int Internal;

	BufferTarget (unsigned int format) : Internal(format) {}

public:
	const static BufferTarget Vertex;
	const static BufferTarget Index;
	const static BufferTarget Texture;
	const static BufferTarget Uniform;
	const static BufferTarget TransformFeedback;
	const static BufferTarget Read;
	const static BufferTarget Write;
	const static BufferTarget AtomicCounter;
	const static BufferTarget ShaderStorage;

	unsigned int GLValue () const;

	bool operator ==  (const BufferTarget &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const BufferTarget &op2) const {return Internal != op2.Internal;}

	std::string ToString () const;
};

class BufferBase
{
	unsigned int ID;
#ifdef _DEBUG
	class Binding
	{
	public:
		int Target;
		int Base;
		Binding () : Base (-1), Target (0) {}
	};
	Binding CurrentBinding;
#endif
	 BufferBase (const BufferBase &);
public:
	void Write (const void *bytes, unsigned int size);
	void Write (const void *bytes, unsigned int offset, unsigned int size);
	void Read (void *bytes, unsigned int size) const;
	void Read (void *bytes, unsigned int offset, unsigned int size) const;

	//BROKEN BROKEN BROKEN
	void Resize (unsigned int bytes);

	void Build (unsigned int bytes);

	BufferBase(unsigned int bytes);
	BufferBase(BufferBase &&moveme);
	virtual ~BufferBase();

	BufferBase &operator= (BufferBase && moveme);

	unsigned int GetID () const { return ID; }

	void Bind (BufferTarget target) const;
	void UnBind () const;
	void BindTo (BufferTarget target, unsigned int index) const;
	void BindToRange (BufferTarget target, unsigned int index, unsigned int offset, unsigned int length) const;

	void CopyTo (BufferBase &other) const;

	void *Map();
	void UnMap();

	unsigned int SizeInBytes () const;
};
 
template <class T>
class Buffer : public BufferBase
{
public:
	Buffer(unsigned int count)
		: BufferBase (count * sizeof(T)) {}

	Buffer(Buffer &&moveme)
		: BufferBase(std::move(moveme))
	{}

	Buffer(const Buffer &) = delete;

	void Write (const T *values, unsigned int count)
	{ BufferBase::Write (static_cast<const void *> (values),count * sizeof(T)); }

	void Write (const T *values, unsigned int offset, unsigned int count)
	{ BufferBase::Write (static_cast<const void *> (values), offset * sizeof(T), count * sizeof(T));	}

	void Write (const std::vector<T> &values)
	{ Write (&values[0],values.size ());}


	void WriteCompletely(const std::vector<T> &values)
	{
		if (values.size() == 0)
			return;

		if (Size() < values.size())
			Build(values.size());

		Write(values);
	}

	void Read (T *destination, unsigned int count) const
	{ BufferBase::Read (static_cast<void*> (destination),count * sizeof(T)); }

	void Read (T *destination, unsigned int offset, unsigned int count) const
	{ BufferBase::Read (destination,offset * sizeof(T), count * sizeof(T)); }

	void Read (std::vector<T> &destination)
	{
		if (destination.size () <  Size ())
		{
			destination.resize (Size());
		}

		Read (&destination[0],destination.size());
	}

	unsigned int Size () const { return SizeInBytes () / sizeof(T); }

	void Resize (unsigned int count)
	{ BufferBase::Resize(count * sizeof(T)); }

	void Build (unsigned int count)
	{ BufferBase::Build (count * sizeof(T)); }

	T *Map() { return static_cast<T*>(BufferBase::Map()); }
};


}}

