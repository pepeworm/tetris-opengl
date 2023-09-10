#pragma once

#include "../../tetromino.hpp"
#include "glad.h"

class ZPiece : public Tetromino {
public:
	/**
	 * @brief Generate a new Z piece
	 * @param renderer The renderer used to render the piece
	 * @param boardData The current game board data
	 * @param startX The starting X position of the piece (starting from the bottom left of the piece)
	 * @param startY The starting Y position of the piece (starting from the bottom left of the piece)
	 */
	ZPiece(Renderer* renderer, BoardData* boardData, float startX, float startY);

	/**
	 * @brief Update the position of the Tetromino
	 * @param startX The new starting X position of the piece (starting from the bottom left of the piece)
	 * @param startY The new starting Y position of the piece (starting from the bottom left of the piece)
	 */
	virtual void updatePos(float startX, float startY);
};