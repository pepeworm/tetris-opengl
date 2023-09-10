#include "inputHandler.hpp"

void InputHandler::handleKeyRight() {
	this->game->activePiece->translateX(1);

	return;
}

void InputHandler::handleKeyLeft() {
	this->game->activePiece->translateX(-1);

	return;
}

void InputHandler::handleKeyUp() {
	this->game->activePiece->rotate(true);

	return;
}

void InputHandler::handleKeyZ() {
	this->game->activePiece->rotate(false);

	return;
}

void InputHandler::handleKeySpace() {
	this->game->activePiece->drop();

	return;
}

void InputHandler::handleKeyC() {
	if (!this->holdStatus) {
		return;
	}

	if (this->game->holdPiece->hidden) {
		// No previous hold piece set

		this->game->holdPiece = this->game->activePiece;
		this->game->holdPiece->hidden = false;
		this->game->activePiece = this->game->getActivePiece();
	} else {
		// A hold piece already exists

		Tetromino* temp = this->game->holdPiece;

		this->game->holdPiece = this->game->activePiece;
		this->game->activePiece = temp;
	}

	this->holdStatus = false;

	return;
}

void InputHandler::setHoldStatus(bool status) {
	this->holdStatus = status;

	return;
}

void InputHandler::detect() {
	// Right arrow key

	if (glfwGetKey(this->game->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		this->key_right_status = true;
	}

	if (!this->game->placePiece && this->key_right_status && (glfwGetKey(this->game->window, GLFW_KEY_RIGHT) == GLFW_RELEASE)) {
		this->key_right_status = false;

		this->handleKeyRight();
	}

	// Left arrow key

	if (glfwGetKey(this->game->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		this->key_left_status = true;
	}

	if (!this->game->placePiece && this->key_left_status && (glfwGetKey(this->game->window, GLFW_KEY_LEFT) == GLFW_RELEASE)) {
		this->key_left_status = false;

		this->handleKeyLeft();
	}

	// Up arrow key

	if (glfwGetKey(this->game->window, GLFW_KEY_UP) == GLFW_PRESS) {
		this->key_up_status = true;
	}

	if (!this->game->placePiece && this->key_up_status && (glfwGetKey(this->game->window, GLFW_KEY_UP) == GLFW_RELEASE)) {
		this->key_up_status = false;

		this->handleKeyUp();
	}

	// Down arrow key

	if (glfwGetKey(this->game->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		this->key_down_status = true;
		this->game->fallInterval = 0.05;
	}

	if (!this->game->placePiece && this->key_down_status && (glfwGetKey(this->game->window, GLFW_KEY_DOWN) == GLFW_RELEASE)) {
		this->key_down_status = false;
		this->game->fallInterval = 0.5;
	}

	// Z key

	if (glfwGetKey(this->game->window, GLFW_KEY_Z) == GLFW_PRESS) {
		this->key_z_status = true;
	}

	if (!this->game->placePiece && this->key_z_status && (glfwGetKey(this->game->window, GLFW_KEY_Z) == GLFW_RELEASE)) {
		this->key_z_status = false;

		this->handleKeyZ();
	}

	// Space key

	if (glfwGetKey(this->game->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->key_space_status = true;
	}

	if (this->key_space_status && (glfwGetKey(this->game->window, GLFW_KEY_SPACE) == GLFW_RELEASE)) {
		this->key_space_status = false;
		this->game->placePiece = true;

		this->handleKeySpace();
	}

	// C key

	if (glfwGetKey(this->game->window, GLFW_KEY_C) == GLFW_PRESS) {
		this->key_c_status = true;
	}

	if (this->key_c_status && (glfwGetKey(this->game->window, GLFW_KEY_C) == GLFW_RELEASE)) {
		this->key_c_status = false;

		this->handleKeyC();
	}

	return;
}