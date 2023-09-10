#include "inputHandler.hpp"

void InputHandler::handleKeyRight() {
	this->activePiece->translateX(1);

	return;
}

void InputHandler::handleKeyLeft() {
	this->activePiece->translateX(-1);

	return;
}

void InputHandler::handleKeyUp() {
	this->activePiece->rotate(true);

	return;
}

void InputHandler::handleKeyZ() {
	this->activePiece->rotate(false);

	return;
}

void InputHandler::handleKeySpace() {
	this->activePiece->drop();

	return;
}

void InputHandler::handleKeyC() {

	return;
}

void InputHandler::setActivePiece(Tetromino* activePiece) {
	this->activePiece = activePiece;

	return;
}

void InputHandler::detect() {
	// Right arrow key

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		this->key_right_status = true;
	}

	if (!this->placePiece && this->key_right_status && (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)) {
		this->key_right_status = false;

		this->handleKeyRight();
	}

	// Left arrow key

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		this->key_left_status = true;
	}

	if (!this->placePiece && this->key_left_status && (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)) {
		this->key_left_status = false;

		this->handleKeyLeft();
	}

	// Up arrow key

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		this->key_up_status = true;
	}

	if (!this->placePiece && this->key_up_status && (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)) {
		this->key_up_status = false;

		this->handleKeyUp();
	}

	// Down arrow key

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		this->key_down_status = true;
		this->fallInterval = 0.05;
	}

	if (!this->placePiece && this->key_down_status && (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)) {
		this->key_down_status = false;
		this->fallInterval = 0.5;
	}

	// Z key

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		this->key_z_status = true;
	}

	if (!this->placePiece && this->key_z_status && (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)) {
		this->key_z_status = false;

		this->handleKeyZ();
	}

	// Space key

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->key_space_status = true;
	}

	if (this->key_space_status && (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)) {
		this->key_space_status = false;
		this->placePiece = true;

		this->handleKeySpace();
	}

	// C key

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		this->key_c_status = true;
	}

	if (this->key_c_status && (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)) {
		this->key_c_status = false;

		this->handleKeyC();
	}

	return;
}