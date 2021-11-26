#include "game.h"
#include <iostream>

using namespace input;

namespace game {

	WorldState state;

	GameState gameState;

	void InitGame() {
		gameState = GameState::GAME_MENU;
	}

	WorldState GetUpdatedWorld(Key input) {
		switch (input) {
		case Key::W:
			std::cout << "W" << std::endl;
			break;
		case Key::A:
			std::cout << "A" << std::endl;
			break;
		case Key::S:
			std::cout << "S" << std::endl;
			break;
		case Key::D:
			std::cout << "D" << std::endl;
			break;
		case Key::RELEASE:
			break;
		}
		return state;
	}
}