#version 130
precision highp float;

#define Roughness ColorData.w
#define SpecularPower MaterialData.w
#define SpecularIntensity NormalData.w
//#define Position gl_Vertex

uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform float LightIntensityCoefficient;
uniform float LightRadius;

uniform vec3 CameraPosition;

uniform mat4 InverseProjection;
uniform mat4 InverseView;

uniform sampler2D ColorBuffer;
uniform sampler2D NormalBuffer;
uniform sampler2D SpecularBuffer;
uniform sampler2D DepthBuffer;

uniform int ScreenWidth;
uniform int ScreenHeight;

//in vec2 ScreenPosition;
in vec4 FragPos;

out vec4 Result;

void main ()
{
	vec2 ScreenPosition = gl_FragCoord.xy;
	ScreenPosition.x /= ScreenWidth;
	ScreenPosition.y /= ScreenHeight;

	//Extract data from the GBuffer
	vec4 NormalData = texture2D (NormalBuffer,ScreenPosition);      //Get ALL the Normal data
	vec4 ColorData = texture2D (ColorBuffer,ScreenPosition);        //Get ALL the Color Data
	vec4 MaterialData = texture2D (SpecularBuffer,ScreenPosition);  //Get All the Material Data
	float DepthZoW = texture2D (DepthBuffer,ScreenPosition).x;         //Get the linear depth
	
	vec2 ScreenCoord = 2 * ScreenPosition - 1;
	
	vec4 ViewPosition4 = InverseView * InverseProjection * vec4(ScreenCoord.x, ScreenCoord.y,DepthZoW,1.0f);
	vec3 Position = ViewPosition4.xyz/ViewPosition4.w;
	
	//Calculate the Surface information
	vec3 Normal = normalize (2.0 * NormalData.xyz  - 1.0); //Convert from [0,1] to [-1,1]
	//vec3 Position = CameraPosition +  normalize (FragPos.xyz/FragPos.w - CameraPosition) * Depth;
	
	//Calculate lighting vectors
	vec3 LightVector = LightPosition - Position.xyz; //from fragment to light
	vec3 ViewVector = normalize (CameraPosition - Position); //from fragment to eye
	vec3 HalfVector = normalize (LightVector + ViewVector); //half vector for blinn
	
	//Point light specific
	float Attenuation = 1.0 - length(LightVector)/LightRadius; //calculate the falloff of the pointlight
	LightVector = normalize(LightVector); //normalize the LightVector for later use
	
	//Important Dot Products
	float NdL = max (0.0, dot (Normal,LightVector));
	float HdN = max (0.0, dot (HalfVector, Normal));
	
	//////////////////////////////////////////
	////////Oren-Nayar Calculations///////////
	//////////////////////////////////////////
	
	//Shamelessly stolen from GDNet Wiki...
	
	float gamma = dot (ViewVector - Normal * dot (ViewVector, Normal), LightVector - Normal * dot (LightVector, Normal));
	
	float RoughnessSquared = (Roughness) * (Roughness);

	float A = 1.0 - 0.5 * (RoughnessSquared / (RoughnessSquared + 0.57));
	float B = 0.45 * (RoughnessSquared / (RoughnessSquared + 0.09));
	
	float alpha = max (acos (dot (ViewVector,Normal)), acos (dot (LightVector, Normal)));
	float beta = min (acos (dot (ViewVector,Normal)), acos (dot (LightVector, Normal)));
	
	float C = sin (alpha) * tan (beta);

	vec3 DiffuseComponent = ColorData.xyz * NdL * (A + B * max(0, gamma) * C);
	
	//////////////////////////////////////////
	//////////Blinn Calculations//////////////
	//////////////////////////////////////////
	
	float SpecularRatio =  pow (clamp (HdN, 0.0, 1.0), SpecularPower * 20);
	vec3 SpecularComponent = (SpecularIntensity) * SpecularRatio * MaterialData.xyz;
	
	Result = vec4 (Attenuation * LightIntensityCoefficient * LightColor *(DiffuseComponent + SpecularComponent),1.0);
	
}