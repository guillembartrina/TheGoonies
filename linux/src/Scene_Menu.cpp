#include "Scene_Menu.h"

#include "Game.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

#include "Scene_Game.h"
#include "Scene_Options.h"
#include "Scene_Credits.h"

Scene_Menu::Scene_Menu()
{
}

Scene_Menu::~Scene_Menu()
{
	delete sprite;
}


void Scene_Menu::init()
{
	if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;

	float windowX = Game::instance().getWindowWidth(), windowY = Game::instance().getWindowHeight();
	projection = glm::ortho(0.f, (windowX - 1), (windowY - 1), 0.f);

	Shader vert(ShaderType_Vertex), frag(ShaderType_Fragment);

	vert.load_fromFile("shaders/default.vert");
	vert.compile();
	frag.load_fromFile("shaders/default.frag");
	frag.compile();
	program.attachShader(vert);
	program.attachShader(frag);
	program.link();

	Texture* textu = new Texture();
	textu->loadFromFile("images/rocks.jpg", PixelFormat::TEXTURE_PIXEL_FORMAT_RGB);
	sprite = new Sprite(glm::vec2(400, 400), glm::vec2(100, 100), textu, program);
}

void Scene_Menu::update(int deltaTime)
{
	if(Game::instance().getKey('p'))
	{
		Game::instance().changeScene(new Scene_Game());
	}
	if(Game::instance().getKey('o'))
	{
		Game::instance().changeScene(new Scene_Options());
	}
	if(Game::instance().getKey('c'))
	{
		Game::instance().changeScene(new Scene_Credits());
	}

	if(Game::instance().getKey('d'))
	{
		sprite->setPosition(sprite->getPosition() + glm::vec2(10, 0));
	}
	if(Game::instance().getKey('a'))
	{
		sprite->setPosition(sprite->getPosition() + glm::vec2(-10, 0));
	}
	if(Game::instance().getKey('w'))
	{
		sprite->setPosition(sprite->getPosition() + glm::vec2(0, -10));
	}
	if(Game::instance().getKey('s'))
	{
		sprite->setPosition(sprite->getPosition() + glm::vec2(0, 10));
	}
}

void Scene_Menu::render()
{
	text.render("MENU", glm::vec2(50, 70), 60, glm::vec4(1, 1, 1, 1));
	text.render("Press P to play", glm::vec2(50, 200), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press O to options", glm::vec2(50, 240), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press C to credits", glm::vec2(50, 280), 30, glm::vec4(1, 1, 1, 1));
	program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("camview"), glm::mat4(1.0));
	sprite->render(program);
}



