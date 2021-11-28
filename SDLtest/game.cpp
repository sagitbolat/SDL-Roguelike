#include "game.h"
#include "entities.h"
#include "worldGeneration.h"
#include <iostream>

namespace game {
	GameState gameState;

	void InitGame() {
		//set game world
		gameState = GameState::GAME_MENU;

		worldState::InitWorldState(MAP_HEIGHT, MAP_WIDTH);

		//generate map
		GenerateWorld(worldState::GetMap());
	}

	void UpdateWorld(input::Key input) {
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
		return;
	}

	void DeallocWorld() {
		delete entities::player;
		worldState::DeallocMap();
		return;
	}
}