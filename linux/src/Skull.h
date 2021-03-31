#ifndef _SKULL_INCLUDE
#define _SKULL_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"

class Skull : public Entity
{

	public:

	Skull(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);
	~Skull();
	void spawn(Level *level) override;
	void update(int deltaTime) override;
	void render(const Program &program) override;
	
	private:

	bool active;
	bool jump;
	bool direction;

	bool jumping;
	float vel;
	glm::ivec2 room;

	float floor;
	float left, right;
};


#endif // _PLAYER_INCLUDE


