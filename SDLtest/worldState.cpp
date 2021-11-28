#include "worldState.h"
#include <iostream>

namespace game {
	namespace worldState {
		Tile* map;
		int height;
		int width;

		struct Tile {
			TileType type;
			BiomeType biome;
			entities::Entities currentEntity;
			entities::Entity* currEntity;

			Tile() {
				//std::cout << "tile constructor" << std::endl;
				type = TileType::EMPTY;
				biome = BiomeType::GOBLIN_CAVE;
				currentEntity = entities::Entities::NONE;
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
		Tile* GetMap() {
			return map;
		}
		void DeallocMap() {
			delete[] map;
		}

	}
}
