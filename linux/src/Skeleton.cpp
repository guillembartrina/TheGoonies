
#include "Skeleton.h"
#include "Level.h"
#include "Utils.h"
#include "Projectile.h"
#include "Game.h"

#include <iostream>

Skeleton::Skeleton(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Monster(MonsterType::MONSTERSKELETON, position, glm::vec2(tileSize.x, tileSize.y*2.f)), program(program)
{
    active = false;
    direction = (RandGen::instance().randomInt() % 2 == 0 ? false : true);

    Sprite* sprite = new Sprite(position, glm::vec2(tileSize.x, tileSize.y*2.f), spritesheet->getTexture(), program);

    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(9, 3), glm::ivec2(1, 2));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(10, 3), glm::ivec2(1, 2));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(11, 3), glm::ivec2(1, 2));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(12, 3), glm::ivec2(1, 2));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->addAnimation(new Animation({0, 1}, {250, 250}));
    sprite->addAnimation(new Animation({2, 3}, {250, 250}));
    sprite->setAnimation((direction ? 0 : 1));

    texCoords = spritesheet->getTexCoords(glm::ivec2(13, 3));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));

    Entity::setSprite(sprite);

    jumping = true;
    vel = 0;
    ts = spritesheet;

    sensor = new Sensor(SensorType::SKELETON, glm::vec2(0.f), glm::vec2(10.f*tileSize.x, 2.f*tileSize.y));
    timer = 3000;

    destroying = -1;
}

Skeleton::~Skeleton() {}

void Skeleton::spawn(Level *level)
{
    Entity::spawn(level);

    glm::ivec2 first, first2;
    level->getFirstOf_Tiles(glm::ivec2(getPosition() / tileSize), 2, CollisionType::BOTTOM, first);
    floor = first.y * tileSize.y + tileSize.y*0.8f;

    glm::ivec2 pos = first;
    int min = -100, max = 100000;
    if(level->getFirstOf_Tiles(pos, 1, CollisionType::ANY, first) && first.x < max) max = first.x;
    if(level->getFirstOf_Tiles(pos, 1, CollisionType::RIGHT, first) && first.x < max) max = first.x;
    right = max * tileSize.x;

    if(level->getFirstOf_Tiles(pos, 3, CollisionType::ANY, first) && first.x > min) min = first.x;
    if(level->getFirstOf_Tiles(pos, 3, CollisionType::LEFT, first) && first.x > min) min = first.x;
    left = (min + 1) * tileSize.x;
}

void Skeleton::update(int deltaTime)
{
    if(destroying >= 0)
    {
        destroying -= deltaTime;
        if(destroying < 0) setDestroy();
        return;
    }

    if(!active)
    {
        if(level->inScreen(getPosition())) active = true;
        return;
    }

    glm::vec2 newPos = glm::vec2(0.f);
    if(direction)
    {
        newPos.x = getPosition().x + 1.f;
        if(newPos.x + getSize().x > right)
        {
            direction = false;
            sprite->setAnimation((direction ? 0 : 1));
            newPos.x = getPosition().x;
        }
    }
    else
    {
        newPos.x = getPosition().x - 1.f;
        if(newPos.x < left)
        {
            direction = true;
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
            jumping = false;
        }
    }
    else
    {
        newPos.y = getPosition().y;
    }

    setPosition(newPos);

    if(direction)
    {
        sensor->setPosition(getPosition());
    }
    else
    {
        sensor->setPosition(getPosition() + glm::vec2(-10.f*tileSize.x, 0.f));
    }

    if(timer > 0) timer -= deltaTime;
    if(timer <= 0 && Entity::areColliding(sensor, level->getPlayer()))
    {
        level->addEntity(new Projectile(getPosition() + glm::vec2(0.f, tileSize.y*0.5f), glm::vec2((direction ? 1.f : -1.f), 0.f), ts, program));
        timer = 3000;
    }

    Entity::update(deltaTime);

}

void Skeleton::render(const Program &program)
{
    if(!active) return;
    Entity::render(program);
}

void Skeleton::kill()
{
    destroying = 1000;
    sprite->setFrame(4);
    Entity::type = EntityType::NONE;
    Game::instance().getEngine()->play2D(sound_kill);
}