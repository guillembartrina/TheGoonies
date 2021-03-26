#pragma once
#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"

enum State { WALK_LEFT, WALK_RIGHT, JUMP_LEFT, JUMP_RIGHT, PUNCH_LEFT, PUNCH_RIGHT, IDLE_LEFT, IDLE_RIGHT, CLIMB};

class Player : public Entity
{

	public:

	Player(const Program &program);
	void update(int deltaTime);
	void render(const Program &program);

	bool active;
	
	private:

	State state;
	int vit, exp;

};


#endif // _PLAYER_INCLUDE


