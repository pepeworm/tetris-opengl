#pragma once

#include "glad.h"
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
private:
	unsigned int shaderProgram;

	/**
	 * @brief Compile a vertex/fragment shader
	 * @param type The type of shader to compile (e.g. GL_VERTEX_SHADER)
	 * @param path The file path to the shader file
	 * @returns The ID of the compiled shader
	 */
	unsigned int compileShader(unsigned int type, const char* path);

public:
	/**
	 * @brief Create a shader instance
	 */
	Shader();
	~Shader();

	/**
	 * @brief Setup the shader program and link the vertex & fragment shaders with it
	 * @param vertexShaderPath The file path to the vertex shader file
	 * @param fragmentShaderPath The file path to the fragment shader file
	 */
	void createShader(const char* vertexShaderPath, const char* fragmentShaderPath);

	/**
	 * @brief Use the shader program
	 */
	void use();

	/**
	 * @brief Set a GLSL `vec4` value of a uniform
	 * @param uniform The name of the uniform to set
	 * @param v0 Index 0 of the uniform value
	 * @param v1 Index 1 of the uniform value
	 * @param v2 Index 2 of the uniform value
	 * @param v3 Index 3 of the uniform value
	 */
	void set4Float(const char* uniform, float v0, float v1, float v2, float v3);
};