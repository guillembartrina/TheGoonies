
#include "GUI.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

GUI::GUI(const glm::mat4& projection, const glm::vec4& rect, int vit, int exp)
{
    Shader vert(ShaderType_Vertex), frag(ShaderType_Fragment);

	vert.load_fromFile("shaders/simple.vert");
	vert.compile();
	frag.load_fromFile("shaders/simple.frag");
	frag.compile();
	program.attachShader(vert);
	program.attachShader(frag);
	program.link();

	this->vit = vit;
	this->exp = exp;

    this->projection = projection;

    if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;
    background = new Quad(glm::vec2(rect.x, rect.w), glm::vec2(rect.y-rect.x, rect.z-rect.w), glm::vec4(0.f, 0.f, 0.f, 1.f), program);
}

GUI::~GUI()
{
    delete background;
}

void GUI::update(int deltatime, int vit, int exp)
{
	this->vit = vit;
	this->exp = exp;
}

void GUI::render()
{
    program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("modelview"), glm::mat4(1.0f));
    program.setUniformValue(program.getUniformLocation("color"), glm::vec4(1.f));
    background->render(program);
    text.render(std::to_string(vit), glm::vec2(10, 40), 24, glm::vec4(1.0, 1.0, 1.0, 1.0));
}