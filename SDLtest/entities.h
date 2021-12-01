#pragma once
namespace entities {

	const int PLAYER_HEALTH = 10;
	const int PLAYER_MANA = 10;
	const int PLAYER_STAMINA = 10;
	const int PLAYER_ATTACK = 4;


	///NEEDS REFACTORING

	/*
		Entity component:
	*/
	struct Entity { //Umbrella term for anything that exists on a tile. items/chest/mob/player/etc.

	};

	/*
		Mob components:
	*/
	struct HealthEntity {
		int maxHealth;
		int currentHealth;
	};
	struct AttackEntity {
		int attack;
	};
	struct StaminaEntity {
		int maxStamina;
		int currentStamina;
	};
	struct ManaEntity {
		int maxMana;
		int currentMana;
	};
	struct EnemyEntity {
		int goldReward;
	};


	//Player Entity
	struct Player : Entity {
	public:
		HealthEntity healthComponent; 
		ManaEntity manaComponent;
		StaminaEntity staminaComponent;
		AttackEntity attackComponent; 
		Player(int health, int mana, int stamina, int attack) {
			healthComponent.maxHealth = health;
			manaComponent.maxMana = mana;
			staminaComponent.maxStamina = stamina;
			attackComponent.attack = attack;
		}
	};

	struct Enemy : Entity {
	};

	//enum class Entities {
	//	NONE = 0,
	//	PLAYER = 1,
	//	ENEMY = 2,
	//	NPC = 3,
	//	LOOT = 4,
	//	ITEM = 5
	//};

	extern Player* player;
	void InitPlayer();
}