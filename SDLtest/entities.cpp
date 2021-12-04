#include "entities.h"
#include "utils.h"
#include <vector>
#include <list>

namespace entities {

	Player* player;

	void InitPlayer() {
		player = new Player(PLAYER_HEALTH, PLAYER_MANA, PLAYER_STAMINA, PLAYER_ATTACK);
	}
	
	
	namespace Astar {
		//std::vector<utils::Vector2> FindPath(utils::Vector2 start, utils::Vector2 end) {
		//	std::list<utils::Vector2> openList;
		//	std::list<utils::Vector2> closedList;
		//	openList.push_back(start);
		//	while (!openList.empty()) {
		//		//find best node in open list:
		//		utils::Vector2 currentNode = openList.front();
		//		for (utils::Vector2 point : openList) {
		//			if (utils::EulerDistance(point, end) < utils::EulerDistance(currentNode, end)) {
		//				currentNode = point;
		//			}
		//		}
		//		//remove currentNode from openList:
		//		openList.remove(currentNode);
		//		

		//	}
		//}

		std::vector<utils::Vector2> GetNeighborsOfCoordinate(utils::Vector2 location) {
			int x = location.x;
			int y = location.y;
			utils::Vector2 v1(x + 1, y);
			utils::Vector2 v2(x - 1, y);
			utils::Vector2 v3(x, y + 1);
			utils::Vector2 v4(x, y - 1);
			std::vector<utils::Vector2> neighbors = { v1, v2, v3, v4 };
			return neighbors;
		}
	}
}