#pragma once

#include "glad.h"

class GameFlags {
public:
	int rotateStatus = 0;
	int translateXStatus = 0;
	bool pauseStatus = false;
	bool dropStatus = false;
    bool softDropStatus = false;
	bool holdStatus = false;

	GameFlags(){};
};