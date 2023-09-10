#include "square.hpp"
#include <filesystem>

Square::Square(float squareSize, float posX, float posY, Renderer* renderer) : squareSize(squareSize), renderer(renderer) {
	this->placeholder = false;
	this->program = new Shader();
	program->createShader(
		(std::filesystem::current_path() / "shader/src/square/shader.vs").c_str(), (std::filesystem::current_path() / "shader/src/square/shader.fs").c_str()
	);

	this->updatePos(posX, posY);

	return;
}

Square::~Square() {
	delete this->program;
	delete this->vao;
	delete this->vbo;
	delete this->ibo;

	return;
}

void Square::setColor(float red, float green, float blue, float alpha) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;

	return;
}

void Square::render() {
	this->renderer->draw(this->program, this->vao, this->ibo, GL_TRIANGLES);
	program->set4Float("rgba", this->red, this->green, this->blue, this->alpha);

	return;
}

void Square::updatePos(float posX, float posY) {
	this->vertexData[0] = posX;
	this->vertexData[1] = posY;
	this->vertexData[2] = posX + this->squareSize;
	this->vertexData[3] = posY;
	this->vertexData[4] = posX + this->squareSize;
	this->vertexData[5] = posY - this->squareSize;
	this->vertexData[6] = posX;
	this->vertexData[7] = posY - this->squareSize;

	this->vao = new VAO();
	this->vbo = new VBO(this->vertexData, 8 * sizeof(float), GL_STATIC_DRAW);
	this->ibo = new IBO(this->indices, 6, GL_STATIC_DRAW);

	this->vbo->pushLayoutData(2, GL_FLOAT, GL_FALSE); // position attribute
	this->vao->attachBuffer(this->vbo, this->ibo);

	this->vao->unbind();
	this->vbo->unbind();
	this->ibo->unbind();

	return;
}