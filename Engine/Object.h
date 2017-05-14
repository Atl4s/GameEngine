#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "Vertex.h"
#include <vector>
#include "GLTexture.h"

class Object
{
public:
	Object();
	~Object();

	bool loadOBJ(std::string path);

	void render();
	void update();

	void createVertexArray();

	void setModel(glm::mat4 model) {
		m_model = model;
	}

	glm::mat4& getModel() {
		return m_model;
	}

private:
	
	GLuint m_vbo;
	GLuint m_vao;

	glm::mat4 m_model = glm::mat4(1.0f);

	GLTexture m_texture;
	GLTexture m_normalMap;

	std::vector<Vertex> m_vertices;
};


















































/*
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <fstream>

class Object
{
public:
	Object();
	~Object();

	bool loadOBJ(std::string path);

	void createVertexArray();

	void render();

private:

	GLuint m_vbo;
	GLuint m_vao;

	GLuint m_texture;

	std::vector<glm::vec3> m_vertices;
	std::vector<unsigned short> m_indices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
};*/

