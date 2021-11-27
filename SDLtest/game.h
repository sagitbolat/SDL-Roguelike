#pragma once
#include "inputHandler.h"
#include "entities.h"

namespace game {
	/*
		Map size constants
	*/
	const int MAP_WIDTH = 160;
	const int MAP_HEIGHT = 90;

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
		TileType type;
		BiomeType biome;
		entities::Entity currentEntity;

		Tile() {
			type = TileType::EMPTY;
			biome = BiomeType::GOBLIN_CAVE;
		}

		Tile(TileType tp, BiomeType bm, entities::Entity entity) {
			type = tp;
			biome = bm;
			currentEntity = entity;
		}
	};

	struct WorldState {
		Tile* map;
		int width;
		int height;
		WorldState(int h, int w) {
			map = new Tile[h * w];
			width = w;
			height = h;
		}

		Tile GetTile(int x, int y) {
			return map[y * width + x];
		}
		void SetTileType(int x, int y, TileType type) {
			map[y * width + x].type = type;
			return;
		}
		void SetTileBiome(int x, int y, BiomeType biome) {
			map[y * width + x].biome = biome;
			return;
		}
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
	WorldState* GetUpdatedWorld(input::Key input);
	void DeallocWorld();
}