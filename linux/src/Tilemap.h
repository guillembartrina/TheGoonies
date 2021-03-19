#ifndef _TILEMAP_INCLUDE
#define _TILEMAP_INCLUDE

#include "glm/glm.hpp"

#include "Program.h"
#include "Texture.h"
#include "Tilesheet.h"

class Tilemap
{

	public:

	Tilemap(const glm::ivec2& mapSize, int* map, const glm::vec2& tileSize, const std::string& tilesheetPath, const glm::ivec2& tilesheetSize, const Program& program);
	~Tilemap();

	void render() const;

	private:

	Tilesheet* tilesheet;
	GLuint VAO, vertices_VBO, texCoords_VBO;
	int elements;

	void buildTilemap(const glm::ivec2& mapSize, int* map, const glm::vec2& tileSize, const Program& program);

};


#endif // _TILE_MAP_INCLUDE


