#pragma once
#include "libraries.h"
#include "glm/glm.hpp"
#include "SpriteBatch.h"
#include "GLTexture.h"
#include "ResourceManager.h"


class Particle
{
protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	long int m_endTime;
	glm::vec4 m_color;

	GLTexture _texture;
public:
	Particle(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration,long int life, glm::vec4 color) :
		m_position(position), m_velocity(velocity), m_acceleration(acceleration), m_endTime(SDL_GetTicks() + life), m_color(color) {
		_texture = ResourceManager::Instance()->getTexture("../assets/triangle.png");
	}
	~Particle();

	void update();
	void draw(SpriteBatch& spriteBatch);
	void clean();
	bool isDead();

};

