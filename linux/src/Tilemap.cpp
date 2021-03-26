#include "Tilemap.h"

#include <iostream>
#include <fstream>

Tilemap::Tilemap(const glm::ivec2& mapSize, const int* map, const glm::vec2& tileSize, Tilesheet* tilesheet, const Program& program)
{
    this->tilesheet = tilesheet;
    buildTilemap(mapSize, map, tileSize, program);
}

Tilemap::~Tilemap()
{
    glDeleteBuffers(1, &vertices_VBO);
    glDeleteBuffers(1, &texCoords_VBO);
    glDeleteVertexArrays(1, &VAO);
    delete tilesheet;
}

void Tilemap::render() const
{
    tilesheet->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, elements);
}

void Tilemap::buildTilemap(const glm::ivec2& mapSize, const int* map, const glm::vec2& tileSize, const Program& program)
{
    int tile;
    glm::vec2 position;

    std::vector<float> vertices, texCoords;

    for(int j = 0; j < mapSize.y; j++)
	{
		for(int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];

            if(tile != -1)
            {
                position = glm::vec2(tileSize.x * i, tileSize.y * j);

                vertices.push_back(position.x); vertices.push_back(position.y);
                vertices.push_back(position.x + tileSize.x); vertices.push_back(position.y);
                vertices.push_back(position.x + tileSize.x); vertices.push_back(position.y + tileSize.y);

                vertices.push_back(position.x); vertices.push_back(position.y);
                vertices.push_back(position.x + tileSize.x); vertices.push_back(position.y + tileSize.y);
                vertices.push_back(position.x); vertices.push_back(position.y + tileSize.y);

                glm::vec4 tC = tilesheet->getTexCoords(tile);

                texCoords.push_back(tC.x); texCoords.push_back(tC.y);
                texCoords.push_back(tC.z); texCoords.push_back(tC.y);
                texCoords.push_back(tC.z); texCoords.push_back(tC.w);

                texCoords.push_back(tC.x); texCoords.push_back(tC.y);
                texCoords.push_back(tC.z); texCoords.push_back(tC.w);
                texCoords.push_back(tC.x); texCoords.push_back(tC.w);

            }
        }
    }

    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

    GLint positionPos = program.getAttributeLocation("position");
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(positionPos, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionPos);

    GLint texCoordPos = program.getAttributeLocation("texCoord");
	glGenBuffers(1, &texCoords_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, texCoords_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(texCoordPos, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordPos);

    glBindVertexArray(0);

    elements = vertices.size();
}