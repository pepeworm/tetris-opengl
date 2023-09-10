#pragma once

#include "../../ibo/ibo.hpp"
#include "../../renderer/renderer.hpp"
#include "../../shader/shader.hpp"
#include "../../vao/vao.hpp"
#include "../../vbo/vbo.hpp"
#include "glad.h"
#include <vector>

class ContainerData {
public:
	float tPos;
	float bPos;
	float rPos;
	float lPos;

	ContainerData(){};
};

class Container {
private:
	float vertexData[8];
	unsigned int indices[8];

protected:
	std::vector<float> vertexDataVector;
	std::vector<unsigned int> indicesVector;

	Renderer* renderer;
	Shader* program;
	VAO* vao;
	VBO* vbo;
	IBO* ibo;

public:
	ContainerData* data = new ContainerData();

	Container(){};

	/**
	 * @brief Sets up the data necessary to render the container
	 * @param renderer The renderer object to use to render the container
	 * @param startX The X co-ordinate of the top left vertex of the container
	 * @param startY The Y co-ordinate of the top left vertex of the container
	 * @param endX The X co-ordinate of the bottom right vertex of the container
	 * @param endY The Y co-ordinate of the bottom right vertex of the container
	 */
	Container(Renderer* renderer, float startX, float startY, float endX, float endY);
	~Container();

	/**
	 * @brief Render the Tetris game board
	 */
	void render();
};