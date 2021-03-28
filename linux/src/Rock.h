#ifndef _ROCK_INCLUDE
#define _ROCK_INCLUDE

#include "Entity.h"
#include "Sensor.h"
#include "Tilesheet.h"

static float rockVel = 2.f;

enum RockState { READY, FALLING, CRASHING, DEAD };

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
};

#endif // _ROCK_INCLUDE