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
}


void Scene_Menu::init()
{
	if(!text.init("fonts/OpenSans-Bold.ttf")) std::cerr << "Could not load font!!!" << std::endl;

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

	texture.loadFromFile("images/menu.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite(glm::vec2(0.f), glm::vec2(windowX, windowY), &texture, program);

	Game::instance().getEngine()->play2D("musics/title.ogg", true);
}

void Scene_Menu::update(int deltaTime)
{
	background->update(deltaTime);
	if(Game::instance().getKey('p'))
	{
		Game::instance().changeScene(new Scene_Game());
	}
	if(Game::instance().getKey('i'))
	{
		Game::instance().changeScene(new Scene_Options());
	}
	if(Game::instance().getKey('c'))
	{
		Game::instance().changeScene(new Scene_Credits());
	}
}

void Scene_Menu::render()
{
	program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("camview"), glm::mat4(1.0));
	program.setUniformValue(program.getUniformLocation("customTexCoord"), 0);
	program.setUniformValue(program.getUniformLocation("color"), glm::vec4(1.f));
	background->render(program);
	text.render("Press P to play", glm::vec2(710, 600), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press I to instructions", glm::vec2(675, 700), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press C to credits", glm::vec2(695, 800), 30, glm::vec4(1, 1, 1, 1));
}



