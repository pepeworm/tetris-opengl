#include "gameState.hpp"
#include <algorithm>
#include <random>

GameState::GameState() {
	this->audio = new Audio("audio/media/domination.wav");
	this->gameBoard = new Board(this->renderer, 0.25f, 0.25f);
	this->gameTimer = new GameTimer();

	this->boardData = gameBoard->data;
	this->holdPiece->hidden = true;
	this->audio->play();

	// Get co-ordinates for the "next piece"

	float containerWidth = (1.0f - this->boardData->rPos) * 0.7;
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

	// Begin game timer

	this->gameTimer->start();

	return;
}

void GameState::handleGameFlags() {
	if (this->gameFlags->rotateStatus) {
		this->activePiece->rotate(this->gameFlags->rotateStatus + 1);
		this->gameFlags->rotateStatus = 0;
	}

	if (this->gameFlags->translateXStatus) {
		this->activePiece->translateX(this->gameFlags->translateXStatus);
		this->gameFlags->translateXStatus = 0;
	}

	if (this->gameFlags->pauseStatus) {
		this->pauseGame = true;
	} else {
		this->pauseGame = false;
	}

	if (this->gameFlags->dropStatus) {
		this->activePiece->drop();
		this->placePiece = true;
		this->gameFlags->dropStatus = false;
	}

	if (this->gameFlags->softDropStatus) {
		this->fallInterval = 0.05;
		this->gameFlags->softDropStatus = false;
	} else {
		this->fallInterval = 0.5;
	}

	if (this->gameFlags->holdStatus) {
		this->getHoldPiece();
		this->gameFlags->holdStatus = false;
	}

	return;
}

void GameState::genNextPieces(unsigned int elems) {
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
	float piecePadding = (containerHeight - totalPiecesHeight) / 4;

	float startY = this->nextPieceContainer->data->tPos - piecePadding;

	for (auto& nextPiece : this->nextPieces) {
		startY -= this->boardData->squareSize * nextPiece->pieceHeight;

		float startX = this->nextPieceContainer->data->lPos + (containerWidth - this->boardData->squareSize * nextPiece->pieceWidth) / 2;
		nextPiece->updatePos(startX, startY);

		startY -= piecePadding;
	}

	return;
}

void GameState::getHoldPiece() {
	if (!this->canHoldStatus) {
		return;
	}

	if (this->holdPiece->hidden) {
		// Hold piece not previously set

		this->holdPiece = this->activePiece;
		this->activePiece = this->getActivePiece();
	} else {
		// Hold piece exists

		std::swap(this->activePiece, this->holdPiece);

		float startX = this->boardData->lPos + this->boardData->squareSize * ((this->boardData->width - this->activePiece->pieceWidth) / 2);
		float startY = this->boardData->tPos - 2 * this->boardData->squareSize;

		this->activePiece->updatePos(startX, startY);
	}

	this->canHoldStatus = false;

	float containerHeight = this->holdPieceContainer->data->tPos - this->holdPieceContainer->data->bPos;
	float containerWidth = this->holdPieceContainer->data->rPos - this->holdPieceContainer->data->lPos;
	float pieceXPadding = (containerWidth - this->boardData->squareSize * this->holdPiece->pieceWidth) / 2;
	float pieceYPadding =
		(containerHeight - this->boardData->squareSize * this->holdPiece->pieceHeight) / 2 + this->boardData->squareSize * this->holdPiece->pieceHeight;

	float startX = this->holdPieceContainer->data->lPos + pieceXPadding;
	float startY = this->holdPieceContainer->data->tPos - pieceYPadding;

	this->holdPiece->updatePos(startX, startY);

	return;
}

Tetromino* GameState::getActivePiece() {
	Tetromino* activePiece = this->nextPieces.front();
	this->nextPieces.pop_front();

	// Move active piece onto the game board

	float startX = this->boardData->lPos + this->boardData->squareSize * ((this->boardData->width - activePiece->pieceWidth) / 2);
	float startY = this->boardData->tPos - 2 * this->boardData->squareSize;

	activePiece->updatePos(startX, startY);

	// Fill in new piece in the next pieces

	this->genNextPieces(1);

	return activePiece;
}