
#include "Item.h"
#include "Level.h"

Item::Item(ItemCode code, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::ITEM, position, tileSize)
{
    this->code = code;

    Sprite* sprite = new Sprite(position, tileSize, spritesheet->getTexture(), program);

    glm::ivec2 pos;

    if(code == KEY)
    {
        pos = glm::ivec2(1, 4);
    }
    else if(code == POTION)
    {
         pos = glm::ivec2(0, 3);
    }
    else if(code >= BAG)
    {
         pos = glm::ivec2(0, 4);
    }

    glm::vec4 texCoords = spritesheet->getTexCoords(pos, glm::ivec2(1, 1));

    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->setFrame(0);

    Entity::setSprite(sprite);
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