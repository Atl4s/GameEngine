#include "Enemy.h"

Enemy::Enemy() : SDLGameObject()
{	
}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_velocity.y = 2;
	m_velocity.x = -0.001;
}

void Enemy::draw(SpriteBatch& spriteBatch)
{
	SDLGameObject::draw(spriteBatch);
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	if (m_position.y < 0) m_velocity.y = 2;
	else if (m_position.y > 400) m_velocity.y = -2;

	SDLGameObject::update();
}

void Enemy::clean() {}