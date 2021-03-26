#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"

enum EntityType {PLAYER, VINE, MONSTER, OBSTACLE, DOOR, ITEM};

class Level;
class Entity
{

	public:

	Entity(const Program& program, Texture* spritesheetPtr, glm::vec2 &size, glm::vec2 &pos, EntityType type);
	void setLevel(Level *level);

	void update(int deltaTime);
	void render(const Program &program);
	void setPosition(const glm::vec2 &pos);
	EntityType getType() const;
	//TODO: static bool isColliding(Entity *a, Entity *b);

	protected:
	Sprite* sprite;
	glm::vec2 position;
	Level *level;
	glm::vec2 size;
	const EntityType type;
	glm::vec2 velocity;
	glm::vec2 acceleration;
};


#endif // _PLAYER_INCLUDE


