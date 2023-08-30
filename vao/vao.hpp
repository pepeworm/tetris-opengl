#pragma once

#include "../ibo/ibo.hpp"
#include "../vbo/vbo.hpp"
#include "glad.h"

class VAO {
private:
	unsigned int vao;

public:
	/**
	 * @brief Create a VAO instance
	 */
	VAO();
	~VAO();

	/**
	 * @brief Attach the provided IBO buffer to the VAO
	 * @param vbo The VBO buffer to attach to the VAO
	 * @param ibo The IBO buffer to attach to the VAO
	 */
	void attachBuffer(VBO* vbo, IBO* ibo);

	/**
	 * @brief Binds this VAO as the current VAO
	 */
	void bind();

	/**
	 * @brief Unbinds this VAO as the current VAO
	 */
	void unbind();
};