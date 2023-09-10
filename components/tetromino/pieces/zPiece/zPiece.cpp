#include "zPiece.hpp"

ZPiece::ZPiece(Renderer* renderer, BoardData* boardData, float startX, float startY) {
	this->renderer = renderer;
	this->boardData = boardData;
	this->pieceType = 'z';

	for (int i = 0; i < 4; i++) {
		this->squares[i] = new Square(this->boardData->squareSize, 0.0f, 0.0f, this->renderer);
	}

	this->updatePos(startX, startY);

	return;
}

void ZPiece::updatePos(float startX, float startY) {
	this->centerX = startX + 1.5 * this->boardData->squareSize;
	this->centerY = startY + 0.5 * this->boardData->squareSize;

	for (int i = 0; i < 2; i++) {
		float xPos = startX + i * this->boardData->squareSize;
		float yPos = startY + 2 * this->boardData->squareSize;

		this->positions[i * 2] = xPos;
		this->positions[i * 2 + 1] = yPos;
	}

	for (int i = 2; i < 4; i++) {
		float xPos = startX + (i - 1) * this->boardData->squareSize;
		float yPos = startY + this->boardData->squareSize;

		this->positions[i * 2] = xPos;
		this->positions[i * 2 + 1] = yPos;
	}

	this->updateBoardPositions();
	this->updateSquares();

	return;
}