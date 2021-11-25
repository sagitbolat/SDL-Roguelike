#pragma once

#include "SDL.h"
#include "SDL_keycode.h"

namespace input {

	enum class Key {
		ESCAPE = 1,
		W = 2,
		A = 3,
		S = 4,
		D = 5,
		ENTER = 6,
		TAB = 7,
		QUIT = 8,
		UNKNOWN = 0,
		RELEASE = 9 // RELEASE IS ONLY USED FOR BUFFERING BETWEEN KEYPRESSES. NOT FOR FUNCTIONALITY
	};

	extern Key currentInput;

	Key PollInput(SDL_Event inputEvent);

}