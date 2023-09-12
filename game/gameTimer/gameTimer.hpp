#pragma once

#include <GLFW/glfw3.h>

class GameTimer {
private:
	double prevTime; // The previous time recorded

public:
	GameTimer(){};

	/**
	 * @brief Start the timer
	 */
	void start();

	/**
	 * @brief Get time elapsed between the present time and when the timer was started
	 * @returns The time elapsed
	 */
	double getElapsedTime();
};