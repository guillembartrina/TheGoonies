#pragma once
#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"

enum State { CLIMB, IDLE_RIGHT, WALK_RIGHT, JUMP_RIGHT, PUNCH_RIGHT, IDLE_LEFT, WALK_LEFT, JUMP_LEFT, PUNCH_LEFT};

class Player : public Entity
{

	public:

	Player(const Program &program);
	void setLevel(Level *level);
	void update(int deltaTime);
	void render(const Program &program);

	bool active;
	
	private:

	State state;
	int vit, exp;

};


#endif // _PLAYER_INCLUDE


