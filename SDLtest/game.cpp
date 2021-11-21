#include "game.h"
#include <iostream>

using namespace input;

namespace game {

	
	int map[MAP_HEIGHT][MAP_WIDTH];
	

	GameState gameState;

	void InitGame() {
		gameState = GameState::GAME_MENU;
	}

	WorldState GetUpdatedWorld(Key input) {
		switch (input) {
		case Key::W:
			map[1][1] = 100;
			std::cout << "W" << std::endl;
			break;
		case Key::A:
			map[1][1] = 100;
			std::cout << "A" << std::endl;
			break;
		case Key::S:
			map[1][1] = 100;
			std::cout << "S" << std::endl;
			break;
		case Key::D:
			map[1][1] = 100;
			std::cout << "D" << std::endl;
			break;
		case Key::RELEASE:
			break;
		}

		WorldState state;
		state.map[0][0] = map[0][0];
		return state;
	}
}