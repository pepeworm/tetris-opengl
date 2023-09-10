#include "board.hpp"
#include <filesystem>

Board::Board(Renderer* renderer, float tPadding, float bPadding) {
	this->renderer = renderer;
	this->data->gameData.resize(this->data->height, std::vector<Square*>(this->data->width, new Square()));

	// Fill in positions array

	this->data->tPos = 1.0f - tPadding; // Top-most position
	this->data->bPos = -1.0f + bPadding; // Bottom-most position

	float xPadding = (2.0f - ((this->data->tPos - this->data->bPos) / 12 * 5)) / 2; // X-axis padding to set the grid in a 5:12 ratio
	this->data->rPos = 1.0f - xPadding; // Right-most position
	this->data->lPos = -1.0f + xPadding; // Left-most position

	this->data->squareSize = (this->data->rPos - this->data->lPos) / this->data->width; // The distance between each vertex

	for (int i = 0; i <= this->data->height; i++) {
		for (int j = 0; j <= this->data->width; j++) {
			this->vertexDataVector.push_back(this->data->lPos + j * this->data->squareSize); // X co-ordinate
			this->vertexDataVector.push_back(this->data->tPos - i * this->data->squareSize); // Y co-ordinate
		}
	}

	// Fill in indices array

	// Horizontal

	for (int i = 0; i < this->vertexDataVector.size() / 2; i += this->data->width + 1) {
		this->indicesVector.push_back(i);
		this->indicesVector.push_back(i + this->data->width);
	}

	// Vertical

	for (int i = 0; i <= this->data->width; i++) {
		this->indicesVector.push_back(i);
		this->indicesVector.push_back(i + (this->data->width + 1) * this->data->height);
	}

	// Initialize shader program, VAO, VBO and IBO

	this->program = new Shader();
	program->createShader(
		(std::filesystem::current_path() / "shader/src/container/shader.vs").c_str(),
		(std::filesystem::current_path() / "shader/src/container/shader.fs").c_str()
	);

	this->vao = new VAO();
	this->vbo = new VBO(&this->vertexDataVector[0], this->vertexDataVector.size() * sizeof(float), GL_STATIC_DRAW);
	this->ibo = new IBO(&this->indicesVector[0], this->indicesVector.size(), GL_STATIC_DRAW);

	this->vbo->pushLayoutData(2, GL_FLOAT, GL_FALSE);
	this->vao->attachBuffer(this->vbo, this->ibo);

	this->vao->unbind();
	this->vbo->unbind();
	this->ibo->unbind();

	return;
}