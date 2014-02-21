#include "shaders/smaa/fragheader.hglsl"

uniform sampler2D edge_tex;
uniform sampler2D area_tex;
uniform sampler2D search_tex;
in vec2 texcoord;
in vec2 pixcoord;
in vec4 offset[3];
in vec4 dummy2;

out vec4 color;
void main()
{
  color = SMAABlendingWeightCalculationPS(texcoord, pixcoord, offset, edge_tex, area_tex, search_tex, ivec4(0)); 
}