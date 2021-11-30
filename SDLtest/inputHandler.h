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
		SHIFT = 8,
		QUIT = 9,
		UNKNOWN = 0,
		RELEASE = 10 // RELEASE IS ONLY USED FOR BUFFERING BETWEEN KEYPRESSES. NOT FOR FUNCTIONALITY
	};

	extern Key currentInput;

	Key PollInput(SDL_Event inputEvent);

}