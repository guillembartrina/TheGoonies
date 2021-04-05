
#include "GUI.h"
#include "Level.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

GUI::GUI(const glm::mat4& projection, const glm::vec4& rect, Player *player, Program &programTexture)
{
    Shader vert(ShaderType_Vertex), frag(ShaderType_Fragment);

	vert.load_fromFile("shaders/simple.vert");
	vert.compile();
	frag.load_fromFile("shaders/simple.frag");
	frag.compile();
	program.attachShader(vert);
	program.attachShader(frag);
	program.link();

	this->player = player;
    this->projection = projection;
	texture = Texture::createTexture("images/gui.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);

	powerupFrames = new Sprite(glm::vec2(0.f), glm::vec2(60.f, 60.f), texture, programTexture);
	for (int i = 0; i < POW_HYPERSHOES - BAG; ++i) {
		powerupFrames->addFrame(new Frame(i*.125f, 0.f, .125f, 1.f));
	}

	friendSprite = new Sprite(glm::vec2(900.f, 17.f), glm::vec2(60.f, 60.f), texture, programTexture);
	friendSprite->addFrame(new Frame(6.f*.125f, 0.f, .0625f, .5f));
	friendSprite->setFrame(0);

    if(!text.init("fonts/OpenSans-Regular.ttf")) std::cerr << "Could not load font!!!" << std::endl;
    background = new Quad(glm::vec2(rect.x, rect.w), glm::vec2(rect.y-rect.x, rect.z-rect.w), glm::vec4(0.f, 0.f, 0.f, 1.f), program);
	maxVitBar = new Quad(glm::vec2(50.f, 15.f), glm::vec2(270.f, 34.f), glm::vec4(1.f, 1.f, 1.f, 1.f), program);
	vitBar = new Quad(glm::vec2(60.f, 17.f), glm::vec2(250.f, 30.f), glm::vec4(0.f, .5f, 0.f, 1.f), program);
	maxExpBar = new Quad(glm::vec2(50.f, 55.f), glm::vec2(270.f, 34.f), glm::vec4(1.f, 1.f, 1.f, 1.f), program);
	expBar = new Quad(glm::vec2(60.f, 57.f), glm::vec2(10.f, 30.f), glm::vec4(0.f, .0f, 5.f, 1.f), program);

	oldVit = -1;
	oldExp = -1;
	
}

GUI::~GUI()
{
    delete background;
}

void GUI::update(int deltatime)
{
	int newVit = player->getVit();
	int newExp = player->getExp();

	if(newVit != oldVit)
	{
		oldVit = newVit;
		delete vitBar;
		vitBar = new Quad(glm::vec2(60.f, 17.f), glm::vec2((player->getVit()/50.f)*250.f, 30.f), glm::vec4(0.f, 1.f, 0.f, 1.f), program);
	}
	if (newExp != oldExp) {
		oldExp = newExp;
		delete expBar;
		expBar = new Quad(glm::vec2(60.f, 57.f), glm::vec2((player->getExp()/1000.f)*250.f, 30.f), glm::vec4(0.f, .0f, 5.f, 1.f), program);
	}
}

void GUI::render(Program &programTexture)
{
    program.setUniformValue(program.getUniformLocation("projection"), projection);
	program.setUniformValue(program.getUniformLocation("modelview"), glm::mat4(1.0f));
    program.setUniformValue(program.getUniformLocation("color"), glm::vec4(1.f));

	programTexture.setUniformValue(programTexture.getUniformLocation("projection"), projection);
	programTexture.setUniformValue(programTexture.getUniformLocation("camview"), glm::mat4(1.0f));
	programTexture.setUniformValue(programTexture.getUniformLocation("modelview"), glm::mat4(1.0f));
	programTexture.setUniformValue(programTexture.getUniformLocation("customTexCoord"), 0);
	programTexture.setUniformValue(programTexture.getUniformLocation("color"), glm::vec4(1.f));

    background->render(program);
	maxVitBar->render(program);
	vitBar->render(program);
	maxExpBar->render(program);
	expBar->render(program);
    text.render("VIT", glm::vec2(10.f, 40.f), 24, glm::vec4(1.0, 1.0, 1.0, 1.0));
	text.render("EXP", glm::vec2(10.f, 80.f), 24, glm::vec4(1.0, 1.0, 1.0, 1.0));
	for (int i = 0; i < player->getPowerups().size()-2; ++i) {
		if (player->getPowerups()[i] != 0) {
			powerupFrames->setPosition(glm::vec2(450.f + i*70.f, 17.f));
			powerupFrames->setFrame(i);
			powerupFrames->render(programTexture);
		}
	}
	if ((player->getLevel())->isTimeStopped()) {
		powerupFrames->setPosition(glm::vec2(450.f + 4 * 70.f, 17.f));
		powerupFrames->setFrame(4);
		powerupFrames->render(programTexture);
	}
	if (player->getPowerups()[5] != 0) {
		powerupFrames->setPosition(glm::vec2(450.f + 5 * 70.f, 17.f));
		powerupFrames->setFrame(5);
		powerupFrames->render(programTexture);
	}

	friendSprite->render(programTexture);
	text.render(std::to_string(player->getFriendCounter()) + "/6", glm::vec2(970.f ,68.f), 48, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	
}