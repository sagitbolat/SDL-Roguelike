#include "worldGeneration.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <cmath>

namespace game {
	const long WORLD_SEED = 123312;

	namespace BSP {
		const int MIN_ROOM_AREA = 100;

		struct BSPNode {
			int width;
			int height;
			int x; 
			int y;
			bool axis; // true is X, false is Y
			BSPNode* n1;
			BSPNode* n2;
			BSPNode(int w, int h, int _x, int _y,bool _axis, BSPNode* _n1, BSPNode* _n2) {
				width = w;
				height = h;
				x = _x;
				y = _y;
				n1 = _n1;
				n2 = _n2;
				axis = _axis;
			}
			std::vector<utils::Vector2> GetCorners(){
				std::vector<utils::Vector2> corners(4);
				corners[0] = utils::Vector2(x, y);
				corners[1] = utils::Vector2(x+width, y);
				corners[2] = utils::Vector2(x, y+height);
				corners[3] = utils::Vector2(x+width, y+height);
				return corners;
			}
			bool isLeaf() {
				if (n1 == nullptr && n2 == nullptr) return true;
				else return false;
			}
			~BSPNode() {
				delete n1;
				delete n2;
			}
		};

		BSPNode* GenerateBSP(int xmin, int xmax, int ymin, int ymax, bool axis) {
			//std::cout << "GENERATING" << std::endl;
			if ((xmax - xmin) * (ymax - ymin) < MIN_ROOM_AREA) return NULL;
			//bool doStop = rand() % 100 < 20;
			//if (doStop) return NULL;
			if (axis) { //axis is X
				int z = (rand() % (xmax - xmin)) + xmin;
				BSPNode* n1 = GenerateBSP(0, z, ymin, ymax, !axis);
				BSPNode* n2 = GenerateBSP(z, xmax, ymin, ymax, !axis);
				return new BSPNode(xmax - xmin, ymax - ymin, xmin, ymin, axis, n1, n2);
			} else { //axis is Y
				int z = (rand() % (ymax - ymin)) + ymin;
				BSPNode* n1 = GenerateBSP(xmin, xmax, 0, z, !axis);
				BSPNode* n2 = GenerateBSP(xmin, xmax, z, ymax, !axis);
				return new BSPNode(xmax - xmin, ymax - ymin, xmin, ymin, !axis, n1, n2);
			}
		}

		void RenderBSP(BSPNode* node){
			if (node->n1 == NULL && node->n2 == NULL) {
				//draw the room in coords
				for (int x = node->x + 1; x < node->x + node->width - 2; x++) {
					for (int y = node->y + 1; y < node->y + node->height - 2; y++) {
						worldState::SetTileType(x, y, worldState::TileType::FLOOR);
					}
				}
				return;
			} else {
				RenderBSP(node->n1);
				RenderBSP(node->n2);
				return;
			}
		}

		void RunBSP(int width, int height) {
			BSPNode* node = GenerateBSP(0, width, 0, height, true);
			RenderBSP(node);
		}

	}

	namespace RoomPlacement {
		//MIN AND MAX Axis Size of a room
		const int ROOM_MAX_SIZE = 10;
		const int ROOM_MIN_SIZE = 6;
		const int NUMBER_OF_ROOMS = 30;
		//const int CHANCE_TO_DRAW_HALLWAY = 50; //out of 100. 50 = 50%
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
		std::vector<utils::Vector2> GenerateRoomLocationsGrid(int width, int height) {
			std::vector<utils::Vector2> positions(NUMBER_OF_ROOMS);
			for (int i = 0; i < NUMBER_OF_ROOMS / 2; i++) {
				int interval = width / ((NUMBER_OF_ROOMS / 2) + 1);
				int x = i * interval + interval;
				for (int j = 0; j < 2; j++) {
					int y = (j+1) * height / 3;
					x += rand() % 10 - 5;
					y += rand() % 20 - 10;
					positions[(j * NUMBER_OF_ROOMS / 2) + (double)i].x = x;
					positions[(j * NUMBER_OF_ROOMS / 2) + (double)i].y = y;
				}
			}
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
					if (/*randomInt > CHANCE_TO_DRAW_HALLWAY ||*/ i != j+1) continue;
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
			std::vector<utils::Vector2> positions = GenerateRoomLocationsGrid(width, height);
			CreateRooms(positions);
			CreateHallways(positions);
			return positions[0];
		}
	}

	void GenerateWorld(worldState::Tile* tileMap, int width, int height) {
		//set randomSeed:
		//srand(WORLD_SEED);

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

		std::cout << width << std::endl;
		std::cout << height << std::endl;
		BSP::RunBSP(width, height);
		utils::Vector2 playerSpawn(width / 2, height / 2);
		//utils::Vector2 playerSpawn = RoomPlacement::GenerateAlgorithm(width, height);

		//Set the outline to be walls
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if ((x >= wallThickness && x < width - wallThickness)
					&& (y >= wallThickness && y < height - wallThickness)) {
					continue;
				}
				worldState::SetTileType(x, y, worldState::TileType::WALL);
			}
		}


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