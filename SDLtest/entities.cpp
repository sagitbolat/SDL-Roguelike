#include "entities.h"

namespace entities {

	Player* player;

	void InitPlayer() {
		player = new Player(10, 10, 10, 2);
	}

}