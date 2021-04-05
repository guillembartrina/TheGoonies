#ifndef _PROJECTILE_INCLUDE
#define _PROJECTILE_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"

static float projectileVel = 2.f;

class Projectile : public Entity
{

	public:

	Projectile(const glm::vec2 &position, const glm::vec2& direction, Tilesheet* spritesheet, const Program& program);

	void spawn(Level* level) override;
    void update(int deltaTime) override;
	void render(const Program &program) override;

	void destroy();

	bool destroying;

	private:

	glm::vec2 direction;
	int timer;
};

#endif // _PROJECTILE_INCLUDE