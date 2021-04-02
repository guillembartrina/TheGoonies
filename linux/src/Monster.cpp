
#include "Skull.h"
#include "Level.h"
#include "Utils.h"

#include <iostream>

Monster::Monster(const glm::vec2 &position, const glm::vec2 &size)
    : Entity(EntityType::MONSTER, position, size) {}