#include "worldGeneration.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <cmath> 

namespace game {
	const long WORLD_SEED = 3838291;

	namespace BSP {
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
			bool IsLeaf() {
				return (left == NULL && right == NULL);
			}
			~TreeNode() {
				delete left;
				delete right;
			}
		};
		const int SMALLEST_PARTITION_SIZE = 10;
		void PartitionOnce(TreeNode* node);
		void PartitionNode(TreeNode* node);
		void SpawnRoom(TreeNode* node);
		void BSPtree(int width, int height) {
			//initialize dungeon node which becomes the root of the tree:
			TreeNode* dungeon = new TreeNode(width - 1, height - 1, 0, 0);
			//create additional tree nodes recursively with a helper function
			//PartitionNode(dungeon, 4);
			PartitionNode(dungeon);
			std::cout << dungeon->right->IsLeaf() << dungeon->left->IsLeaf() << std::endl;
			//traverse tree and spawn a room inside the limits of each leaf node
			SpawnRoom(dungeon);
			//connect all sister nodes with a hallway.

			//at the end delete dungeon
			delete dungeon;
		}
		void PartitionOnce(TreeNode* node) {
			int axis = rand() % 2;
			int rangeX = std::abs(node->maxX - node->minX);
			int rangeY = std::abs(node->maxY - node->minY);
			int value;
			if (axis == 0) {
				value = rand()%rangeX + (node->minX);
			}
			else {
				value = rand()%rangeY + (node->minY);
			}
			TreeNode* left = NULL;
			TreeNode* right = NULL;
			if (axis == 0) {
				left = new TreeNode(node->minX + value - 1, node->maxY, node->minX, node->minY);
				right = new TreeNode(node->maxX, node->maxY, node->minX + value + 1, node->minY);
			}
			else {
				left = new TreeNode(node->maxX, node->minY + value - 1, node->minX, node->minY);
				right = new TreeNode(node->maxX, node->maxY, node->minX, node->minY + value + 1);
			}
			std::cout << "Partitioning" << std::endl;
			(*node).AddLeft(left);
			(*node).AddRight(right);
		}
		void PartitionNode(TreeNode* node) {
			PartitionOnce(node);
			PartitionOnce((*node).left);
			PartitionOnce((*node).right);
		}
		void SpawnRoom(TreeNode* node) {
			int paddingLeft = rand() % 3 + 2;
			int paddingRight = rand() % 3 + 2;
			int paddingUp = rand() % 3 + 1;
			int paddingDown = rand() % 3 + 1;
			if (node == NULL) return;
			else if (node->IsLeaf()) {
				int minX = node->minX + paddingLeft;
				int maxX = node->maxX - paddingRight;
				int minY = node->minY + paddingUp;
				int maxY = node->maxY - paddingDown;
				for (int x = minX; x < maxX; x++) {
					for (int y = minY; y < maxY; y++) {
						worldState::SetTileType(x, y, worldState::TileType::FLOOR);
					}
				}
			}
			else {
				SpawnRoom((*node).left);
				SpawnRoom((*node).right);
			}

		}
	}

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
		BSP::BSPtree(width, height);

		//Spawn Player
		entities::InitPlayer();
		worldState::MovePlayer((int)width / 2, (int)height / 2);

		//Spawn enemies and loot
	}
}
//OLD PARTITION CODE:
//	if (i > 5) return;
		//	//choose an axis to partition
		//	int axis = rand() % 2;
		//	//choose a random coordinate to partition along.
		//	//if axis = 0, range is set to Yrange, if axis is 1, range is set to Xrange.
		//	if (node == NULL) return;
		//	int rangeX = std::abs(node->maxX - node->minX);
		//	int rangeY = std::abs(node->maxY - node->minY);
		//	if (rangeX < SMALLEST_PARTITION_SIZE || rangeY < SMALLEST_PARTITION_SIZE) return;
		//	int value;
		//	if (axis == 0) {
		//		value = rangeX/2 + (node->minX);
		//	}
		//	else {
		//		value = rangeY/2 + (node->minY);
		//	}
		//
		//	//create partition along axis
		//	TreeNode* left = NULL;
		//	TreeNode* right = NULL;
		//	if (axis == 0) {
		//		left = new TreeNode(node->minX + value, node->maxY, node->minX, node->minY);
		//		right = new TreeNode(node->maxX, node->maxY, node->minX + value, node->minY);
		//	}
		//	else {
		//		left = new TreeNode(node->maxX, node->minY + value, node->minX, node->minY);
		//		right = new TreeNode(node->maxX, node->maxY, node->minX, node->minY + value);
		//	}

		//	node->AddLeft(left);
		//	node->AddRight(right);
		//	PartitionNode(left, i+1);
		//	PartitionNode(right, i+1);
		//	std::cout << "Partitioning" << std::endl;
		//	return;