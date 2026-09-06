#include"OrbitCamera.hpp"

OrbitCamera::OrbitCamera() {
	WorldUp = { 0.0f, 1.0f, 0.0f };
	
	target = { 0.0f, 0.0f, 0.0f };
	radius = 3.0f;
	theta = 90.0f;
	phi = 0.0f;

	dirty = true;

	cachedView = glm::mat4(1.0f);

	sensitivity = 0.1f;

	scrollSpeed = 0.2f;
}

glm::mat4 OrbitCamera::GetViewMatrix() {
	if (dirty) {
		glm::vec3 position = CalculatePosition();
		cachedView = glm::lookAt(position, target, WorldUp);
	}
	return cachedView;
}

void OrbitCamera::processMouseInput(float xoffset, float yoffset, bool is_dragging = false, GLboolean constraintPitch = true) {
	if (is_dragging) {
		theta += sensitivity * xoffset;
		phi += sensitivity * yoffset;

		dirty = true;
	}
}

void OrbitCamera::processKeyboardInput(char key, float deltaTime) {
}

void OrbitCamera::processMouseScroll(float yoffset, float deltaTime) {
	radius -= yoffset * scrollSpeed;
	dirty = true;
}

glm::vec3 OrbitCamera::getPosition() { return CalculatePosition(); }

glm::vec3 OrbitCamera::getFront()
{
	return target - getPosition();
}

glm::vec3 OrbitCamera::CalculatePosition() {
	phi = glm::clamp(phi, -89.0f, 89.0f);
	glm::vec3 pos;
	pos.x = target.x + radius * glm::cos(glm::radians(phi)) * glm::sin(glm::radians(theta));
	pos.y = target.y + radius * glm::sin(glm::radians(phi));
	pos.z = target.z + radius * glm::cos(glm::radians(phi)) * glm::cos(glm::radians(theta));

	return pos;
}