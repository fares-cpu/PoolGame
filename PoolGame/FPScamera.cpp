#include"FPSCamera.hpp"


FPSCamera::FPSCamera() {
	m_eye = glm::vec3(0.0f, 0.0f, 3.0f);
	m_target = glm::vec3(0.0f, 0.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_yaw = -90.0f; m_pitch = 0.0f; m_roll = 0.0f;
	m_fov = 45.0f;
	m_sensitivity = 0.1f;
	m_speed = 4.0f;

	m_dirty = 1;

	m_cachedView = glm::mat4(1.0f);

	updateCameraVectors();
}

glm::mat4 FPSCamera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& WorldUp) {
	m_cachedView = glm::lookAt(eye, target, WorldUp);
	return m_cachedView;
}

glm::mat4 FPSCamera::GetViewMatrix() {
	if (m_dirty) {
		updateCameraVectors();
		return LookAt(m_eye, m_eye + m_front, m_worldUp);
	}
	return m_cachedView;
}

void FPSCamera::processMouseInput(float xoffset, float yoffset, bool is_dragging = false, GLboolean constraintPitch = true) {
	xoffset *= m_sensitivity;
	yoffset *= m_sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constraintPitch) {
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}
	updateCameraVectors();
}

void FPSCamera::processKeyboardInput(char key, float deltaTime) {
	float speed = m_speed * deltaTime;
	if (key == 'w') {
		m_eye += speed * m_front;
	}
	if (key == 's') {
		m_eye -= speed * m_front;
	}
	if (key == 'a') {
		m_eye -= speed * m_right;
	}
	if (key == 'd') {
		m_eye += speed * m_right;
	}
	m_dirty = true;
}

void FPSCamera::processMouseScroll(float yoffset, float deltaTime) {}

glm::vec3 FPSCamera::getPosition() {
	return m_eye;
}

glm::vec3 FPSCamera::getFront()
{
	return m_front;
}

void FPSCamera::updateCameraVectors() {
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}