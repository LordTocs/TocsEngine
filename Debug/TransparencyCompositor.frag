#version 140

out vec4 Color;

vec4 Evaluate ();

void main ()
{
	Color = Evaluate();
}