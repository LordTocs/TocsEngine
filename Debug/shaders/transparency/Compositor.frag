#include "shaders/transparency/Compositing.hglsl"

void main ()
{
	AddFrag(Evaluate(),gl_FragCoord.z,0);
}