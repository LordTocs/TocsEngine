#version 130
precision highp float;

//Uniforms
uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 Lattice[8];
uniform vec3 BoundsCenter;
uniform vec3 BoundsReach;

//Per vertex input
in vec4 InPosition;
in vec2 InTextureCoordinate; 
in vec3 InNormal;


//Outputs to the Pixel Shader
out vec3 GeometryNormal;
out vec2 Depth;
out vec2 TextureCoordinate;

vec3 DeformWithLattice (vec3 pos)
{
	vec3 normalizedpos = (pos - BoundsCenter)/(BoundsReach * 2);
	vec3 s01 = mix(Lattice[0],Lattice[1],normalizedpos.x); //Shitty as fuck...
	vec3 s32 = mix(Lattice[3],Lattice[2],normalizedpos.x);
	vec3 s45 = mix(Lattice[4],Lattice[5],normalizedpos.x);
	vec3 s76 = mix(Lattice[7],Lattice[6],normalizedpos.x);
	
	vec3 f0145 = mix(s01,s45,normalizedpos.y);
	vec3 f3276 = mix(s32,s76,normalizedpos.y);
	
	return mix(f0145,f3276,normalized.z);
}

void main()
{
	vec3 DeformedPosition = DeformWithLattice(InPosition);
	vec3 DeformedNormalEndpoint = DeformWithLattice(InPosition + InNormal); //This doesn't work...
	vec3 DeformedNormal = DeformedNormalEndpoint - DeformedPosition; //How do deform a normal with a lattice?

	GeometryNormal = (mat3 (View) * mat3 (World) * DeformedNormal);
	TextureCoordinate = InTextureCoordinate;
	gl_Position = (Projection * View * World) * DeformedPosition;
	Depth =  gl_Position.zw;
} 

