#version 130
//The vertex shader operates on each vertex

//input data from the VBO
in vec3 vertexPosition;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 P;

void main()
{
	gl_Position = P * vec4(vertexPosition, 1.0);
	
	fragmentPosition = vertexPosition;
	
	fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);
}