#include "Player.h"
#include "Game.h"
#include "Level.h"

#include <GL/glut.h>
#include <iostream>

Player::Player(const Program& program) : Entity(EntityType::PLAYER, glm::vec2(0.f, 0.f), tileSize*glm::vec2(1.5f, 2.f))
{
	active = false;

	texture = Texture::createTexture("images/player.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* sprite = new Sprite(glm::vec2(0.f), tileSize*2.f, texture, program);

	for(int i = 0; i < 2; i++) sprite->addFrame(new Frame(i*0.25f, 0.f, 0.25f, 0.125f)); //0, 1
	for(int i = 0; i < 3; i++) sprite->addFrame(new Frame(i*0.25f, 1.f*0.125f, 0.25f, 0.125f)); //2, 3, 4
	sprite->addFrame(new Frame(0.f, 2.f*0.125f, 0.25f, 0.125f)); //5
	sprite->addFrame(new Frame(0.f, 3.f*0.125f, 0.25f, 0.125f)); //6
	for(int i = 0; i < 3; i++) sprite->addFrame(new Frame(i*0.25f, 4.f*0.125f, 0.25f, 0.125f)); //7,8,9
	sprite->addFrame(new Frame(0.f, 5.f*0.125f, 0.25f, 0.125f)); //10
	sprite->addFrame(new Frame(0.f, 6.f*0.125f, 0.25f, 0.125f)); //11

	sprite->addAnimation(new Animation({0,1}, {500.f, 500.f}));//0: Climbing
	sprite->addAnimation(new Animation({ 2,3,2,4 }, { 250.f, 250.f, 250.f, 250.f })); //1: Walk right
	sprite->addAnimation(new Animation({ 6, 2 }, { 200.f, 50.f })); //2: Punch right
	sprite->addAnimation(new Animation({ 7, 8, 7, 9 }, { 250.f, 250.f, 250.f, 250.f })); //3: Walk left
	sprite->addAnimation(new Animation({ 11, 7 }, { 200.f, 50.f }));//4: Punch left

	sprite->setFrame(2);

	Entity::setSprite(sprite, glm::vec2(-0.25f*tileSize.x, 0.f));
}

Player::~Player()
{
	delete texture;
}

void Player::spawn(Level *level)
{
	Entity::spawn(level);
	active = true;
}

void Player::update(int deltaTime)
{
	if(!active) return;

	glm::vec2 newPos;
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		/*if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);*/
		Entity::setPosition(Entity::getPosition() + glm::vec2(-2, 0));
		if(level->collisionMoveLeft(Entity::getPosition(), Entity::getSize(), newPos))
		{
			Entity::setPosition(newPos);
			//sprite->changeAnimation(STAND_LEFT);
		}
	}

	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		/*if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);*/
		Entity::setPosition(Entity::getPosition() + glm::vec2(2, 0));
		if(level->collisionMoveRight(Entity::getPosition(), Entity::getSize(), newPos))
		{
			Entity::setPosition(newPos);
			//sprite->changeAnimation(STAND_RIGHT);
		}
	}

	else if(Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		/*if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);*/
		Entity::setPosition(Entity::getPosition() + glm::vec2(0, -2));
		if(level->collisionMoveUp(Entity::getPosition(), Entity::getSize(), newPos))
		{
			Entity::setPosition(newPos);
			//sprite->changeAnimation(STAND_RIGHT);
		}
	}

	else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		/*if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);*/
		Entity::setPosition(Entity::getPosition() + glm::vec2(0, 2));
		if(level->collisionMoveDown(Entity::getPosition(), Entity::getSize(), newPos))
		{
			Entity::setPosition(newPos);
			//sprite->changeAnimation(STAND_RIGHT);
		}
	}
	/*else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}*/
	
	/*if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}*/
	Entity::update(deltaTime);
}

void Player::render(const Program &program)
{
	if(!active) return;
	Entity::render(program);
}




