#include "shaders/smaa/fragheader.hglsl"

uniform sampler2D albedo_tex; 
in vec2 texcoord; 
in vec4 offset[3]; 

out vec4 color; 

void main()
{ 
	color = vec4(SMAALumaEdgeDetectionPS(texcoord, offset, albedo_tex),0,1);
}
