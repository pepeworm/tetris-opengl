#pragma once

#include "../game/gameFlags/gameFlags.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class InputHandler {
private:
	GLFWwindow* window;
	GameFlags* gameFlags;

	std::vector<bool> keyStatus; // Use key codes to access values
	std::vector<unsigned int> validKeys = {GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_Z, GLFW_KEY_SPACE, GLFW_KEY_C};

public:
	/**
	 * @brief Setup input handler
	 * @param window The GLFW window object
	 * @param gameFlags The game flags to change according to key inputs detected
	 */
	InputHandler(GLFWwindow* window, GameFlags* gameFlags);

	/**
	 * @brief Begin detecting input events
	 */
	void detect();
};