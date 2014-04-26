#version 130
precision highp float;

uniform sampler2D Texture;

in vec2 TextureCoordinate;

out vec4 Result;

void main ()
{
	Result = texture2D (Texture,TextureCoordinate);
}