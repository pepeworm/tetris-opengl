#include "game.hpp"
#include <algorithm>
#include <random>

void GameTimer::start() {
	this->prevTime = glfwGetTime();

	return;
}

double GameTimer::getElapsedTime() {
	return glfwGetTime() - prevTime;
}

void Game::genNextPieces(unsigned int elems) {
	std::vector<char> temp;
	std::sample(this->validPieces.begin(), this->validPieces.end(), std::back_inserter(temp), elems, std::mt19937{std::random_device{}()});

	for (char type : temp) {
		Tetromino* nextPiece;

		if (type == 'i') {
			nextPiece = new IPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		} else if (type == 'j') {
			nextPiece = new JPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		} else if (type == 'l') {
			nextPiece = new LPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		} else if (type == 'o') {
			nextPiece = new OPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		} else if (type == 's') {
			nextPiece = new SPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		} else if (type == 't') {
			nextPiece = new TPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		} else {
			nextPiece = new ZPiece(this->renderer, this->boardData, 0.0f, 0.0f);
		}

		this->nextPieces.push_back(nextPiece);
	}

	// Place next pieces inside the "next piece" container

	float totalPiecesHeight = 0.0f; // Total height of all generated pieces

	for (auto& nextPiece : this->nextPieces) {
		totalPiecesHeight += this->boardData->squareSize * nextPiece->pieceHeight;
	}

	float containerHeight = this->nextPieceContainer->data->tPos - this->nextPieceContainer->data->bPos;
	float containerWidth = this->nextPieceContainer->data->rPos - this->nextPieceContainer->data->lPos;
	float piecePadding = (containerHeight - totalPiecesHeight) / 3;
	float startY = this->nextPieceContainer->data->tPos - piecePadding;

	for (auto& nextPiece : this->nextPieces) {
		float startX = this->nextPieceContainer->data->lPos + (containerWidth - this->boardData->squareSize * nextPiece->pieceWidth) / 2;
		nextPiece->updatePos(startX, startY);

		startY -= this->boardData->squareSize * nextPiece->pieceHeight + piecePadding;
	}

	return;
}

void Game::placeActivePiece() {
	for (int i = 0; i < 4; i++) {
		unsigned int r = this->activePiece->boardPositions[i * 2 + 1];
		unsigned int c = this->activePiece->boardPositions[i * 2];

		this->boardData->gameData[r][c] = this->activePiece->squares[i];
	}

	return;
}

void Game::renderHoldPiece() {
	if (this->holdPiece->hidden) {
		return;
	}

	float pieceHeight = this->holdPiece->pieceHeight * this->boardData->squareSize;
	float pieceWidth = this->holdPiece->pieceWidth * this->boardData->squareSize;

	float containerHeight = this->holdPieceContainer->data->tPos - this->holdPieceContainer->data->bPos;
	float containerWidth = this->holdPieceContainer->data->rPos - this->holdPieceContainer->data->lPos;
	float startX = this->holdPieceContainer->data->lPos + (containerWidth - pieceWidth) / 2;
	float startY = this->holdPieceContainer->data->tPos - (containerHeight - pieceHeight) / 2;

	this->holdPiece->updatePos(startX, startY);

	return;
}

void Game::renderPlayedPieces() {
	for (auto& r : this->boardData->gameData) {
		for (auto& c : r) {
			if (!c->placeholder) {
				c->render();
			}
		}
	}

	return;
}

void Game::clearRows() {
	unsigned int startRow = -1; // First complete row
	unsigned int rowCnt = 0; // Total number of rows to clear

	// Get rows to clear

	for (int r = 0; r < this->boardData->height; r++) {
		bool validRow = true; // Whether a row can be cleared

		for (int c = 0; c < this->boardData->width; c++) {
			if (this->boardData->gameData[r][c]->placeholder) {
				validRow = false;

				break;
			}
		}

		if (validRow) {
			if (startRow == -1) {
				startRow = r;
			}

			rowCnt++;
		}
	}

	// Clear the rows

	for (int r = startRow; r < startRow + rowCnt; r++) {
		for (int c = 0; c < this->boardData->width; c++) {
			delete this->boardData->gameData[r][c];

			this->boardData->gameData[r][c] = new Square();
		}
	}

	// Move all rows above rowCnt rows down

	for (int r = startRow - 1; r >= 0; r--) {
		for (int c = 0; c < this->boardData->width; c++) {
			if (this->boardData->gameData[r][c]->placeholder) {
				continue;
			}

			float xPos = this->boardData->gameData[r][c]->vertexData[0];
			float yPos = this->boardData->gameData[r][c]->vertexData[1];

			this->boardData->gameData[r][c]->updatePos(xPos, yPos - rowCnt * this->boardData->squareSize);
			this->boardData->gameData[r + rowCnt][c] = this->boardData->gameData[r][c];
			this->boardData->gameData[r][c] = new Square();
		}
	}

	return;
}

