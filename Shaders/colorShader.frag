#version 450
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D m_sampler;

void main()
{
	vec4 textureColor = texture(m_sampler, fragmentUV);
	
	color = textureColor * fragmentColor;
}