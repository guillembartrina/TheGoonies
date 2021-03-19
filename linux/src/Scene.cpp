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
	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	level = new Level("levels/test.txt", program);
	projection = glm::ortho(0.f, (windowX - 1), (windowY - 1), 0.f);

	if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;
}

void Scene::update(int deltaTime)
{
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

	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	level->render(glm::vec4(0.f, (windowX - 1), (windowY - 1), 100.f), program);

	text.render("DUDE", glm::vec2(50, 50), 24, glm::vec4(1, 1, 1, 1));
}

void Scene::initShaders()
{
	Shader vert(ShaderType_Vertex), frag(ShaderType_Fragment);

	vert.load_fromFile("shaders/default.vert");
	vert.compile();
	frag.load_fromFile("shaders/default.frag");
	frag.compile();
	program.attachShader(vert);
	program.attachShader(frag);
	program.link();
}



