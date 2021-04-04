#ifndef _SKELETON_INCLUDE
#define _SKELETON_INCLUDE

#include "Monster.h"
#include "Tilesheet.h"
#include "Sensor.h"

class Skeleton : public Monster
{

	public:

	Skeleton(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);
	~Skeleton();
	void spawn(Level *level) override;
	void update(int deltaTime) override;
	void render(const Program &program) override;
	void kill() override;
	
	private:

	bool active;
	bool direction;

	bool jumping;
	float vel;
	glm::ivec2 room;

	float floor;
	float left, right;

	Sensor* sensor;

	Tilesheet* ts;
	const Program& program;

	int timer;
	int destroying;
};


#endif // _PLAYER_INCLUDE


