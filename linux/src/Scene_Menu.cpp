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
	if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;
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
}

void Scene_Menu::render()
{
	text.render("MENU", glm::vec2(50, 70), 60, glm::vec4(1, 1, 1, 1));
	text.render("Press P to play", glm::vec2(50, 200), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press O to options", glm::vec2(50, 240), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press C to credits", glm::vec2(50, 280), 30, glm::vec4(1, 1, 1, 1));
}