void Game::initActivePiece() {
	float startX = this->boardData->lPos + this->boardData->squareSize * ((this->boardData->width - activePiece->pieceWidth) / 2);
	activePiece->updatePos(startX, this->boardData->tPos - 2 * this->boardData->squareSize);

	return;
}

Game::Game(GLFWwindow* window) : window(window) {
	this->renderer = new Renderer();
	this->inputHandler = new InputHandler(this);

	this->gameBoard = new Board(renderer, 0.2f, 0.2f);
	this->boardData = gameBoard->data;

	this->gameTimer = new GameTimer();

	// Get co-ordinates for the "next piece"

	float containerWidth = (1.0f - this->boardData->rPos) * 0.6;
	float containerHeight = (this->boardData->tPos - this->boardData->bPos) * 0.5;
	float containerPadding = (1.0f - containerWidth - this->boardData->rPos) / 2;

	float containerStartX = this->boardData->rPos + containerPadding;
	float containerStartY = this->boardData->tPos;
	float containerEndX = containerStartX + containerWidth;
	float containerEndY = containerStartY - containerHeight;

	this->nextPieceContainer = new Container(renderer, containerStartX, containerStartY, containerEndX, containerEndY);

	// Get co-ordinates for the "hold piece" container

	containerHeight = (this->boardData->tPos - this->boardData->bPos) * 0.25;

	containerStartX = -1.0f + containerPadding;
	containerStartY = this->boardData->tPos;
	containerEndX = containerStartX + containerWidth;
	containerEndY = containerStartY - containerHeight;

	this->holdPieceContainer = new Container(renderer, containerStartX, containerStartY, containerEndX, containerEndY);

	// Generate the next pieces and set the current active piece & placeholder hold piece

	this->genNextPieces(3);
	this->activePiece = this->getActivePiece();
	this->holdPiece->hidden = true;

	// Begin game timer

	this->gameTimer->start();

	return;
}

Game::~Game() {
	delete this->gameBoard;
	delete this->nextPieceContainer;
	delete this->holdPieceContainer;
	delete this->activePiece;

	return;
}

void Game::gameLoop() {
	this->renderer->clearScreen();
	this->renderer->enableBlend();
	this->renderer->fillScreen(0.06f, 0.11f, 0.14f, 1.0f);

	// Handle input

	this->inputHandler->detect();

	// Draw elements

	this->renderPlayedPieces();
	this->activePiece->render(this->activePiece->pieceType);
	this->nextPieceContainer->render();
	this->holdPieceContainer->render();
	this->gameBoard->render();

	// Render next pieces

	for (auto& nextPiece : this->nextPieces) {
		nextPiece->render(nextPiece->pieceType);
	}

	// Active piece logic

	if (this->gameTimer->getElapsedTime() >= this->fallInterval) {
		if (!this->activePiece->translateY()) {
			// Give the active piece 1 more cycle of time to transform before placing it down

			if (this->placePiece) {
				this->placeActivePiece();
				this->clearRows();

				this->activePiece = this->getActivePiece();
				this->placePiece = false;
				this->inputHandler->setHoldStatus(true);
			} else {
				this->placePiece = true;
			}
		}

		this->gameTimer->start();
	}

	return;
}

Tetromino* Game::getActivePiece() {
	Tetromino* activePiece = this->nextPieces.front();
	this->nextPieces.pop_front();

	// Move active piece onto the game board

	this->initActivePiece();

	// Fill in new piece in the next pieces

	this->genNextPieces(1);

	return activePiece;
}