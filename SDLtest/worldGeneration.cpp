#include "worldGeneration.h"

#include <iostream>

namespace game {

	void SpawnPlayer(int x, int y);

	void GenerateWorld(worldState::Tile* tileMap, int width, int height) {
		//Randomly generate world map
		int wallThickness = 1;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if ((x >= wallThickness && x < width - wallThickness) 
					&& (y >= wallThickness && y < height - wallThickness)) {
					worldState::SetTileType(x, y, worldState::TileType::FLOOR);
				}
				else { worldState::SetTileType(x, y, worldState::TileType::WALL); }
			}
		}

		//Spawn Player
		entities::InitPlayer();
		worldState::MovePlayer((int)width / 2, (int)height / 2);
		//SpawnPlayer((int)width/2, (int)height / 2);

		//Spawn enemies and loot
	}

	/*void SpawnPlayer(int x, int y) {
		worldState::SetTileEntity(x, y, &*entities::player);
	}*/
}