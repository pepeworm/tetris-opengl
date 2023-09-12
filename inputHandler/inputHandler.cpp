#include "inputHandler.hpp"

InputHandler::InputHandler(GLFWwindow* window, GameFlags* gameFlags) : window(window), gameFlags(gameFlags) {
	this->keyStatus.resize(GLFW_KEY_LAST, false);

	return;
}

void InputHandler::detect() {
	for (auto key : this->validKeys) {
		if (glfwGetKey(window, key) == GLFW_PRESS) {
			this->keyStatus[key] = true;
			
			if (key == GLFW_KEY_DOWN) {
				this->gameFlags->softDropStatus = true;
			}
		}

		if (this->keyStatus[key] && (glfwGetKey(window, key) == GLFW_RELEASE)) {
			this->keyStatus[key] = false;

			if (key == GLFW_KEY_RIGHT) {
				this->gameFlags->translateXStatus = 1;
			}

			if (key == GLFW_KEY_LEFT) {
				this->gameFlags->translateXStatus = -1;
			}

			if (key == GLFW_KEY_UP) {
				this->gameFlags->rotateStatus = 1;
			}

			if (key == GLFW_KEY_DOWN) {
				this->gameFlags->softDropStatus = false;
			}

			if (key == GLFW_KEY_Z) {
				this->gameFlags->rotateStatus = -1;
			}

			if (key == GLFW_KEY_SPACE) {
				this->gameFlags->dropStatus = true;
			}

			if (key == GLFW_KEY_C) {
				this->gameFlags->holdStatus = true;
			}
		}
	}

	return;
}