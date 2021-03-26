#include "Entity.h"
#include "Level.h"

Entity::Entity(EntityType type, const glm::vec2 &pos, const glm::vec2 &size, Texture* spritesheet, const Program& program) : type(type)
{
	sprite = nullptr;
	if(spritesheet) sprite = new Sprite(glm::vec2(0.f, 0.f), size, spritesheet, program);
	position = pos;
	this->size = size;
}

void Entity::setLevel(Level *level)
{
	this->level = level;
}

void Entity::update(int deltaTime)
{
	if(sprite) sprite->update(deltaTime);
	//TODO: Recalcular velocitat a partir de l'acceleraci�
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

void Entity::setPosition(const glm::vec2 &pos) {
	position = pos;
	if(sprite) sprite->setPosition(pos);
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

