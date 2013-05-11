 #version 130
precision highp float;

//Uniforms
uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

//Per vertex input
in vec4 InPosition;

//Outputs to the Pixel Shader
//out vec2 ScreenPosition;
out vec4 FragPos;

void main()
{
	gl_Position = (Projection * View * World) * InPosition;
	//ScreenPosition = 0.5 * ((vec2(gl_Position.x, gl_Position.y)/gl_Position.w) + 1);
	FragPos = (World) * InPosition;
} 