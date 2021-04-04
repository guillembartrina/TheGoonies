#include "Player.h"
#include "Game.h"
#include "Level.h"
#include "Sensor.h"
#include "Door.h"

#include <GL/glut.h>
#include <iostream>
#include <list>

Player::Player(const Program& program) : Entity(EntityType::PLAYER, glm::vec2(0.f, 0.f), tileSize*glm::vec2(1.5f, 2.f))
{
	active = false;
	change = -1;
	dead = false;
	won = false;

	this->velocity = glm::vec2(0.f, 0.f);
	this->acceleration = glm::vec2(0.f, 0.2f);
	this->vit = 50;
	this->exp = 0;
	this->hurtTimer = -1;
	this->hasKey = false;
	this->friendCounter = 0;
	powerups = std::vector<int>(POW_HYPERSHOES - BAG, 0);

	texture = Texture::createTexture("images/player.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
	Sprite* sprite = new Sprite(glm::vec2(0.f), tileSize*2.f, texture, program);

	for(int i = 0; i < 2; i++) sprite->addFrame(new Frame(i*0.25f, 0.f, 0.25f, 0.125f)); //0, 1
	for(int i = 0; i < 3; i++) sprite->addFrame(new Frame(i*0.25f, 1.f*0.125f, 0.25f, 0.125f)); //2, 3, 4
	sprite->addFrame(new Frame(0.f, 2.f*0.125f, 0.25f, 0.125f)); //5
	sprite->addFrame(new Frame(0.f, 3.f*0.125f, 0.25f, 0.125f)); //6
	for(int i = 0; i < 3; i++) sprite->addFrame(new Frame(i*0.25f, 4.f*0.125f, 0.25f, 0.125f)); //7,8,9
	sprite->addFrame(new Frame(0.f, 5.f*0.125f, 0.25f, 0.125f)); //10
	sprite->addFrame(new Frame(0.f, 6.f*0.125f, 0.25f, 0.125f)); //11

	sprite->addAnimation(new Animation({0,1}, {250.f, 250.f}));//0: Climbing
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

	sound_jump = Game::instance().getEngine()->addSoundSourceFromFile("sounds/jump.wav");
	sound_jump->setDefaultVolume(0.2f);
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

	if (Game::instance().getSpecialKey(GLUT_KEY_HOME)) {
		level->spawnPlayer(this, -1);
	}

	if (hurtTimer >= 0) {
		hurtTimer -= deltaTime;
		if(hurtSubtimer >= 0)
		{
			hurtSubtimer -= deltaTime;
			if(hurtSubtimer < 0)
			{
				hurtSubtimer = -200;
				sprite->setReverseColor(false);
			}
		}
		else
		{
			hurtSubtimer += deltaTime;
			if(hurtSubtimer > 0)
			{
				hurtSubtimer = 200;
				sprite->setReverseColor(true);
			}
		}
		if (hurtTimer < 0) sprite->setReverseColor(false);
	}
	touchingVine = false;
	updateEntityCollisions();
	updateMovement();

	Entity::update(deltaTime);
}

void Player::updateMovement() {
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

	if (state == CLIMB) {
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			Entity::setPosition(Entity::getPosition() + glm::vec2(0, 1.f));
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			Entity::setPosition(Entity::getPosition() + glm::vec2(0, -1.f));
		}
		if (touchingVine) {
			if (climbableVine->getType() == VINE_TOP) {
				Entity::setPosition(climbableVine->getPosition()+glm::vec2(0.f, -16.f));
			}
			else {
				Entity::setPosition(climbableVine->getPosition() + glm::vec2(0.f, -16.f));
			}
			state = IDLE_RIGHT;
			sprite->setAnimation(state);
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
		if (touchingVine && climbableVine->getType() == VINE_BOTTOM) {
			state = CLIMB;
			setPosition(climbableVine->getPosition() + glm::vec2(-2.0f, -32.0f));
			sprite->setAnimation(state);
			return;
		}
		else {
			if (state != JUMP_LEFT && state != JUMP_RIGHT && state != CLIMB) {
				velocity = glm::vec2(velocity.x, -4.0f);
				Game::instance().getEngine()->play2D(sound_jump);
			}
			if (state == WALK_LEFT || state == PUNCH_LEFT || state == IDLE_LEFT) {
				newState = JUMP_LEFT;
			}
			if (state == WALK_RIGHT || state == PUNCH_RIGHT || state == IDLE_RIGHT) {
				newState = JUMP_RIGHT;
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		if (touchingVine && climbableVine->getType() == VINE_TOP) {
			state = CLIMB;
			setPosition(climbableVine->getPosition() + glm::vec2(-2.0f, 16.0f));
			sprite->setAnimation(state);
			return;
		}
	}

	glm::vec2 oldPos = Entity::getPosition();

	velocity = velocity + acceleration;
	//if (velocity.y >= 4.f) velocity = glm::vec2(velocity.x, 3.9f);

	float futureY = oldPos.y + velocity.y;

	if(velocity.y != 0.f)
	{
		if(velocity.y < 0.f && level->collisionMoveUp(glm::vec2(oldPos.x, futureY), Entity::getSize(), newPos))
		{
			futureY = newPos.y;
			velocity = glm::vec2(velocity.x, 0.f);
		}
		else if (velocity.y > 0 && level->collisionMoveDown(glm::vec2(oldPos.x, futureY), Entity::getSize(), newPos))
		{
			futureY = newPos.y;
			velocity = glm::vec2(velocity.x, 0.f);
			if(state == JUMP_RIGHT) newState = (velocity.x > 0.f ? WALK_RIGHT : IDLE_RIGHT);
			if(state == JUMP_LEFT) newState = (velocity.x < 0.f ? WALK_LEFT : IDLE_LEFT);
		}
	}

	if(futureY > oldPos.y && state != JUMP_LEFT && state != JUMP_RIGHT)
	{
		if (state == IDLE_RIGHT || state == WALK_RIGHT || state == PUNCH_RIGHT) newState = JUMP_RIGHT;
		if (state == IDLE_LEFT || state == WALK_LEFT || state == PUNCH_LEFT) newState = JUMP_LEFT;
	} 

	float futureX = oldPos.x + velocity.x;

	if(velocity.x != 0.f)
	{
		if (velocity.x < 0.f && level->collisionMoveLeft(glm::vec2(futureX, oldPos.y), Entity::getSize(), newPos)) {
			futureX = newPos.x;
			velocity = glm::vec2(0.f, velocity.y);
			if (newState == WALK_LEFT) newState = IDLE_LEFT;
		}
		else if (velocity.x > 0.f && level->collisionMoveRight(glm::vec2(futureX, oldPos.y), Entity::getSize(), newPos)) {
			futureX = newPos.x;
			velocity = glm::vec2(0.f, velocity.y);
			if (newState == WALK_RIGHT) newState = IDLE_RIGHT;
		}
	}

	Entity::setPosition(glm::vec2(futureX, futureY));	

	if (newState != state) {
		state = newState;
		sprite->setAnimation(state);
	}
}

void Player::updateEntityCollisions() {
	std::list<Entity *> entities = level->getEntities();
	for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if (areColliding(this, *it)) {
			if ((*it)->getType() == OBSTACLE) {
				getHurt(5);
			} else if ((*it)->getType() == ITEM) {
				handleEntityCollisionItem(*it);
			} else if ((*it)->getType() == DOOR) {
				Door *door = (Door *)*it;
				if (hasKey) {
					door->unlock();
					hasKey = false;
				}
			} else if ((*it)->getType() == MONSTER) {
				getHurt(10);
			}
			else if ((*it)->getType() == SENSOR)
			{
				Sensor *sensor = (Sensor *)*it;
				if (sensor->getType() == VINE_TOP || sensor->getType() == VINE_BOTTOM) {
					touchingVine = true;
					climbableVine = sensor;
				}
			}
		}
	}
}

void Player::handleEntityCollisionItem(Entity *it) {
	Item *item = (Item *)it;
	if (item->getCode() == KEY) {
		if (!hasKey) {
			item->setDestroy();
			hasKey = true;
		}
	} else if (item->getCode() == POTION) {
		vit = (vit + 20) > 50 ? 50 : vit + 20;
		item->setDestroy();
	} else if (item->getCode() >= POW_YELLOWHELMET && item->getCode() <= POW_HYPERSHOES) {
		int powerUpCode = item->getCode() - POW_YELLOWHELMET;
		if (powerups[powerUpCode] == 0) {
			item->setDestroy();
			powerups[powerUpCode] = item->getCode() == POW_HYPERSHOES ? -1 : 2;
		}
	} else if (item->getCode() == FRIEND) {
		item->setDestroy();
		++friendCounter;
	}
}

void Player::getHurt(int damage) {
	if (hurtTimer < 0) {
		vit -= damage;
		hurtTimer = 1000;
		hurtSubtimer = 200;
		sprite->setReverseColor(true);
		if(vit <= 0) dead = true;
	}
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

std::vector<int> Player::getPowerups() const {
	return powerups;
}

int Player::getFriendCounter() const {
	return friendCounter;
}

int Player::changeLevel()
{
	return change;
}

bool Player::isDead() const
{
	return dead;
}

bool Player::hasWon() const
{
	return won;
}




