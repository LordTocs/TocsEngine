#version 400
uniform sampler2D Depth;

in vec2 TextureCoordinate;

void main ()
{
	float depth = texture2D(Depth,TextureCoordinate).r;
	gl_FragDepth = depth;
}