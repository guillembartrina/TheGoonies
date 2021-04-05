
#include "Rock.h"
#include "Level.h"
#include "Player.h"
#include "Game.h"

#include <iostream>
#include <algorithm>

Rock::Rock(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::OBSTACLE_ROCK, position, glm::vec2(tileSize.x*2.f, tileSize.y))
{
    state = ROCK_READY;

    Sprite* sprite = new Sprite(position, glm::vec2(tileSize.x*2.f, tileSize.y), spritesheet->getTexture(), program);

    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(8, 0), glm::ivec2(2, 1));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(10, 0), glm::ivec2(2, 1));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->setFrame(0);

    Entity::setSprite(sprite);
}

void Rock::spawn(Level* level)
{
    Entity::spawn(level);
    glm::ivec2 fin1, fin2;
    level->getFirstOf_Tiles(glm::ivec2(Entity::getPosition().x / tileSize.x, Entity::getPosition().y / tileSize.y), 2, CollisionType::BOTTOM, fin1);
    level->getFirstOf_Tiles(glm::ivec2((Entity::getPosition().x / tileSize.x)+1, Entity::getPosition().y / tileSize.y), 2, CollisionType::BOTTOM, fin2);
    end = (std::min(fin1.y, fin2.y)+1)*tileSize.y;
    sensor = new Sensor(SensorType::ROCK, Entity::getPosition() + glm::vec2(-0.5*tileSize.x, 0.f), glm::vec2(2.f*tileSize.x, (end-Entity::getPosition().y)));
}

void Rock::update(int deltaTime)
{
    switch (state)
    {
        case ROCK_READY:
        {
            Player* player;        
            if(sensor && (player = level->getPlayer()))
            {
                if(Entity::areColliding(sensor, player)) state = ROCK_FALLING;
            }
        }
            break;
        case ROCK_FALLING:
        {
            if(getPosition().y + getSize().y + rockVel >= end)
            {
                setPosition(glm::vec2(getPosition().x, end - getSize().y));
                sprite->setFrame(1);
                state = ROCK_CRASHING;
                timer = rockCrashing;
                type = EntityType::NONE;
            }
            else
            {
                setPosition(getPosition() + glm::vec2(0.f, rockVel));
            }
        }
            break;
        case ROCK_CRASHING:
            timer -= deltaTime;
            if(timer < 0)
            {
                state = ROCK_DEAD;
                Entity::setDestroy();
            }
            break;
        default:
            break;
    }
    Entity::update(deltaTime);
}

void Rock::render(const Program &program)
{
    if(state != ROCK_DEAD) Entity::render(program);
}
