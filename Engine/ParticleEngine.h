#pragma once
#include <vector>
#include "Particle.h"


class ParticleEngine
{
protected:
	std::vector<Particle*> particles;
	glm::vec2 m_position;
	int max_particles;
	int min_life, max_life;
	int m_speed;
	glm::vec4 m_color;

public:
	ParticleEngine(int maxPart, glm::vec2 position, int minLife, int maxLife, int speed, glm::vec4 color);
	~ParticleEngine();
	void setPosition(glm::vec2 position) { m_position = position; }
	glm::vec2 getPosition() { return m_position; }

	void update();
	void draw(SpriteBatch& spriteBatch);
	void clear() {};
};

