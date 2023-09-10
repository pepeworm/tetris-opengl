#include "lPiece.hpp"

LPiece::LPiece(Renderer* renderer, BoardData* boardData, float startX, float startY) {
	this->renderer = renderer;
	this->boardData = boardData;
	this->pieceType = 'l';

	for (int i = 0; i < 4; i++) {
		this->squares[i] = new Square(this->boardData->squareSize, 0.0f, 0.0f, this->renderer);
	}

	this->updatePos(startX, startY);

	return;
}

void LPiece::updatePos(float startX, float startY) {
	this->centerX = startX + 1.5 * this->boardData->squareSize;
	this->centerY = startY + 0.5 * this->boardData->squareSize;

	for (int i = 0; i < 3; i++) {
		float xPos = startX + i * this->boardData->squareSize;
		float yPos = startY + this->boardData->squareSize;

		this->positions[i * 2] = xPos;
		this->positions[i * 2 + 1] = yPos;
	}

	this->positions[6] = startX + 2 * this->boardData->squareSize;
	this->positions[7] = startY + 2 * this->boardData->squareSize;

	this->updateBoardPositions();
	this->updateSquares();

	return;
}