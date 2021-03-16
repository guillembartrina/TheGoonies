#include "Level.h"

#include "Game.h"

#include <iostream>
#include <fstream>

Level::Level(const std::string& path, const Program& program)
{
    if(!load(path)) std::cerr << "Error reading level file!" << std::endl;
    glm::ivec2 tileSize = glm::vec2(Game::instance().getWindowWidth() / roomSize.x, Game::instance().getWindowHeight() / roomSize.y);
    tileMap = new Tilemap(glm::ivec2(0, 0), size, level, tileSize, tsPath, tsSize, program);
}

Level::~Level()
{
    delete tileMap;
    delete level;
}

void Level::render() const
{
    tileMap->render();
}

glm::ivec2 Level::getSize() const
{
    return size;
}

bool Level::load(const std::string& path) //Add loading errors returning 'false'
{
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) return false;
    std::string dummy;

    getline(file, name);
    getline(file, tsPath);
    file >> tsSize.x >> tsSize.y;
    
    int rooms, roomsX, roomsY;
    file >> rooms;
    file >> roomsX >> roomsY;
    getline(file, dummy); //Next line
    size = glm::ivec2(roomsX * roomSize.x, roomsY * roomSize.y);
    glm::ivec2* roomPositions = new glm::ivec2[rooms];
    for(int j = 0; j < roomsY; j++)
    {
        getline(file, dummy);
        for(int i = 0; i < roomsX; i++)
        {
            if(dummy[i] != ' ')
            {
                roomPositions[dummy[i]-'0'] = glm::ivec2(i, j);
            }
        }
    }

    level = new int[size.x * size.y];
    for(int i = 0; i < size.x; i++) for(int j = 0; j < size.y; j++) level[j*size.x+i] = -1;

    int room;
    char index;
    for(int k = 0; k < rooms; k++)
    {
        file >> room;
        getline(file, dummy); //Next line
        int roomOffsetX = roomPositions[room].x*roomSize.x;
        int roomOffsetY = roomPositions[room].y*roomSize.y;
        for(int j = 0; j < roomSize.y; j++)
        {
            getline(file, dummy);
            for(int i = 0; i < roomSize.x; i++)
            {
                index = dummy[i];
                level[(roomOffsetY+j)*size.x+(roomOffsetX+i)] = (index-' ');
            }
        }
    }

    delete roomPositions;

    file.close();
    return true;
}