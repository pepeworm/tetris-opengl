#include "game/game.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>

int main() {
	// Initialization of GLFW and GLAD

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Tetris", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;

		return -1;
	}

	glViewport(0, 0, 800, 800);

	Game* game = new Game(window);

	// Rendering Loop

	while (!glfwWindowShouldClose(window)) {
		game->gameLoop();

		// Swap buffers and poll for events

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete game;
	
	glfwTerminate();

	return 0;
}