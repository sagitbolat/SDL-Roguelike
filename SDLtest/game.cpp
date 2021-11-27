#include "game.h"
#include "entities.h"
#include "worldGeneration.h"
#include <iostream>

namespace game {

	WorldState* state = new WorldState(MAP_HEIGHT, MAP_WIDTH);

	GameState gameState;

	void InitGame() {
		//set game world
		gameState = GameState::GAME_MENU;

		//generate map
		GenerateWorld(state);
	}

	WorldState* GetUpdatedWorld(input::Key input) {
		switch (input) {
		case input::Key::W:
			std::cout << "W" << std::endl;
			break;
		case input::Key::A:
			std::cout << "A" << std::endl;
			break;
		case input::Key::S:
			std::cout << "S" << std::endl;
			break;
		case input::Key::D:
			std::cout << "D" << std::endl;
			break;
		case input::Key::RELEASE:
			break;
		}
		return state;
	}

	void DeallocWorld() {
		delete[] state->map;
		delete state;
		return;
	}
}