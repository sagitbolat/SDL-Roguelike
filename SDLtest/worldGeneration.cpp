#include "worldGeneration.h"
#include "utils.h"

#include <iostream>
#include <vector>

namespace game {
	const long WORLD_SEED = 3838291;

	void GenerateWorld(worldState::Tile* tileMap, int width, int height) {
		//set randomSeed:
		srand(WORLD_SEED);

		//Randomly generate world map
		int wallThickness = 1;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				/*if ((x >= wallThickness && x < width - wallThickness) 
					&& (y >= wallThickness && y < height - wallThickness)) {
					worldState::SetTileType(x, y, worldState::TileType::FLOOR);
				}
				else { worldState::SetTileType(x, y, worldState::TileType::WALL); }*/
				worldState::SetTileType(x, y, worldState::TileType::WALL);
			}
		}

		//Spawn Player
		entities::InitPlayer();
		worldState::MovePlayer((int)width / 2, (int)height / 2);

		//Spawn enemies and loot
	}

	void BSPtree(worldState::Tile* tileMap, int width, int height) {
		std::vector<utils::Vector2> roomCorners;
		struct TreeNode {
			int maxX = 0;
			int maxY = 0;
			int minX = 0;
			int minY = 0;
			TreeNode* left;
			TreeNode* right;

			TreeNode(int max_x, int max_y, int min_x, int min_y) {
				maxX = max_x;
				maxY = max_y;
				minX = min_x;
				minY = min_y;
				left = NULL;
				right = NULL;
			}
			void AddLeft(TreeNode* tn) {
				delete left;
				left = tn;
			}
			void AddRight(TreeNode* tn) {
				delete right;
				right = tn;
			}
			~TreeNode() {
				delete left;
				delete right;
			}
		};
		//initialize dungeon node which becomes the root of the tree:
		TreeNode dungeon(width - 1, height - 1, 0, 0);
		//create additional tree nodes recursively with a helper function

		//traverse tree and spawn a room inside the limits of each leaf node

		//connect all sister nodes with a hallway.
	}
}