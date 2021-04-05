#pragma once
#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"
#include "Item.h"
#include "Sensor.h"
#include "Hitbox.h"
#include <vector>
#include "irr/irrKlang.h"

static float flyVel = 4.f;

enum State { CLIMB, IDLE_RIGHT, WALK_RIGHT, JUMP_RIGHT, PUNCH_RIGHT, IDLE_LEFT, WALK_LEFT, JUMP_LEFT, PUNCH_LEFT};

class Player : public Entity
{

	public:

	Player(const Program &program);
	~Player();
	void spawn(Level *level) override;
	void update(int deltaTime) override;
	void render(const Program &program) override;

	int getVit() const;
	int getExp() const;
	int getFriendCounter() const;
	Level * getLevel() const;
	std::vector<int> getPowerups() const;

	int changeLevel();
	bool isDead() const;
	bool hasWon() const;

	void gainExp(int exp);
	
	private:

	bool active;
	bool tped;
	int tpedTimer;
	int dashTimer;
	bool touchedGroundSinceDash;

	int change;
	bool dead;
	bool won;

	float velConstant;

	void updateMovement();
	void updateEntityCollisions();

	void handleEntityCollisionItem(Entity *it);
	void getHurt(int damage);

	State state;
	int vit, exp;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	int hurtTimer;
	int hurtSubtimer;
	bool hasKey;
	int friendCounter;
	bool touchingVine;
	std::vector<int> powerups;
	Sensor *climbableVine;
	Hitbox *punchHitbox;

	Texture* texture;

	bool fly;
	bool godmode;

	irrklang::ISoundSource* sound_jump, *sound_damage, *sound_rescue, *sound_pickup, *sound_portal;

};


#endif // _PLAYER_INCLUDE


