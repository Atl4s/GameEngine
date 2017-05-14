#pragma once

#include "GameObject.h"
#include "glm/glm.hpp"
#include "SpriteBatch.h"

class SDLGameObject : public GameObject
{
public:

	virtual ~SDLGameObject(){};
	SDLGameObject();
	virtual void draw(SpriteBatch& spriteBatch);
	virtual void update();
	virtual void clean(){};
	virtual void load(const LoaderParams* pParams);

	glm::vec2 getPosition(){ return m_position; }
	int getWidth(){ return m_width; }
	int getHeight(){ return m_height; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	int m_width;  int m_height;

	int m_currentRow;  int m_currentFrame;

	int m_numFrames;

	glm::vec4 _uv;
	GLTexture _texture;
	glm::vec4 m_color;
};