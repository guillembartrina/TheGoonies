#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "Level.h"

class Level;

class Player
{

public:
	Player(const Program &program);
	void update(int deltaTime);
	void render(const Program &program);
	
	void setLevel(Level *level);
	void setPosition(const glm::vec2 &pos);
	
private:
	bool bJumping;
	glm::vec2 posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	Level *map;
};


#endif // _PLAYER_INCLUDE


