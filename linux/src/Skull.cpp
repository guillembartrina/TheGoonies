
#include "Skull.h"
#include "Level.h"
#include "Utils.h"

#include <iostream>

Skull::Skull(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::MONSTER, position, tileSize)
{
    active = false;
    jump = (randomInt() % 2 == 0 ? false : true);
    direction = (randomInt() % 2 == 0 ? false : true);

    Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);
    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(2, 3));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(2, 4));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(3, 3));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(3, 4));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->addAnimation(new Animation({0, 1}, {200, 200}));
    sprite->addAnimation(new Animation({2, 3}, {200, 200}));
    sprite->setAnimation((direction ? 0 : 1));

    Entity::setSprite(sprite);

    jumping = true;
    vel = 0;
}

Skull::~Skull() {}

void Skull::spawn(Level *level)
{
    Entity::spawn(level);

    glm::ivec2 first;
    level->getFirstOf_Tiles(glm::ivec2(getPosition() / tileSize), 2, CollisionType::BOTTOM, first);
    floor = first.y * tileSize.x + tileSize.y*0.8f;

    glm::ivec2 pos = first;
    if(!level->getFirstOf_Tiles(pos, 1, CollisionType::ANY, first))
    {
        level->getFirstOf_Tiles(pos, 1, CollisionType::RIGHT, first);
    }
    right = first.x * tileSize.x;

    if(!level->getFirstOf_Tiles(pos, 3, CollisionType::ANY, first))
    {
        level->getFirstOf_Tiles(pos, 3, CollisionType::LEFT, first);
    }
    left = (first.x + 1) * tileSize.x;
}

void Skull::update(int deltaTime)
{
    if(!active)
    {
        if(level->inScreen(getPosition())) active = true;
        return;
    }

    glm::vec2 newPos = glm::vec2(0.f);
    if(direction)
    {
        newPos.x = getPosition().x + 2.f;
        if(newPos.x + getSize().x > right)
        {
            direction = !direction;
            sprite->setAnimation((direction ? 0 : 1));
            newPos.x = getPosition().x;
        }
    }
    else
    {
        newPos.x = getPosition().x - 2.f;
        if(newPos.x < left)
        {
            direction = !direction;
            sprite->setAnimation((direction ? 0 : 1));
            newPos.x = getPosition().x;
        }
    }

    if(jumping)
    {
        vel += 0.15f;
        newPos.y = getPosition().y + vel;
        if(newPos.y + getSize().y > floor)
        {
            newPos.y = floor - getSize().y;
            if(jump)
            {
                vel = -2.f;
            }
            else
            {
                jumping = false;
            }
        }
    }
    else
    {
        newPos.y = getPosition().y;
    }

    setPosition(newPos);
    Entity::update(deltaTime);

}

void Skull::render(const Program &program)
{
    if(!active) return;
    Entity::render(program);
}