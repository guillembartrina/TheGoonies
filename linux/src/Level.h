#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>

#include "Program.h"
#include "Texture.h"
#include "Tilemap.h"
#include "Player.h"

static glm::ivec2 roomSize = glm::ivec2(32, 20);
static glm::vec2 tileSize = glm::vec2(16.f, 16.f);

class Level
{

	public:

	Level(const std::string& path, const Program& program);
	~Level();

	void render(const glm::vec4& rect, const Program& program) const;
	void update(int deltatime);

	glm::ivec2 getMapSize() const;

	private:

	std::string name;
	glm::ivec2 mapSize;
	int* map;
	std::string tsPath;
	glm::ivec2 tsSize;
	glm::ivec2 spawn;
	
	Player* player;
	Tilemap* tileMap;

	glm::ivec2 cam, spawnPlayer;

	bool load(const std::string& path);

};


#endif // _TILE_MAP_INCLUDE


