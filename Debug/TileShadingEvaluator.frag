#version 140
#define attencutoff 0.005
#define ConstantAttenuation 1.0
#define LinearAttenuation 0.22f
#define QuadraticAttenuation 0.20
#define LIGHT_GRID_MAX_DIM_X 60
#define LIGHT_GRID_MAX_DIM_Y 34
#define NUM_POSSIBLE_LIGHTS 40

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

uniform ivec2 GridSize;
uniform unsigned int TileSize;

in vec3 VertPos;

void ShadePrep ();
vec4 Shade (vec3 LightDir, vec3 ViewDir, vec3 LightColor, float Attenuation);

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
		
		color += Shade(normalize(L), normalize(-VertPos),LightColor[lightIndex].rgb,attenuation);
	}

	return color;
}