#include "audio.hpp"

void Audio::play() {
	this->engine->play2D(this->src, true);

	return;
}

void Audio::stop() {
    this->engine->stopAllSounds();

    return;
}