
#include "Skull.h"
#include "Level.h"
#include "Utils.h"
#include "Game.h"

#include <iostream>

Skull::Skull(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Monster(MonsterType::SKULL, position, tileSize)
{
    active = false;
    jump = (RandGen::instance().randomInt() % 2 == 0 ? false : true);
    direction = (RandGen::instance().randomInt() % 2 == 0 ? false : true);

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

    texCoords = spritesheet->getTexCoords(glm::ivec2(9, 5));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));

    Entity::setSprite(sprite);

    jumping = true;
    vel = 0;
    destroying = -1;
}

Skull::~Skull() {}

void Skull::spawn(Level *level)
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

void Skull::update(int deltaTime)
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
        newPos.x = getPosition().x + 2.f;
        if(newPos.x + getSize().x > right)
        {
            direction = false;
            sprite->setAnimation((direction ? 0 : 1));
            newPos.x = getPosition().x;
        }
    }
    else
    {
        newPos.x = getPosition().x - 2.f;
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

void Skull::kill()
{
    destroying = 1000;
    sprite->setFrame(4);
	level->getPlayer()->gainExp(100);
    Entity::type = EntityType::NONE;
    Game::instance().getEngine()->play2D(sound_kill);
}