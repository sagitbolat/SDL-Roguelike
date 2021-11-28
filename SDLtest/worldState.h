#pragma once
#include "entities.h"


namespace game {
	namespace worldState {

		struct Tile;
		extern int width;
		extern int height;

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

		void InitWorldState(int h, int w);
		TileType GetTileType(int x, int y);
		entities::Entity* GetCurrentEntity(int x, int y);
		void SetTileType(int x, int y, TileType type);
		void SetTileBiome(int x, int y, BiomeType biome);
		void SetTileEntity(int x, int y, entities::Entity* entity);
		Tile* GetMap();
		void DeallocMap();
	}
}