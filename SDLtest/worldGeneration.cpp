#include "worldGeneration.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "time.h""

namespace game {
	long WORLD_SEED = time(0);

	namespace RoomPlacement {
		//MIN AND MAX Axis Size of a room
		const int ROOM_MAX_SIZE = 10;
		const int ROOM_MIN_SIZE = 6;
		const int NUMBER_OF_ROOMS = 144;
		const int NUMBER_OF_ROWS = 9;
		const int CHANCE_TO_DRAW_HALLWAY = 30; //out of 100. 50 = 50%

		utils::Vector2 PositionAtCoordinate(std::vector<utils::Vector2>* positions, int x, int y) {
			int i = x * NUMBER_OF_ROWS + y;
			if (i >= NUMBER_OF_ROOMS) {
				std::cout << "Array Overflow when calling PositionAtCoordinate()" << std::endl;
				return  (*positions)[0];
			}
			return (*positions)[i];
		}

		std::vector<utils::Vector2>* GenerateRoomLocationsGrid(int width, int height) {
			std::vector<utils::Vector2>* positions = new std::vector<utils::Vector2>(NUMBER_OF_ROOMS);
			for (int i = 0; i < NUMBER_OF_ROOMS / NUMBER_OF_ROWS; i++) {
				int interval = width / ((NUMBER_OF_ROOMS / NUMBER_OF_ROWS) + 1);
				int x = i * interval + interval;
				for (int j = 0; j < NUMBER_OF_ROWS; j++) {
					int y = (j+1) * height / (NUMBER_OF_ROWS+1);
					x += rand() % 10 - 5;
					y += rand() % 20 - 10;
					(*positions)[(j * NUMBER_OF_ROOMS / NUMBER_OF_ROWS) + (double)i].x = utils::ClampInt(x, 1, width - 2);;
					(*positions)[(j * NUMBER_OF_ROOMS / NUMBER_OF_ROWS) + (double)i].y = utils::ClampInt(y, 1, height - 2);;
				}
			}
			return positions;
		}
		//expand the room out to a random size between the min and max size.
		void CreateRooms(std::vector<utils::Vector2>* positions, int mapWidth, int mapHeight) {
			for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
				//generate the size of the room
				int x = (*positions)[i].x;
				int y = (*positions)[i].y;
				int xsize = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE) + ROOM_MIN_SIZE;
				int ysize = rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE) + ROOM_MIN_SIZE;
				
				int minX = std::fmax(1, x - (xsize / 2));
				int minY = std::fmax(1, y - (ysize / 2));
				int maxX = std::fmin(mapWidth - 2, x + (xsize / 2));
				int maxY = std::fmin(mapHeight - 2, y + (ysize / 2));

				//set to floor tiles
				for (int i = minX; i < maxX; i++) {
					for (int j = minY; j < maxY; j++) {
						worldState::SetTileType(i, j, worldState::TileType::FLOOR);
					}
				}

			}
		}
		//draw hallways between the room positions.
		void DrawHallway(utils::Vector2 room1, utils::Vector2 room2) {
			int x1 = room1.x;
			int x2 = room2.x;
			int y1 = room1.y;
			int y2 = room2.y;

			for (int x = std::fmin(x1, x2); x < std::fmax(x2, x1); x++) {
				worldState::SetTileType(x, y1, worldState::TileType::FLOOR);
			}
			for (int y = std::fmin(y1, y2); y < std::fmax(y1, y2) + 1; y++) {
				worldState::SetTileType(x2, y, worldState::TileType::FLOOR);
			}
		}
		void CreateHallwaysLinear(std::vector<utils::Vector2>* positions) {
			for (int i = 0; i < NUMBER_OF_ROOMS - 1; i++) {
				int j = i + 1;
				int k = rand() % NUMBER_OF_ROOMS;
				if (k == i || k == i + 1 || k == i - 1) { //if k and i are already connected
					if (k+2 >= NUMBER_OF_ROOMS - 1) {
						k -= 2;
					}
					else {
						k += 2;
					}
				}
				DrawHallway((*positions)[i], (*positions)[j]);
				int toDrawAnotherHall = rand() % 100;
				if (toDrawAnotherHall <= CHANCE_TO_DRAW_HALLWAY)
					DrawHallway((*positions)[i], (*positions)[k]);
			}
			/*for (int i = 0; i < NUMBER_OF_ROOMS / NUMBER_OF_ROOMS; i++) {
				for (int j = 0)
			} */

		}

		utils::Vector2 GenerateAlgorithm(int width, int height) {
			std::vector<utils::Vector2>* positions = GenerateRoomLocationsGrid(width, height);
			CreateRooms(positions, width, height);
			CreateHallwaysLinear(positions);
			utils::Vector2 startRoom(positions->at(0).x, positions->at(0).y);
			delete positions;
			return startRoom;
		}
	}

	void GenerateWorld(worldState::Tile* tileMap, int width, int height) {
		//set randomSeed:
		srand(WORLD_SEED);
		//Randomly generate world map
		int wallThickness = 1;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				worldState::SetTileType(x, y, worldState::TileType::WALL);
			}
		}
		utils::Vector2 playerSpawn = RoomPlacement::GenerateAlgorithm(width, height);

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