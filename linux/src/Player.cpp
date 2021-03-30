#include "Player.h"
#include "Game.h"
#include "Level.h"

#include <GL/glut.h>
#include <iostream>

Player::Player(const Program& program) : Entity(EntityType::PLAYER, glm::vec2(0.f, 0.f), tileSize*glm::vec2(1.5f, 2.f))
{
	active = false;

	this->velocity = glm::vec2(0.f, 0.f);
	this->acceleration = glm::vec2(0.f, 2.f);

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
	sprite->addAnimation(new Animation({ 2 }, { 500.f })); // 1: Idle right
	sprite->addAnimation(new Animation({3,2,4,2 }, { 250.f, 250.f, 250.f, 250.f })); //2: Walk right
	sprite->addAnimation(new Animation({ 5 }, { 500.f })); // 3: Jump right
	sprite->addAnimation(new Animation({ 6, 2 }, { 200.f, 50.f })); //4: Punch right
	sprite->addAnimation(new Animation({ 7 }, { 500.f })); //5: Idle left
	sprite->addAnimation(new Animation({8, 7, 9,7 }, { 250.f, 250.f, 250.f, 250.f })); //6: Walk left
	sprite->addAnimation(new Animation({ 10 }, { 500.f })); //7: Jump left
	sprite->addAnimation(new Animation({ 11, 7 }, { 200.f, 50.f }));//8: Punch left

	sprite->setFrame(2);
	Entity::setSprite(sprite, glm::vec2(-0.25f*tileSize.x, 0.f));
	
	state = IDLE_RIGHT;
	fly = false;
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
	
	// Special modes
	if (!fly && Game::instance().getSpecialKey(GLUT_KEY_F1)) {
		fly = true;
	}
	if (fly && Game::instance().getSpecialKey(GLUT_KEY_F2)) {
		fly = false;
	}
	

	glm::vec2 newPos;
	if (fly) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			Entity::setPosition(Entity::getPosition() + glm::vec2(-flyVel, 0));
			if (level->collisionMoveLeft(Entity::getPosition(), Entity::getSize(), newPos))
			{
				Entity::setPosition(newPos);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			Entity::setPosition(Entity::getPosition() + glm::vec2(flyVel, 0));
			if (level->collisionMoveRight(Entity::getPosition(), Entity::getSize(), newPos))
			{
				Entity::setPosition(newPos);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			Entity::setPosition(Entity::getPosition() + glm::vec2(0, -flyVel));
			if (level->collisionMoveUp(Entity::getPosition(), Entity::getSize(), newPos))
			{
				Entity::setPosition(newPos);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			Entity::setPosition(Entity::getPosition() + glm::vec2(0, flyVel));
			if (level->collisionMoveDown(Entity::getPosition(), Entity::getSize(), newPos))
			{
				Entity::setPosition(newPos);
			}
		}
		return;
	}

	State newState = state;

	if (Game::instance().getKey('z')) {
		if(state != JUMP_LEFT && state != JUMP_RIGHT) velocity = glm::vec2(0.f, velocity.y);
		if (state == WALK_LEFT || state == IDLE_LEFT) {
			newState = PUNCH_LEFT;
		}
		if (state == WALK_RIGHT || state == IDLE_RIGHT) {
			newState = PUNCH_RIGHT;
		}
	} else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		velocity = glm::vec2(-2.0f, velocity.y);
		if (state != JUMP_LEFT && state != JUMP_RIGHT
			&& state != CLIMB && state != WALK_LEFT) {
			newState = WALK_LEFT;
		}
		else if (state == JUMP_RIGHT) {
			newState = JUMP_LEFT;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		velocity = glm::vec2(2.0f, velocity.y);
		if (state != JUMP_LEFT && state != CLIMB 
			&& state != JUMP_RIGHT && state != WALK_RIGHT) {
			newState = WALK_RIGHT;
		}
		else if (state == JUMP_LEFT) {
			newState = JUMP_RIGHT;
		}
	} else {
		velocity = glm::vec2(0.f, velocity.y);
		if (state == WALK_RIGHT || state == PUNCH_RIGHT) {
			newState = IDLE_RIGHT;
		}
		else if (state == WALK_LEFT || state == PUNCH_LEFT) {
			newState = IDLE_LEFT;
		}
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		if (state != JUMP_LEFT && state != JUMP_RIGHT && state != CLIMB) {
			velocity = glm::vec2(velocity.x, -4.0f);
			acceleration = glm::vec2(0.f, .2f);
		}
		if (state == WALK_LEFT || state == PUNCH_LEFT || state == IDLE_LEFT) {
			newState = JUMP_LEFT;
		}
		if (state == WALK_RIGHT || state == PUNCH_RIGHT || state == IDLE_RIGHT) {
			newState = JUMP_RIGHT;
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_HOME)) {
		level->spawn(this);
	}

	velocity = velocity + acceleration;
	if (velocity.y >= 4.f) velocity = glm::vec2(velocity.x, 3.9f);
	Entity::setPosition(position + glm::vec2(velocity.x, 0.f));
	if (velocity.x < 0 && level->collisionMoveLeft(Entity::getPosition(), Entity::getSize(), newPos)) {
		velocity = glm::vec2(0.f, velocity.y);
		Entity::setPosition(newPos);
		if (newState == WALK_LEFT) newState = IDLE_LEFT;
	} else if (velocity.x >= 0 && level->collisionMoveRight(Entity::getPosition(), Entity::getSize(), newPos)) {
		velocity = glm::vec2(0.f, velocity.y);
		Entity::setPosition(newPos);
		if (newState == WALK_RIGHT) newState = IDLE_RIGHT;
	} 
	Entity::setPosition(position + glm::vec2(0.f, velocity.y));
	if (velocity.y < 0 && level->collisionMoveUp(Entity::getPosition(), Entity::getSize(), newPos)) {
		Entity::setPosition(newPos);
		velocity = glm::vec2(velocity.x, 0.f);
	} else if (velocity.y >= 0 && level->collisionMoveDown(Entity::getPosition(), Entity::getSize(), newPos)) {
		Entity::setPosition(newPos);
		velocity = glm::vec2(velocity.x, 0.f);
		acceleration = glm::vec2(0.f, 2.f);
		if (newState == JUMP_RIGHT) newState = IDLE_RIGHT;
		if (newState == JUMP_LEFT) newState = IDLE_LEFT;
	}
	else {
		if (newState != JUMP_LEFT && newState != JUMP_RIGHT && velocity.y != 0.f) {
			if (newState == IDLE_RIGHT || newState == WALK_RIGHT || newState == PUNCH_RIGHT) newState = JUMP_RIGHT;
			if (newState == IDLE_LEFT || newState == WALK_LEFT || newState == PUNCH_LEFT) newState = JUMP_LEFT;
		}
	}

	if (newState != state) {
		state = newState;
		sprite->setAnimation(state);
	}
	
	Entity::update(deltaTime);
}

void Player::render(const Program &program)
{
	if(!active) return;
	Entity::render(program);
}

int Player::getVit() const
{
	return vit;
}

int Player::getExp() const
{
	return exp;
}




