#pragma once
#include <string>
namespace Tocs {
namespace Parallel {

class ImageFormat
{
	enum InternalFormat
	{
		rgba8,
		argb8,
		bgra8,
		a8sn,
		a16sn,
		a8un,
		a16un,
		a8s,
		a16s,
		a32s,
		a8u,
		a16u,
		a32u,
		afloat,
		ahalf,
		rgfloat

	};
	ImageFormat (InternalFormat format)
		: Internal (format) {}

	InternalFormat Internal;
public:
	const static ImageFormat RGBA8;
	const static ImageFormat ARGB8;
	const static ImageFormat BGRA8;
	const static ImageFormat A8SN;
	const static ImageFormat A16SN;
	const static ImageFormat A8UN;
	const static ImageFormat A16UN;
	const static ImageFormat A8S;
	const static ImageFormat A16S;
	const static ImageFormat A32S;
	const static ImageFormat A8U;
	const static ImageFormat A16U;
	const static ImageFormat A32U;
	const static ImageFormat AFLOAT;
	const static ImageFormat AHALF;
	const static ImageFormat RGFLOAT;

	unsigned int ChannelOrder () const;
	unsigned int ChannelType () const;
	unsigned int PixelSizeInBytes () const;

	bool operator ==  (const ImageFormat &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const ImageFormat &op2) const {return Internal != op2.Internal;}
};

}}