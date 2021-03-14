#ifndef _TILESHEET_INCLUDE
#define _TILESHEET_INCLUDE

#include <string>

#include "glm/glm.hpp"

#include "Texture.h"

class Tilesheet
{

	public:

	Tilesheet(const std::string& path, const glm::ivec2& size);
	~Tilesheet();

    glm::vec4 getTexCoords(int index);

	void use() const;

	private:

	glm::ivec2 size;
    glm::vec2 tileSize, halfTexel;
    Texture texture;
	//glm::ivec2 position, mapSize, tilesheetSize;
	//int tileSize, blockSize;
	//glm::vec2 tileTexSize;

};


#endif // _TILESHEET_INCLUDE
