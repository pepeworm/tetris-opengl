#pragma once

#include "glad.h"
#include <vector>

class LayoutElement {
public:
	unsigned int count;
	unsigned int type;
	unsigned int normalized;

	LayoutElement(unsigned int count, unsigned int type, unsigned int normalized) : count(count), type(type), normalized(normalized){};
};

class VBO {
private:
	std::vector<LayoutElement*> layoutElements;
	unsigned int stride;
	unsigned int vbo;

	/**
	 * @brief Get the size in bytes of a specified OpenGL type
	 * @param type The OpenGL type to get the size in bytes of (e.g. GL_FLOAT)
	 * @returns The size in bytes of the OpenGL type
	 */
	unsigned int getSizeOfType(unsigned int type);

public:
	/**
	 * @brief Sets up the VBO
	 * @param data The data to use for the VBO
	 * @param size The size (in bytes) in the VBO
	 * @param usage The expected type of data usage (e.g. GL_STATIC_DRAW)
	 */
	VBO(void* data, unsigned int size, unsigned int usage);
	~VBO();

	/**
	 * @brief Push data for each vertex attribute to the layout for the currently bound VBO
	 * @param count The number of components in the current vertex attribute
	 * @param type The type of the current vertex attribute (e.g. GL_FLOAT)
	 * @param normalized Whether a point should be normalized
	 */
	void pushLayoutData(unsigned int count, unsigned int type, unsigned int normalized);

	/**
	 * @brief Binds this VBO as the current Array Buffer
	 */
	void bind();

	/**
	 * @brief Unbinds this VBO as the current Array Buffer
	 */
	void unbind();

	/**
	 * @brief Get the size of a vertex attribute
	 * @param count The number of components in the vertex attribute
	 * @param type The type of the current vertex attribute (e.g. GL_FLOAT)
	 * @returns The size of the vertex attribute
	 */
	unsigned int getAttributeSize(unsigned int count, unsigned int type);

	/**
	 * @brief Get the data inside the vertex buffer layout
	 * @returns The data for each vertex buffer attribute
	 */
	std::vector<LayoutElement*> getLayoutElements();

	/**
	 * @brief Get the stride (distance between each vertex in the layout)
	 * @returns The stride
	 */
	unsigned int getStride();
};