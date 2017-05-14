#include "stdafx.h"
#include "Camera3D.h"
#include "glm/ext.hpp"
#include "Timing.h"


Camera3D* Camera3D::s_pInstance = 0;

Camera3D::~Camera3D()
{
}

void Camera3D::update()
{
	handleEvents();

	if (m_needsMatrixUpdate) {

		m_view = glm::lookAt(m_cameraPosition, m_viewPosition, m_up);

		m_MVP = m_projection * m_view * m_model;

		m_needsMatrixUpdate = false;
	}
}

void Camera3D::handleEvents()
{
	InputHandler::Instance()->update();

	glm::vec2 mousePosition = InputHandler::Instance()->getRelativeMousePosition();
	

	m_phi += mousePosition.x / 100;
	m_theta += mousePosition.y / 100;

	if (m_phi > 2 * 3.1415) m_phi -= 2 * 3.1415;
	else if (m_phi < 0)  m_phi += 2 * 3.1415;

	if (m_theta > 3.1415) m_theta = 3.1415;
	else if (m_theta < 0)  m_theta = 0;

	m_direction = m_speed * Timing::Instance()->getDelta() * 
		glm::vec3(cos(m_phi) * sin(m_theta), cos(m_theta), sin(m_phi) * sin(m_theta));

	m_right = m_speed * Timing::Instance()->getDelta() *
		glm::vec3(cos(m_phi - (3.1415 / 2)), 0, sin(m_phi - (3.1415 / 2)));

	m_up = glm::normalize(glm::cross(m_direction, m_right));

	setViewPosition(m_cameraPosition + m_direction);

	if (InputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		printf("position: %f, %f, %f \n", m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);
	}
	if (InputHandler::Instance()->getMouseButtonState(LEFT))
	{
		std::cout << mousePosition.x << ", " << mousePosition.y << std::endl;
	}
	if (InputHandler::Instance()->getMouseButtonState(MIDDLE))
	{
		
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	{
		setCamPosition(m_cameraPosition + m_right);
		setViewPosition(m_viewPosition + m_right);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		setCamPosition(m_cameraPosition - m_right);
		setViewPosition(m_viewPosition - m_right);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
	{
		setCamPosition(m_cameraPosition + m_direction);
		setViewPosition(m_viewPosition + m_direction);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
	{
		setCamPosition(m_cameraPosition - m_direction);
		setViewPosition(m_viewPosition - m_direction);
	}
}