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

	Texture* getTexture();
    glm::vec4 getTexCoords(int index);
	glm::vec4 getTexCoords(glm::ivec2 pos, glm::ivec2 size = glm::ivec2(1, 1));

	void use() const;

	private:

	glm::ivec2 size;
    glm::vec2 tileSize, halfTexel;
    Texture texture;
};


#endif // _TILESHEET_INCLUDE
