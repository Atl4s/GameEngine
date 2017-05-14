#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


#include <iostream>
#include "InputHandler.h"

class Camera3D
{
protected:
	Camera3D() :
		m_speed(3.0f),
		m_phi(0.0f),
		m_theta(0.0f),
		m_direction(0.0f),
		m_cameraPosition(glm::vec3(10.0f, 0.0f, 0.0f)),
		m_viewPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_projection(glm::perspective(glm::radians(m_FoV), m_aspectRatio, m_near, m_far)),
		m_model(glm::mat4(1.0f))
	{
		m_view = glm::lookAt(m_cameraPosition, m_viewPosition, m_up);
		m_MVP = m_projection * m_view * m_model; 
	};
	~Camera3D();

	static Camera3D* s_pInstance;
public:

	static Camera3D* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Camera3D();
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

	glm::mat4 getMVP() { return m_MVP; }
	glm::mat4 getView() { return m_view; }
	glm::mat4 getProjection() { return m_view; }

	void update();

	float getFoV() { return m_FoV; }
	float getAspectRatio() { return m_aspectRatio; }
	float getNear() { return m_near; }
	float getFar() { return m_far; }

	glm::vec3 getCamPosition() { return m_cameraPosition; }
	glm::vec3 getViewPosition() { return m_viewPosition; }
	glm::vec3 getUpVector() { return m_up; }
	glm::vec3 getRightVector() { return m_right; }
	glm::vec3 getDirectionVector() { return m_direction; }


	void setSpeed(float speed) {
		m_speed = speed;
		m_needsMatrixUpdate = true;
	}
	void setFoV(float FoV) { 
		m_FoV = FoV; 
		m_needsMatrixUpdate = true; 
	}
	void setAspectRatio(float aspectRatio) {
		m_aspectRatio = aspectRatio;
		m_needsMatrixUpdate = true; 
	}
	void setNear(float Near) {
		m_near = Near;
		m_needsMatrixUpdate = true;
	}
	void setFar(float Far) { 
		m_far = Far;
		m_needsMatrixUpdate = true;
	}

	void setCamPosition(glm::vec3 cameraPosition) {
		m_cameraPosition = cameraPosition; 
		m_needsMatrixUpdate = true;
	}
	void setViewPosition(glm::vec3 viewPosition) {
		m_viewPosition = viewPosition; 
		m_needsMatrixUpdate = true;
	}
	void setUpVector(glm::vec3 upVector) { 
		m_up = upVector;
		m_needsMatrixUpdate = true;
	}

private:

	bool m_needsMatrixUpdate;

	float m_FoV = 45.0f;
	float m_aspectRatio = 4.0f / 3.0f;
	float m_near = 0.1f, m_far = 10000.0f;
	float m_phi, m_theta;
	float m_speed;

	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_model;
	glm::mat4 m_MVP;

	glm::vec3 m_cameraPosition;
	glm::vec3 m_viewPosition;
	glm::vec3 m_up;
	
	glm::vec3 m_direction;
	glm::vec3 m_right;

	void handleEvents();
};


