#ifndef _MONSTER_INCLUDE
#define _MONSTER_INCLUDE

#include "Entity.h"
#include "Tilesheet.h"
#include "irr/irrKlang.h"

class Monster : public Entity
{

	public:

	Monster(const glm::vec2 &position, const glm::vec2 &size);
	
	virtual void kill() = 0;

	protected:

	static irrklang::ISoundSource* sound_kill;

};


#endif // _MONSTER_INCLUDE


