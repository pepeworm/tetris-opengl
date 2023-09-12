#include "gameTimer.hpp"

void GameTimer::start() {
	this->prevTime = glfwGetTime();

	return;
}

double GameTimer::getElapsedTime() {
	return glfwGetTime() - prevTime;
}
