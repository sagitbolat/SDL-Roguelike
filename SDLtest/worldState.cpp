#include "worldState.h"
#include <iostream>

namespace game {
	namespace worldState {
		Tile* map;
		int height;
		int width;
		utils::Vector2 playerPos;
		utils::Direction playerDirection;

		//method declaration
		bool isTileWalkable(TileType type);

		struct Tile {
			TileType type;
			BiomeType biome;
			entities::Entity* currEntity;

			Tile() {
				//std::cout << "tile constructor" << std::endl;
				type = TileType::EMPTY;
				biome = BiomeType::GOBLIN_CAVE;
				currEntity = NULL;
			}

			void SetEntity(entities::Entity*& entity) {
				currEntity = entity;
			}
		};

		void InitWorldState(int h, int w) {
			map = new Tile[h * w];
			width = w;
			height = h;
		}
		Tile GetTile(int x, int y) {
			return map[y * width + x];
		}
		TileType GetTileType(int x, int y) {
			return GetTile(x, y).type;
		}
		entities::Entity* GetCurrentEntity(int x, int y) {
			return GetTile(x, y).currEntity;
		}
		
		void SetTileType(int x, int y, TileType type) {
			map[y * width + x].type = type;
			return;
		}
		void SetTileBiome(int x, int y, BiomeType biome) {
			map[y * width + x].biome = biome;
			return;
		}
		void SetTileEntity(int x, int y, entities::Entity* entity) {
			map[y * width + x].SetEntity(entity);
			return;
		}

		//THIS METHOD PRESERVES PLAYER DIRECTION
		void MovePlayer(int x, int y) {

			//if trying to move into a wall, return out of the method
			if (!isTileWalkable(map[y * width + x].type)) return;

			std::cout << "Player moved from " << playerPos.x << ", " << playerPos.y << " to " << x << ", " << y << std::endl;
			
			//check if move ends up in the bounds of the map
			if (x < 0 || y < 0 || x >= width || y >= height) return;

			//if the player is already instantiated, then remove him from his current tile
			if (map[playerPos.y * width + playerPos.x].currEntity != NULL) {
				map[playerPos.y * width + playerPos.x].currEntity = NULL;
			}
			//move the player to the new tile, if that tile is empty
			//and set the player position to the new position
			if (map[playerPos.y * width + playerPos.x].currEntity == NULL) {
				map[y * width + x].currEntity = entities::player;
				playerPos.x = x;
				playerPos.y = y;
			} else {
				//handle event if there is an entity in the tile to move to. For now throws exception
				throw "TRIED TO MOVE PLAYER TO OCCUPIED TILE. IMPLEMENT THE BEHAVIOUR IN worldState::MovePlayer() FIRST.";
			}
		}
		//THIS METHOD CHANGED PLAYER DIRECTION
		void MovePlayer(utils::Direction direction) {
			int x = playerPos.x;
			int y = playerPos.y;
			switch (direction) {
			case utils::Direction::UP:
				MovePlayer(x, y - 1);
				break;
			case utils::Direction::DOWN:
				MovePlayer(x, y + 1);
				break;
			case utils::Direction::LEFT:
				MovePlayer(x - 1, y);
				break;
			case utils::Direction::RIGHT:
				MovePlayer(x + 1, y);
				break;
			}
			// update enemy positions.
		}
		bool isTileWalkable(TileType type) {
			if (type == TileType::WALL || type == TileType::EMPTY) {
				return false;
			}
			return true;
		}
		
		Tile* GetMap() {
			return map;
		}

		void DeallocMap() {
			delete[] map;
		}
	}
}
