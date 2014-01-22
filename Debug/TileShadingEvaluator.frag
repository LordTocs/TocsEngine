#version 420
#define LIGHT_GRID_MAX_DIM_X 60
#define LIGHT_GRID_MAX_DIM_Y 34
#define NUM_POSSIBLE_LIGHTS 40

uniform mat4 InvView;

layout(std140) uniform LightGrid
{
  ivec4 LightCountAndOffsets[LIGHT_GRID_MAX_DIM_X * LIGHT_GRID_MAX_DIM_Y];
};

uniform isamplerBuffer LightIndexLists;

layout(std140) uniform LightPositionsRanges
{
  vec4 LightPositionRange[NUM_POSSIBLE_LIGHTS];
};
layout(std140) uniform LightColors
{
  vec4 LightColor[NUM_POSSIBLE_LIGHTS];
};
layout(std140) uniform LightShadows
{
  int LightShadow[NUM_POSSIBLE_LIGHTS];
};

uniform ivec2 GridSize;
uniform unsigned int TileSize;

uniform samplerCubeArrayShadow ShadowMaps;

in vec3 VertPos;

void ShadePrep ();
vec4 Shade (vec3 LightDir, vec3 ViewDir, vec3 LightColor, float Attenuation);


//http://stackoverflow.com/questions/18176274/cubemap-shadow-mapping-not-working
float VectorToDepthValue (vec3 Vec, float n, float f)
{
	vec3 AbsVec = abs(Vec);
    float LocalZcomp = max(AbsVec.x, max(AbsVec.y, AbsVec.z));

    float NormZComp = (f+n) / (f-n) - (2*f*n)/(f-n)/LocalZcomp;
    return (NormZComp + 1.0) * 0.5;
}


vec4 Evaluate()
{
	ivec2 l = ivec2(int(gl_FragCoord.x) / int(TileSize), int(gl_FragCoord.y) / int(TileSize));
	int index = l.x + l.y * GridSize.x;
	int lightCount = LightCountAndOffsets[index].x;
	int lightOffset = LightCountAndOffsets[index].y;

	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	ShadePrep ();
	for (int i = 0; i < lightCount; ++i)
	{
		int lightIndex = texelFetch(LightIndexLists, lightOffset + i).x;
		vec3 LightPos = LightPositionRange[lightIndex].xyz;
		float radius = LightPositionRange[lightIndex].w;
		
		vec3 L = LightPos - VertPos;
		float distance = length(L);
		float attenuation = max(1 - distance/radius,0);
		
		vec3 WL = -(InvView * vec4(L,0)).xyz;
		vec3 WLnorm = normalize(WL);
		
		int shadow = LightShadow[lightIndex];
		
		//if (shadow != -1)
		//{
			float comparedepth = VectorToDepthValue(WL - WLnorm * 0.05,0.01,radius);
			attenuation *= texture(ShadowMaps, vec4(WL,shadow),comparedepth); 
		//}
		
		vec4 s = Shade(normalize(L), normalize(-VertPos),LightColor[lightIndex].rgb,attenuation);
		color = vec4(color.rgb + s.rgb, max(s.a,color.a));
		//color += vec4(shadow/10.0f, shadow/10.0f, shadow/10.0f,1);
				
		//color += vec4(attenuation,attenuation,attenuation,0.1);
		//color += vec4 (abs(WL).xz,0,1);
		//color += vec4 (abs(InvView * vec4 (VertPos,1)).xyz,1);
	}

	return color;
}