#pragma once

#include "glad.h"

class IBO {
private:
	unsigned int ibo;
	unsigned int count;

public:
	/**
	 * @brief Sets up the IBO
	 * @param data The data to use for the IBO
	 * @param count The number of elements in the IBO
	 * @param usage The expected type of data usage (e.g. GL_STATIC_DRAW)
	*/
	IBO(void* data, unsigned int count, unsigned int usage);
	~IBO();

	/**
	 * @brief Binds this IBO as the current Array Buffer
	 */
	void bind();

	/**
	 * @brief Unbinds this IBO as the current Array Buffer
	 */
	void unbind();

	/**
	 * @brief Return the number of elements inside the IBO
	 */
	unsigned int getElementCount();
};