#pragma once
#include "entities.h"
#include "game.h"

namespace worldState {

	struct Tile;
	extern int width;
	extern int height;

	void InitWorldState(int h, int w);
	Tile GetTile(int x, int y);
	game::TileType GetTileType(int x, int y);
	void SetTileType(int x, int y, game::TileType type);
	void SetTileBiome(int x, int y, game::BiomeType biome);
	void SetTileEntity(int x, int y, entities::Entity* entity);
	Tile* GetMap();
	void DeallocMap();
}