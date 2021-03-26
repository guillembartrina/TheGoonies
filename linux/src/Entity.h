#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"

enum EntityType {PLAYER, VINE, MONSTER, OBSTACLE, DOOR, ITEM};

class Level;

class Entity
{

	public:

	Entity(EntityType type, const glm::vec2 &pos, const glm::vec2 &size, Texture* spritesheet, const Program& program);
	void setLevel(Level *level);

	void update(int deltaTime);
	void render(const Program &program);

	glm::vec2 getSize() const;

	glm::vec2 getPosition() const;
	void setPosition(const glm::vec2 &pos);
	EntityType getType() const;
	
	static bool areColliding(Entity *a, Entity *b);

	protected:

	const EntityType type;
	glm::vec2 size;
	glm::vec2 position, velocity, acceleration;
	Sprite* sprite;

	Level *level;
};


#endif // _ENTITY_INCLUDE


