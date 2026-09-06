#pragma once
#include<iostream>
#include<glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "camera.hpp"

class OrbitCamera : public Camera {

	glm::vec3 WorldUp;

	glm::vec3 target;
	float radius;
	float theta;
	float phi;

	bool dirty;

	glm::mat4 cachedView;

	float sensitivity;
	float scrollSpeed;

public:

	OrbitCamera();

	glm::mat4 GetViewMatrix() override;
	void processMouseInput(float xoffset, float yoffset, bool is_dragging, GLboolean constraintPitch) override;

	void processKeyboardInput(char key, float deltaTime) override;

	void processMouseScroll(float yoffset, float deltaTime) override;

	glm::vec3 getPosition() override;

	glm::vec3 getFront() override;
private:
	glm::vec3 CalculatePosition();


};