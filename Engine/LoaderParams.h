#pragma once
#include "libraries.h"
#include "GLTexture.h"
#include "Vertex.h"

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, std::string texturePath, glm::vec4 color, int numFrames, int callbackID = 0, int animSpeed = 0) : m_x(x), m_y(y),
		m_width(width), m_height(height), _color(color), m_numFrames(numFrames), m_callbackID(callbackID), m_animSpeed(animSpeed)
	{
		_texture = ResourceManager::Instance()->getTexture(texturePath);
	}
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	GLTexture getTexture() const { return _texture; }
	glm::vec4 getColor() const { return _color; }
	int getNumFrames() const { return m_numFrames; }
	int getCallBackID() const { return m_callbackID; }
	int getAnimSpeed() const { return m_animSpeed; }

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	GLTexture _texture;
	glm::vec4 _color;
	int m_numFrames;
	int m_callbackID;
	int m_animSpeed;
};