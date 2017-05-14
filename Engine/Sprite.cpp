#include "stdafx.h"
#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>
#include "ResourceManager.h"


Sprite::Sprite()
{
	m_vboID = 0;
}


Sprite::~Sprite()
{
	if (m_vboID != 0)
	{
		glDeleteBuffers(1, &m_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height, std::string texturePath)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height - height;

	m_texture = ResourceManager::Instance()->getTexture(texturePath);

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}

	Vertex vertexData[6];

	//first triangle
	vertexData[0].position = glm::vec3(x + width, y + height, 0.0f);
	vertexData[2].position = glm::vec3(x, y, 0.0f);
	vertexData[1].position = glm::vec3(x, y + height, 0.0f);

	vertexData[0].uv = glm::vec2(1.0f, 1.0f);
	vertexData[1].uv = glm::vec2(0.0f, 1.0f);
	vertexData[2].uv = glm::vec2(0.0f, 0.0f);

	//second triangle
	vertexData[3].position = glm::vec3(x, y, 0.0f);
	vertexData[4].position = glm::vec3(x + width, y, 0.0f);
	vertexData[5].position = glm::vec3(x + width, y + height, 0.0f);

	vertexData[3].uv = glm::vec2(0.0f, 0.0f);
	vertexData[4].uv = glm::vec2(1.0f, 0.0f);
	vertexData[5].uv = glm::vec2(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	vertexData[1].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vertexData[4].color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture.id);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	//color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}