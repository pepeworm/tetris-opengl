#pragma once

#include "../ibo/ibo.hpp"
#include "../shader/shader.hpp"
#include "../vao/vao.hpp"
#include "glad.h"

// For debug & testing

#define assert(x)                                                                                                                                              \
	if (!(x))                                                                                                                                                  \
		__builtin_trap();
#define glCall(x)                                                                                                                                              \
	glClearErrors();                                                                                                                                           \
	x;                                                                                                                                                         \
	assert(glLogCall(#x, __FILE__, __LINE__));

void glClearErrors();
bool glLogCall(const char* function, const char* file, int line);

class Renderer {
private:
public:
	/**
	 * @brief Create a renderer instance
	 */
	Renderer(){};

	/**
	 * @brief Draw onto the screen
	 * @param shader The shader program to use
	 * @param vao The VAO to use
	 * @param ibo The IBO to use
	 * @param primitiveType The primitive type to render with (e.g. GL_LINES)
	 */
	void draw(Shader* shader, VAO* vao, IBO* ibo, unsigned int primitiveType);

	/**
	 * @brief Clear the screen
	 */
	void clearScreen();

	/**
	 * @brief Fill the screen with a specified color
	 * @param red The red value
	 * @param green The green value
	 * @param blue The blue value
	 * @param alpha The alpha value
	 */
	void fillScreen(float red, float green, float blue, float alpha);

	/**
	 * @brief Enables the blending of colors
	 */
	void enableBlend();
};