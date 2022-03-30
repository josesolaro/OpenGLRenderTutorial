#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "control.h"
#include "renderer.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //no backward-compatible features

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGlTutorial", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to Init GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);//screen Space?
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); }); //resizing

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//GL_FILL

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer::processInput(window);
		renderer::render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}