#pragma once
#include <string>
namespace Tocs {
namespace Math {

class Color
{
public:
	unsigned char R,G,B,A;

	Color()
		: R(0), G(0), B(0), A(0) {}
	Color(unsigned char r, unsigned char g, unsigned char b)
		: R(r), G(g), B(b), A(255) {}
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		: R(r), G(g), B(b), A(a) {}

	static Color FromHex(const std::string &hex);

	float RedNorm() const { return R / 255.0f; }
	float GreenNorm() const { return G / 255.0f; }
	float BlueNorm() const { return B / 255.0f; }
	float AlphaNorm() const { return A / 255.0f; }
};

Color operator* (Color color, float scalar);
Color operator* (float scalar, Color color);

}}