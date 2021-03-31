
#include "Door.h"
#include "Level.h"

Door::Door(int unlocks, ItemCode item, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::DOOR, position, glm::vec2(tileSize.x, tileSize.y*2.f)), program(program)
{
    this->unlocks = unlocks;
    this->item = item;
    this->ts = spritesheet;
    destroying = false;

    Sprite* sprite = new Sprite(position, tileSize*3.f, spritesheet->getTexture(), program);

    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(4, 3), glm::ivec2(3, 3));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->setFrame(0);
    Entity::setSprite(sprite, -tileSize);

    lock = new Sprite(glm::vec2(0.f), tileSize, spritesheet->getTexture(), program);
    texCoords = spritesheet->getTexCoords(glm::ivec2(2, 4));
    lock->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    lock->setFrame(0);
}

void Door::update(int deltaTime)
{
    if(destroying)
    {
        lock->update(deltaTime);
        timer -= deltaTime;
        if(timer < 0)
        {
            setDestroy();
        }
    }
    else Entity::update(deltaTime);
}

void Door::render(const Program &program)
{
    if(destroying)
    {
        lock->render(program);
    }
    else
    {
        for(int i = 0; i < unlocks; i++)
        {
            lock->setPosition(getPosition() + glm::vec2(-tileSize.x*2.f, -tileSize.y*i));
            lock->render(program);
        }
        Entity::render(program);
    }
}

void Door::unlock()
{
    if(destroying) return;
    unlocks--;
    if(unlocks == 0)
    {
        if(item == ITEM_NONE)
        {
            delete lock;
            lock = new Sprite(getPosition(), glm::vec2(tileSize.x, tileSize.y*2.f), ts->getTexture(), program);
            glm::vec4 texCoords = ts->getTexCoords(glm::ivec2(7, 3), glm::ivec2(1, 2));
            lock->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
            texCoords = ts->getTexCoords(glm::ivec2(8, 3), glm::ivec2(1, 2));
            lock->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
            lock->addAnimation(new Animation({0, 1}, {200, 200}));
            lock->setAnimation(0);
            destroying = true;
            timer = doorDestroying;
        }
        else
        {
            level->addEntity(new Item(item, getPosition(), ts, program));
            setDestroy();
        }
    }
}