#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>
#include <vector>

#include "Program.h"
#include "Texture.h"
#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"

static glm::ivec2 roomSize = glm::ivec2(32, 20);
static glm::vec2 tileSize = glm::vec2(16.f, 16.f);
static glm::vec2 floorOffset = glm::vec2(0.f, -2.f);

class Level
{

	public:

	Level(const std::string& path, const Program& program);
	~Level();

	void spawn(Player* player);

	void render(const glm::vec4& rect, const Program& program) const;
	void update(int deltatime);

	glm::ivec2 getMapSize() const;
	/*
	TODO:
	bool collisionMoveLeft(Entity *a)
	bool collisionMoveRight(Entity *a)
	bool collisionMoveDown(Entity *a)
	*/

	private:

	std::string name;
	glm::ivec2 mapSize;
	int* map;
	std::string tsPath;
	glm::ivec2 tsSize;
	glm::ivec2 spawnPos;
	
	Player* player;
	std::vector<Entity *> entities;
	Tilemap* tileMap;

	glm::ivec2 cam;

	bool load(const std::string& path);

};


#endif // _TILE_MAP_INCLUDE


