#version 450
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec3 fragmentNormal;
in vec3 fragmentTangent;

out vec4 color;

struct LightSource
{
        //int type;
		float power;
        vec3 position;
        //vec3 direction;
        //vec4 color;
};

uniform sampler2D m_texture;
uniform sampler2D m_normalMap;

uniform vec3 camPosition;

uniform LightSource light[10];

uniform mat4 M;

void main()
{	
	vec4 textureColor = texture(m_texture, fragmentUV);
	vec4 normalMap = texture(m_normalMap, fragmentUV);
	
	vec3 camDirection = mat3(M) * (camPosition - fragmentPosition);
	
	vec3 normal = 2*normalMap.xyz - 1;
	
	vec3 tangent = fragmentTangent - dot(fragmentTangent, fragmentNormal) * fragmentNormal;
	
	vec3 bitangent = cross(tangent, fragmentNormal);
	
	mat3 TBN = mat3(tangent, bitangent, fragmentNormal);
	
	normal = normalize(TBN * normal);

	vec4 ambientColor = vec4(0.01, 0.01, 0.01, 1.0);
	vec4 diffuseColor = vec4(0.0);
	vec4 specularColor = vec4(0.0);
	float brightness = 0.1;
	float reflects = 0.1;

	for (int i = 0; i < light.length(); i++) {
		vec3 lightDirection = light[i].position - (mat3(M) * fragmentPosition);
		brightness += light[i].power * clamp(dot(normal, normalize(lightDirection))/dot(lightDirection, lightDirection), 0, 1);
		reflects += light[i].power * clamp(dot(normalize(camDirection), normalize(reflect(-lightDirection, normal)))/dot(lightDirection, lightDirection), 0, 1);
	}
	
	
	diffuseColor = textureColor * fragmentColor * brightness;
	
	specularColor = textureColor * fragmentColor * pow(reflects, 5);
	
	color = ambientColor + diffuseColor + specularColor;
	
	color.w = 1.0;
}