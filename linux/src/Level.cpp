#include "Level.h"

#include "Game.h"

#include <iostream>
#include <fstream>
#include "glm/gtc/matrix_transform.hpp"

Level::Level(const std::string& path, const Program& program)
{
    cam = glm::ivec2(0, 0);
    if(!load(path)) std::cerr << "Error reading level file!" << std::endl;
    tileMap = new Tilemap(mapSize, map, tileSize, new Tilesheet(tsPath, tsSize), program);
}

Level::~Level()
{
    delete tileMap;
    delete[] map;
}

void Level::spawn(Player* player)
{
    player->setLevel(this);
    player->setPosition(spawnPos);
    this->player = player;
}

void Level::render(const glm::vec4& rect, const Program& program) const
{
    glm::mat4 modelview = glm::mat4(1.f);
    glm::mat4 camview = glm::mat4(1.f);

    glm::vec2 translate2 = glm::vec2(rect.x, rect.w); // Lower the map
    camview = glm::translate(camview, glm::vec3(translate2, 0.f));

    glm::vec2 scale = glm::vec2(rect.y - rect.x, rect.z - rect.w) / (glm::vec2(roomSize) * tileSize); // World coordinates -> window coordinates
    camview = glm::scale(camview, glm::vec3(scale, 1.f));

    program.setUniformValue(program.getUniformLocation("camview"), camview);

    glm::vec2 translate1 = -1.f * glm::vec2(cam) * glm::vec2(roomSize) * tileSize; // Room selection
    modelview = glm::translate(modelview, glm::vec3(translate1, 0.f));

    program.setUniformValue(program.getUniformLocation("modelview"), modelview);
    tileMap->render();

	player->render(program);
	for (int i = 0; i < entities.size(); ++i) {
		entities[i]->render(program);
	}
}

void Level::update(int deltatime) {
	player->update(deltatime);
	for (int i = 0; i < entities.size(); ++i) {
		entities[i]->update(deltatime);
	}
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

    int spawnRoom, spawnX, spawnY;
    file >> spawnRoom >> spawnX >> spawnY;
    spawnPos = glm::ivec2((roomPositions[spawnRoom].x*roomSize.x+spawnX)*tileSize.x, (roomPositions[spawnRoom].y*roomSize.y+spawnY)*tileSize.y);

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