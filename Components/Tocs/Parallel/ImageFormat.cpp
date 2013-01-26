#include "ImageFormat.h"
#include <CL/cl.h>
namespace Tocs {
namespace Parallel {

const ImageFormat ImageFormat::RGBA8 (rgba8);
const ImageFormat ImageFormat::ARGB8 (argb8);
const ImageFormat ImageFormat::BGRA8 (bgra8);
const ImageFormat ImageFormat::A8SN (a8sn);
const ImageFormat ImageFormat::A16SN (a16sn);
const ImageFormat ImageFormat::A8UN (a8un);
const ImageFormat ImageFormat::A16UN (a16un);
const ImageFormat ImageFormat::A8S (a8s);
const ImageFormat ImageFormat::A16S (a16s);
const ImageFormat ImageFormat::A32S (a32s);
const ImageFormat ImageFormat::A8U (a8u);
const ImageFormat ImageFormat::A16U (a16u);
const ImageFormat ImageFormat::A32U (a32u);
const ImageFormat ImageFormat::AFLOAT (afloat);
const ImageFormat ImageFormat::AHALF (ahalf);
const ImageFormat ImageFormat::RGFLOAT (rgfloat);

unsigned int ImageFormat::ChannelOrder () const
{
	switch (Internal)
	{
	case rgba8:
		return CL_RGBA;
	case argb8:
		return CL_ARGB;
	case bgra8:
		return CL_BGRA;
	case a8sn:
		return CL_A;
	case a16sn:
		return CL_A;
	case a8un:
		return CL_A;
	case a16un:
		return CL_A;
	case a8s:
		return CL_A;
	case a16s:
		return CL_A;
	case a32s:
		return CL_A;
	case a8u:
		return CL_A;
	case a16u:
		return CL_A;
	case a32u:
		return CL_A;
	case afloat:
		return CL_A;
	case ahalf:
		return CL_A;
	case rgfloat:
		return CL_RG;
	}
	return 0;
}

unsigned int ImageFormat::ChannelType () const
{
	switch (Internal)
	{
	case rgba8:
		return CL_UNORM_INT8;
	case argb8:
		return CL_UNORM_INT8;
	case bgra8:
		return CL_UNORM_INT8;
	case a8sn:
		return CL_SNORM_INT8;
	case a16sn:
		return CL_SNORM_INT16;
	case a8un:
		return CL_UNORM_INT8;
	case a16un:
		return CL_UNORM_INT16;
	case a8s:
		return CL_SIGNED_INT8;
	case a16s:
		return CL_SIGNED_INT16;
	case a32s:
		return CL_SIGNED_INT32;
	case a8u:
		return CL_UNSIGNED_INT8;
	case a16u:
		return CL_UNSIGNED_INT16;
	case a32u:
		return CL_UNSIGNED_INT32;
	case afloat:
		return CL_FLOAT;
	case ahalf:
		return CL_HALF_FLOAT;
	case rgfloat:
		return CL_FLOAT;
	}
	return 0;
}


unsigned int ImageFormat::PixelSizeInBytes () const
{
	switch (Internal)
	{
	case rgba8:
		return 4;
	case argb8:
		return 4;
	case bgra8:
		return 4;
	case a8sn:
		return 1;
	case a16sn:
		return 2;
	case a8un:
		return 1;
	case a16un:
		return 2;
	case a8s:
		return 1;
	case a16s:
		return 2;
	case a32s:
		return 4;
	case a8u:
		return 1;
	case a16u:
		return 2;
	case a32u:
		return 4;
	case afloat:
		return 4;
	case ahalf:
		return 2;
	case rgfloat:
		return 8;
	}
	return 0;
}
}}