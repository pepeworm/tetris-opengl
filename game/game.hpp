#pragma once

#include "../components/container/board/board.hpp"
#include "../components/tetromino/pieces/iPiece/iPiece.hpp"
#include "../components/tetromino/pieces/jPiece/jPiece.hpp"
#include "../components/tetromino/pieces/lPiece/lPiece.hpp"
#include "../components/tetromino/pieces/oPiece/oPiece.hpp"
#include "../components/tetromino/pieces/sPiece/sPiece.hpp"
#include "../components/tetromino/pieces/tPiece/tPiece.hpp"
#include "../components/tetromino/pieces/zPiece/zPiece.hpp"
#include "../inputHandler/inputHandler.hpp"
#include "../renderer/renderer.hpp"
#include "glad.h"
#include <deque>
#include <vector>

class GameTimer {
private:
	double prevTime; // The previous time recorded

public:
	GameTimer(){};

	/**
	 * @brief Start the timer
	 */
	void start();

	/**
	 * @brief Get time elapsed between the present time and when the timer was started
	 * @returns The time elapsed
	 */
	double getElapsedTime();
};

class Game {
private:
	Renderer* renderer;
	Board* gameBoard;
	BoardData* boardData;
	GameTimer *gameTimer, pieceTimer;
	InputHandler* inputHandler;
	Container* nextPieceContainer;
	Container* holdPieceContainer;

	std::vector<char> validPieces = {'i', 'j', 'l', 'o', 's', 't', 'z'};
	std::deque<Tetromino*> nextPieces;

	/**
	 * @brief Generate new next Tetromino pieces and push it into the pieces queue
	 */
	void genNextPieces(unsigned int elems);

	/**
	 * @brief Place the active Tetromino piece onto the game board
	 */
	void placeActivePiece();

	/**
	 * @brief Render the currently held piece, if available
	 */
	void renderHoldPiece();

	/**
	 * @brief Renders the played pieces in the game data
	 */
	void renderPlayedPieces();

	/**
	 * @brief Check and clear rows if possible
	 */
	void clearRows();

	/**
	 * @brief Initialize the new active piece's initial position
	 */
	void initActivePiece();

public:
	bool placePiece = false;
	double fallInterval = 0.5; // Falling speed in seconds

	GLFWwindow* window;
	Tetromino* activePiece;
	Tetromino* holdPiece = new Tetromino();

	Game(GLFWwindow* window);
	~Game();

	/**
	 * @brief Run game loop
	 */
	void gameLoop();

	/**
	 * @brief Get a new active piece
	 * @returns A new Tetromino
	 */
	Tetromino* getActivePiece();
};