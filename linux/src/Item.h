#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"

enum ItemCode { KEY, POTION, BAG, POW_YELLOWHELMET, POW_GRAYRAINCOAT, POW_GREYSPELLBOOK, POW_YELLOWSPELLBOOK, POW_TIMESTOPPER, POW_HYPERSHOES };

class Item : public Entity
{

	public:

	Item(ItemCode code, const glm::vec2 &position, Tilesheet* spritesheet, const Program& program);

    void update(int deltaTime) override;
	void render(const Program &program) override;

	private:

	ItemCode code;
};

#endif // _ROCK_INCLUDE