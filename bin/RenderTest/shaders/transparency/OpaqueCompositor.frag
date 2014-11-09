#version 140

out vec4 Output;

in vec3 VertPos;

vec4 Evaluate (vec3 ViewPos);

void main ()
{
	Output = Evaluate(VertPos);
}