#include "smaa/vertheader.hglsl"

in vec4 pos;
in vec2 tex;
out vec2 texcoord;
out vec4 offset;
out vec4 dummy2;

void main()
{
  texcoord = tex;
  gl_Position = pos;
  SMAANeighborhoodBlendingVS(texcoord, offset);
}