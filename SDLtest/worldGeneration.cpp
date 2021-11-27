#include "worldGeneration.h"

#include <iostream>

namespace game {

	void GenerateWorld(WorldState* state) {
		//Randomly generate world map
		for (int x = 0; x < MAP_WIDTH; x++) {
			for (int y = 0; y < MAP_HEIGHT; y++) {
				int i = rand() % 3;
				switch (i)
				{
				case 0:
					(*state).SetTileType(x, y, TileType::FLOOR);
					break;
				case 1:
					(*state).SetTileType(x, y, TileType::WALL);
					break;
				default:
					(*state).SetTileType(x, y, TileType::EMPTY);
					break;
				}
			}
		}
		//Spawn enemies and loot
	}
}