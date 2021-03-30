#include "Level.h"

#include "Game.h"
#include "Rock.h"
#include "Droplet.h"

#include <iostream>
#include <fstream>
#include "glm/gtc/matrix_transform.hpp"

Level::Level(const std::string& path, const Program& program)
{
    cam = glm::ivec2(2, 0);
    if(!load(path, program)) std::cerr << "Error reading level file!" << std::endl;
}

Level::~Level()
{
    for(Entity* e : entities)
    {
        delete e;
    }
    delete tileMap;
    delete tilesheet;
    delete movingsheet;
    delete[] map;
}

void Level::spawnPlayer(Player* player)
{
    this->player = player;
    player->setPosition(glm::vec2(spawnPos) - tileSize*glm::vec2(0.25f, 0.2f)); //Change??
    player->spawn(this);
}

void Level::render(const glm::vec4& rect, const Program& program) const
{
    program.setUniformValue(program.getUniformLocation("color"), glm::vec4(1.f));
    
    glm::mat4 modelview = glm::mat4(1.f);
    glm::mat4 camview = glm::mat4(1.f);

    glm::vec2 translate2 = glm::vec2(rect.x, rect.w); // Lower the map
    camview = glm::translate(camview, glm::vec3(translate2, 0.f));

    glm::vec2 scale = glm::vec2(rect.y - rect.x, rect.z - rect.w) / (glm::vec2(roomSize) * tileSize); // World coordinates -> window coordinates
    camview = glm::scale(camview, glm::vec3(scale, 1.f));

    glm::vec2 translate1 = -1.f * glm::vec2(cam) * glm::vec2(roomSize) * tileSize; // Room selection
    camview = glm::translate(camview, glm::vec3(translate1, 0.f));

    program.setUniformValue(program.getUniformLocation("camview"), camview);

    program.setUniformValue(program.getUniformLocation("modelview"), modelview);
    tileMap->render();

	for(Entity* e : entities)
    {
		e->render(program);
	}
	if(player) player->render(program);
}

void Level::update(int deltatime)
{
    if(player)
    {
        int playerX = (player->getPosition().x + 0.5f*player->getSize().x) / (tileSize.x * roomSize.x),
            playerY = (player->getPosition().y + 0.5f*player->getSize().y) / (tileSize.y * roomSize.y);
        if(cam != glm::ivec2(playerX, playerY)) cam = glm::ivec2(playerX, playerY);
    }

	for(auto it = entities.begin(); it != entities.end(); )
    {
		(*it)->update(deltatime);

        if((*it)->toDestroy()) it = entities.erase(it);
        else it++;
	}
	if(player) player->update(deltatime);
}

glm::ivec2 Level::getMapSize() const
{
    return mapSize;
}

Player* Level::getPlayer()
{
    return player;
}

std::list<Entity *>& Level::getEntities()
{
    return entities;
}

