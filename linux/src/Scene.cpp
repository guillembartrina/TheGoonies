#include "Scene.h"

#include "Game.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
{
	pos = glm::ivec2(0, 0);
}

Scene::~Scene()
{
	delete level;
}


void Scene::init()
{
	initShaders();

	level = new Level("levels/test.txt", program);
	glm::vec4 p = level->getProjection(pos);
	projection = glm::ortho(p.x, p.y, p.z, p.w);
}

void Scene::update(int deltaTime)
{
	glm::vec4 p = level->getProjection(pos);
	projection = glm::ortho(p.x, p.y, p.z, p.w);
	if(Game::instance().getKey('a'))
	{
		pos += glm::ivec2(-32, 0);
	}
	if(Game::instance().getKey('s'))
	{
		pos += glm::ivec2(0, 32);
	}
	if(Game::instance().getKey('d'))
	{
		pos += glm::ivec2(32, 0);
	}
	if(Game::instance().getKey('w'))
	{
		pos += glm::ivec2(0, -32);
	}
}

void Scene::render()
{
	program.use();
	program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("modelview"), glm::mat4(1.0f));
	level->render();
}

void Scene::initShaders()
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



