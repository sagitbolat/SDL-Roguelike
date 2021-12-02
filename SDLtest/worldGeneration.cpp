#include "worldGeneration.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <cmath> 

namespace game {
	const long WORLD_SEED = 123312;

	namespace BSP {
		const int SMALLEST_PARTITION_SIZE = 10;
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
			int GetSmallerAxis() {
				int width = std::abs(maxX - minX);
				int height = std::abs(maxY- minY);
				if (width > height) return height;
				else return width;
			}
			bool IsLeaf() {
				return (left == NULL && right == NULL);
			}
			void PrintString() {
				std::cout << "Room x: (" << minX << ", " << maxX << ") y: (" << minY << ", " << maxY << ")" << std::endl;
			}
			~TreeNode() {
				delete left;
				delete right;
			}
		};
		void PartitionOnce(TreeNode* node);
		void PartitionNode(TreeNode* node);
		void SpawnRoom(TreeNode* node);
		void BSPtree(int width, int height) {
			//initialize dungeon node which becomes the root of the tree:
			TreeNode* dungeon = new TreeNode(width - 1, height - 1, 0, 0);
			//create additional tree nodes recursively with a helper function
			//PartitionNode(dungeon, 4);
			PartitionNode(dungeon);
			std::cout << dungeon->right->left->IsLeaf() << dungeon->left->left->IsLeaf() << std::endl;
			//traverse tree and spawn a room inside the limits of each leaf node
			SpawnRoom(dungeon);
			
			dungeon->PrintString();
			dungeon->left->PrintString();
			dungeon->right->PrintString();
			dungeon->left->left->PrintString();
			dungeon->left->right->PrintString();
			dungeon->right->left->PrintString();
			dungeon->right->right->PrintString();
			
			//connect all sister nodes with a hallway.

			//at the end delete dungeon
			delete dungeon;
		}
		void PartitionOnce(TreeNode* node) {
			if (node == NULL) return;
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
				left = new TreeNode(node->minX + value, node->maxY, node->minX, node->minY);
				right = new TreeNode(node->maxX, node->maxY, node->minX + value, node->minY);
			}
			else {
				left = new TreeNode(node->maxX, node->minY + value, node->minX, node->minY);
				right = new TreeNode(node->maxX, node->maxY, node->minX, node->minY + value);
			}
			node->AddLeft(left);
			node->AddRight(right);
		}
		void PartitionNode(TreeNode* node) {
			PartitionOnce(node);
			PartitionOnce(node->left);
			PartitionOnce(node->right);
			PartitionOnce(node->left->left);
			PartitionOnce(node->left->right);
			PartitionOnce(node->right->left);
			PartitionOnce(node->right->right);
			/*if (node->GetSmallerAxis() < SMALLEST_PARTITION_SIZE) return;
			if (node == NULL) return;
			std::cout << "Partitioning" << std::endl;
			PartitionOnce(node);
			if (node->left != NULL) {
				PartitionNode(node->left);
			}
			if (node->right != NULL) {
				PartitionNode(node->right);
			}*/
		}
		void SpawnRoom(TreeNode* node) {
			int paddingLeft = rand() % 5 + 1;
			int paddingRight = rand() % 5 + 1;
			int paddingUp = rand() % 5 + 1;
			int paddingDown = rand() % 5 + 1;
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
				SpawnRoom(node->left);
				SpawnRoom(node->right);
			}

		}
	}

	namespace RoomPlacement {
		//MIN AND MAX Axis Size of a room
		const int ROOM_MAX_SIZE = 10;
		const int ROOM_MIN_SIZE = 6;
		const int NUMBER_OF_ROOMS = 30;
		const int CHANCE_TO_DRAW_HALLWAY = 10; //out of 100. 50 = 50%
		std::vector<utils::Vector2> GenerateRoomLocations(int width, int height) {
			//select random positions for rooms.
			std::vector<utils::Vector2> positions(NUMBER_OF_ROOMS);
			for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
				utils::Vector2 position;
				double minDistane = 2000;
				int iters = 0;
				do {
					int x = rand() % (width - ROOM_MAX_SIZE) + (ROOM_MAX_SIZE / 2);
					int y = rand() % (height - ROOM_MAX_SIZE) + (ROOM_MAX_SIZE / 2);
					position.x = x;
					position.y = y;
					for (int j = 0; j < NUMBER_OF_ROOMS; j++) {
						double distance = utils::ManhattanDistance(position, positions[i]);
						minDistane = std::fmin(distance, minDistane);
					}
					iters += 1;
				} while (minDistane < ROOM_MAX_SIZE && iters < 1000);
				//if too close to an existing room, repeat previous steps
				positions[i] = position;
			}
			//return positions
			return positions;
		}
		//expand the room out to a random size between the min and max size.
		void CreateRooms(std::vector<utils::Vector2> positions) {
			for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
				//generate the size of the room
				int x = positions[i].x;
				int y = positions[i].y;
				int xsize = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE) + ROOM_MIN_SIZE;
				int ysize = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE) + ROOM_MIN_SIZE;

				//set to floor tiles
				for (int i = x - (xsize / 2); i < x + (xsize / 2); i++) {
					for (int j = y - (ysize / 2); j < y + (ysize / 2); j++) {
						worldState::SetTileType(i, j, worldState::TileType::FLOOR);
					}
				}

			}
		}
		//draw hallways between the room positions.
		void CreateHallways(std::vector<utils::Vector2> positions) {
			for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
				for (int j = 0; j < NUMBER_OF_ROOMS; j++) {
					if (j == i) continue;
					int randomInt = rand() % 100;
					if (randomInt > CHANCE_TO_DRAW_HALLWAY && i != j+1) continue;
					int minx = std::fmin(positions[i].x, positions[j].x);
					int maxx = std::fmax(positions[i].x, positions[j].x);
					int miny = std::fmin(positions[i].y, positions[j].y);
					int maxy = std::fmax(positions[i].y, positions[j].y);

					for (int x = minx; x < maxx; x++) {
						int minOrMax = rand() % 2;
						int y;
						if (minOrMax == 1) y = maxy;
						else y = miny;
						worldState::SetTileType(x, maxy, worldState::TileType::FLOOR);
					}
					for (int y = miny; y < maxy; y++) {
						int minOrMax = rand() % 2;
						int x;
						if (minOrMax == 1) x = maxx;
						else x = minx;
						worldState::SetTileType(minx, y, worldState::TileType::FLOOR);
					}
				}
			}
		}

		utils::Vector2 GenerateAlgorithm(int width, int height) {
			std::vector<utils::Vector2> positions = GenerateRoomLocations(width, height);
			CreateRooms(positions);
			CreateHallways(positions);
			return positions[0];
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
		//BSP::BSPtree(width, height);
		utils::Vector2 playerSpawn = RoomPlacement::GenerateAlgorithm(width, height);

		//Spawn Player
		entities::InitPlayer();
		worldState::MovePlayer(playerSpawn.x, playerSpawn.y);

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