#include "Entity.h"
#include "Level.h"

Entity::Entity(const Program& program, Texture* spritesheetPtr, glm::vec2 &size, glm::vec2 &pos, EntityType type) {
	sprite = nullptr;
	if(spritesheetPtr) sprite = new Sprite(glm::vec2(0.f, 0.f), size, spritesheetPtr, program);
	position = pos;
	this->size = size;
	this->type = type;
}

void Entity::setLevel(Level *level) {
	level = level;
}

void Entity::update(int deltaTime) {
	if(sprite) sprite->update(deltaTime);
	//TODO: Recalcular velocitat a partir de l'acceleració
}

void Entity::render(const Program &program)
{
	if(sprite) sprite->render(program);
}

void Entity::setPosition(const glm::vec2 &pos) {
	position = pos;
	if(sprite) sprite->setPosition(pos);
}

EntityType Entity::getType() const{
	return type;
}