bool Level::collisionMoveLeft(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const
{
    int x = pos.x / tileSize.x;
    int ymin = pos.y / tileSize.y, ymax = (pos.y + size.y - 1.f) / tileSize.y;

    for(int y = ymin; y <= ymax; y++)
    {
        switch(collisionMap[map[y*mapSize.x+x]])
        {
            case CollisionType::FULL:
            case CollisionType::RIGHT:
                shouldbe = glm::vec2((x+1)*tileSize.x, pos.y);
                return true;
                break;
            case CollisionType::LEFT:
                if(pos.x < (x+0.5f)*tileSize.x)
                {
                    shouldbe = glm::vec2((x+0.5f)*tileSize.x, pos.y);
                    return true;
                }
                break;
            case CollisionType::TOP:
                if(pos.y < (y+0.5f)*tileSize.y)
                {
                    shouldbe = glm::vec2((x+1)*tileSize.x, pos.y);
                    return true;
                }
                break;
            case CollisionType::BOTTOM:
                if((pos.y + size.y - 1.f) > (y+0.8)*tileSize.y)
                {
                    shouldbe = glm::vec2((x+1)*tileSize.x, pos.y);
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool Level::collisionMoveRight(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const
{
    int x = (pos.x + size.x - 1.f) / tileSize.x;
    int ymin = pos.y / tileSize.y, ymax = (pos.y + size.y - 1.f) / tileSize.y;

    for(int y = ymin; y <= ymax; y++)
    {
        switch(collisionMap[map[y*mapSize.x+x]])
        {
            case CollisionType::FULL:
            case CollisionType::LEFT:
                shouldbe = glm::vec2(x*tileSize.x - size.x, pos.y);
                return true;
                break;
            case CollisionType::RIGHT:
                if((pos.x + size.x - 1.f) > (x+0.5f)*tileSize.x)
                {
                    shouldbe = glm::vec2((x+0.5f)*tileSize.x - size.x, pos.y);
                    return true;
                }
                break;
            case CollisionType::TOP:
                if(pos.y < (y+0.5f)*tileSize.y)
                {
                    shouldbe = glm::vec2(x*tileSize.x - size.x, pos.y);
                    return true;
                }
                break;
            case CollisionType::BOTTOM:
                if((pos.y + size.y - 1.f) > (y+0.8f)*tileSize.y)
                {
                    shouldbe = glm::vec2(x*tileSize.x - size.x, pos.y);
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool Level::collisionMoveUp(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const
{
    int xmin = pos.x / tileSize.x, xmax = (pos.x + size.x - 1.f) / tileSize.x;
    int y = pos.y / tileSize.y;

    for(int x = xmin; x <= xmax; x++)
    {
        switch(collisionMap[map[y*mapSize.x+x]])
        {
            case CollisionType::FULL:
            case CollisionType::BOTTOM:
                shouldbe = glm::vec2(pos.x, (y+1)*tileSize.y);
                return true;
                break;
            case CollisionType::TOP:
                if(pos.y < (y+0.5f)*tileSize.y)
                {
                    shouldbe = glm::vec2(pos.x, (y+0.5f)*tileSize.y);
                    return true;
                }
                break;
            case CollisionType::LEFT:
                if(pos.x < (x+0.5f)*tileSize.x)
                {
                    shouldbe = glm::vec2(pos.x, (y+1)*tileSize.y);
                    return true;
                }
                break;
            case CollisionType::RIGHT:
                if((pos.x + size.x - 1.f) > (x+0.5f)*tileSize.x)
                {
                    shouldbe = glm::vec2(pos.x, (y+1)*tileSize.y);
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool Level::collisionMoveDown(const glm::vec2& pos, const glm::vec2& size, glm::vec2& shouldbe) const
{
    int xmin = pos.x / tileSize.x, xmax = (pos.x + size.x - 1.f) / tileSize.x;
    int y = (pos.y + size.y - 1.f) / tileSize.y;

    for(int x = xmin; x <= xmax; x++)
    {
        switch(collisionMap[map[y*mapSize.x+x]])
        {
            case CollisionType::FULL:
            case CollisionType::TOP:
                shouldbe = glm::vec2(pos.x, y*tileSize.y - size.y);
                return true;
                break;
            case CollisionType::BOTTOM:
                if((pos.y + size.y - 1.f) > (y+0.8f)*tileSize.y)
                {
                    shouldbe = glm::vec2(pos.x, (y+0.8f)*tileSize.y - size.y); //-1 pixel?
                    return true;
                }
                break;
            case CollisionType::LEFT:
                if(pos.x < (x+0.5f)*tileSize.x)
                {
                    shouldbe = glm::vec2(pos.x, y*tileSize.y - size.y);
                    return true;
                }
                break;
            case CollisionType::RIGHT:
                if((pos.x + size.x - 1.f) > (x+0.5f)*tileSize.x)
                {
                    shouldbe = glm::vec2(pos.x, y*tileSize.y - size.y);
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool Level::getFirstOf(const glm::vec2& pos, const glm::vec2& size, int direction, glm::vec2& first) const //REFACTOR!
{
    glm::vec2 curr = pos;
    while(true)
    {
        switch (direction)
        {
            case 0:
                if(curr.y < 0.f) return false;
                if(collisionMoveUp(curr, size, first)) return true;
                curr.y -= tileSize.y*0.5f;
                break;
            case 1:
                if(curr.x + size.x >= mapSize.x*tileSize.x) return false;
                if(collisionMoveRight(curr, size, first)) return true;
                curr.y += tileSize.x*0.5f;
                break;
            case 2:
                if(curr.y + size.y >= mapSize.y*tileSize.y) return false;
                if(collisionMoveDown(curr, size, first)) return true;
                curr.y += tileSize.y*0.5f;
                break;
            case 3:
                if(curr.x < 0.f) return false;
                if(collisionMoveLeft(curr, size, first)) return true;
                curr.y -= tileSize.x*0.5f;
                break;
        
            default:
                break;
        }
    }
}

bool Level::getFirstOf_Tiles(const glm::ivec2& ini, int direction, CollisionType type, glm::ivec2& first) const
{
    glm::ivec2 curr = ini;
    while(curr.x >= 0 && curr.y >= 0 && curr.x < mapSize.x && curr.y < mapSize.y)
    {
        if(collisionMap[map[curr.y*mapSize.x+curr.x]] == type)
        {
            first = curr;
            return true;
        }
        switch (direction)
        {
            case 0:
                curr.y--;
                break;
            case 1:
                curr.x++;
                break;
            case 2:
                curr.y++;
                break;
            case 3:
                curr.x--;
                break;
            default:
                break;
        }
    }
    return false;
}

bool Level::load(const std::string& path, const Program& program) //Add loading errors returning 'false'
{
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) return false;
    std::string dummy;

    getline(file, name);
    std::string tilesPath;
    getline(file, tilesPath);
    glm::ivec2 tilesSize;
    file >> tilesSize.x >> tilesSize.y;
    tilesheet = new Tilesheet(tilesPath, tilesSize);
    
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
    spawnPos = roomRelativeToWorldCoords(roomPositions, spawnRoom, glm::ivec2(spawnX, spawnY)); //glm::vec2((roomPositions[spawnRoom].x*roomSize.x+spawnX)*tileSize.x, (roomPositions[spawnRoom].y*roomSize.y+spawnY)*tileSize.y);

    getline(file, dummy); //Next line
    for(int i = 0; i < 96; i++) collisionMap[i] = CollisionType::FULL;
    getline(file, dummy); //Any
    for(unsigned int i = 0; i < dummy.length(); i++) collisionMap[dummy[i]-' '] = CollisionType::ANY;
    getline(file, dummy); //Full
    for(unsigned int i = 0; i < dummy.length(); i++) collisionMap[dummy[i]-' '] = CollisionType::FULL;
    getline(file, dummy); //Bottom
    for(unsigned int i = 0; i < dummy.length(); i++) collisionMap[dummy[i]-' '] = CollisionType::BOTTOM;
    getline(file, dummy); //Top
    for(unsigned int i = 0; i < dummy.length(); i++) collisionMap[dummy[i]-' '] = CollisionType::TOP;
    getline(file, dummy); //Right
    for(unsigned int i = 0; i < dummy.length(); i++) collisionMap[dummy[i]-' '] = CollisionType::RIGHT;
    getline(file, dummy); //Left
    for(unsigned int i = 0; i < dummy.length(); i++) collisionMap[dummy[i]-' '] = CollisionType::LEFT;

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

                //Map-wise entities
                switch (index)
                {
                    case '%':
                        addEntity(new Sensor(SensorType::VINE_TOP, roomRelativeToWorldCoords(roomPositions, room, glm::ivec2(i, j-1)), tileSize));
                        break;
                    case '$':
                        addEntity(new Sensor(SensorType::VINE_BOTTOM, roomRelativeToWorldCoords(roomPositions, room, glm::ivec2(i, j)), tileSize));
                        break;
                    default:
                        break;
                }
            }
        }
    }

    tileMap = new Tilemap(mapSize, map, tileSize, tilesheet, program);

    //---
    std::string movingPath;
    getline(file, movingPath);
    glm::ivec2 movingSize;
    file >> movingSize.x >> movingSize.y;
    movingsheet = new Tilesheet(movingPath, movingSize);

    int elements, elementType;
    file >> elements;
    for(int i = 0; i < elements; i++)
    {
        file >> elementType;
        switch (elementType)
        {
            case 1:
            {
                int elementRoom, elementX, elementY;
                file >> elementRoom >> elementX >> elementY;
                addEntity(new Rock(roomRelativeToWorldCoords(roomPositions, elementRoom, glm::ivec2(elementX, elementY)), movingsheet, program));
            }
                break;
            case 2:
            {
                int elementRoom, elementX, elementY;
                file >> elementRoom >> elementX >> elementY;
                addEntity(new Droplet(roomRelativeToWorldCoords(roomPositions, elementRoom, glm::ivec2(elementX, elementY)), movingsheet, program));
            }
                break;
            
            default:
                break;
        }
    }

    delete roomPositions;

    file.close();
    return true;
}

glm::vec2 Level::roomRelativeToWorldCoords(glm::ivec2* roomPositions, int room, glm::ivec2 coords) const
{
    return glm::vec2((roomPositions[room].x*roomSize.x+coords.x)*tileSize.x, (roomPositions[room].y*roomSize.y+coords.y)*tileSize.y);
}

void Level::addEntity(Entity* entity)
{
    entity->spawn(this);
    entities.push_back(entity);
}