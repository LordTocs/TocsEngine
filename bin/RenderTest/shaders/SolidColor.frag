#version 130
precision highp float;

uniform vec4 Color;

out vec4 ColorOut;

void main ()
{
	ColorOut = Color;
}