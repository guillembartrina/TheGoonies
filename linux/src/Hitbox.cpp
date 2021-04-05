#include "Hitbox.h"
#include "Monster.h"
#include "Level.h"
#include <list>
#include "Game.h"

Hitbox::Hitbox(const glm::vec2 &pos, const glm::vec2 &size) : Sensor(SensorType::HITBOX, pos, size, 99) {
	activeCounter = 0;
}

void Hitbox::update(int deltatime) {
	if (activeCounter > 0) {
		activeCounter -= deltatime;
		std::list<Entity *>& entities = level->getEntities();
		for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
			if (areColliding(this, *it)) {
				if ((*it)->getType() == MONSTER) {
					Monster *monster= (Monster *)*it;
					monster->kill();
				}
			}
		}
	}
}

void Hitbox::setActive(int activeTime) {
	activeCounter = activeTime;
}

bool Hitbox::isActive() {
	return activeCounter > 0;
}