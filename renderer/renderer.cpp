#include "renderer.hpp"
#include <iostream>
#include <sstream>
#include <string>

void glClearErrors() {
	while (glGetError() != GL_NO_ERROR) {
		continue;
	}

	return;
}

bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::stringstream ss;
		ss << std::hex << error;
		std::string res(ss.str());

		std::cout << "[OpenGL Error]: " << '(' << res << "): " << function << ' ' << file << ':' << line << '\n';

		return false;
	}

	return true;
}

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::draw(Shader* shader, VAO* vao, IBO* ibo, unsigned int primitiveType) {
	vao->bind();
	ibo->bind();
	shader->use();

	glCall(glDrawElements(primitiveType, ibo->getElementCount(), GL_UNSIGNED_INT, (void*)0));

	return;
}

void Renderer::clearScreen() {
	glCall(glClear(GL_COLOR_BUFFER_BIT));

	return;
}

void Renderer::fillScreen(float red, float green, float blue, float alpha) {
	glCall(glClearColor(red, green, blue, alpha));

	return;
}

void Renderer::enableBlend() {
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	glCall(glEnable(GL_BLEND));

	return;
}