#version 130
precision highp float;

//Uniforms
uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

//Per vertex input
in vec4 InPosition;
in vec2 InTextureCoordinate; 
in vec3 InNormal;

//Outputs to the Pixel Shader
out vec3 GeometryNormal;
out vec2 Depth;
out vec2 TextureCoordinate;

void main()
{
	GeometryNormal = (mat3 (View) * mat3 (World) * InNormal);
	TextureCoordinate = InTextureCoordinate;
	gl_Position = (Projection * View * World) * InPosition;
	Depth =  gl_Position.zw;
} 

