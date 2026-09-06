#pragma once
#include <glm/glm.hpp>
#include "camera.hpp"

class FPSCamera : public Camera{
private:
	glm::vec3 m_eye;
	glm::vec3 m_target;
	glm::vec3 m_worldUp;

	float m_yaw, m_pitch, m_roll;
	float m_fov;
	float m_sensitivity, m_speed;

	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;

	bool m_dirty;


	glm::mat4 m_cachedView;

public:
	FPSCamera();
	
	glm::mat4 LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& WorldUp);

	glm::mat4 GetViewMatrix() override;


	void processMouseInput(float xoffset, float yoffset, bool is_dragging, GLboolean constraintPitch) override;

	void processKeyboardInput(char key, float deltaTime) override;

	void processMouseScroll(float yoffset, float deltaTime) override;

	glm::vec3 getPosition() override;

	glm::vec3 getFront() override;

private:
	void updateCameraVectors();

};