#version 130
precision highp float;

//Per vertex input
in vec4 InPosition;
in vec2 InTextureCoordinate; 
in vec3 InNormal;

//Outputs to the Pixel Shader
out vec3 Normal;
out vec2 TextureCoordinate;

void main()
{
	Normal = InNormal;
	TextureCoordinate = InTextureCoordinate;
	gl_Position = InPosition;
} 

