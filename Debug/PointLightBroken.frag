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

//Coordinates should be in View Space


void main ()
{
	vec2 ScreenPosition = gl_FragCoord.xy;
	ScreenPosition.x /= ScreenWidth;
	ScreenPosition.y /= ScreenHeight;

	//Extract data from the GBuffer
	vec4 NormalData = texture2D (NormalBuffer,ScreenPosition);      //Get ALL the Normal data
	vec4 ColorData = texture2D (ColorBuffer,ScreenPosition);        //Get ALL the Color Data
	vec4 MaterialData = texture2D (SpecularBuffer,ScreenPosition);  //Get All the Material Data
	float DepthZoW = texture2D (DepthBuffer,ScreenPosition).x;        
	
	vec2 ScreenCoord = 2 * ScreenPosition - 1;
	
	vec4 ViewPosition4 = InverseView * InverseProjection * vec4(ScreenCoord.x, ScreenCoord.y,DepthZoW,1.0f);
	vec3 Position = ViewPosition4.xyz/ViewPosition4.w;
	
	//Calculate the Surface information
	vec3 Normal = normalize (2.0 * NormalData.xyz  - 1.0); //Convert from [0,1] to [-1,1]
	//vec3 Position = CameraPosition +  normalize (FragPos.xyz/FragPos.w - CameraPosition) * -Depth;
	
	//Calculate lighting vectors
	vec3 LightVector = LightPosition - Position.xyz; //from fragment to light
	vec3 ViewVector = normalize (CameraPosition - Position); //from fragment to eye
	vec3 HalfVector = normalize (LightVector + ViewVector); //half vector for blinn
	
	//Point light specific
	float Attenuation = 1.0 - length(LightVector)/LightRadius; //calculate the falloff of the pointlight
	LightVector = normalize(LightVector); //normalize the LightVector for later use
	
	//Important Dot Products
	float NdL = clamp (dot (Normal,LightVector),0.0,1.0);
	float NdH = clamp (dot (HalfVector, Normal),0.0,1.0);
	float NdV = clamp (dot (ViewVector, Normal),0.0,1.0);
	float VdH = clamp (dot (ViewVector, HalfVector),0.0,1.0);
	float RoughnessSquared = Roughness * Roughness;
	
	float geo_numerator   = 2.0f * NdH;
    float geo_denominator = VdH;
 
    float geo_b = (geo_numerator * NdV ) / geo_denominator;
    float geo_c = (geo_numerator * NdL ) / geo_denominator;
    float geo   = min( 1.0f, min( geo_b, geo_c ) );

	float roughness_a = 1.0f / ( 4.0f * RoughnessSquared * pow( NdH, 4 ) );
	float roughness_b = NdH * NdH - 1.0f;
	float roughness_c = RoughnessSquared * NdH * NdH;

	float roughness = roughness_a * exp( roughness_b / roughness_c );
	
	// Next evaluate the Fresnel value
    // -------------------------------
    float fresnel = pow( 1.0f - VdH, 5.0f );
    fresnel *= ( 1.0f - SpecularPower );
    fresnel += SpecularPower;
 
 
 
    // Put all the terms together to compute
    // the specular term in the equation
    // -------------------------------------
    vec3 Rs_numerator   = vec3( fresnel * geo * roughness );
    float Rs_denominator  = NdV * NdL;
    vec3 Rs             = Rs_numerator/ Rs_denominator;
 
 
 
    // Put all the parts together to generate
    // the final colour
    // --------------------------------------
    vec3 final = max(0.0f, NdL) * (MaterialData.xyz * Rs + ColorData.xyz) * LightColor;
 
 
 
    // Return the result
    // -----------------
    Result = vec4(NormalData.xyz , 1.0f );
	
}