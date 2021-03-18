#include "Tilesheet.h"

#include <iostream>
#include <fstream>

Tilesheet::Tilesheet(const std::string& path, const glm::ivec2& size)
{
    this->size = size;
    tileSize = glm::vec2(1.f / size.x, 1.f / size.y);
    texture.loadFromFile(path, PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    texture.setWrapS(GL_CLAMP_TO_EDGE);
	texture.setWrapT(GL_CLAMP_TO_EDGE);
	texture.setMinFilter(GL_NEAREST);
	texture.setMagFilter(GL_NEAREST);
    halfTexel = glm::vec2(0.5f / texture.width(), 0.5f / texture.height());
}

Tilesheet::~Tilesheet() {}

glm::vec4 Tilesheet::getTexCoords(int index)
{
    int row = index / size.x, column = index % size.x;
    if(row >= size.y) std::cerr << "Tilesheet invalid index" << std::endl;

    return glm::vec4(tileSize.x * column,
                     tileSize.y * row,
                     tileSize.x * (column + 1) - halfTexel.x,
                     tileSize.y * (row + 1) - halfTexel.y);
}

void Tilesheet::use() const
{
    //Enable texture0??
    glEnable(GL_TEXTURE_2D);
    texture.use();
}