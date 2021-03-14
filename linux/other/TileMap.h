#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include "glm/glm.hpp"

#include "Texture.h"
#include "Program.h"


class TileMap
{

	public:

	TileMap(int window_width, int window_height, const std::string& path, Program &program);
	~TileMap();

	void render() const;

	private:

	GLuint VAO;
	GLuint VBO_vertices;
	GLuint VBO_texCoords;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;

	int layer;

	bool loadLevel(const std::string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, Program &program);

};


#endif // _TILE_MAP_INCLUDE


