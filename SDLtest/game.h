#pragma once
#include "inputHandler.h"
#include "entities.h"

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

	enum class BiomeType {
		GOBLIN_CAVE = 0,
		ORC_DEN = 1,
		DRAGON_LAIR = 2,
	};

	struct Tile {
		int x;
		int y;
		int colorBG;
		int colorFG;
		TileType type;
		BiomeType biome;
		entities::Entity currentEntity;

		Tile() {
		}

		Tile(int _x, int _y, int bg, int fg, TileType tp, BiomeType bm, entities::Entity entity) {
			x = _x;
			y = _y;
			colorBG = bg;
			colorFG = fg;
			type = tp;
			biome = bm;
			currentEntity = entity;
		}
	};

	struct WorldState {
		Tile map[MAP_HEIGHT][MAP_WIDTH];
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
	void DeallocWorld();
}