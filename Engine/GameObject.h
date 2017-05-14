#pragma once

#include "libraries.h"
#include "ResourceManager.h"
#include "LoaderParams.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

class GameObject
{
public:

	virtual void draw(SpriteBatch& spriteBatch) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void load(const LoaderParams* pParams) = 0;
	virtual ~GameObject(){};

protected:
	
	GameObject(){}
	
};
