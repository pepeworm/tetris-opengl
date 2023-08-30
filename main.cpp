#include "components/board/board.hpp"
#include "glad.h"
#include "ibo/ibo.hpp"
#include "inputHandler/inputHandler.hpp"
#include "renderer/renderer.hpp"
#include "shader/shader.hpp"
#include "vao/vao.hpp"
#include "vbo/vbo.hpp"
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

	Renderer* renderer = new Renderer();

	Board* gameBoard = new Board(0.3f, 0.2f, renderer);
	BoardData* boardData = gameBoard->getBoardData();

	InputHandler* inputHandler = new InputHandler(window, renderer, boardData);

	// Rendering Loop

	double previousTime = glfwGetTime();
	unsigned int frameCount = 0;

	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		frameCount++;

		if (currentTime - previousTime >= 0.5) {
			// Display the frame count here any way you want.
			std::cout << frameCount << '\n';

			frameCount = 0;
			previousTime = currentTime;

			inputHandler->DELETETHIS();
		}

		renderer->clearScreen();
		renderer->enableBlend();
		renderer->fillScreen(0.06f, 0.11f, 0.14f, 1.0f);

		// Handle input

		inputHandler->detect();

		// Draw elements

		gameBoard->render();

		// Swap buffers and poll for events

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}