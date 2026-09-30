
#include"FPScamera.hpp"
#include<filesystem>
#include<spdlog/spdlog.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Shader.hpp"
#include"model_loading.hpp"




GLFWwindow* init_glfw();
void framebuffer_size_callback(GLFWwindow* window, int width, int hight);




int main() {
	GLFWwindow* window = init_glfw();
	Camera* camera = new FPSCamera();
	Model* modelAsset = new Model("assets/models/table.obj");
	glm::mat4 modelMat(1.0f);
	Shader shaderTable("shaders/vertex.glsl", "shaders/tablefragment.glsl");

	shaderTable.use();
	shaderTable.set_vec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shaderTable.set_vec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shaderTable.set_vec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shaderTable.set_vec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shaderTable.set_mat4("model", modelMat);
		shaderTable.set_mat4("view", camera->GetViewMatrix());
		shaderTable.set_mat4("projection", camera->perspective());
		shaderTable.set_vec3("viewPos", camera->getPosition());

		modelAsset->Draw(shaderTable);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	delete camera;
	delete modelAsset;
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