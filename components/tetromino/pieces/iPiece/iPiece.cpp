#include "iPiece.hpp"

IPiece::IPiece(Renderer* renderer, BoardData* boardData, float startX, float startY) {
	this->renderer = renderer;
	this->boardData = boardData;
	this->pieceType = 'i';
	this->pieceHeight = 1;
	this->pieceWidth = 4;

	for (int i = 0; i < 4; i++) {
		this->squares[i] = new Square(this->boardData->squareSize, 0.0f, 0.0f, this->renderer);
	}

	this->updatePos(startX, startY);

	return;
}

void IPiece::updatePos(float startX, float startY) {
	this->centerX = startX + 2 * this->boardData->squareSize;
	this->centerY = startY;

	for (int i = 0; i < 4; i++) {
		float xPos = startX + i * this->boardData->squareSize;
		float yPos = startY + this->boardData->squareSize;

		this->positions[i * 2] = xPos;
		this->positions[i * 2 + 1] = yPos;
	}

	this->updateBoardPositions();
	this->updateSquares();

	return;
}