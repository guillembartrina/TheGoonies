#include "Scene_Game.h"

#include "Game.h"

#include <iostream>
#include <cmath>
#include "Scene_Menu.h"
#include <GL/glut.h>

#include <glm/gtc/matrix_transform.hpp>

Scene_Game::Scene_Game()
{
	gameover = false;
	won = false;
}

Scene_Game::~Scene_Game()
{
	for(Level* l : levels)
	{
		delete l;
	}
	delete player;
	music->drop();
}


void Scene_Game::init()
{
	if(!text.init("fonts/OpenSans-ExtraBold.ttf")) std::cerr << "Could not load font!!!" << std::endl;

	initShaders();
	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	projection = glm::ortho(0.f, (windowX - 1), (windowY - 1), 0.f);

	player = new Player(program);
	gui = new GUI(projection, glm::vec4(0.f, windowX, 99.f, 0.f), player, program);

	for(int i = 0; i <= 4; i++)
	{
		levels.push_back(new Level("levels/" + std::to_string(i) + ".txt", program));
	}

	level = levels.front();
	level->spawnPlayer(player, -1);

	music = Game::instance().getEngine()->play2D("musics/loop.ogg", true, false, true);
	music->setVolume(0.1f);
}

void Scene_Game::update(int deltaTime)
{
	if(gameover || won)
	{
		timer -= deltaTime;
		if(timer < 0)
		{
			Game::instance().changeScene(new Scene_Menu());
		}
	}
	else
	{
		if(Game::instance().getKey('0'))
		{
			level = levels[0];
			level->spawnPlayer(player, -1);
		}
		if(Game::instance().getKey('1'))
		{
			level = levels[1];
			level->spawnPlayer(player, -1);
		}
		if(Game::instance().getKey('2'))
		{
			level = levels[2];
			level->spawnPlayer(player, -1);
		}
		if(Game::instance().getKey('3'))
		{
			level = levels[3];
			level->spawnPlayer(player, -1);
		}
		if(Game::instance().getKey('4'))
		{
			level = levels[4];
			level->spawnPlayer(player, -1);
		}

		int nlvl;
		if((nlvl = player->changeLevel()) >= 0)
		{
			int lvlId = nlvl >> 16;
			int portalId = nlvl & 0xFFFF;
			level = levels[lvlId];
			level->spawnPlayer(player, portalId);
		}
		if(player->hasWon())
		{
			timer = 3000;
			won = true;
		}
		if(player->isDead())
		{
			timer = 5000;
			gameover = true;
			music->stop();
			Game::instance().getEngine()->play2D("sounds/gameover.ogg");
		}
		level->update(deltaTime);
		gui->update(deltaTime);
	}
}

void Scene_Game::render()
{
	if(gameover)
	{
		text.render("> GAME OVER <", glm::vec2(400, 500), 100, glm::vec4(1, 0, 0, 1));
	}
	else if(won)
	{
		text.render("YOU HAVE WON!", glm::vec2(400, 500), 100, glm::vec4(0, 1, 0, 1));
	}
	else
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



