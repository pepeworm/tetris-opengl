#pragma once

#include "gameState/gameState.hpp"
#include "glad.h"
#include <deque>
#include <vector>

class Game {
private:
	GLFWwindow* window;
	InputHandler* inputHandler;
	GameState* gameState = new GameState();

	/**
	 * @brief Place the active Tetromino piece onto the game board
	 */
	void placeActivePiece();

public:
	Game(GLFWwindow* window);
	~Game();

	/**
	 * @brief Run game loop
	 */
	void gameLoop();
};