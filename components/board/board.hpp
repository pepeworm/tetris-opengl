#pragma once

#include "../../ibo/ibo.hpp"
#include "../../renderer/renderer.hpp"
#include "../../shader/shader.hpp"
#include "../../vao/vao.hpp"
#include "../../vbo/vbo.hpp"
#include "glad.h"
#include <vector>

class BoardData {
public:
	unsigned int width = 10;
	unsigned int height = 24;

	float squareSize;
	float tPos;
	float bPos;
	float rPos;
	float lPos;

	BoardData();
};

class Board {
private:
	std::vector<float> vertexDataVector;
	std::vector<unsigned int> indicesVector;

	BoardData* data = new BoardData();

	Renderer* renderer;

	Shader* program;
	VAO* vao;
	VBO* vbo;
	IBO* ibo;

public:
	/**
	 * @brief Sets up the data necessary to render the 10 x 24 Tetris game board
	 * @param tPadding The top padding relative to the game window
	 * @param bPadding The bottom padding relative to the game window
	 * @param renderer The renderer object to use to render the game board
	 */
	Board(float tPadding, float bPadding, Renderer* renderer);
	~Board();

	/**
	 * @brief Render the Tetris game board
	 */
	void render();

	/**
	 * @brief Get the board data
	 * @returns The board data (square size, top position, etc.)
	 */
	BoardData* getBoardData();
};