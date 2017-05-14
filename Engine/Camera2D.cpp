#include "stdafx.h"
#include "Camera2D.h"

Camera2D* Camera2D::s_pInstance = 0;

Camera2D::Camera2D() : m_position(0.0f, 0.0f), m_camMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_angle(0.0f), m_rotAxis(glm::vec3(0.0f, 1.0f, 0.0f)), m_needsMatrixUpdate(true), m_width(640), m_height(480)
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::init(int width, int height) {
	m_width = width;
	m_height = height;
	m_orthoMatrix = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height);
}

void Camera2D::update()
{
	handleEvents();

	if (m_needsMatrixUpdate) {
		glm::vec3 translate(-m_position.x + m_width/2, -m_position.y + m_height/2, 0.0f);
		m_camMatrix = glm::translate(m_orthoMatrix, translate);

		m_camMatrix = glm::rotate(m_camMatrix, m_angle, m_rotAxis);

		glm::vec3 scale(m_scale, m_scale, 0.0f);
		m_camMatrix = glm::scale(glm::mat4(1.0f), scale) * m_camMatrix;

		m_needsMatrixUpdate = false;
	}
}

void Camera2D::handleEvents()
{
	InputHandler::Instance()->update();
	if (InputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		//setScale(m_scale + 0.01f);
	}
	if (InputHandler::Instance()->getMouseButtonState(LEFT))
	{
		//setScale(m_scale - 0.01f);
	}
	if (InputHandler::Instance()->getMouseButtonState(MIDDLE))
	{
		glm::vec2 mousePos = InputHandler::Instance()->getMousePosition();
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
		mousePos = convertScreenToWorld(mousePos);
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	{
		setPosition(m_position + glm::vec2(10.0f, 0.0f));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		setPosition(m_position + glm::vec2(-10.0f, 0.0f));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
	{
		setPosition(m_position + glm::vec2(0.0f, -10.0f));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
	{
		setPosition(m_position + glm::vec2(0.0f, 10.0f));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_O))
	{
		setAngle(m_angle + 0.01f);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_P))
	{
		setAngle(m_angle - 0.01f);
	}
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
{

	screenCoords.y = m_height - screenCoords.y;
	screenCoords -= glm::vec2(m_width / 2, m_height / 2);
	screenCoords /= m_scale;
	screenCoords += m_position;

	glm::vec3 tempCoords(screenCoords.x, screenCoords.y, 1.0f);
	screenCoords = glm::rotate(tempCoords, -m_angle, m_rotAxis);


	return screenCoords;
}