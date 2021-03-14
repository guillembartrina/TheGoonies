#include "Level.h"

#include <iostream>
#include <fstream>

Level::Level(const std::string& path, const Program& program)
{
    map = nullptr;
    tileMap = nullptr;
    if(!load(path)) std::cerr << "Error reading file!" << std::endl;
    tileMap = new Tilemap(glm::ivec2(0, 0), mapSize, map, glm::ivec2(64, 64), tilesheetPath, tilesheetSize, program);
}

Level::~Level()
{
    if(tileMap != nullptr) delete tileMap;
    if(map != nullptr) delete map;
}

void Level::render() const
{
    tileMap->render();
}

glm::ivec2 Level::getMapSize() const
{
    return mapSize;
}

bool Level::load(const std::string& path)
{
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) return false;

    getline(file, name);
    getline(file, tilesheetPath);
    file >> tilesheetSize.x >> tilesheetSize.y;
    file >> mapSize.x >> mapSize.y;

    map = new int[mapSize.x * mapSize.y];
    char index;
    for(int j = 0; j < mapSize.y; j++)
    {
        for(int i = 0; i < mapSize.x; i++)
        {
            file >> index;
            map[j*mapSize.x+i] = (index == ' ' ? -1 : index-'A');
        }
    }

    file.close();
    return true;
}