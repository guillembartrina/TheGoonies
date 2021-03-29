#pragma once
#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"

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
	
	private:

	bool active;

	State state;
	int vit, exp;
	glm::vec2 velocity;
	glm::vec2 acceleration;

	Texture* texture;

	bool fly;

};


#endif // _PLAYER_INCLUDE


