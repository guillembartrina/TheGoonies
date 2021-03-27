#include <GL/glew.h>
#include <GL/glut.h>

#include "Game.h"

Game::Game()
{
	windowWidth = windowHeight = 0;
	scene = nullptr;
	newScene = nullptr;
}

void Game::init(int windowWidth, int windowHeight, IScene* scene)
{
	bPlay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->scene = scene;
	this->scene->init();
}

bool Game::update(int deltaTime)
{
	if(newScene != nullptr)
	{
		delete scene;
		scene = newScene;
		newScene = nullptr;
		scene->init();
	}

	if(scene != nullptr) scene->update(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(scene != nullptr) scene->render();
}

void Game::keyPressed(int key)
{
	if(key == 27) bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

int Game::getWindowWidth() const
{
	return windowWidth;
}

int Game::getWindowHeight() const
{
	return windowHeight;
}

void Game::changeScene(IScene* scene)
{
	this->newScene = scene;
}





