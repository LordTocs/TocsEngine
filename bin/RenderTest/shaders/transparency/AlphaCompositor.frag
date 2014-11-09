#include "shaders/transparency/Compositing.hglsl"

in vec3 VertPos;

void main ()
{
	AddFrag(Evaluate(VertPos),gl_FragCoord.z,0);
}