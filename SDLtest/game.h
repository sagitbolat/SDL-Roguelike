#pragma once
#include "inputHandler.h"

namespace game {
	/*
		Map size constants
	*/
	const int MAP_WIDTH = 16;
	const int MAP_HEIGHT = 8;

	enum class TileType {
		EMPTY = 0,
		FLOOR = 1,
		WALL = 2,
		CHARACTER = 3,
		ENEMY = 4
	};

	struct WorldState {
		TileType map[MAP_HEIGHT][MAP_WIDTH];
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