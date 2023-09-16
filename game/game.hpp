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
#include "../audio/audio.hpp"
#include "gameFlags/gameFlags.hpp"
#include "gameTimer/gameTimer.hpp"
#include "glad.h"
#include <deque>
#include <vector>

class Game {
private:
	GLFWwindow* window;
	InputHandler* inputHandler;
	Audio* audio;
	Board* gameBoard;
	BoardData* boardData;
	Container* nextPieceContainer;
	Container* holdPieceContainer;

	Renderer* renderer = new Renderer();
	GameTimer* gameTimer = new GameTimer();
	GameFlags* gameFlags = new GameFlags();

	Tetromino* activePiece;
	Tetromino* holdPiece = new Tetromino();

	bool placePiece = false;
	bool pauseGame = false;
	bool canHoldStatus = true; // Whether the active piece can be currently held
	double fallInterval = 0.5; // Falling speed in seconds

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
	 * @brief Get a new hold piece
	 */
	void getHoldPiece();

	/**
	 * @brief Detect changes in the game flags and handle them accordingly
	 */
	void handleGameFlags();

	/**
	 * @brief Get a new active piece
	 * @returns A new Tetromino
	 */
	Tetromino* getActivePiece();

public:
	Game(GLFWwindow* window);
	~Game();

	/**
	 * @brief Run game loop
	 */
	void gameLoop();
};