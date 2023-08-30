#include "vao.hpp"
#include "../renderer/renderer.hpp"

VAO::VAO() {
	glCall(glGenVertexArrays(1, &this->vao));
	glCall(glBindVertexArray(this->vao));

	return;
}

VAO::~VAO() {
	glCall(glDeleteVertexArrays(1, &this->vao));

	return;
}

void VAO::attachBuffer(VBO* vbo, IBO* ibo) {
	this->bind();
	vbo->bind();
	ibo->bind();

	unsigned int offset = 0;
	std::vector<LayoutElement*> layoutElements = vbo->getLayoutElements();

	for (int i = 0; i < layoutElements.size(); i++) {
		LayoutElement* element = layoutElements[i];
		unsigned int stride = vbo->getStride();

		glCall(glEnableVertexAttribArray(i));
		glCall(glVertexAttribPointer(i, element->count, element->type, element->normalized, stride, (void*)offset));

		offset += vbo->getAttributeSize(element->count, element->type);
	}

	return;
}

void VAO::bind() {
	glCall(glBindVertexArray(this->vao));

	return;
}

void VAO::unbind() {
	glCall(glBindVertexArray(0));

	return;
}