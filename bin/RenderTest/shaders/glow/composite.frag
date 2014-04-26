#version 400
uniform sampler2D Destination;
uniform sampler2D BlurMap;
uniform int BlendMode;

in vec2 TextureCoordinate;

out vec4 Color;

void main ()
{
	vec4 dst = texture2D(Destination, TextureCoordinate); // rendered scene
	vec4 src = texture2D(BlurMap, TextureCoordinate); // glowmap

	/*if ( BlendMode == 0 )
	{
		// Additive blending (strong result, high overexposure)
		Color = min(src + dst, 1.0);
	}
	else*/ if ( BlendMode == 1 )
	{
		// Screen blending (mild result, medium overexposure)
		Color = clamp((src + dst) - (src * dst), 0.0, 1.0);
		Color.w = 1.0;
	}
	//else if ( BlendMode == 2 )
	//{
	//	// Softlight blending (light result, no overexposure)
	//	// Due to the nature of soft lighting, we need to bump the black region of the glowmap
	//	// to 0.5, otherwise the blended result will be dark (black soft lighting will darken
	//	// the image).
	//	src = (src * 0.5) + 0.5;
	//	
	//	Color.xyz = vec3((src.x <= 0.5) ? (dst.x - (1.0 - 2.0 * src.x) * dst.x * (1.0 - dst.x)) : (((src.x > 0.5) && (dst.x <= 0.25)) ? (dst.x + (2.0 * src.x - 1.0) * (4.0 * dst.x * (4.0 * dst.x + 1.0) * (dst.x - 1.0) + 7.0 * dst.x)) : (dst.x + (2.0 * src.x - 1.0) * (sqrt(dst.x) - dst.x))),
	//				(src.y <= 0.5) ? (dst.y - (1.0 - 2.0 * src.y) * dst.y * (1.0 - dst.y)) : (((src.y > 0.5) && (dst.y <= 0.25)) ? (dst.y + (2.0 * src.y - 1.0) * (4.0 * dst.y * (4.0 * dst.y + 1.0) * (dst.y - 1.0) + 7.0 * dst.y)) : (dst.y + (2.0 * src.y - 1.0) * (sqrt(dst.y) - dst.y))),
	//				(src.z <= 0.5) ? (dst.z - (1.0 - 2.0 * src.z) * dst.z * (1.0 - dst.z)) : (((src.z > 0.5) && (dst.z <= 0.25)) ? (dst.z + (2.0 * src.z - 1.0) * (4.0 * dst.z * (4.0 * dst.z + 1.0) * (dst.z - 1.0) + 7.0 * dst.z)) : (dst.z + (2.0 * src.z - 1.0) * (sqrt(dst.z) - dst.z))));
	//	Color.w = 1.0;
	//}
	/*else
	{
		// Show just the glow map
		Color = src;
	}*/
}