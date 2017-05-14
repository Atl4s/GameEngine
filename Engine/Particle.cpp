#include "Particle.h"
#include "Timing.h"


Particle::~Particle()
{
}

void Particle::update()
{
	m_velocity += m_acceleration;
	//m_position += m_velocity;
	m_position += Timing::Instance()->getDelta() * m_velocity;
	m_color.r - 0.01f> 0 ? m_color.r -= 0.01f : m_color.r = 0.0f;
	m_color.g - 0.08f > 0 ? m_color.g -= 0.08f : m_color.g = 0.0f;
	m_color.b - 0.3f > 0 ? m_color.b -= 0.3f : m_color.b = 0.0f;
}

void Particle::draw(SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	spriteBatch.addGlyph(glm::vec4(m_position.x, m_position.y, 30, 30), uv, _texture.id, 0.0f, m_color);
}

void Particle::clean()
{

}

bool Particle::isDead()
{
	return (SDL_GetTicks() >= m_endTime);
}