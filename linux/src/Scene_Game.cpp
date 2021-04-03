#include "Scene_Game.h"

#include "Game.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Scene_Game::Scene_Game()
{
}

Scene_Game::~Scene_Game()
{
	for(Level* l : levels)
	{
		delete l;
	}
	delete player;
}


void Scene_Game::init()
{
	initShaders();
	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	projection = glm::ortho(0.f, (windowX - 1), (windowY - 1), 0.f);

	player = new Player(program);
	gui = new GUI(projection, glm::vec4(0.f, windowX, 99.f, 0.f), player, program);

	for(int i = 1; i <= 1; i++)
	{
		levels.push_back(new Level("levels/" + std::to_string(i) + ".txt", program));
	}

	level = levels.front();
	level->spawnPlayer(player, -1);
}

void Scene_Game::update(int deltaTime)
{
	int nlvl;
	if((nlvl = player->changeLevel()) >= 0)
	{
		int lvlId = nlvl >> 32;
		int portalId = nlvl & 0x00FF;
		level = levels[lvlId];
		level->spawnPlayer(player, portalId);
	}
	level->update(deltaTime);
	gui->update(deltaTime);
}

void Scene_Game::render()
{
	program.use();
	program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("camview"), glm::mat4(1.0f));
	program.setUniformValue(program.getUniformLocation("modelview"), glm::mat4(1.0f));
	program.setUniformValue(program.getUniformLocation("customTexCoord"), 0);
	program.setUniformValue(program.getUniformLocation("color"), glm::vec4(1.f));
	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	level->render(glm::vec4(0.f, (windowX - 1), (windowY - 1), 100.f), program);
	gui->render(program);
}

void Scene_Game::initShaders()
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



