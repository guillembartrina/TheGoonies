#include "Scene.h"

#include "Game.h"

#include <iostream>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
{
}

Scene::~Scene()
{
	delete level;
}


void Scene::init()
{
	initShaders();
	projection = glm::ortho(0.f, float(Game::instance().getWindowWidth() - 1), float(Game::instance().getWindowHeight() - 1), 0.f);

	level = new Level("levels/test.txt", program);
}

void Scene::update(int deltaTime)
{
}

void Scene::render()
{
	program.use();
	program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("modelview"), glm::mat4(1.0f));
	level->render();
}

void Scene::initShaders()
{
	Shader vert(ShaderType_Vertex), frag(ShaderType_Fragment);

	vert.load_fromFile("shaders/texture.vert");
	vert.compile();
	frag.load_fromFile("shaders/texture.frag");
	frag.compile();
	program.attachShader(vert);
	program.attachShader(frag);
	program.link();

	/*
	GLint count;
	glGetProgramiv(program.getId(), GL_ACTIVE_ATTRIBUTES, &count);
	std::cout << count;
	*/
}



