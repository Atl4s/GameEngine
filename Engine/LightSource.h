#pragma once

#include "glm/glm.hpp"
#include "GLSLProgram.h"
#include <string>

class LightSource
{
public:
	LightSource() : m_type(0),
					m_power(1),
					m_position(glm::vec3(0)),
					m_direction(glm::vec3(1)),
					m_color(glm::vec4(1))
	{}
	LightSource(int type, GLfloat power, glm::vec3 position, glm::vec3 direction, glm::vec4 color) :
		m_type(type),
		m_power(power),
		m_position(position),
		m_direction(direction),
		m_color(color)
	{}
	~LightSource() {}

	void init(int type, GLfloat power, glm::vec3 position, glm::vec3 direction, glm::vec4 color) {
		m_type = type;
		m_power = power;
		m_position = position;
		m_direction = direction;
		m_color = color;
	}

	void setType(int type) { m_type = type; }
	void setPower(GLfloat power) { m_power = power; }
	void setPosition(glm::vec3 position) { m_position = position; }
	void setDirection(glm::vec3 direction) { m_direction = direction; }
	void setColor(glm::vec4 color) { m_color = color; }

	void setUniform(GLSLProgram& program, std::string uniform_name, int uniform_number);

private:
	int m_type;
	GLfloat m_power;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec4 m_color;
};

