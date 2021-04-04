
#include "Droplet.h"
#include "Level.h"
#include "Player.h"
#include "Game.h"

#include <iostream>

Droplet::Droplet(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::OBSTACLE, position, tileSize)
{
    ini = position;
    timer = dropletWaiting;
    state = DROPLET_WAITING;
    type = EntityType::NONE;

    Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);

    glm::vec4 texCoords;
    for(int i = 0; i < 3; i++) //0, 1, 2
    {
        texCoords = spritesheet->getTexCoords(glm::ivec2(i, 1));
        sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    }
    texCoords = spritesheet->getTexCoords(glm::ivec2(3, 1)); //3
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    texCoords = spritesheet->getTexCoords(glm::ivec2(4, 1)); //4
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));

    sprite->addAnimation(new Animation({0, 1, 2}, {300.f, 300.f, 200.f}));

    Entity::setSprite(sprite);
}

void Droplet::spawn(Level* level)
{
    Entity::spawn(level);
    glm::ivec2 fin;
    level->getFirstOf_Tiles(glm::ivec2(Entity::getPosition().x / tileSize.x, Entity::getPosition().y / tileSize.y), 2, CollisionType::BOTTOM, fin);
    end = (fin.y+1)*tileSize.y;
}

void Droplet::update(int deltaTime)
{
    switch (state)
    {
        case DROPLET_WAITING:
            timer -= deltaTime;
            if(timer < 0)
            {
                sprite->setAnimation(0);
                state = DROPLET_LOADING;
                timer = dropletLoading;
                type = EntityType::OBSTACLE;
            }
            break;
        case DROPLET_LOADING:
        {
            timer -= deltaTime;
            if(timer < 0)
            {
                sprite->setAnimation(-1);
                sprite->setFrame(2);
                state = DROPLET_FALLING;
            }
        }
            break;
        case DROPLET_FALLING:
            if(getPosition().y + getSize().y + dropletVel >= end)
            {
                setPosition(glm::vec2(getPosition().x, end - getSize().y));
                sprite->setFrame(3);
                state = DROPLET_CRASHING;
                timer = dropletCrashing;
            }
            else
            {
                setPosition(getPosition() + glm::vec2(0.f, dropletVel));
            }
            break;
        case DROPLET_CRASHING:
        {
            timer -= deltaTime;
            if(timer < 0)
            {
                state = DROPLET_WAITING;
                type = EntityType::NONE;
                timer = dropletWaiting;
                setPosition(ini);
            }
        }
            break;
        default:
            break;
    }
    Entity::update(deltaTime);
}

void Droplet::render(const Program &program)
{
    if(state != DROPLET_WAITING) Entity::render(program);
}
