#ifndef _ROCK_INCLUDE
#define _ROCK_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"

class Rock : public Entity
{

	public:

	Rock(const glm::vec2 &pos, Tilesheet* spritesheet, const Program& program);

    void update(int deltaTime);
	void render(const Program &program);

	protected:

};

#endif // _ROCK_INCLUDE