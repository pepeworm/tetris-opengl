#include "shader.hpp"
#include "../renderer/renderer.hpp"

Shader::Shader() {
	this->shaderProgram = glCreateProgram();

	return;
}

Shader::~Shader() {
	glDeleteShader(shaderProgram);

	return;
}

unsigned int Shader::compileShader(unsigned int type, const char* path) {
	std::string rawCode;
	std::ifstream shaderFile;
	std::stringstream shaderStream;

	shaderFile.open(path);
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	rawCode = shaderStream.str();
	const char* shaderCode = rawCode.c_str();

	unsigned int shaderID = glCreateShader(type);
	glCall(glShaderSource(shaderID, 1, &shaderCode, NULL));
	glCall(glCompileShader(shaderID));

	// Check for shader compile errors

	int result;
	int length;
	glCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result));

	if (!result) {
		glCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));

		char* msg = (char*)malloc(length * sizeof(char));
		glCall(glGetShaderInfoLog(shaderID, length, &length, msg));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << '\n';
		std::cout << msg << '\n';

		glCall(glDeleteShader(shaderID));

		return 0;
	}

	return shaderID;
}

void Shader::createShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	unsigned int vertexShader = this->compileShader(GL_VERTEX_SHADER, vertexShaderPath);
	unsigned int fragmentShader = this->compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	glCall(glAttachShader(this->shaderProgram, vertexShader));
	glCall(glAttachShader(this->shaderProgram, fragmentShader));
	glCall(glLinkProgram(this->shaderProgram));

	// Check for shader program linking errors

	int result;
	int length;

	glCall(glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &result));

	if (!result) {
		glCall(glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &length));

		char* msg = (char*)malloc(length * sizeof(char));
		glCall(glGetShaderInfoLog(this->shaderProgram, length, &length, msg));

		std::cout << "Shader program failed to link" << '\n';
		std::cout << msg << '\n';

		glCall(glDeleteShader(this->shaderProgram));

		return;
	}

	glCall(glDeleteShader(vertexShader));
	glCall(glDeleteShader(fragmentShader));

	return;
}

void Shader::use() {
	glUseProgram(this->shaderProgram);

	return;
}

void Shader::set4Float(const char* uniform, float v0, float v1, float v2, float v3) {
	glCall(glUniform4f(glGetUniformLocation(this->shaderProgram, uniform), v0, v1, v2, v3));

	return;
}