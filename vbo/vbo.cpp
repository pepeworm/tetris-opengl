#include "vbo.hpp"
#include "../renderer/renderer.hpp"

unsigned int VBO::getSizeOfType(unsigned int type) {
	switch (type) {
	case GL_FLOAT:
		return 4;
	case GL_UNSIGNED_INT:
		return 4;
	}

	assert(false);

	return 0;
}

VBO::VBO(void* data, unsigned int size, unsigned int usage) : stride(0) {
	glCall(glGenBuffers(1, &this->vbo));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, this->vbo));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));

	return;
}

VBO::~VBO() {
	glCall(glDeleteBuffers(1, &this->vbo));

	return;
}

void VBO::pushLayoutData(unsigned int count, unsigned int type, unsigned int normalized) {
	this->layoutElements.push_back(new LayoutElement(count, type, normalized));
	this->stride += this->getAttributeSize(count, type);

	return;
}

void VBO::bind() {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, this->vbo));

	return;
}

void VBO::unbind() {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	return;
}

unsigned int VBO::getAttributeSize(unsigned int count, unsigned int type) {
	return count * this->getSizeOfType(type);
}

std::vector<LayoutElement*> VBO::getLayoutElements() {
	return this->layoutElements;
}

unsigned int VBO::getStride() {
	return this->stride;
}