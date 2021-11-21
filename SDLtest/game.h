#pragma once
#include "inputHandler.h"

namespace game {
	/*
		Map size constants
	*/
	const int MAP_WIDTH = 1;
	const int MAP_HEIGHT = 1;

	struct WorldState {
		int map[MAP_HEIGHT][MAP_WIDTH];
	};

	/*
		Enum that represents gamestate
	*/
	enum class GameState {
		GAME_MENU,
		GAME_ACTIVE,
		GAME_PAUSE,
		GAME_OVER,
		GAME_QUIT
	};
	extern GameState gameState;

	//Runs at the start of the application once.
	void InitGame();
	//Runs after every input.
	WorldState GetUpdatedWorld(input::Key input);
}