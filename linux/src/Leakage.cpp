
#include "Leakage.h"
#include "Level.h"
#include "Player.h"
#include "Game.h"

#include <iostream>
#include <algorithm>

Leakage::Leakage(bool left, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::OBSTACLE, position, tileSize*2.f)
{
    state = LEAKAGE_WAITING;

    full = new Sprite(position, tileSize*2.f, spritesheet->getTexture(), program);
    

    glm::vec4 texCoords;
    if(left)
    {
        ini = new Sprite(position + tileSize, tileSize, spritesheet->getTexture(), program);
        texCoords = spritesheet->getTexCoords(glm::ivec2(15, 0), glm::ivec2(1, 1));
        ini->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(14, 0), glm::ivec2(1, 1));
        ini->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(8, 1), glm::ivec2(2, 2));
        full->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(10, 1), glm::ivec2(2, 2));
        full->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    }
    else
    {
        ini = new Sprite(position + glm::vec2(0.f, tileSize.y), tileSize, spritesheet->getTexture(), program);
        texCoords = spritesheet->getTexCoords(glm::ivec2(13, 0), glm::ivec2(1, 1));
        ini->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(12, 0), glm::ivec2(1, 1));
        ini->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(12, 1), glm::ivec2(2, 2));
        full->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(14, 1), glm::ivec2(2, 2));
        full->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    }

    ini->addAnimation(new Animation({0, 1}, {100, 100}));
    full->addAnimation(new Animation({0, 1}, {100, 100}));

    timer = leakageWaiting;
    type = NONE;

    this->left = left;

    Entity::setSprite(ini);
}

Leakage::~Leakage()
{
    if(state != LEAKAGE_LOADING) delete full;
    else delete ini;
}

void Leakage::spawn(Level* level)
{
    Entity::spawn(level);
}

void Leakage::update(int deltaTime)
{
    switch (state)
    {
        case LEAKAGE_WAITING:
        {
            timer -= deltaTime;
            if(timer < 0)
            {
                if(left)
                {
                    Entity::setSprite(ini, tileSize);
                }
                else
                {
                    Entity::setSprite(ini, glm::vec2(0.f, tileSize.y));
                }
                ini->setAnimation(0);
                timer = leakageLoading;
                state = LEAKAGE_LOADING;
            }
        }
            break;
        case LEAKAGE_LOADING:
        {
            timer -= deltaTime;
            if(timer < 0)
            {
                Entity::setSprite(full);
                full->setAnimation(0);
                type = OBSTACLE;
                timer = leakageActive;
                state = LEAKAGE_ACTIVE;
            }
        }
            break;
        case LEAKAGE_ACTIVE:
        {
            timer -= deltaTime;
            if(timer < 0)
            {
                type = NONE;
                timer = leakageWaiting;
                state = LEAKAGE_WAITING;
            }
        }
        default:
            break;
    }
    Entity::update(deltaTime);
}

void Leakage::render(const Program &program)
{
    if(state != LEAKAGE_WAITING) Entity::render(program);
}
