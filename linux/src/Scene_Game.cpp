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
	delete level;
	delete player;
}


void Scene_Game::init()
{
	initShaders();
	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	projection = glm::ortho(0.f, (windowX - 1), (windowY - 1), 0.f);

	gui = new GUI(projection, glm::vec4(0.f, windowX, 99.f, 0.f));
	player = new Player(program);
	level = new Level("levels/1.txt", program);
	level->spawn(player);
}

void Scene_Game::update(int deltaTime)
{
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
	gui->render();
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



