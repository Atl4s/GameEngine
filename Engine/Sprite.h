#pragma once
#include "libraries.h"
#include "GLTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);

	void draw();

private:

	float m_x, m_y, m_width, m_height;
	GLuint m_vboID;
	GLTexture m_texture;
};

