#version 460

in vec3 vertexIn;
in vec4 colorIn;
out vec4 colorOut;

void main()
{
	colorOut = colorIn;
	gl_Position - position;
}