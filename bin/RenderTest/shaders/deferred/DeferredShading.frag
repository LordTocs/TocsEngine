#version 420
#include "shaders/brdf/blinnphong.hglsl"
#include "shaders/lighting/TiledLighting.hglsl"

uniform mat4 InvProjection;
uniform sampler2D ColorBuffer;
uniform sampler2D NormalBuffer;
uniform sampler2D SpecularBuffer;
uniform sampler2D DepthBuffer;

vec4 DiffuseColor;
vec4 SpecularColor;
float SpecularPower;
float SpecularIntensity;

vec3 Normal;

in vec2 TextureCoordinate;
out vec4 OutColor;

void ShadePrep ()
{
	//Sample GBuffer
	vec4 NormalData =   texture2D (NormalBuffer,TextureCoordinate);     //Get ALL the Normal data
	vec4 ColorData =    texture2D (ColorBuffer,TextureCoordinate);      //Get ALL the Color Data
	vec4 MaterialData = texture2D (SpecularBuffer,TextureCoordinate);   //Get All the Material Data
	
	DiffuseColor = vec4(ColorData.xyz,1.0);
	SpecularColor = vec4(MaterialData.xyz, 1.0);
	SpecularPower =  MaterialData.w;
	SpecularIntensity = NormalData.w;
	Normal = normalize (2.0 * NormalData.xyz  - 1.0);
}

vec4 ConstantShading(vec4 AmbientLight)
{
	return AmbientLight * DiffuseColor;
}

vec4 Shade (vec3 LightDir, vec3 ViewDir, vec3 LightColor, float Attenuation)
{
	return BlinnPhong (LightDir, ViewDir, LightColor, Attenuation, Normal, DiffuseColor, SpecularColor, SpecularPower, SpecularIntensity);
}

void main()
{
	float DepthNDC = texture2D (DepthBuffer, TextureCoordinate).x;

	vec2 ScreenCoord = vec2(2 * TextureCoordinate.x - 1, 2 * TextureCoordinate.y - 1);
	vec4 ViewPosition = InvProjection * vec4(ScreenCoord.x, ScreenCoord.y, DepthNDC, 1.0f);
	ViewPosition /= ViewPosition.w;

	OutColor = Evaluate(ViewPosition.xyz);
}
