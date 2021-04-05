#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"

enum EntityType {PLAYER, MONSTER, OBSTACLE, OBSTACLE_ROCK, OBSTACLE_DROPLET, PROJECTILE, SENSOR, ITEM, DOOR, NONE};

class Level;

class Entity
{

	public:

	Entity(EntityType type, const glm::vec2 &position, const glm::vec2 &size);
	static Entity* texturedEntity(EntityType type, const glm::vec2 &position, const glm::vec2 &size, Texture* spritesheet, const Program& program);
	~Entity();
	void setSprite(Sprite* sprite, const glm::vec2& spriteOffset = glm::vec2(0.f), bool del = false);
	virtual void spawn(Level *level);

	virtual void update(int deltaTime);
	virtual void render(const Program &program);

	glm::vec2 getSize() const;

	glm::vec2 getPosition() const;
	void setPosition(const glm::vec2 &position);
	EntityType getType() const;
	
	static bool areColliding(Entity *a, Entity *b);

	void setDestroy();
	bool toDestroy() const;

	protected:

	EntityType type;
	glm::vec2 size;
	glm::vec2 position;
	
	Sprite* sprite;
	glm::vec2 spriteOffset;

	Level *level;

	bool destroy;
};


#endif // _ENTITY_INCLUDE


