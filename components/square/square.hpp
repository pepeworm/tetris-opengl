#pragma once

#include "../../ibo/ibo.hpp"
#include "../../renderer/renderer.hpp"
#include "../../shader/shader.hpp"
#include "../../vao/vao.hpp"
#include "../../vbo/vbo.hpp"
#include "glad.h"

class Square {
private:
	float squareSize;
	float red;
	float green;
	float blue;
	float alpha;

	unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

	Renderer* renderer;

	Shader* program;
	VAO* vao;
	VBO* vbo;
	IBO* ibo;

public:
	float vertexData[8];
	bool placeholder = true; // If the square is a placeholder or not

	/**
	 * @brief Create a placeholder square
	 */
	Square(){};

	/**
	 * @brief Sets up the data necessary to render a square
	 * @param squareSize The size of the square (should be equal to the square sizes on the game board)
	 * @param posX The X position of the top left vertex of the square
	 * @param posY The Y position of the top left vertex of the square
	 * @param renderer The renderer object to use to render the square
	 */
	Square(float squareSize, float posX, float posY, Renderer* renderer);
	~Square();

	/**
	 * @brief Set the color of the square
	 * @param red The red value for the color of the square
	 * @param green The green value for the color of the square
	 * @param blue The blue value for the color of the square
	 * @param alpha The alpha value for the color of the square
	 */
	void setColor(float red, float green, float blue, float alpha);

	/**
	 * @brief Render the square
	 */
	void render();

	/**
	 * @brief Update the square's position and the buffers (VAO, VBO, etc.)
	 * @param posX The X position of the top left vertex of the square
	 * @param posY The Y position of the top left vertex of the square
	 */
	void updatePos(float posX, float posY);
};