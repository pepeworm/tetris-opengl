#pragma once

#include "../components/container/board/board.hpp"
#include "../components/tetromino/pieces/iPiece/iPiece.hpp"
#include "../components/tetromino/pieces/jPiece/jPiece.hpp"
#include "../components/tetromino/pieces/lPiece/lPiece.hpp"
#include "../components/tetromino/pieces/oPiece/oPiece.hpp"
#include "../components/tetromino/pieces/sPiece/sPiece.hpp"
#include "../components/tetromino/pieces/tPiece/tPiece.hpp"
#include "../components/tetromino/pieces/zPiece/zPiece.hpp"
#include "../game/game.hpp"
#include "../renderer/renderer.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>

class InputHandler {
private:
	Game* game;

	bool key_right_status = false;
	bool key_left_status = false;
	bool key_up_status = false;
	bool key_down_status = false;
	bool key_z_status = false;
	bool key_space_status = false;
	bool key_c_status = false;

	bool holdStatus = true; // True if hold piece is available to use

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
	 * @param game The current game
	 */
	InputHandler(Game* game) : game(game){};

	/**
	 * @brief Set the hold piece status
	 * @param status The new status
	 */
	void setHoldStatus(bool status);

	/**
	 * @brief Begin detecting input events
	 */
	void detect();
};