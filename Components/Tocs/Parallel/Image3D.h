#pragma once
#include "ImageFormat.h"
#include "Enums.h"
#include "Context.h"
#include "IntermediateEvent.h"
#include <Tocs/Drawing/Image.h>
#include <vector>
struct _cl_mem;

namespace Tocs {

namespace Graphics { class Texture3D; }

namespace Parallel {

class Image3D
{
	_cl_mem *ImagePtr;
	ImageFormat Format;
	Image3D (const Image3D &);
	Image3D &operator =(const Image3D &);
public:
	Image3D(unsigned int width, unsigned int height, unsigned int depth, const ImageFormat &format, const BufferAccess &access, Context &context);
	Image3D(Graphics::Texture3D &linkme,const BufferAccess &access, Context &context);
	Image3D(Image3D &&moveme);
	~Image3D();

	Image3D &operator= (Image3D &&moveme);

	unsigned int Width () const;
	unsigned int Height () const;
	unsigned int Depth () const;
	_cl_mem *GetCLPtr () const { return ImagePtr; }

	class WriteEvent : public IntermediateEvent
	{
		const void *Data;
		unsigned int OffsetX, OffsetY, OffsetZ;
		unsigned int Width, Height, Depth;
		Image3D &Img;
	public:
		WriteEvent (Image3D &img, unsigned int offsetx, unsigned int offsety, unsigned int offsetz, unsigned int width, unsigned int height,unsigned int depth, const void *data)
			: Img(img), Data(data), OffsetX(offsetx), OffsetY(offsety), OffsetZ(offsetz), Width(width), Height(height), Depth(depth)
		{}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			//queue.WriteImage2D (Img,OffsetX,OffsetY,Width,Height,Data,dependants);
		}
	};

	class ReadEvent : public IntermediateEvent
	{
		void *Dest;
		unsigned int OffsetX, OffsetY, OffsetZ;
		unsigned int Width, Height, Depth;
		Image3D &Img;
	public:
		ReadEvent (Image3D &img, unsigned int offsetx, unsigned int offsety, unsigned int offsetz, unsigned int width, unsigned int height,unsigned int depth, void *dest)
			: Img(img), Dest(dest), OffsetX(offsetx), OffsetY(offsety), OffsetZ(offsetz), Width(width), Height(height), Depth(depth)
		{}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			queue.ReadImage3D (Img,OffsetX,OffsetY,OffsetZ,Width,Height,Depth,Dest,dependants);
		}
	};

	class AcquireEvent : public IntermediateEvent
	{
		Image3D &Img;
	public:
		AcquireEvent (Image3D &image)
			: Img(image) {}

		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			queue.Acquire(Img,dependants);
		}
	};

	class ReleaseEvent : public IntermediateEvent
	{
		Image3D &Img;
	public:
		ReleaseEvent (Image3D &image)
			: Img(image) {}

		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			queue.Release(Img,dependants);
		}
	};

	AcquireEvent AcquireGL ()
	{
		return AcquireEvent (*this);
	}

	ReleaseEvent ReleaseGL ()
	{
		return ReleaseEvent (*this);
	}

	template <class T>
	ReadEvent Read (std::vector <T> &dest)
	{
		unsigned int elementcount = (Format.PixelSizeInBytes () * Width () * Height () * Depth ()) / sizeof(T); //Add chec to make sure its divisible later
		dest.resize (elementcount);
		return ReadEvent (*this,0,0,0,Width(),Height(),Depth(),&dest[0]);
	}

	template <class T>
	WriteEvent Write (const std::vector <T> &data)
	{
		unsigned int elementcount = (Format.PixelSizeInBytes () * Width () * Height () * Depth ()) / sizeof(T); //Add chec to make sure its divisible later

		if (data.size () != elementcount)
			throw "WTF";
		
		return WriteEvent (*this,0,0,0,Width(),Height(),Depth(),&data[0]);
	}



	const ImageFormat &GetFormat () const { return Format; }
};

}}