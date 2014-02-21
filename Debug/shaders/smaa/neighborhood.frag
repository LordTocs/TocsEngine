#include "shaders/smaa/fragheader.hglsl"

uniform sampler2D albedo_tex;
uniform sampler2D blend_tex;
in vec2 texcoord;
in vec4 offset;

out vec4 color;
void main()
{
  color = SMAANeighborhoodBlendingPS(texcoord, offset, albedo_tex, blend_tex);
}