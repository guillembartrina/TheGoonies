
#include "Item.h"
#include "Level.h"

Item::Item(ItemCode code, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::ITEM, position, tileSize)
{
    this->code = code;

    glm::vec4 texCoords;

    if(code == KEY)
    {
        Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);
        texCoords = spritesheet->getTexCoords(glm::ivec2(1, 4), glm::ivec2(1, 1));
        sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        sprite->setFrame(0);
        Entity::setSprite(sprite);
    }
    else if(code == POTION)
    {
        Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);
        texCoords = spritesheet->getTexCoords(glm::ivec2(0, 3), glm::ivec2(1, 1));
        sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        sprite->setFrame(0);
        Entity::setSprite(sprite);
    }
    else if(code >= BAG && code < FRIEND)
    {
        Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);
        texCoords = spritesheet->getTexCoords(glm::ivec2(0, 4), glm::ivec2(1, 1));
        sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        sprite->setFrame(0);
        Entity::setSprite(sprite);
    }
    else if(code == FRIEND)
    {
        Sprite* sprite = new Sprite(position, glm::vec2(tileSize.x, tileSize.y*2.f), spritesheet->getTexture(), program);
        texCoords = spritesheet->getTexCoords(glm::ivec2(7, 3), glm::ivec2(1, 2));
        sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        texCoords = spritesheet->getTexCoords(glm::ivec2(8, 3), glm::ivec2(1, 2));
        sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
        sprite->addAnimation(new Animation({0, 1}, {200, 200}));
        sprite->setAnimation(0);
        Entity::setSprite(sprite);
    }
}

void Item::update(int deltaTime)
{
    Entity::update(deltaTime);
}

void Item::render(const Program &program)
{
    Entity::render(program);
}

ItemCode Item::getCode() const {
	return code;
}