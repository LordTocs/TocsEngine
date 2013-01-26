#pragma once
#include "ImageFormat.h"
#include "Enums.h"
#include "Context.h"
#include "IntermediateEvent.h"
#include <Tocs/Drawing/Image.h>
#include <vector>
struct _cl_mem;

namespace Tocs {

namespace Graphics { class Texture2D; }

namespace Parallel {

class Image2D
{
	_cl_mem *ImagePtr;
	ImageFormat Format;
	Image2D (const Image2D &);
	Image2D &operator =(const Image2D &);
public:
	Image2D(unsigned int width, unsigned int height, const ImageFormat &format, const BufferAccess &access, Context &context);
	Image2D(Tocs::Graphics::Texture2D &linkme, const BufferAccess &access, Context &context);
	Image2D(Image2D &&moveme);
	~Image2D();

	Image2D &operator= (Image2D &&moveme);


	unsigned int Width () const;
	unsigned int Height () const;
	_cl_mem *GetCLPtr () const { return ImagePtr; }

	class WriteEvent : public IntermediateEvent
	{
		const void *Data;
		unsigned int OffsetX, OffsetY;
		unsigned int Width, Height;
		Image2D &Img;
	public:
		WriteEvent (Image2D &img, unsigned int offsetx, unsigned int offsety, unsigned int width, unsigned int height, const void *data)
			: Img(img), Data(data), OffsetX(offsetx), OffsetY(offsety), Width(width), Height(height)
		{}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			queue.WriteImage2D (Img,OffsetX,OffsetY,Width,Height,Data,dependants);
		}
	};

	class ReadEvent : public IntermediateEvent
	{
		void *Dest;
		unsigned int OffsetX, OffsetY;
		unsigned int Width, Height;
		Image2D &Img;
	public:
		ReadEvent (Image2D &img, unsigned int offsetx, unsigned int offsety, unsigned int width, unsigned int height, void *dest)
			: Img(img), Dest(dest), OffsetX(offsetx), OffsetY(offsety), Width(width), Height(height)
		{}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			queue.ReadImage2D (Img,OffsetX,OffsetY,Width,Height,Dest,dependants);
		}
	};

	class AcquireEvent : public IntermediateEvent
	{
		Image2D &Img;
	public:
		AcquireEvent (Image2D &image)
			: Img(image) {}

		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			queue.Acquire(Img,dependants);
		}
	};

	class ReleaseEvent : public IntermediateEvent
	{
		Image2D &Img;
	public:
		ReleaseEvent (Image2D &image)
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
		unsigned int elementcount = (Format.PixelSizeInBytes () * Width () * Height ()) / sizeof(T); //Add chec to make sure its divisible later
		dest.resize (elementcount);
		return ReadEvent (*this,0,0,Width(),Height(),&dest[0]);
	}

	template <class T>
	WriteEvent Write (const std::vector <T> &data)
	{
		unsigned int elementcount = (Format.PixelSizeInBytes () * Width () * Height ()) / sizeof(T); //Add chec to make sure its divisible later

		if (data.size () != elementcount)
			throw "WTF";
		
		return WriteEvent (*this,0,0,Width(),Height(),&data[0]);
	}

	ReadEvent Read (Drawing::Image &image)
	{
		if (image.GetWidth () != Width () || image.GetHeight () != Height () || Format != ImageFormat::RGBA8)
			throw "WTF";
		return ReadEvent (*this,0,0,Width(),Height(),image.GetDataPtr ());
	}

	WriteEvent Write (Drawing::Image &image)
	{
		if (image.GetWidth () != Width () || image.GetHeight () != Height () || Format != ImageFormat::RGBA8)
			throw "WTF";
		return WriteEvent (*this,0,0,Width(),Height(),image.GetDataPtr ());
	}

	const ImageFormat &GetFormat () const { return Format; }
};

}}

