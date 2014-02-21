 #version 130
precision highp float;

//Uniforms
uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

//Per vertex input
in vec4 InPosition;

void main()
{
	gl_Position = (Projection * View * World) * InPosition;
} 