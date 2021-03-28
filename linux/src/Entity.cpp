#include "Entity.h"
#include "Level.h"

#include <iostream>

Entity::Entity(EntityType type, const glm::vec2 &position, const glm::vec2 &size)
{
	this->type = type;
	this->position = position;
	this->size = size;
	sprite = nullptr;
	spriteOffset = glm::ivec2(0.f);
}

Entity::~Entity()
{
	delete sprite;
}

Entity* Entity::texturedEntity(EntityType type, const glm::vec2 &position, const glm::vec2 &size, Texture* spritesheet, const Program& program)
{
	Entity* entity = new Entity(type, position, size);
	entity->setSprite(new Sprite(position, size, spritesheet, program));
	return entity;
}

void Entity::setSprite(Sprite* sprite, const glm::vec2& spriteOffset)
{
	if(sprite) delete this->sprite;
	this->sprite = sprite;
	this->spriteOffset = spriteOffset;
	sprite->setPosition(position + spriteOffset);
}

void Entity::spawn(Level *level)
{
	this->level = level;
}

void Entity::update(int deltaTime)
{
	if(sprite) sprite->update(deltaTime);
}

void Entity::render(const Program &program)
{
	if(sprite) sprite->render(program);
}

glm::vec2 Entity::getSize() const{
	return size;
}

glm::vec2 Entity::getPosition() const{
	return position;
}

void Entity::setPosition(const glm::vec2 &position) {
	this->position = position;
	if(sprite) sprite->setPosition(position + spriteOffset);
}

EntityType Entity::getType() const{
	return type;
}

bool Entity::areColliding(Entity *a, Entity *b)
{
	float minx1 = a->getPosition().x,
		  maxx1 = minx1 + a->getSize().x,
		  miny1 = a->getPosition().y,
		  maxy1 = miny1 + a->getSize().y;
	float minx2 = b->getPosition().x,
		  maxx2 = minx2 + b->getSize().x,
		  miny2 = b->getPosition().y,
		  maxy2 = miny2 + b->getSize().y;

	return (minx1 < maxx2) && (minx2 < maxx1) && (miny1 < maxy2) && (miny2 < maxy1);
}

