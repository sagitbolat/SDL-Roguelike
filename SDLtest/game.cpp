#include "game.h"
#include "entities.h"
#include <iostream>

namespace game {

	WorldState* state = new WorldState();

	GameState gameState;

	//function declarations
	void GenerateWorld();

	void InitGame() {
		gameState = GameState::GAME_MENU;
		GenerateWorld();
	}

	void GenerateWorld() {
		//Randomly generate world map

		//Spawn enemies and loot
	}

	WorldState GetUpdatedWorld(input::Key input) {
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
		return *state;
	}

	void DeallocWorld() {
		delete state;
		return;
	}
}