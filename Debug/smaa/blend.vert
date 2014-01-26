#include "smaa/vertheader.hglsl"

in vec4 pos;
in vec2 tex;
out vec2 texcoord;
out vec2 pixcoord;
out vec4 offset[3];
out vec4 dummy2;

void main()
{
  texcoord = tex;
  gl_Position = pos;
  SMAABlendingWeightCalculationVS(texcoord, pixcoord, offset);
}