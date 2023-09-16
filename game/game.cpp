#include "game.hpp"

void Game::placeActivePiece() {
	for (int i = 0; i < 4; i++) {
		unsigned int r = this->gameState->activePiece->boardPositions[i * 2 + 1];
		unsigned int c = this->gameState->activePiece->boardPositions[i * 2];

		this->gameState->boardData->gameData[r][c] = this->gameState->activePiece->squares[i];
	}

	return;
}

Game::Game(GLFWwindow* window) : window(window) {
	this->inputHandler = new InputHandler(window, this->gameState->gameFlags);

	// Generate the next pieces and set the current active piece

	this->gameState->genNextPieces(3);
	this->gameState->activePiece = this->gameState->getActivePiece();

	return;
}

Game::~Game() {
	delete this->gameState->gameBoard;
	delete this->gameState->nextPieceContainer;
	delete this->gameState->holdPieceContainer;
	delete this->gameState->activePiece;

	return;
}

void Game::gameLoop() {
	// Prepare screen

	this->gameState->renderer->clearScreen();
	this->gameState->renderer->enableBlend();
	this->gameState->renderer->fillScreen(0.06f, 0.11f, 0.14f, 1.0f);

	// Handle input

	if (!this->gameState->placePiece) {
		this->inputHandler->detect();
	}

	this->gameState->handleGameFlags();

	// Check for a top out

	if (this->gameState->boardData->checkTopOut()) {
		this->gameState->audio->stop();
		
		delete this->gameState;
		this->gameState = new GameState();

		this->inputHandler = new InputHandler(this->window, this->gameState->gameFlags);

		// Generate the next pieces and set the current active piece

		this->gameState->genNextPieces(3);
		this->gameState->activePiece = this->gameState->getActivePiece();

		return;
	}

	// Draw elements

	if (!this->gameState->holdPiece->hidden) {
		this->gameState->holdPiece->render(this->gameState->holdPiece->pieceType);
	}

	this->gameState->boardData->renderPlayedPieces();
	this->gameState->activePiece->render(this->gameState->activePiece->pieceType);
	this->gameState->nextPieceContainer->render();
	this->gameState->holdPieceContainer->render();
	this->gameState->gameBoard->render();

	// Render next pieces

	for (auto& nextPiece : this->gameState->nextPieces) {
		nextPiece->render(nextPiece->pieceType);
	}

	// Check if the game is paused

	if (this->gameState->pauseGame) {
		return;
	}

	// Active piece logic

	if (this->gameState->fallInterval && this->gameState->gameTimer->getElapsedTime() >= this->gameState->fallInterval) {
		if (!this->gameState->activePiece->translateY()) {
			// Give the active piece 1 more cycle of time to transform before placing it down

			if (this->gameState->placePiece) {
				this->placeActivePiece();
				this->gameState->boardData->clearRows();

				this->gameState->activePiece = this->gameState->getActivePiece();
				this->gameState->fallInterval = 0.5;
				this->gameState->placePiece = false;
			} else {
				this->gameState->placePiece = true;
			}

			this->gameState->canHoldStatus = true;
		}

		this->gameState->gameTimer->start();
	}

	return;
}