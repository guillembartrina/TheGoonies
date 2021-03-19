#include "Scene_Credits.h"

#include "Game.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

#include "Scene_Menu.h"

Scene_Credits::Scene_Credits()
{
}

Scene_Credits::~Scene_Credits()
{
}


void Scene_Credits::init()
{
	if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;
}

void Scene_Credits::update(int deltaTime)
{
	if(Game::instance().getKey('m'))
	{
		Game::instance().changeScene(new Scene_Menu());
	}
}

void Scene_Credits::render()
{
	text.render("CREDITS", glm::vec2(50, 70), 60, glm::vec4(1, 1, 1, 1));
	text.render("Press M to menu", glm::vec2(50, 200), 30, glm::vec4(1, 1, 1, 1));
}



