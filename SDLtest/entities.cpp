#include "entities.h"

namespace entities {

	Player* player;

	void InitPlayer() {
		player = new Player(PLAYER_HEALTH, PLAYER_MANA, PLAYER_STAMINA, PLAYER_ATTACK);
	}

}