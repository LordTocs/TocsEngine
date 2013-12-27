#version 140
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
out vec3 VertPos;

void main()
{
	GeometryNormal = (mat3 (View) * mat3 (World) * InNormal.xyz);
	TextureCoordinate = InTextureCoordinate;
	vec4 vpos = (View * World) * InPosition;
	VertPos = vpos.xyz / vpos.w;
	gl_Position = (Projection * vpos);
	Depth =  gl_Position.zw;
} 

