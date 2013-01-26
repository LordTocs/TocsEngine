#include "Color.h"

namespace Tocs {
namespace Math {


static char HexDigit (char a)
{
	if (a >= '0' && a <= '9')
		return a - '0';
	if (a >= 'a' && a <= 'f')
		return a - 'a' + 10;
	if (a >= 'A' && a <= 'F')
		return a - 'A' + 10;
	return 0;
}
static char Hex (char a, char b)
{
	return HexDigit(a) * 16 + HexDigit(b);
}

Color Color::FromHex(const std::string &hex)
{
	if (hex.length () == 7)
		return Color (Hex (hex[1],hex[2]),Hex(hex[3],hex[4]),Hex(hex[5],hex[6]));
	if (hex.length () == 9)
		return Color (Hex (hex[1],hex[2]),Hex(hex[3],hex[4]),Hex(hex[5],hex[6]),Hex(hex[7],hex[8]));
	return Color ();
}

}}