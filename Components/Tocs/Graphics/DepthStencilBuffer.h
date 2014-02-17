#pragma once
#include <string>

namespace Tocs {
namespace Graphics {

class DepthStencilFormat
{
	enum InternalFormat
	{
		depth24stencil8,
		depth32stencil8
	};
	DepthStencilFormat (InternalFormat format) : Internal (format) {}

	InternalFormat Internal;
public:
	const static DepthStencilFormat D24S8;
	const static DepthStencilFormat D32S8;

	bool IsSupported () const;
	std::string ToString () const;

	unsigned int InternalGLFormat () const;
	unsigned int Format () const;
	unsigned int Type () const;

	bool operator ==  (const DepthStencilFormat &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const DepthStencilFormat &op2) const {return Internal != op2.Internal;}
};

class DepthStencilBuffer
{
	unsigned int ID;

	void BuildBuffer (int width, int height, const DepthStencilFormat &format);

	DepthStencilFormat _Format;

	int _Width;
	int _Height;
public:
	DepthStencilBuffer(int width, int height, const DepthStencilFormat &format);
	DepthStencilBuffer(DepthStencilBuffer &&moveme);
	~DepthStencilBuffer();

	void Bind () const;
	void Bind (int Register) const;
	void UnBind () const;

	int Width () const { return _Width; };
	int Height () const { return _Height; };

	int GetID () const { return ID; }

	void ReadData(DepthStencilFormat format, void *data) const;

	void SaveDebug(const std::string &filename);
};

}}