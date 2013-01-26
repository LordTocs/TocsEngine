#pragma once
#include <vector>
#include <string>
#include "Image.h"

namespace Tocs {
namespace Drawing {

class AnimatedGif
{
public:
	class Frame
	{
		Image FrameImage;
		float Time;
	public:
		Frame (const Image &frame, float time)
			: FrameImage (frame), Time (time)
		{}

		Frame (unsigned int width, unsigned int height, float time)
			: FrameImage (width,height), Time (time)
		{}

		Frame (Frame &&moveme)
			: FrameImage (std::move(moveme.FrameImage)), Time(moveme.Time)
		{}

		const Image &GetImage () const { return FrameImage; }
		Image &GetImage () { return FrameImage; }

		float GetTime () const { return Time; }
	};
private:
	unsigned int Width;
	unsigned int Height;
	std::vector<Frame> Frames;
public:
	AnimatedGif(unsigned int width, unsigned int height)
		: Width(width), Height(height) {}

	void AddFrame (const Image &image, float time);

	void WriteToFile (const std::string &filename);


};

}}