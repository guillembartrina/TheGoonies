#ifndef _LEAKAGE_INCLUDE
#define _LEAKAGE_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"

static int leakageWaiting = 2000;
static int leakageLoading = 800;
static int leakageActive = 1200;

enum LeakageState {LEAKAGE_WAITING, LEAKAGE_LOADING, LEAKAGE_ACTIVE};

class Leakage : public Entity
{

	public:

	Leakage(bool left, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);
	~Leakage();

	void spawn(Level* level) override;
    void update(int deltaTime) override;
	void render(const Program &program) override;

	private:

	Sprite* full, *ini;

	bool left;
	LeakageState state;
	int timer;
};

#endif // _DROPLET_INCLUDE