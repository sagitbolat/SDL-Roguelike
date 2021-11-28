#include "worldGeneration.h"
#include "worldState.h"

#include <iostream>

namespace game {

	void SpawnPlayer(int x, int y);

	void GenerateWorld(worldState::Tile* tileMap) {
		//Randomly generate world map
		int wallThickness = 1;
		for (int x = 0; x < MAP_WIDTH; x++) {
			for (int y = 0; y < MAP_HEIGHT; y++) {
				//int i = rand() % 3;
				/*switch (i)
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
				}*/
				if ((x >= wallThickness && x < MAP_WIDTH - wallThickness) 
					&& (y >= wallThickness && y < MAP_HEIGHT - wallThickness)) {
					worldState::SetTileType(x, y, TileType::FLOOR);
				}
				else { worldState::SetTileType(x, y, TileType::WALL); }
			}
		}

		//Spawn Player
		entities::InitPlayer();
		SpawnPlayer((int)MAP_WIDTH/2, (int)MAP_HEIGHT / 2);

		//Spawn enemies and loot
	}

	void SpawnPlayer(int x, int y) {
		worldState::SetTileEntity(x, y, &*entities::player);
	}
}