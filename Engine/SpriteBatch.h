#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include <vector>


enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph
{
	GLuint texture;
	float depth;

	Vertex topLeft, topRight, bottomLeft, bottomRight;
};

class RenderBatch
{
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
		offset(Offset), 
		numVertices(NumVertices), 
		texture(Texture){
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;


};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	void addGlyph(const glm::vec4& rect, const glm::vec4& uvRect, GLuint texture, float depth, const glm::vec4& color);

	void renderBatch();

private:

	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint m_vbo;
	GLuint m_vao;

	GlyphSortType m_sortType;

	std::vector<Glyph*> m_pGlyphs;
	std::vector<RenderBatch> m_renderBatches;
};

