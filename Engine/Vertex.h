#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>


struct Vertex
{
	glm::vec3 position;

	glm::vec4 color;

	glm::vec2 uv;

	glm::vec3 normal;

	glm::vec3 tangent;
};