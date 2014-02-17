#version 400

uniform vec2 TexelSize;
uniform sampler2D BlurSource;

uniform int Orientation;
uniform int BlurAmount;
uniform float BlurScale;
uniform float BlurStrength;

in vec2 TextureCoordinate;

out vec4 Color;

float Gaussian (float x, float deviation)
{
	return (1.0 / sqrt(2.0 * 3.141592 * deviation)) * exp(-((x * x) / (2.0 * deviation)));	
}

void main ()
{
	// Locals
	float halfBlur = float(BlurAmount) * 0.5;
	vec4 colour = vec4(0.0);
	vec4 texColour = vec4(0.0);
	
	// Gaussian deviation
	float deviation = halfBlur * 0.35;
	deviation *= deviation;
	float strength = 1.0 - BlurStrength;
	
	if ( Orientation == 0 )
	{
		// Horizontal blur
		for (int i = 0; i < BlurAmount; ++i)
		{
			float offset = float(i) - halfBlur;
			texColour = texture2D(BlurSource, TextureCoordinate + vec2(offset * TexelSize.x * BlurScale, 0.0)) * Gaussian(offset * strength, deviation);
			colour += texColour;
		}
	}
	else
	{
		// Vertical blur
		for (int i = 0; i < BlurAmount; ++i)
		{
			float offset = float(i) - halfBlur;
			texColour = texture2D(BlurSource, TextureCoordinate + vec2(0.0, offset * TexelSize.y * BlurScale)) * Gaussian(offset * strength, deviation);
			colour += texColour;
		}
	}
	
	// Apply colour
	Color = clamp(colour, 0.0, 1.0);
	Color.w = 1.0;
	
	//Color = vec4 (TextureCoordinate,0,1);
}