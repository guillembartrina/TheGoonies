#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"
#include "Item.h"
#include "irr/irrKlang.h"

static int doorDestroying = 2000;

class Door : public Entity
{

	public:

	Door(int unlocks, ItemCode item, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);

    void update(int deltaTime) override;
	void render(const Program &program) override;

	void unlock();

	private:

	int unlocks;
	ItemCode item;
	Tilesheet* ts;
	const Program& program;
	Sprite* lock;

	static irrklang::ISoundSource* sound_unlock;
};

#endif // _ROCK_INCLUDE