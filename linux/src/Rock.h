#ifndef _ROCK_INCLUDE
#define _ROCK_INCLUDE

#include "Entity.h"
#include "Sensor.h"
#include "Tilesheet.h"

static float rockVel = 2.f;
static int rockCrashing = 250;

enum RockState { ROCK_READY, ROCK_FALLING, ROCK_CRASHING, ROCK_DEAD };

class Rock : public Entity
{

	public:

	Rock(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);

	void spawn(Level* level) override;
    void update(int deltaTime) override;
	void render(const Program &program) override;

	private:

	float end;
	RockState state;
	Sensor* sensor;
	int timer;
};

#endif // _ROCK_INCLUDE