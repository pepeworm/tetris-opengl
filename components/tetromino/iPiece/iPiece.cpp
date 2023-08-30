#include "iPiece.hpp"
#include <algorithm>

iPiece::iPiece(BoardData* boardData, Renderer* renderer) : boardData(boardData), renderer(renderer) {
	for (int i = 0; i < 4; i++) {
		float xPos = this->boardData->lPos + (i * this->boardData->squareSize + (this->boardData->width - 4) / 2 * this->boardData->squareSize);
		float yPos = this->boardData->tPos + this->boardData->squareSize;

		this->positions[i * 2] = xPos;
		this->positions[i * 2 + 1] = yPos;

		this->squares[i] = new Square(this->boardData->squareSize, xPos, yPos, this->renderer);
	}

	return;
}

iPiece::~iPiece() {
	for (int i = 0; i < 4; i++) {
		delete this->squares[i];
	}

	return;
}

void iPiece::render() {
	for (int i = 0; i < 4; i++) {
		// Don't render the square if its Y co-ordinate is outside of the game board

		if (positions[i * 2 + 1] > this->boardData->tPos) {
			continue;
		}

		this->squares[i]->render(0.0f, 1.0f, 1.0f, 1.0f);
	}

	return;
}

void iPiece::translateX(int dir) {
	float cX = dir * this->boardData->squareSize;

	if (cX > 0) {
		float xPos = -1.0f; // Location of the point on the I piece that is closest to the right edge

		for (int i = 0; i < 8; i += 2) {
			xPos = std::max(xPos, this->positions[i]);
		}

		// Check if the far right square is not already on the edge

		if (xPos + cX < this->boardData->rPos) {
			for (int i = 0; i < 4; i++) {
				this->positions[i * 2] += cX;

				this->squares[i]->updatePos(this->positions[i * 2], this->positions[i * 2 + 1]);
			}
		}
	} else {
		float xPos = 1.0f; // Location of the point on the I piece that is closest to the left edge

		for (int i = 0; i < 8; i += 2) {
			xPos = std::min(xPos, this->positions[i]);
		}
		// Check if the far left square is not already on the edge

		if (xPos > this->boardData->lPos) {
			for (int i = 0; i < 4; i++) {
				this->positions[i * 2] += cX;

				this->squares[i]->updatePos(this->positions[i * 2], this->positions[i * 2 + 1]);
			}
		}
	}

	return;
}

void iPiece::translateY() {
	// TODO check if this is touching another piece

	if (this->positions[1] - this->boardData->squareSize > this->boardData->bPos) {
		for (int i = 0; i < 4; i++) {
			this->positions[i * 2 + 1] -= this->boardData->squareSize;

			this->squares[i]->updatePos(this->positions[i * 2], this->positions[i * 2 + 1]);
		}
	}

	return;
}

void iPiece::rotate(int dir) {
	// TODO check for wall kicks

	float dist = dir * this->boardData->squareSize;

	if (dir < 0) {
		if (!this->rotationStatus) {
			this->rotationStatus = 3;
		} else {
			this->rotationStatus--;
		}
	}

	this->rotationStatus %= 4;

	if (!this->rotationStatus) {
		this->positions[0] += 2 * dist;
		this->positions[1] += dist;
		this->positions[2] += dist;
		this->positions[5] -= dist;
		this->positions[6] -= dist;
		this->positions[7] -= 2 * dist;
	} else if (this->rotationStatus == 1) {
		this->positions[0] += dist;
		this->positions[1] -= 2 * dist;
		this->positions[3] -= dist;
		this->positions[4] -= dist;
		this->positions[6] -= 2 * dist;
		this->positions[7] += dist;
	} else if (this->rotationStatus == 2) {
		this->positions[0] -= 2 * dist;
		this->positions[1] -= dist;
		this->positions[2] -= dist;
		this->positions[5] += dist;
		this->positions[6] += dist;
		this->positions[7] += 2 * dist;
	} else {
		this->positions[0] -= dist;
		this->positions[1] += 2 * dist;
		this->positions[3] += dist;
		this->positions[4] += dist;
		this->positions[6] += 2 * dist;
		this->positions[7] -= dist;
	}

	// Update squares

	for (int i = 0; i < 4; i++) {
		this->squares[i]->updatePos(this->positions[i * 2], this->positions[i * 2 + 1]);
	}

	if (dir > 0) {
		this->rotationStatus++;
	}

	return;
}