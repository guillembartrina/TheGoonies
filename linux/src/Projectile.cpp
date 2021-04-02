
#include "Projectile.h"
#include "Level.h"
#include "Player.h"
#include "Game.h"

#include <iostream>
#include <algorithm>

Projectile::Projectile(const glm::vec2 &position, const glm::vec2& direction, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::OBSTACLE, position, tileSize*0.8f)
{
    Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);

    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(1, 5));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(2, 5));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(3, 5));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(8, 5));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(7, 5));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->addAnimation(new Animation({0, 1, 2}, {150, 150, 150}));
    sprite->addAnimation(new Animation({0, 2, 1}, {150, 150, 150}));
    sprite->setAnimation((direction.x >= 0.f ? 1 : 0));

    Entity::setSprite(sprite, -tileSize*0.1f);

    this->direction = glm::normalize(direction);
    destroying = false;
}

void Projectile::spawn(Level* level)
{
    Entity::spawn(level);
}

void Projectile::update(int deltaTime)
{
    if(!destroying)
    {
        glm::vec2 futurePos = getPosition() + direction * projectileVel;

        glm::vec2 junk;
        if(direction.x > 0 && level->collisionMoveRight(futurePos, getSize(), junk)) destroying = true;
        else if (direction.y > 0 && level->collisionMoveDown(futurePos, getSize(), junk)) destroying = true;
        else if (direction.x < 0 && level->collisionMoveLeft(futurePos, getSize(), junk)) destroying = true;
        else if (direction.y < 0 && level->collisionMoveUp(futurePos, getSize(), junk)) destroying = true;
        else
        {
            setPosition(futurePos);
        }

        if(destroying)
        {
            sprite->setAnimation(-1);
            sprite->setFrame((direction.x >= 0.f ? 4 : 3));
            timer = 800;
        }
    }
    else
    {
        timer -= deltaTime;
        if(timer < 0)
        {
            Entity::setDestroy();
        }
    }
    Entity::update(deltaTime);
}

void Projectile::render(const Program &program)
{
    Entity::render(program);
}
