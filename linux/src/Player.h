#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "Tilemap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	Player(const glm::ivec2 &tileMapPos, const Program &program);
	void update(int deltaTime);
	void render(const Program &program, const glm::mat4 &modelview);
	
	void setTileMap(Tilemap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	Tilemap *map;

};


#endif // _PLAYER_INCLUDE


