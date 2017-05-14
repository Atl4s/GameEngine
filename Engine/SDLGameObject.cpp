#include "SDLGameObject.h"

SDLGameObject::SDLGameObject() : GameObject()
{
}

void SDLGameObject::load(const LoaderParams* pParams)
{
	m_position = glm::vec2(pParams->getX(), pParams->getY());
	m_velocity = glm::vec2(0, 0);
	m_acceleration = glm::vec2(0, 0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	_texture = pParams->getTexture();
	m_currentRow = 0;
	m_currentFrame = 0;
	m_numFrames = pParams->getNumFrames();
	m_color = pParams->getColor();
	_uv = glm::vec4(1.0f * m_currentFrame / m_numFrames, 0.0f, 1.0f / m_numFrames, 1.0f);
}

void SDLGameObject::draw(SpriteBatch& spriteBatch)
{ 	
	spriteBatch.addGlyph(glm::vec4(m_position.x, m_position.y, m_width, m_height), _uv, _texture.id, 0.0f, m_color);
}

void SDLGameObject::update()
{
	if (m_velocity.x >= 0)
		_uv = glm::vec4(1.0f * m_currentFrame / m_numFrames, 0.0f, 1.0f / m_numFrames, 1.0f);
	else
		_uv = glm::vec4(1.0f * m_currentFrame / m_numFrames, 0.0f, -1.0f / m_numFrames, 1.0f);
	m_velocity += m_acceleration;
	m_position += m_velocity;
}