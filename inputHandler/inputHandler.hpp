#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "../components/board/board.hpp"
#include "../renderer/renderer.hpp"
#include "../components/tetromino/iPiece/iPiece.hpp"

class InputHandler {
private:
    GLFWwindow* window;

	bool key_right_status = false;
	bool key_left_status = false;
    bool key_up_status = false;
    bool key_z_status = false;

    iPiece* piece;

	/**
	 * @brief Handle the right arrow key input
	 */
	void handleKeyRight();

	/**
	 * @brief Handle the left arrow key input
	 */
	void handleKeyLeft();

	/**
	 * @brief Handle the up arrow key input
	 */
	void handleKeyUp();

	/**
	 * @brief Handle the Z key input
	 */
	void handleKeyZ();

public:
	/**
	 * @brief Setup input handler
	 * @param window The GLFW window object
	 */
	// InputHandler(GLFWwindow* window);
    InputHandler(GLFWwindow* window, Renderer* renderer, BoardData* boardData);
	~InputHandler();

    /**
     * @brief Begin detecting input events 
    */
    void detect();

    void DELETETHIS();
};