
#include "Door.h"
#include "Level.h"

Door::Door(int unlocks, ItemCode item, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::DOOR, position, tileSize*3.f), program(program)
{
    this->unlocks = unlocks;
    this->item = item;
    this->ts = spritesheet;

    Sprite* sprite = new Sprite(position, tileSize*3.f, spritesheet->getTexture(), program);

    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(4, 3), glm::ivec2(3, 3));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->setFrame(0);
    Entity::setSprite(sprite);

    lock = new Sprite(glm::vec2(0.f), tileSize, spritesheet->getTexture(), program);
    texCoords = spritesheet->getTexCoords(glm::ivec2(1, 3));
    lock->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    lock->setFrame(0);
}

void Door::update(int deltaTime)
{
    Entity::update(deltaTime);
}

void Door::render(const Program &program)
{
    for(int i = 0; i < unlocks; i++)
    {
        lock->setPosition(getPosition() + glm::vec2(-tileSize.x, -tileSize.y*(i-1)));
        lock->render(program);
    }
    Entity::render(program);
}

void Door::unlock()
{
    unlocks--;
    if(unlocks == 0)
    {
        level->addEntity(new Item(item, getPosition() + tileSize, ts, program));
        setDestroy();
    }
}