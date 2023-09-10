#pragma once

#include "../components/container/board/board.hpp"
#include "../components/tetromino/pieces/iPiece/iPiece.hpp"
#include "../components/tetromino/pieces/jPiece/jPiece.hpp"
#include "../components/tetromino/pieces/lPiece/lPiece.hpp"
#include "../components/tetromino/pieces/oPiece/oPiece.hpp"
#include "../components/tetromino/pieces/sPiece/sPiece.hpp"
#include "../components/tetromino/pieces/tPiece/tPiece.hpp"
#include "../components/tetromino/pieces/zPiece/zPiece.hpp"
#include "../renderer/renderer.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>

class InputHandler {
private:
	GLFWwindow* window;

	bool key_right_status = false;
	bool key_left_status = false;
	bool key_up_status = false;
	bool key_down_status = false;
	bool key_z_status = false;
	bool key_space_status = false;
	bool key_c_status = false;

	Tetromino* activePiece;
	bool& placePiece;
	double& fallInterval;

	/**
	 * @brief Handle the right arrow key input
	 */
	void handleKeyRight();

	/**
	 * @brief Handle the left arrow key input
	 */
	void handleKeyLeft();

	/**
	 * @brief Handle the up arrow key input
	 */
	void handleKeyUp();

	/**
	 * @brief Handle the Z key input
	 */
	void handleKeyZ();

	/**
	 * @brief Handle the space key input
	 */
	void handleKeySpace();

	/**
	 * @brief Handle the C key input
	 */
	void handleKeyC();

public:
	/**
	 * @brief Setup input handler
	 * @param window The GLFW window object
	 * @param placePiece A reference to the placePiece in game.cpp
	 * @param fallInterval A reference to the fallInterval in game.cpp
	 */
	InputHandler(GLFWwindow* window, bool& placePiece, double& fallInterval) : window(window), placePiece(placePiece), fallInterval(fallInterval){};

	/**
	 * @brief Set the current active game piece to transform according to the appropriate keyboard inputs
	 * @param activePiece The current active game piece
	 */
	void setActivePiece(Tetromino* activePiece);

	/**
	 * @brief Begin detecting input events
	 */
	void detect();
};