#include "game.h"
#include "worldGeneration.h"
#include <iostream>

namespace game {
	GameState gameState;

	//method identifiers
	void MovePlayerInDirection(utils::Direction direction);

	void InitGame() {
		//set game world
		gameState = GameState::GAME_MENU;

		worldState::InitWorldState(MAP_HEIGHT, MAP_WIDTH);

		//generate map
		GenerateWorld(worldState::GetMap(), MAP_WIDTH, MAP_HEIGHT);
	}

	void HandleInput(input::Key input) {
		switch (input) {
		case input::Key::W:
			std::cout << "W" << std::endl;
			MovePlayerInDirection(utils::Direction::UP);
			break;
		case input::Key::A:
			std::cout << "A" << std::endl;
			MovePlayerInDirection(utils::Direction::LEFT);
			break;
		case input::Key::S:
			std::cout << "S" << std::endl;
			MovePlayerInDirection(utils::Direction::DOWN);
			break;
		case input::Key::D:
			std::cout << "D" << std::endl;
			MovePlayerInDirection(utils::Direction::RIGHT);
			break;
		case input::Key::RELEASE:
			break;
		}
		return;
	}

	void MovePlayerInDirection(utils::Direction direction) {
		worldState::MovePlayer(direction);
	}

	void DeallocWorld() {
		delete entities::player;
		worldState::DeallocMap();
		return;
	}
}