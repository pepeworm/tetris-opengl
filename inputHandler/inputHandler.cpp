#include "inputHandler.hpp"

void InputHandler::handleKeyRight() {
    this->piece->translateX(1);

	return;
}

void InputHandler::handleKeyLeft() {
    this->piece->translateX(-1);

    return;
}

void InputHandler::handleKeyUp() {
    this->piece->rotate(1);

	return;
}

void InputHandler::handleKeyZ() {
	this->piece->rotate(-1);

	return;
}

InputHandler::InputHandler(GLFWwindow* window, Renderer* renderer, BoardData* boardData) : window(window) {
	this->piece = new iPiece(boardData, renderer);
}

InputHandler::~InputHandler() {}

void InputHandler::detect() {
    this->piece->render();

	// Right arrow key

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		this->key_right_status = true;
	}

	if (this->key_right_status && (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)) {
		this->key_right_status = false;

		this->handleKeyRight();
	}

	// Left arrow key

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		this->key_left_status = true;
	}

	if (this->key_left_status && (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)) {
		this->key_left_status = false;

		this->handleKeyLeft();
	}

    // Up arrow key

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		this->key_up_status = true;
	}

	if (this->key_up_status && (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)) {
		this->key_up_status = false;

		this->handleKeyUp();
	}

	// Z key

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		this->key_z_status = true;
	}

	if (this->key_z_status && (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)) {
		this->key_z_status = false;

		this->handleKeyZ();
	}

	return;
}

void InputHandler::DELETETHIS() {
    this->piece->translateY();    

    return;
}