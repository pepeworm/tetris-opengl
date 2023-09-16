#pragma once

#include <audio/irrKlang.h>

#if defined(WIN32)
#include <conio.h>
#else
#include "audio/conio.h"
#endif

#pragma comment(lib, "irrKlang.lib")

class Audio {
private:
	const char* src;
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

public:
	Audio(const char* src) : src(src){};

	/**
	 * @brief Play the audio file located at the path (`src`) passed into the constructor function
	 */
	void play();

	/**
	 * @brief Stop the sound(s) being currently played
	 */
	void stop();
};