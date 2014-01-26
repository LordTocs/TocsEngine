#include "smaa/vertheader.hglsl"
in vec4 pos;
in vec2 tex;
out vec2 texcoord;
out vec4 offset[3];
void main()
{
  texcoord = tex;
  gl_Position = pos;
  SMAAEdgeDetectionVS(texcoord, offset);
}