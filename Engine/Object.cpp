#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Object.h"
#include <algorithm>
#include "InputHandler.h"
#include "ResourceManager.h"
#include <iostream>

Object::Object() : m_vbo(0), m_vao(0)
{
}


Object::~Object()
{
}


void Object::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//orphan the data
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	//upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex), m_vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao);
	//std::cout << m_vertices.size() << std::endl;
	
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_L))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture.id);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_normalMap.id);
	}

	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	

	glBindVertexArray(0);
}

void Object::update()
{
	m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));
	m_model = glm::rotate(m_model, 0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_model = glm::scale(m_model, glm::vec3(1.001f, 1.001f, 1.001f));
	
	for (int i = 0; i < m_vertices.size(); i++) {
		m_vertices[i].position = m_model * glm::vec4(m_vertices[i].position, 1.0f);
		m_vertices[i].normal = m_model * glm::vec4(m_vertices[i].normal, 1.0f);
		m_vertices[i].tangent = m_model * glm::vec4(m_vertices[i].tangent, 1.0f);
	}
}

void Object::createVertexArray()
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
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	//position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	//color attribute pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	//normal attribute pointer
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//tangent attribute pointer
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glBindVertexArray(0);
}

bool Object::loadOBJ(
	std::string path)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen(path.c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	glm::vec3 tangent;
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// compute tangent
		if (i % 3 == 0) {
			glm::vec3 v0 = temp_vertices[vertexIndices[i] - 1];
			glm::vec3 v1 = temp_vertices[vertexIndices[i+1] - 1];
			glm::vec3 v2 = temp_vertices[vertexIndices[i+2] - 1];

			glm::vec2 uv0 = temp_uvs[uvIndices[i] - 1];
			glm::vec2 uv1 = temp_uvs[uvIndices[i+1] - 1];
			glm::vec2 uv2 = temp_uvs[uvIndices[i+2] - 1];

			glm::vec3 deltaPos1 = v1 - v0;
			glm::vec3 deltaPos2 = v2 - v0;

			glm::vec2 deltaUV1 = uv1 - uv0;
			glm::vec2 deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			
			tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		}

		// set vertex
		Vertex vertex;
		vertex.position = temp_vertices[vertexIndices[i] - 1];
		vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex.uv = temp_uvs[uvIndices[i] - 1];
		vertex.normal = temp_normals[normalIndices[i] - 1];
		vertex.tangent = tangent;
		m_vertices.push_back(vertex);
	}

	m_texture = ResourceManager::Instance()->getTexture("../assets/lilith_body.png");
	m_normalMap = ResourceManager::Instance()->getTexture("../assets/brick.png");
}