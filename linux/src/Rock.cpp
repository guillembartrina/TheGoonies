
#include "Rock.h"
#include "Level.h"

Rock::Rock(const glm::vec2 &pos, Tilesheet* spritesheet, const Program& program)
    : Entity(EntityType::OBSTACLE, pos, glm::vec2(tileSize.x*2.f, tileSize.y), spritesheet->getTexture(), program)
{
    glm::vec4 texCoords = spritesheet->getTexCoords(glm::ivec2(8, 0), glm::ivec2(2, 1));
    sprite->addFrame(new Frame(texCoords.x, texCoords.y, texCoords.z-texCoords.x, texCoords.w-texCoords.y));
    sprite->setFrame(0);
}

void Rock::update(int deltaTime)
{

}

void Rock::render(const Program &program)
{
    Entity::render(program);
}
