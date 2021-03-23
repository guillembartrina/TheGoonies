#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE


#include "Sprite.h"
#include "Level.h"

class Level;

class Entity
{

	public:

	Entity(const Program &program);
	void setLevel(Level *level);

	void update(int deltaTime);
	void render(const Program &program);
	
	void setPosition(const glm::vec2 &pos);
	
	private:

	glm::vec2 position, size;
	Texture spritesheet;
	Sprite* sprite;
	Level *level;
};


#endif // _PLAYER_INCLUDE


