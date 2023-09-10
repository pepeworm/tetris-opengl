#include "tetromino.hpp"
#include <algorithm>
#include <iterator>

bool Tetromino::isValidTransform(float transformPos[8], std::vector<std::vector<Square*>>& gameData) {
	for (int i = 0; i < 4; i++) {
		// Check collision with board edges

		float xPos = transformPos[i * 2];
		float yPos = transformPos[i * 2 + 1];

		if (xPos < this->boardData->lPos || xPos > this->boardData->rPos - this->boardData->squareSize ||
			yPos < this->boardData->bPos + this->boardData->squareSize) {
			return false;
		}

		// Check collision with other game pieces

		int r = (this->boardData->tPos - yPos) / this->boardData->squareSize;
		int c = (xPos - this->boardData->lPos) / this->boardData->squareSize;

		if (!gameData[r][c]->placeholder) {
			return false;
		}
	}

	return true;
}

void Tetromino::updateSquares() {
	for (int i = 0; i < 4; i++) {
		this->squares[i]->updatePos(this->positions[i * 2], this->positions[i * 2 + 1]);
	}

	return;
}

void Tetromino::updateBoardPositions() {
	for (int i = 0; i < 4; i++) {
		this->boardPositions[i * 2] = (this->positions[i * 2] - this->boardData->lPos) / this->boardData->squareSize;
		this->boardPositions[i * 2 + 1] = (this->boardData->tPos - this->positions[i * 2 + 1]) / this->boardData->squareSize;
	}

	return;
}

Tetromino::~Tetromino() {
	for (int i = 0; i < 4; i++) {
		delete this->squares[i];
	}

	return;
}

void Tetromino::render(char pieceType) {
	if (this->hidden) {
		return;
	}
	
	for (int i = 0; i < 4; i++) {
		std::vector<float> rgb = this->pieceColor[pieceType];

		this->squares[i]->setColor(rgb[0], rgb[1], rgb[2], 1.0f);
		this->squares[i]->render();
	}

	return;
}

bool Tetromino::translateX(int dir) {
	float cX = dir * this->boardData->squareSize;

	float translatePos[8];
	std::copy(std::begin(this->positions), std::end(this->positions), std::begin(translatePos));

	for (int i = 0; i < 4; i++) {
		translatePos[i * 2] += cX;
	}

	if (this->isValidTransform(translatePos, this->boardData->gameData)) {
		for (int i = 0; i < 4; i++) {
			this->squares[i]->updatePos(translatePos[i * 2], translatePos[i * 2 + 1]);
		}

		std::copy(std::begin(translatePos), std::end(translatePos), std::begin(this->positions));
		this->updateBoardPositions();

		// Update the centerX of the Tetromino

		this->centerX += cX;

		return true;
	}

	return false;
}

bool Tetromino::translateY() {
	float translatePos[8];
	std::copy(std::begin(this->positions), std::end(this->positions), std::begin(translatePos));

	for (int i = 0; i < 4; i++) {
		translatePos[i * 2 + 1] -= this->boardData->squareSize;
	}

	if (this->isValidTransform(translatePos, this->boardData->gameData)) {
		for (int i = 0; i < 4; i++) {
			this->squares[i]->updatePos(translatePos[i * 2], translatePos[i * 2 + 1]);
		}

		std::copy(std::begin(translatePos), std::end(translatePos), std::begin(this->positions));
		this->updateBoardPositions();

		// Update the centerY of the Tetromino

		this->centerY -= this->boardData->squareSize;

		return true;
	}

	return false;
}

void Tetromino::drop() {
	while (true) {
		if (!this->translateY()) {
			break;
		}
	}

	return;
}

bool Tetromino::rotate(bool clockwise) {
	float rotatePos[8];
	std::copy(std::begin(this->positions), std::end(this->positions), std::begin(rotatePos));

	if (clockwise) {
		for (int i = 0; i < 4; i++) {
			float temp = rotatePos[i * 2 + 1] - this->centerY + this->centerX;

			rotatePos[i * 2 + 1] = -rotatePos[i * 2] + this->centerX + this->centerY;
			rotatePos[i * 2] = temp - this->boardData->squareSize;
		}
	} else {
		for (int i = 0; i < 4; i++) {
			float temp = rotatePos[i * 2] - this->centerX + this->centerY;

			rotatePos[i * 2] = -rotatePos[i * 2 + 1] + this->centerY + this->centerX;
			rotatePos[i * 2 + 1] = temp + this->boardData->squareSize;
		}
	}

	if (this->isValidTransform(rotatePos, this->boardData->gameData)) {
		for (int i = 0; i < 4; i++) {
			this->squares[i]->updatePos(rotatePos[i * 2], rotatePos[i * 2 + 1]);
		}

		std::copy(std::begin(rotatePos), std::end(rotatePos), std::begin(this->positions));
		this->updateBoardPositions();

		return true;
	}

	return false;
}
