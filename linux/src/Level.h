#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include <string>

#include "Program.h"
#include "Texture.h"
#include "Tilemap.h"

static glm::ivec2 roomSize = glm::vec2(32, 22);

class Level
{

	public:

	Level(const std::string& path, const Program& program);
	~Level();

	void render() const;

	glm::ivec2 getSize() const;

	private:

	std::string name;
	glm::ivec2 size;
	int* level;
	std::string tsPath;
	glm::ivec2 tsSize;
	
	Tilemap* tileMap;

	bool load(const std::string& path);

};


#endif // _TILE_MAP_INCLUDE


