
#include "Skull.h"
#include "Level.h"
#include "Utils.h"
#include "Game.h"

#include <iostream>

irrklang::ISoundSource* Monster::sound_kill = Game::instance().getEngine()->addSoundSourceFromFile("sounds/kill.mp3");

Monster::Monster(const glm::vec2 &position, const glm::vec2 &size)
    : Entity(EntityType::MONSTER, position, size)
{
    sound_kill->setDefaultVolume(0.3f);
}