#pragma once

#include "../../square/square.hpp"
#include "../container.hpp"
#include "glad.h"

class BoardData : public ContainerData {
public:
	float squareSize;

	unsigned int width = 10;
	unsigned int height = 24;

	std::vector<std::vector<Square*>> gameData;

	BoardData(){};

	/**
	 * @brief Renders the played pieces in the game data
	 */
	void renderPlayedPieces();

	/**
	 * @brief Checking if rows can be cleared and clear if possible
	 */
	void clearRows();

	/**
	 * @brief Check if the next active Tetromino will be a top out
	 * @returns Whether the next piece placed will result in a top out
	 */
	bool checkTopOut();
};

class Board : public Container {
public:
	BoardData* data = new BoardData();

	/**
	 * @brief Sets up the data necessary to render the 10 x 24 Tetris game board
	 * @param renderer The renderer object to use to render the game board
	 * @param tPadding The top padding relative to the game window
	 * @param bPadding The bottom padding relative to the game window
	 */
	Board(Renderer* renderer, float tPadding, float bPadding);
};