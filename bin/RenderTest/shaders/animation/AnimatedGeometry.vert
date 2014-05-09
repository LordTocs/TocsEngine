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
in vec3 InTangent;
in vec4 BoneWeights;
in uvec4 BoneIndices;

layout(std430, binding=0) buffer BoneBuffer
{
	mat4x2 Bones[];
};


//Outputs to the Pixel Shader
out vec3 GeometryNormal;
out vec3 GeometryTangent;
out vec2 Depth;
out vec2 TextureCoordinate;
out vec3 VertPos;

mat4x2 BlendedDualQuaternion ()
{
	mat4x2 bone0 = Bones[BoneIndices.x];
	mat4x2 bone1 = Bones[BoneIndices.y];
	mat4x2 bone2 = Bones[BoneIndices.z];
	mat4x2 bone3 = Bones[BoneIndices.w];
	
	mat4x2 blended = 
		bone0 * BoneWeights.x +
		bone1 * BoneWeights.y +
		bone2 * BoneWeights.z +
		bone3 * BoneWeights.w;
		
	float mag = length(blended[0]);
	return blended / mag;
}

vec3 TransformPosition (vec3 position, vec4 real, vec4 dual)
{
	return position +
        2 * cross( real.xyz, cross(real.xyz, position) + real.w*position ) + //Position
        2 * (real.w * dual.xyz - dual.w * real.xyz +  //Rotation
            cross( real.xyz, dual.xyz));
}

vec3 TransformVector (vec3 vector, vec4 real, vec4 dual)
{
	return vector + 2.0 * cross( real.xyz, cross( dual.xyz, vector ) + 
                          dual.w * vector );
}

void main()
{
	mat4x2 blended = BlendedDualQuaternion ();
	GeometryNormal = (mat3 (View) * mat3 (World) * TransformVector(InNormal.xyz, blended[0], blended[1]));
	GeometryTangent = (mat3 (View) * mat3 (World) * TransformVector(InTangent.xyz, blended[0], blended[1]));
	TextureCoordinate = InTextureCoordinate;
	vec4 vpos = (View * World) * vec4(TransformPosition(InPosition.xyz, blended[0], blended[1]),1);
	VertPos = vpos.xyz / vpos.w;
	gl_Position = (Projection * vpos);
	Depth =  gl_Position.zw;
} 

