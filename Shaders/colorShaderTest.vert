#version 450
//The vertex shader operates on each vertex

//input data from the VBO
in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;
in vec3 vertexNormal;
in vec3 vertexTangent;

out vec3 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;
out vec3 fragmentNormal;
out vec3 fragmentTangent;

uniform mat4 MVP;
uniform mat4 M;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);
	
	fragmentPosition = vertexPosition;
	
	fragmentColor = vertexColor;
	
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
	
	fragmentNormal = normalize(mat3(M) * vertexNormal);
	
	fragmentTangent = normalize(mat3(M) * vertexTangent);
}