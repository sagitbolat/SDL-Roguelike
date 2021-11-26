#pragma once
namespace entities {

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
	struct Player : HealthEntity, AttackEntity, StaminaEntity, ManaEntity {
	public:
		Player(int mana, int health) {
			maxMana = mana;
			maxHealth = health;
		}
	};

	struct Goblin : HealthEntity, AttackEntity, StaminaEntity, EnemyEntity {
		Goblin(int health, int attack, int stamina, int reward) {
			maxHealth = health;
			currentHealth = health;
			maxStamina = stamina;
			currentStamina = stamina;
			goldReward = reward;
		}
	};
}