#include "stdafx.h"
#include "AnimatedGraphic.h"


AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw(SpriteBatch& spriteBatch)
{
	SDLGameObject::draw(spriteBatch);
}

void AnimatedGraphic::clean(){}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}
