#pragma once
#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"

enum State { WALK_LEFT, WALK_RIGHT, JUMP_LEFT, JUMP_RIGHT, PUNCH_LEFT, PUNCH_RIGHT, IDLE_LEFT, IDLE_RIGHT, CLIMB};

class Player : public Entity
{

public:
	Player(const Program &program, Texture* spritesheetPtr);
	void update(int deltaTime);
	
private:
	State state;
	int vit, exp;
	//int jumpAngle, startY;
};


#endif // _PLAYER_INCLUDE


