#include "Player.h"
#include "Game.h"
#include "Level.h"

#include <GL/glut.h>
#include <iostream>

Player::Player(const Program& program) : Entity(EntityType::PLAYER, glm::vec2(0.f, 0.f), tileSize*2.f, Texture::createTexture("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA), program)
{
	active = false;

	for(int i = 0; i < 2; i++) sprite->addFrame(new Frame(i*0.25f, 0.f, 0.25f, 0.125f)); //0, 1
	for(int i = 0; i < 3; i++) sprite->addFrame(new Frame(i*0.25f, 1.f*0.125f, 0.25f, 0.125f)); //2, 3, 4
	sprite->addFrame(new Frame(0.f, 2.f*0.125f, 0.25f, 0.125f)); //5
	sprite->addFrame(new Frame(0.f, 3.f*0.125f, 0.25f, 0.125f)); //6
	for(int i = 0; i < 3; i++) sprite->addFrame(new Frame(i*0.25f, 4.f*0.125f, 0.25f, 0.125f)); //7,8,9
	sprite->addFrame(new Frame(0.f, 5.f*0.125f, 0.25f, 0.125f)); //10
	sprite->addFrame(new Frame(0.f, 6.f*0.125f, 0.25f, 0.125f)); //11

	sprite->setFrame(3);
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
		if(level->collisionMoveLeft(this, newPos))
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
		if(level->collisionMoveRight(this, newPos))
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
		if(level->collisionMoveUp(this, newPos))
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
		if(level->collisionMoveDown(this, newPos))
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




