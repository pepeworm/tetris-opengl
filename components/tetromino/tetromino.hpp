#pragma once

#include "../components/container/board/board.hpp"
#include "../components/square/square.hpp"
#include "../renderer/renderer.hpp"
#include "glad.h"
#include <unordered_map>
#include <vector>

class Tetromino {
protected:
	Renderer* renderer;
	BoardData* boardData;

	float positions[8];

	float centerX; // The X co-ordinate of the center of the Tetromino
	float centerY; // The Y co-ordinate of the center of the Tetromino

	std::unordered_map<char, std::vector<float>> pieceColor = {{'i', {0.0f, 1.0f, 1.0f}}, {'j', {0.0f, 0.0f, 1.0f}}, {'l', {1.0f, 0.65f, 0.0f}},
															   {'o', {1.0f, 1.0f, 0.0f}}, {'s', {0.0f, 1.0f, 0.0f}}, {'t', {0.5f, 0.0f, 0.5f}},
															   {'z', {1.0f, 0.0f, 0.0f}}};

	/**
	 * @brief Check if a transformation (translation or rotation) is possible
	 * @param transformPos The position of the Tetromino after a possible transformation
	 * @param gameData The current game data
	 */
	bool isValidTransform(float transformPos[8], std::vector<std::vector<Square*>>& gameData);

	/**
	 * @brief Update the 4 squares in the Tetromino with the positions array
	 */
	void updateSquares();

	/**
	 * @brief Update `boardPositions` according to the current state of `positions`
	 */
	void updateBoardPositions();

public:
	char pieceType;
	bool hidden = false;
	unsigned int pieceHeight = 2;
	unsigned int pieceWidth = 3;

	Square* squares[4];
	unsigned int boardPositions[8];

	Tetromino(){};
	virtual ~Tetromino();

	/**
	 * @brief Render the Tetromino
	 * @param pieceType The type of piece to render ('i', 'j', 'l', 'o', 's', 't', or 'z')
	 */
	void render(char pieceType);

	/**
	 * @brief Translate the piece about the X-axis
	 * @param dir The X-axis direction to translate the piece (`-1` for left & `1` for right)
	 * @returns If the translation succeeded
	 */
	bool translateX(int dir);

	/**
	 * @brief Translate the piece about the Y-axis towards the bottom of the game board
	 * @returns If the translation succeeded
	 */
	bool translateY();

	/**
	 * @brief Drop the piece towards the bottom of the game board
	 */
	void drop();

	/**
	 * @brief Update the position of the Tetromino
	 * @param startX The new starting X position of the piece (starting from the bottom left of the piece)
	 * @param startY The new starting Y position of the piece (starting from the bottom left of the piece)
	 */
	virtual void updatePos(float startX, float startY){};

	/**
	 * @brief Rotate the Tetromino
	 * @param clockwise Whether or not to rotate the Tetromino in the clockwise direction
	 * @returns If the rotation succeeded
	 */
	virtual bool rotate(bool clockwise);
};