#pragma once

#include "../../../renderer/renderer.hpp"
#include "../../board/board.hpp"
#include "../../square/square.hpp"
#include "glad.h"

class iPiece {
private:
	BoardData* boardData;
	Square* squares[4];
	float positions[8];

	Renderer* renderer;

	unsigned int rotationStatus = 0;

	/**
	 * @brief Check if a transformation (translation or rotation) is possible
	 */
	bool isValidTransform();

public:
	/**
	 * @brief Create the Tetris I piece
	 * @param boardData The current Tetris game board data
	 * @param renderer The renderer to use to render the piece
	 */
	iPiece(BoardData* boardData, Renderer* renderer);
	~iPiece();

	/**
	 * @brief Render the square
	 */
	void render();

	/**
	 * @brief Translate the piece about the X-axis
	 * @param dir The X-axis direction to translate the piece (`-1` for left & `1` for right)
	 */
	void translateX(int dir);

	/**
	 * @brief Translate the piece about the Y-axis towards the bottom of the game board
	 */
	void translateY();

	/**
	 * @brief Rotate the piece
	 * @param dir The direction of rotation (`-1` for counter-clockwise & `1` for clockwise)
	 */
	void rotate(int dir);
};