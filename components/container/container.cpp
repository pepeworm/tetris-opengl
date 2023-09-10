#include "container.hpp"
#include <filesystem>

Container::Container(Renderer* renderer, float startX, float startY, float endX, float endY) : renderer(renderer) {	
	this->data->lPos = startX;
    this->data->tPos = startY;
    this->data->rPos = endX;
    this->data->bPos = endY;

	// Fill in positions array

	this->vertexData[0] = startX;
	this->vertexData[1] = startY;
	this->vertexData[2] = endX;
	this->vertexData[3] = startY;
	this->vertexData[4] = startX;
	this->vertexData[5] = endY;
	this->vertexData[6] = endX;
	this->vertexData[7] = endY;

	// Fill in indices array

	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 1;
	this->indices[3] = 3;
	this->indices[4] = 3;
	this->indices[5] = 2;
	this->indices[6] = 2;
	this->indices[7] = 0;

	// Initialize shader program, VAO, VBO and IBO

	this->program = new Shader();
	program->createShader(
		(std::filesystem::current_path() / "shader/src/container/shader.vs").c_str(), (std::filesystem::current_path() / "shader/src/container/shader.fs").c_str()
	);

	this->vao = new VAO();
	this->vbo = new VBO(vertexData, 8 * sizeof(float), GL_STATIC_DRAW);
	this->ibo = new IBO(indices, 8, GL_STATIC_DRAW);

	this->vbo->pushLayoutData(2, GL_FLOAT, GL_FALSE);
	this->vao->attachBuffer(this->vbo, this->ibo);

	this->vao->unbind();
	this->vbo->unbind();
	this->ibo->unbind();

	return;
}

Container::~Container() {
	delete this->program;
	delete this->vao;
	delete this->vbo;
	delete this->ibo;

	return;
}

void Container::render() {
	this->renderer->draw(this->program, this->vao, this->ibo, GL_LINES);

	return;
}