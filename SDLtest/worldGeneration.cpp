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
		const int ROOM_MIN_SIZE = 2;
		const int NUMBER_OF_ROOMS = 144;
		const int NUMBER_OF_ROWS = 9;
		const int CHANCE_TO_DRAW_HALLWAY = 70; //out of 100. 50 = 50%
		const bool RANDOMIZE_ROOM_POSITION_OFFSET = true;
		const int Y_OFFSET = 3;
		const int X_OFFSET = 2;

		utils::Vector2 PositionAtCoordinate(std::vector<utils::Vector2>* positions, int x, int y) {
			int i = y * (NUMBER_OF_ROOMS/NUMBER_OF_ROWS) + x;
			if (i >= NUMBER_OF_ROOMS) {
				//std::cout << "Array Overflow when calling PositionAtCoordinate()" << std::endl;
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
					int y = (j + 1) * height / (NUMBER_OF_ROWS + 1);
					if (RANDOMIZE_ROOM_POSITION_OFFSET) {
						x += rand() % (X_OFFSET * 2) - X_OFFSET;
						y += rand() % (Y_OFFSET * 2) - Y_OFFSET;
					}
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
			for (int i = 0; i < NUMBER_OF_ROOMS / NUMBER_OF_ROWS ; i++) {
				for (int j = 0; j < NUMBER_OF_ROWS; j++) {
					utils::Vector2 pos1 = PositionAtCoordinate(positions, i, j);
					utils::Vector2 pos2 = PositionAtCoordinate(positions, i + 1, j);
					utils::Vector2 pos3 = PositionAtCoordinate(positions, i, j + 1);
					if (pos2 != utils::Vector2(0, 0)) {
						if(rand() % 100 <= CHANCE_TO_DRAW_HALLWAY) DrawHallway(pos1, pos2);
					}
					if (pos3 != utils::Vector2(0, 0)) {
						if (rand() % 100 <= CHANCE_TO_DRAW_HALLWAY) DrawHallway(pos1, pos3);
					}
				}
			}
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