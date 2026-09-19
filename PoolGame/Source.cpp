#include<spdlog/spdlog.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

GLFWwindow* init_glfw();
void framebuffer_size_callback(GLFWwindow* window, int width, int hight);

int main() {
	GLFWwindow* window = init_glfw();
	while (!glfwWindowShouldClose(window)) {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

GLFWwindow* init_glfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "PoolGL", NULL, NULL);
	
	if (window == NULL) {
		spdlog::error("GLFW::Failed to create glfw window");
		glfwTerminate();
		exit(-1);
	}spdlog::info("GLFW::Created glfw window successfully");
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("GLAD::Failed to initialize glad");
		exit(-1);
	}spdlog::info("GLAD::Loaded glad successfully");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int hight) {
	glViewport(0, 0, width, hight);
}