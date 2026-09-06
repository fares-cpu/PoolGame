#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float aspectRatio = 16.0f / 9.0f;

    virtual ~Camera() = default;

    virtual glm::mat4 GetViewMatrix() = 0;

    virtual void processMouseInput(float xoffset, float yoffset, bool is_dragging = false, GLboolean constraintPitch = true) = 0;

    virtual void processKeyboardInput(char key, float deltaTime) = 0;

    virtual void processMouseScroll(float yoffset, float deltaTime) = 0;

    virtual glm::vec3 getPosition() = 0;

    virtual glm::vec3 getFront() = 0;

    glm::mat4 perspective() {
		return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	}

	glm::mat4 perspective(float angle, float aspect, float near, float far) {
		return glm::perspective(glm::radians(angle), aspect, near, far);
	}

};