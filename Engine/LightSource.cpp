#include "stdafx.h"
#include "LightSource.h"

void LightSource::setUniform(GLSLProgram& program, std::string uniform_name, int uniform_number)
{
	std::string uniform = uniform_name + "[" + std::to_string(uniform_number) + "].";

	//GLuint location = program.getUniformLocation(uniform + "type");
	//glUniform1i(location, m_type);

	GLuint location = program.getUniformLocation(uniform + "power");
	glUniform1f(location, m_power);

	location = program.getUniformLocation(uniform + "position");
	glUniform3fv(location, 1, &(m_position[0]));

	//location = program.getUniformLocation(uniform + "direction");
	//glUniform3fv(location, 1, &(m_direction[0]));

	//location = program.getUniformLocation(uniform + "color");
	//glUniform4fv(location, 1, &(m_color[0]));
}
