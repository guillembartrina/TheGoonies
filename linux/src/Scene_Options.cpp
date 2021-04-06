#include "Scene_Options.h"

#include "Game.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

#include "Scene_Menu.h"

Scene_Options::Scene_Options()
{
}

Scene_Options::~Scene_Options()
{
}


void Scene_Options::init()
{
	if(!textBold.init("fonts/OpenSans-Bold.ttf")) std::cerr << "Could not load font!!!" << std::endl;
	if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;
}

void Scene_Options::update(int deltaTime)
{
	if(Game::instance().getKey('m'))
	{
		Game::instance().changeScene(new Scene_Menu());
	}
}

void Scene_Options::render()
{
	textBold.render("Instructions", glm::vec2(60, 100), 80, glm::vec4(1, 1, 1, 1));
	text.render("Character movement: Arrow keys", glm::vec2(60, 200), 30, glm::vec4(1, 1, 1, 1));
	text.render("Punch: Z", glm::vec2(60, 235), 30, glm::vec4(1, 1, 1, 1));
	text.render("Dash: C while moving ", glm::vec2(60, 270), 30, glm::vec4(1, 1, 1, 1));
	text.render("Use portal: X", glm::vec2(60, 305), 30, glm::vec4(1, 1, 1, 1));
	text.render("Press M to menu", glm::vec2(1300, 100), 30, glm::vec4(1, 1, 1, 1));
}



