#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>

#include "Program.h"
#include "Texture.h"
#include "Tilemap.h"

#define WINDOW_X_TILES 40
#define WINDOW_Y_TILES	20

class Level
{

	public:

	Level(const std::string& path, const Program& program);
	~Level();

	void render() const;

	glm::ivec2 getMapSize() const;

	private:

	std::string name;
	std::string tilesheetPath;
	glm::ivec2 tilesheetSize;
	glm::ivec2 mapSize;
	int* map;
	
	Tilemap* tileMap;

	bool load(const std::string& path);

};


#endif // _TILE_MAP_INCLUDE


