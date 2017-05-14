#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
	Enemy();

	virtual void load(const LoaderParams* pParams);

	virtual void draw(SpriteBatch& spriteBatch);

	virtual void update();

	virtual void clean();
};

class EnemyCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Enemy();
	}
};