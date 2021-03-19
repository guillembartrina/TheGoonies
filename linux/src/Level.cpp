#include "Level.h"

#include "Game.h"

#include <iostream>
#include <fstream>
#include "glm/gtc/matrix_transform.hpp"

Level::Level(const std::string& path, const Program& program)
{
    cam = glm::ivec2(1, 1);
    if(!load(path)) std::cerr << "Error reading level file!" << std::endl;
    tileMap = new Tilemap(mapSize, map, tileSize, tsPath, tsSize, program);
}

Level::~Level()
{
    delete tileMap;
    delete[] map;
}

void Level::render(const glm::vec4& rect, const Program& program) const
{
    glm::mat4 modelView = glm::mat4(1.f);

    glm::vec2 translate2 = glm::vec2(rect.x, rect.w); // Lower the map
    modelView = glm::translate(modelView, glm::vec3(translate2, 0.f));

    glm::vec2 scale = glm::vec2(rect.y - rect.x, rect.z - rect.w) / (glm::vec2(roomSize) * tileSize); // World coordinates -> window coordinates
    modelView = glm::scale(modelView, glm::vec3(scale, 1.f));

    glm::vec2 translate1 = -1.f * glm::vec2(cam) * glm::vec2(roomSize) * tileSize; // Room selection
    modelView = glm::translate(modelView, glm::vec3(translate1, 0.f));

    program.setUniformValue(program.getUniformLocation("modelview"), modelView);
    tileMap->render();
}

glm::ivec2 Level::getMapSize() const
{
    return mapSize;
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
    mapSize = glm::ivec2(roomsX * roomSize.x, roomsY * roomSize.y);
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

    map = new int[mapSize.x * mapSize.y];
    for(int i = 0; i < mapSize.x; i++) for(int j = 0; j < mapSize.y; j++) map[j*mapSize.x+i] = -1;

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
                map[(roomOffsetY+j)*mapSize.x+(roomOffsetX+i)] = (index-' ');
            }
        }
    }

    delete roomPositions;

    file.close();
    return true;
}