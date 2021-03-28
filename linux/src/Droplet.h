#ifndef _DROPLET_INCLUDE
#define _DROPLET_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"

static float dropletVel = 2.f;
static float dropletWaiting = 600;
static float dropletLoading = 800;
static float dropletCrashing = 300;

enum DropletState {DROPLET_WAITING, DROPLET_LOADING, DROPLET_FALLING, DROPLET_CRASHING};

class Droplet : public Entity
{

	public:

	Droplet(const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);

	void spawn(Level* level) override;
    void update(int deltaTime) override;
	void render(const Program &program) override;

	private:

	glm::vec2 ini;
	float end;
	DropletState state;
	int timer;
};

#endif // _DROPLET_INCLUDE