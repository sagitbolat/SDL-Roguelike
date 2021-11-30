#pragma once
#include "inputHandler.h"
#include "entities.h"
#include "worldState.h"
#include <iostream>

namespace game {
	/*
		Map size constants
	*/
	const int MAP_WIDTH = 80;
	const int MAP_HEIGHT = 45;

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
	void HandleInput(input::Key input);
	void DeallocWorld();
}