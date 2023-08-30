#include "ibo.hpp"
#include "../renderer/renderer.hpp"

IBO::IBO(void* data, unsigned int count, unsigned int usage) : count(count) {
	glCall(glGenBuffers(1, &this->ibo));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));

	return;
}

IBO::~IBO() {
	glCall(glDeleteBuffers(1, &this->ibo));
}

void IBO::bind() {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo));

	return;
}

void IBO::unbind() {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	return;
}

unsigned int IBO::getElementCount() {
	return this->count;
}