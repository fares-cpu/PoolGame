#include "input.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset, yoffset;
	if (first_mouse) {
		lastX = xpos;
		lastY = ypos;
		first_mouse = false;
	}
	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	
	camera->processMouseInput(xoffset, yoffset, isDragging);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
