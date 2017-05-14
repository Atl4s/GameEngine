#version 130
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

void main()
{
	
	color = fragmentColor;
}