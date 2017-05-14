#include "stdafx.h"
#include "SpriteBatch.h"
#include <algorithm>
#include "InputHandler.h"

SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
{
}


SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
{
	m_sortType = sortType;
	m_renderBatches.clear();
	for (int i = 0; i < m_pGlyphs.size(); i++) {
		delete m_pGlyphs[i];
	}
	m_pGlyphs.clear();
}
void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::addGlyph(const glm::vec4& rect, const glm::vec4& uvRect, GLuint texture, float depth, const glm::vec4& color)
{
	Glyph* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	//float z = rand();
	float z = 0.0f;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.position = glm::vec3(rect.x, rect.y + rect.w, z);
	newGlyph->topLeft.uv = glm::vec2(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.position = glm::vec3(rect.x, rect.y, z);
	newGlyph->bottomLeft.uv = glm::vec2(uvRect.x, uvRect.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.position = glm::vec3(rect.x + rect.z, rect.y, z);
	newGlyph->bottomRight.uv = glm::vec2(uvRect.x + uvRect.z, uvRect.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.position = glm::vec3(rect.x + rect.z, rect.y + rect.w, z);
	newGlyph->topRight.uv = glm::vec2(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	m_pGlyphs.push_back(newGlyph);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(m_vao);

	for (int i = 0; i < m_renderBatches.size(); i++)
	{
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else 
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
		}
		
		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(m_pGlyphs.size() * 6);
	if (m_pGlyphs.empty()) {
		return;
	}

	int offset = 0;
	int cv = 0; //current vertex
	m_renderBatches.emplace_back(offset, 6, m_pGlyphs[0]->texture);
	vertices[cv++] = m_pGlyphs[0]->topLeft;
	vertices[cv++] = m_pGlyphs[0]->bottomLeft;
	vertices[cv++] = m_pGlyphs[0]->bottomRight;
	vertices[cv++] = m_pGlyphs[0]->bottomRight;
	vertices[cv++] = m_pGlyphs[0]->topRight;
	vertices[cv++] = m_pGlyphs[0]->topLeft;
	offset += 6;

	for (int cg = 1; cg < m_pGlyphs.size(); cg++) { //current glyph
		if (m_pGlyphs[cg]->texture != m_pGlyphs[cg - 1]->texture) {
			m_renderBatches.emplace_back(offset, 6, m_pGlyphs[cg]->texture);
		}
		else {
			m_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = m_pGlyphs[cg]->topLeft;
		vertices[cv++] = m_pGlyphs[cg]->bottomLeft;
		vertices[cv++] = m_pGlyphs[cg]->bottomRight;
		vertices[cv++] = m_pGlyphs[cg]->bottomRight;
		vertices[cv++] = m_pGlyphs[cg]->topRight;
		vertices[cv++] = m_pGlyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//orphan the data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	//upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	if (m_vao == 0) {
		glGenVertexArrays(1, &m_vao);
	}
	glBindVertexArray(m_vao);

	if (m_vbo == 0) {
		glGenBuffers(1, &m_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	//color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
	switch (m_sortType) {
		case GlyphSortType::BACK_TO_FRONT :
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), compareTexture);
			break;
	}
	
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}
bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}
bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return (a->texture < b->texture);
}
