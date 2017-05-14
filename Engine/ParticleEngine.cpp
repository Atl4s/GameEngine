#include "ParticleEngine.h"


ParticleEngine::ParticleEngine(int maxpart, glm::vec2 position, int minLife, int maxLife, int speed, glm::vec4 color) : max_particles(maxpart), m_position(position),
min_life(minLife), max_life(maxLife - minLife),m_speed(speed), m_color(color)
{
	for (int i = 0; i < max_particles; i++)
	{
		float fi = (static_cast<float>(rand()) * 2 * 3.1415 / RAND_MAX);
		float r = (static_cast<float>(rand()) * m_speed / RAND_MAX);
		particles.push_back(new Particle(m_position + glm::vec2(rand()%20-10,rand()%10-5), glm::vec2((r*cos(fi)), (r*sin(fi))), glm::vec2(0, 0), rand()%(max_life/10),
			m_color));
	}
}


ParticleEngine::~ParticleEngine()
{
	for (int i = 0; i < max_particles; i++)
	{
		delete particles[i];
	}
}

void ParticleEngine::update()
{
	for (int i = 0; i < max_particles; i++)
	{
		if (particles[i]->isDead())
		{
			delete particles[i];
			float fi = (static_cast<float>(rand()) * 2 * 3.1415 / RAND_MAX);
			float r = (static_cast<float>(rand()) * m_speed / RAND_MAX);
			particles[i] = new Particle(m_position + glm::vec2(rand() % 20 - 10, rand() % 10 - 5), glm::vec2((r*cos(fi)), (r*sin(fi))), glm::vec2(0, 0),
				min_life + rand() % (max_life), m_color);
		}
		else
		{
			particles[i]->update();
		}
	}
}

void ParticleEngine::draw(SpriteBatch& spriteBatch)
{
	for (int i = 0; i < max_particles; i++)
	{
		particles[i]->draw(spriteBatch);
	}
}