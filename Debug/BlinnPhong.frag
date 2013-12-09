#version 140

uniform sampler2D DiffuseTexture;
uniform float SpecularPower;
uniform float SpecularIntensity;
uniform vec4  SpecularColor;

in vec2 TextureCoordinate;
in vec4 GeometryNormal;
vec4 BlinnPhong (vec4 LightDir, vec4 ViewDir, vec4 LightColor, float Attenuation, vec4 Normal, vec4 Diffuse, vec4 Specular, float SpecularPower, float SpecularIntensity)
{
	float NdotL = dot(LightDir,Normal);
	float intensity = clamp(NdotL,0,1);
	
	vec4 result = intensity * Diffuse * Attenuation * vec4(LightColor.rgb,1);
	
	vec4 Half = normalize(LightDir + ViewDir);
	float NdotH = dot (Normal,Half);
	intensity = pow(clamp (NdotH,0,1), SpecularPower);
	
	result += intensity * Specular * SpecularIntensity * Attenuation * vec4(LightColor.rgb,1);

	return result;
}

vec4 diffusecolor;

void ShadePrep ()
{
	diffusecolor = texture2D(DiffuseTexture,TextureCoordinate);
}

vec4 Shade (vec4 LightDir, vec4 ViewDir, vec4 LightColor, float Attenuation)
{
	return BlinnPhong (LightDir, ViewDir, LightColor, Attenuation, normalize(GeometryNormal), diffusecolor, SpecularColor, SpecularPower, SpecularIntensity);
}
