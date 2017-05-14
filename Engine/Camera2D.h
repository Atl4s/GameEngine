#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


#include <iostream>
#include "InputHandler.h"

class Camera2D
{
protected:
	Camera2D();
	~Camera2D();

	static Camera2D* s_pInstance;
public:

	static Camera2D* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Camera2D();
			return s_pInstance;
		}
		return s_pInstance;
	}

	static bool DeleteInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = 0;
			return true;
		}
		return false;
	}

	void init(int width, int height);

	void update();

	void reset() { setPosition(glm::vec2(0.0f)); setScale(1.0f); setAngle(0.0f); setRotAxis(glm::vec3(0.0f, 0.0f, 1.0f)); }

	void setPosition(const glm::vec2& position) {  m_position = position; m_needsMatrixUpdate = true; }
	void setScale(float scale) { m_scale = scale; m_needsMatrixUpdate = true; }
	void setAngle(float angle) { m_angle = angle; m_needsMatrixUpdate = true; }
	void setRotAxis(glm::vec3 rotAxis) { m_rotAxis = rotAxis; m_needsMatrixUpdate = true; }

	glm::vec2 getPosition() { return m_position; }
	float getScale() { return m_scale; }
	float getAngle() { return m_angle; }
	glm::vec3 getRotAxis() { return m_rotAxis; }

	glm::mat4 getCamMatrix() { return m_camMatrix; }

	glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

private:
	int m_width, m_height;
	bool m_needsMatrixUpdate;
	float m_scale;
	float m_angle;
	glm::vec2 m_position;
	glm::mat4 m_camMatrix;
	glm::mat4 m_orthoMatrix;
	glm::vec3 m_rotAxis;

	void handleEvents();
};


