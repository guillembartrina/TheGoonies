#include "Scene2.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Scene2::Scene2()
{
	map = NULL;
}

Scene2::~Scene2()
{
	if(map != NULL) delete map;
}


void Scene2::init()
{
	initShaders();
	texture.loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	//map = TileMap::createTileMap("levels/level01.txt", glm::vec2(32, 16), program);
	//projection = glm::ortho(0.f, float(640 - 1), float(480 - 1), 0.f);

	glGenVertexArrays(1, &rectVAO);
	glBindVertexArray(rectVAO);

	std::vector<float> vertices = { 0.0,    0.0,
									1.0,    0.0,
									0.0,    1.0,
									1.0,    1.0 };
	
	std::vector<float> texCoords = {0.0,    0.0,
									1.0,    0.0,
									0.0,    1.0,
									1.0,    1.0 };

	std::vector<unsigned int> indices = { 0,  2,  1,
											1,  2,  3 };

	glGenBuffers(1, &rectiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectiVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	posLocation = program.getAttributeLocation("position");
	glGenBuffers(1, &rectvVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rectvVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posLocation);

	texCoordLocation = program.getAttributeLocation("texCoordvfvf");
	glGenBuffers(1, &recttVBO);
	glBindBuffer(GL_ARRAY_BUFFER, recttVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordLocation);
	
	glBindVertexArray(0);
}

void Scene2::update(int deltaTime)
{
}

void Scene2::render()
{
	program.use();
	program.setUniformValue(program.getUniformLocation("projection"), glm::mat4(1.0f));
	program.setUniformValue(program.getUniformLocation("modelview"), glm::mat4(1.0f));
	//map->render();
	//texture.use();
	glBindVertexArray(rectVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Scene2::initShaders()
{
	Shader vert(ShaderType_Vertex), frag(ShaderType_Fragment);

	vert.load_fromFile("shaders/texture.vert");
	vert.compile();
	frag.load_fromFile("shaders/texture.frag");
	frag.compile();
	program.attachShader(vert);
	program.attachShader(frag);
	program.link();

	/*
	GLint count;
	glGetProgramiv(program.getId(), GL_ACTIVE_ATTRIBUTES, &count);
	std::cout << count;
	*/
}



